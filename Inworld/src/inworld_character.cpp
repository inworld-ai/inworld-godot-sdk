#include "inworld_character.h"

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
	ClassDB::bind_method(D_METHOD("on_text_event", "text"), &InworldCharacter::on_text_event);
	ADD_SIGNAL(MethodInfo("text_event", PropertyInfo(Variant::STRING, "text")));
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

void InworldCharacter::on_text_event(String p_text) {
	emit_signal("text_event", p_text);
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
	if (p_established) {
		session->connect_text_events(brain, Callable(this, "on_text_event"));
	} else {
		session->disconnect_text_events(brain, Callable(this, "on_text_event"));
	}
}
