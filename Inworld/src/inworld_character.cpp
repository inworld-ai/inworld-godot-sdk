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

	ClassDB::bind_method(D_METHOD("set_session", "session"), &InworldCharacter::set_session);
	ClassDB::bind_method(D_METHOD("get_session"), &InworldCharacter::get_session);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "session", PROPERTY_HINT_NODE_TYPE, "InworldSession"), "set_session", "get_session");

	ClassDB::bind_method(D_METHOD("on_session_established", "established"), &InworldCharacter::on_session_established);

	ClassDB::bind_method(D_METHOD("send_text", "text"), &InworldCharacter::send_text);

	ClassDB::bind_method(D_METHOD("on_event_text", "text"), &InworldCharacter::on_event_text);
	ClassDB::bind_method(D_METHOD("on_event_audio", "audio"), &InworldCharacter::on_event_audio);
	ClassDB::bind_method(D_METHOD("on_event_emotion", "emotion"), &InworldCharacter::on_event_emotion);
	ClassDB::bind_method(D_METHOD("on_event_trigger", "trigger"), &InworldCharacter::on_event_trigger);
	ClassDB::bind_method(D_METHOD("on_event_control", "control"), &InworldCharacter::on_event_control);

	ADD_SIGNAL(MethodInfo("message_talk", PropertyInfo(Variant::OBJECT, "talk")));
	ADD_SIGNAL(MethodInfo("message_stt", PropertyInfo(Variant::OBJECT, "stt")));
	ADD_SIGNAL(MethodInfo("message_emotion", PropertyInfo(Variant::OBJECT, "emotion")));
	ADD_SIGNAL(MethodInfo("message_trigger", PropertyInfo(Variant::OBJECT, "trigger")));
	ADD_SIGNAL(MethodInfo("message_control", PropertyInfo(Variant::OBJECT, "control")));
}

InworldCharacter::InworldCharacter() :
		Node(), brain(), session(nullptr) {
}

InworldCharacter::~InworldCharacter() {
}

void InworldCharacter::set_brain(String p_brain) {
	unbind_brain_from_session();
	brain = p_brain;
	bind_brain_to_session();
}

String InworldCharacter::get_brain() const {
	return brain;
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
	if (session == nullptr || session->get_connection_state() != InworldSession::ConnectionState::CONNECTED) {
		return;
	}
	session->send_text(brain, p_text);
}

void InworldCharacter::on_event_text(Ref<InworldEventText> p_event_text) {
	if (p_event_text->get_source_actor_type() == StringName("Agent")) {
		Ref<InworldMessageTalk> message_talk;
		message_talk.instantiate();

		message_talk->text = p_event_text->text;
		emit_signal("message_talk", message_talk);
	} else {
		Ref<InworldMessageSpeechToText> message_stt;
		message_stt.instantiate();

		message_stt->text = p_event_text->text;
		message_stt->complete = p_event_text->complete;
	}
}

void InworldCharacter::on_event_audio(Ref<InworldEventDataAudio> p_event_audio) {
	Ref<InworldMessageTalk> message_talk;
	message_talk.instantiate();

	message_talk->chunk = p_event_audio->chunk;
	emit_signal("message_talk", message_talk);
}

void InworldCharacter::on_event_emotion(Ref<InworldEventEmotion> p_event_emotion) {
	Ref<InworldMessageEmotion> message_emotion;
	message_emotion.instantiate();

	message_emotion->behavior = p_event_emotion->behavior;
	message_emotion->strength = p_event_emotion->strength;

	emit_signal("message_emotion", message_emotion);
}

void InworldCharacter::on_event_trigger(Ref<InworldEventTrigger> p_event_trigger) {
	Ref<InworldMessageTrigger> message_trigger;
	message_trigger.instantiate();

	message_trigger->name = p_event_trigger->name;
	message_trigger->params = p_event_trigger->params;

	emit_signal("message_trigger", message_trigger);
}

void InworldCharacter::on_event_control(Ref<InworldEventControl> p_event_control) {
	Ref<InworldMessageControl> message_control;
	message_control.instantiate();

	message_control->type = p_event_control->type;

	emit_signal("message_control", message_control);
}

void InworldCharacter::bind_brain_to_session() {
	if (session == nullptr) {
		return;
	}
	session->connect("established", Callable(this, "on_session_established"));
	on_session_established(session->get_established());
}

void InworldCharacter::unbind_brain_from_session() {
	if (session == nullptr) {
		return;
	}
	session->disconnect("established", Callable(this, "on_session_established"));
	on_session_established(false);
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
}
