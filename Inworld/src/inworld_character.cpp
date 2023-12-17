/**
 * Copyright 2023 Theai, Inc. (DBA Inworld)
 *
 * Use of this source code is governed by the Inworld.ai Software Development Kit License Agreement
 * that can be found in the LICENSE.md file or at https://www.inworld.ai/sdk-license
 */

#include "inworld_character.h"

#include "inworld_event.h"
#include "inworld_message.h"
#include "inworld_session.h"
#include "inworld_talk_queue.h"

#include "Utils/Utils.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void InworldCharacter::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_brain", "brain"), &InworldCharacter::set_brain);
	ClassDB::bind_method(D_METHOD("get_brain"), &InworldCharacter::get_brain);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "brain"), "set_brain", "get_brain");

	ClassDB::bind_method(D_METHOD("get_given_name"), &InworldCharacter::get_given_name);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "given_name"), "", "get_given_name");

	ClassDB::bind_method(D_METHOD("set_session", "session"), &InworldCharacter::set_session);
	ClassDB::bind_method(D_METHOD("get_session"), &InworldCharacter::get_session);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "session", PROPERTY_HINT_NODE_TYPE, "InworldSession"), "set_session", "get_session");

	ClassDB::bind_method(D_METHOD("on_session_established", "established"), &InworldCharacter::on_session_established);
	ClassDB::bind_method(D_METHOD("on_session_connected", "connected"), &InworldCharacter::on_session_connected);

	ClassDB::bind_method(D_METHOD("send_text", "text"), &InworldCharacter::send_text);
	ClassDB::bind_method(D_METHOD("send_trigger", "text", "params"), &InworldCharacter::send_trigger);
	ClassDB::bind_method(D_METHOD("start_audio_session"), &InworldCharacter::start_audio_session);
	ClassDB::bind_method(D_METHOD("stop_audio_session"), &InworldCharacter::stop_audio_session);
	ClassDB::bind_method(D_METHOD("send_audio", "data"), &InworldCharacter::send_audio);

	ClassDB::bind_method(D_METHOD("interrupt"), &InworldCharacter::interrupt);

	ClassDB::bind_method(D_METHOD("on_event_text", "text"), &InworldCharacter::on_event_text);
	ClassDB::bind_method(D_METHOD("on_event_audio", "audio"), &InworldCharacter::on_event_audio);
	ClassDB::bind_method(D_METHOD("on_event_emotion", "emotion"), &InworldCharacter::on_event_emotion);
	ClassDB::bind_method(D_METHOD("on_event_trigger", "trigger"), &InworldCharacter::on_event_trigger);
	ClassDB::bind_method(D_METHOD("on_event_control", "control"), &InworldCharacter::on_event_control);

	ClassDB::bind_method(D_METHOD("finish_current_message_talk"), &InworldCharacter::finish_current_message_talk);
	ClassDB::bind_method(D_METHOD("on_talk_queue_next_ready"), &InworldCharacter::on_talk_queue_next_ready);

	ADD_SIGNAL(MethodInfo("message_talk", PropertyInfo(Variant::OBJECT, "talk")));
	ADD_SIGNAL(MethodInfo("message_stt", PropertyInfo(Variant::OBJECT, "stt")));
	ADD_SIGNAL(MethodInfo("message_emotion", PropertyInfo(Variant::OBJECT, "emotion")));
	ADD_SIGNAL(MethodInfo("message_trigger", PropertyInfo(Variant::OBJECT, "trigger")));
	ADD_SIGNAL(MethodInfo("message_control", PropertyInfo(Variant::OBJECT, "control")));

	ADD_SIGNAL(MethodInfo("conversing_start", PropertyInfo(Variant::OBJECT, "player")));
	ADD_SIGNAL(MethodInfo("conversing_end", PropertyInfo(Variant::OBJECT, "player")));

	ADD_SIGNAL(MethodInfo("interrupted"));

	BIND_ENUM_CONSTANT(AFFECTION);
	BIND_ENUM_CONSTANT(ANGER);
	BIND_ENUM_CONSTANT(BELLIGERENCE);
	BIND_ENUM_CONSTANT(CONTEMPT);
	BIND_ENUM_CONSTANT(CRITICISM);
	BIND_ENUM_CONSTANT(DEFENSIVENESS);
	BIND_ENUM_CONSTANT(DISGUST);
	BIND_ENUM_CONSTANT(DOMINEERING);
	BIND_ENUM_CONSTANT(HUMOR);
	BIND_ENUM_CONSTANT(INTEREST);
	BIND_ENUM_CONSTANT(JOY);
	BIND_ENUM_CONSTANT(NEUTRAL);
	BIND_ENUM_CONSTANT(SADNESS);
	BIND_ENUM_CONSTANT(STONEWALLING);
	BIND_ENUM_CONSTANT(SURPRISE);
	BIND_ENUM_CONSTANT(TENSE);
	BIND_ENUM_CONSTANT(TENSION);
	BIND_ENUM_CONSTANT(VALIDATION);
	BIND_ENUM_CONSTANT(WHINING);
	
	BIND_ENUM_CONSTANT(WEAK);
	BIND_ENUM_CONSTANT(NORMAL);
	BIND_ENUM_CONSTANT(STRONG);
}

InworldCharacter::InworldCharacter() :
		Node{}, brain{}, session{ nullptr }, pending_interaction_ids{}, canceled_interaction_ids{}, current_voice_interaction_id{}, talk_queue{ nullptr }, wants_audio_session{ false } {
	talk_queue = memnew(InworldTalkQueue);
	talk_queue->connect("next_ready", Callable(this, "on_talk_queue_next_ready"));
}

InworldCharacter::~InworldCharacter() {
	if (talk_queue != nullptr) {
		memdelete(talk_queue);
		talk_queue = nullptr;
	}
}

void InworldCharacter::set_brain(String p_brain) {
	unbind_brain_from_session();
	brain = p_brain;
	bind_brain_to_session();
}

String InworldCharacter::get_brain() const {
	return brain;
}

String InworldCharacter::get_given_name() const {
	if (session == nullptr || !session->get_established()) {
		return {};
	}
	return session->get_given_name(brain);
}

void InworldCharacter::set_session(InworldSession *p_session) {
	unbind_brain_from_session();
	session = p_session;
	bind_brain_to_session();
}

InworldSession *InworldCharacter::get_session() const {
	return session;
}

void InworldCharacter::send_text(String p_text) {
	if (session == nullptr || !session->get_established()) {
		return;
	}
	interrupt();
	session->send_text(brain, p_text);
}

void InworldCharacter::send_trigger(String p_name, Dictionary p_params) {
	if (session == nullptr || !session->get_established()) {
		return;
	}
	interrupt();
	session->send_trigger(brain, p_name, p_params);
}

void InworldCharacter::start_audio_session() {
	wants_audio_session = true;
	if (session == nullptr || !session->get_established()) {
		return;
	}
	session->start_audio_session(brain);
}

void InworldCharacter::stop_audio_session() {
	wants_audio_session = false;
	if (session == nullptr || !session->get_established()) {
		return;
	}
	session->stop_audio_session(brain);
}

void InworldCharacter::send_audio(PackedByteArray p_data) {
	if (session == nullptr || !session->get_established()) {
		return;
	}
	session->send_audio(brain, p_data);
}

void InworldCharacter::interrupt() {
	Vector<String> pending_interaction_ids_copy = pending_interaction_ids;
	for (const String &pending_interaction_id : pending_interaction_ids_copy) {
		if (pending_interaction_id == current_voice_interaction_id) {
			break;
		} else {
			pending_interaction_ids.erase(pending_interaction_id);
			canceled_interaction_ids.push_back(pending_interaction_id);
		}
	}

	Vector<Ref<InworldMessageTalk>> talks_to_interrupt = talk_queue->get_talks();
	if (!talks_to_interrupt.is_empty()) {
		Ref<InworldMessageTalk> message_talk = talks_to_interrupt[0];
		String interaction_id = message_talk->get_interaction_id();
		Vector<String> utterance_ids;
		for (const Ref<InworldMessageTalk> &talk_to_interrupt : talks_to_interrupt) {
			if (interaction_id != talk_to_interrupt->get_interaction_id()) {
				session->cancel_response(brain, interaction_id, utterance_ids);
				interaction_id = talk_to_interrupt->get_interaction_id();
			}
			utterance_ids.push_back(interaction_id);
		}
		session->cancel_response(brain, interaction_id, utterance_ids);
		talk_queue->clear();
		emit_signal("interrupted");
	}
}

void InworldCharacter::_on_event(InworldEvent *p_event) {
	const String interaction_id = p_event->get_interaction_id();
	if (!canceled_interaction_ids.has(interaction_id) && !pending_interaction_ids.has(interaction_id)) {
		pending_interaction_ids.push_back(interaction_id);
	}
}

bool InworldCharacter::_is_event_canceled(InworldEvent *p_event) {
	const String interaction_id = p_event->get_interaction_id();
	return canceled_interaction_ids.has(interaction_id);
}

void InworldCharacter::on_event_text(Ref<InworldEventText> p_event_text) {
	_on_event(p_event_text.ptr());
	if (_is_event_canceled(p_event_text.ptr())) {
		return;
	}

	if (p_event_text->get_source_actor_type() == StringName("Agent")) {
		talk_queue->update_text(p_event_text->get_interaction_id(), p_event_text->get_utterance_id(), p_event_text->text);
	} else {
		current_voice_interaction_id = p_event_text->get_interaction_id();
		interrupt();
		if (p_event_text->complete) {
			current_voice_interaction_id = String{};
		}

		Ref<InworldMessageSpeechToText> message_stt;
		message_stt.instantiate();

		message_stt->text = p_event_text->text;
		message_stt->complete = p_event_text->complete;
		emit_signal("message_stt", message_stt);
	}
}

void InworldCharacter::on_event_audio(Ref<InworldEventDataAudio> p_event_audio) {
	_on_event(p_event_audio.ptr());
	if (_is_event_canceled(p_event_audio.ptr())) {
		return;
	}

	TypedArray<InworldMessageTalk::Viseme> visemes;
	for(uint32_t i = 0; i < p_event_audio->phonemes.size(); ++i) {
		InworldEventDataAudio::Phoneme *phoneme = Object::cast_to<InworldEventDataAudio::Phoneme>(&*p_event_audio->phonemes[i]);
		const String viseme_from_phoneme = String(Inworld::Utils::PhonemeToViseme(String(phoneme->code).utf8().get_data()).c_str());
		if(!viseme_from_phoneme.is_empty()) {
			InworldMessageTalk::Viseme *viseme = memnew(InworldMessageTalk::Viseme);
			viseme->code = StringName(viseme_from_phoneme);
			viseme->time_stamp = phoneme->time_stamp;
			visemes.push_back(Variant(viseme));
		}
	}

	talk_queue->update_audio(p_event_audio->get_interaction_id(), p_event_audio->get_utterance_id(), p_event_audio->chunk, visemes);
}

void InworldCharacter::on_event_emotion(Ref<InworldEventEmotion> p_event_emotion) {
	_on_event(p_event_emotion.ptr());

	Ref<InworldMessageEmotion> message_emotion;
	message_emotion.instantiate();
	message_emotion->interaction_id = p_event_emotion->get_interaction_id();
	message_emotion->utterance_id = p_event_emotion->get_utterance_id();

	message_emotion->behavior = p_event_emotion->behavior;
	message_emotion->strength = p_event_emotion->strength;

	emit_signal("message_emotion", message_emotion);
}

void InworldCharacter::on_event_trigger(Ref<InworldEventTrigger> p_event_trigger) {
	_on_event(p_event_trigger.ptr());

	Ref<InworldMessageTrigger> message_trigger;
	message_trigger.instantiate();
	message_trigger->interaction_id = p_event_trigger->get_interaction_id();
	message_trigger->utterance_id = p_event_trigger->get_utterance_id();

	message_trigger->name = p_event_trigger->name;
	message_trigger->params = p_event_trigger->params;

	emit_signal("message_trigger", message_trigger);
}

void InworldCharacter::on_event_control(Ref<InworldEventControl> p_event_control) {
	_on_event(p_event_control.ptr());

	if (p_event_control->type == String("InteractionEnd")) {
		pending_interaction_ids.erase(p_event_control->get_interaction_id());
		canceled_interaction_ids.erase(p_event_control->get_interaction_id());
	}

	Ref<InworldMessageControl> message_control;
	message_control.instantiate();
	message_control->interaction_id = p_event_control->get_interaction_id();
	message_control->utterance_id = p_event_control->get_utterance_id();

	message_control->type = p_event_control->type;

	emit_signal("message_control", message_control);
}

void InworldCharacter::finish_current_message_talk() {
	talk_queue->finish_current();
}

void InworldCharacter::on_talk_queue_next_ready(Ref<InworldMessageTalk> p_message_talk) {
	emit_signal("message_talk", p_message_talk);
}

void InworldCharacter::bind_brain_to_session() {
	if (session == nullptr) {
		return;
	}
	session->connect("established", Callable(this, "on_session_established"));
	on_session_established(session->get_established());

	session->connect("connected", Callable(this, "on_session_connected"));
	on_session_connected(session->get_connected());
}

void InworldCharacter::unbind_brain_from_session() {
	if (session == nullptr) {
		return;
	}
	session->disconnect("established", Callable(this, "on_session_established"));
	on_session_established(false);

	session->disconnect("connected", Callable(this, "on_session_connected"));
	on_session_connected(false);
}

void InworldCharacter::on_session_established(bool p_established) {
#define CONNECT_EVENT(Type) \
	session->connect_##Type##_events(brain, Callable(this, String("on_event_") + String(#Type)));

#define DISCONNECT_EVENT(Type) \
	session->disconnect_##Type##_events(brain, Callable(this, String("on_event") + String(#Type)));

	if (p_established) {
		CONNECT_EVENT(text)
		CONNECT_EVENT(audio)
		CONNECT_EVENT(emotion)
		CONNECT_EVENT(trigger)
		CONNECT_EVENT(control)
	} else {
		DISCONNECT_EVENT(text)
		DISCONNECT_EVENT(audio)
		DISCONNECT_EVENT(emotion)
		DISCONNECT_EVENT(trigger)
		DISCONNECT_EVENT(control)
	}

#undef CONNECT_EVENT
#undef DISCONNECT_EVENT

	if (wants_audio_session) {
		p_established ? session->start_audio_session(brain) : session->stop_audio_session(brain);
	}
}

void InworldCharacter::on_session_connected(bool p_connected) {
}
