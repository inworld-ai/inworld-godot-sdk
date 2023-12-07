#include "inworld_character.h"

#include "inworld_event.h"
#include "inworld_message.h"
#include "inworld_session.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void InworldCharacter::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_brain", "brain"), &InworldCharacter::set_brain);
	ClassDB::bind_method(D_METHOD("get_brain"), &InworldCharacter::get_brain);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "brain"), "set_brain", "get_brain");

	ClassDB::bind_method(D_METHOD("get_name"), &InworldCharacter::get_name);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "name"), "", "get_name");

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

	ClassDB::bind_method(D_METHOD("get_talk_queue"), &InworldCharacter::get_talk_queue);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "talk_queue"), "", "get_talk_queue");

	ClassDB::bind_method(D_METHOD("on_talk_queue_next_ready"), &InworldCharacter::on_talk_queue_next_ready);
	ClassDB::bind_method(D_METHOD("on_talk_queue_next_popped"), &InworldCharacter::on_talk_queue_next_popped);

	ADD_SIGNAL(MethodInfo("message_talk", PropertyInfo(Variant::OBJECT, "talk")));
	ADD_SIGNAL(MethodInfo("message_stt", PropertyInfo(Variant::OBJECT, "stt")));
	ADD_SIGNAL(MethodInfo("message_emotion", PropertyInfo(Variant::OBJECT, "emotion")));
	ADD_SIGNAL(MethodInfo("message_trigger", PropertyInfo(Variant::OBJECT, "trigger")));
	ADD_SIGNAL(MethodInfo("message_control", PropertyInfo(Variant::OBJECT, "control")));

	ADD_SIGNAL(MethodInfo("talk_queue_next_ready", PropertyInfo(Variant::OBJECT, "talk_queue")));

	ADD_SIGNAL(MethodInfo("interrupted"));
}

InworldCharacter::InworldCharacter() :
		Node{}, brain{}, session{ nullptr }, talk_queue{ nullptr }, wants_audio_session{ false } {
	talk_queue = memnew(InworldTalkQueue);
	talk_queue->connect("next_ready", Callable(this, "on_talk_queue_next_ready"));
	talk_queue->connect("next_popped", Callable(this, "on_talk_queue_next_popped"));
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

String InworldCharacter::get_name() const {
	if (session == nullptr || !session->get_connected()) {
		return {};
	}
	return session->get_name(brain);
}

void InworldCharacter::set_session(InworldSession *p_session) {
	unbind_brain_from_session();
	session = p_session;
	bind_brain_to_session();
}

InworldSession *InworldCharacter::get_session() const {
	return session;
}

InworldTalkQueue *InworldCharacter::get_talk_queue() const {
	return talk_queue;
}

void InworldCharacter::send_text(String p_text) {
	if (session == nullptr || !session->get_connected()) {
		return;
	}
	interrupt();
	session->send_text(brain, p_text);
}

void InworldCharacter::send_trigger(String p_name, Dictionary p_params) {
	if (session == nullptr || !session->get_connected()) {
		return;
	}
	session->send_trigger(brain, p_name, p_params);
}

void InworldCharacter::start_audio_session() {
	wants_audio_session = true;
	if (session == nullptr || !session->get_connected()) {
		return;
	}
	session->start_audio_session(brain);
}

void InworldCharacter::stop_audio_session() {
	wants_audio_session = false;
	if (session == nullptr || !session->get_connected()) {
		return;
	}
	session->stop_audio_session(brain);
}

void InworldCharacter::send_audio(PackedByteArray p_data) {
	if (session == nullptr || !session->get_connected()) {
		return;
	}
	session->send_audio(brain, p_data);
}

void InworldCharacter::interrupt() {
	canceled_interaction_ids.append_array(pending_interaction_ids);
	pending_interaction_ids.clear();

	Vector<String> pending_interaction_ids_copy = pending_interaction_ids;
	bool interrupted = false;
	for (const String &pending_interaction_id : pending_interaction_ids_copy) {
		interrupt_interaction(pending_interaction_id);
		interrupted = true;
	}
	if (interrupted) {
		emit_signal("interrupted");
	}
}

void InworldCharacter::interrupt_interaction(String p_interaction_id) {
	Vector<String> utterance_ids = talk_queue->interrupt_interaction(p_interaction_id);
	session->cancel_response(brain, p_interaction_id, utterance_ids);
	pending_interaction_ids.erase(p_interaction_id);
	canceled_interaction_ids.push_back(p_interaction_id);
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
		talk_queue->update_text(p_event_text->get_utterance_id(), p_event_text->text);
	} else {
		const String interaction_id = p_event_text->get_interaction_id();
		interrupt();
		canceled_interaction_ids.erase(interaction_id);
		pending_interaction_ids = { interaction_id };

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

	talk_queue->update_chunk(p_event_audio->get_utterance_id(), p_event_audio->chunk);
}

void InworldCharacter::on_event_emotion(Ref<InworldEventEmotion> p_event_emotion) {
	_on_event(p_event_emotion.ptr());

	Ref<InworldMessageEmotion> message_emotion;
	message_emotion.instantiate();

	message_emotion->behavior = p_event_emotion->behavior;
	message_emotion->strength = p_event_emotion->strength;

	emit_signal("message_emotion", message_emotion);
}

void InworldCharacter::on_event_trigger(Ref<InworldEventTrigger> p_event_trigger) {
	_on_event(p_event_trigger.ptr());

	Ref<InworldMessageTrigger> message_trigger;
	message_trigger.instantiate();

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

	message_control->type = p_event_control->type;

	emit_signal("message_control", message_control);
}

void InworldCharacter::on_talk_queue_next_ready() {
	emit_signal("talk_queue_next_ready", talk_queue);
}

void InworldCharacter::on_talk_queue_next_popped(Ref<InworldMessageTalk> p_message_talk) {
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
