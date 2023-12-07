#include "inworld_player.h"

#include "inworld_character.h"
#include "inworld_microphone.h"
#include "inworld_session.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void InworldPlayer::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_name", "name"), &InworldPlayer::set_name);
	ClassDB::bind_method(D_METHOD("get_name"), &InworldPlayer::get_name);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "name"), "set_name", "get_name");

	ClassDB::bind_method(D_METHOD("set_target_character", "target_character"), &InworldPlayer::set_target_character);
	ClassDB::bind_method(D_METHOD("get_target_character"), &InworldPlayer::get_target_character);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "target_character", PROPERTY_HINT_NODE_TYPE, "InworldCharacter"), "set_target_character", "get_target_character");

	ClassDB::bind_method(D_METHOD("set_talking", "talking"), &InworldPlayer::set_talking);
	ClassDB::bind_method(D_METHOD("get_talking"), &InworldPlayer::get_talking);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "talking"), "set_talking", "get_talking");

	ClassDB::bind_method(D_METHOD("on_target_message_talk", "talk"), &InworldPlayer::on_target_message_talk);
	ClassDB::bind_method(D_METHOD("on_target_message_stt", "stt"), &InworldPlayer::on_target_message_stt);
	ClassDB::bind_method(D_METHOD("on_target_message_emotion", "emotion"), &InworldPlayer::on_target_message_emotion);
	ClassDB::bind_method(D_METHOD("on_target_message_trigger", "trigger"), &InworldPlayer::on_target_message_trigger);
	ClassDB::bind_method(D_METHOD("on_target_message_control", "control"), &InworldPlayer::on_target_message_control);

	ADD_SIGNAL(MethodInfo("target_message_talk", PropertyInfo(Variant::OBJECT, "talk")));
	ADD_SIGNAL(MethodInfo("target_message_stt", PropertyInfo(Variant::OBJECT, "stt")));
	ADD_SIGNAL(MethodInfo("target_message_emotion", PropertyInfo(Variant::OBJECT, "emotion")));
	ADD_SIGNAL(MethodInfo("target_message_trigger", PropertyInfo(Variant::OBJECT, "trigger")));
	ADD_SIGNAL(MethodInfo("target_message_control", PropertyInfo(Variant::OBJECT, "control")));
}

InworldPlayer::InworldPlayer() :
		Node{}, name{ "Player" }, target_character{ nullptr }, microphone{ nullptr }, talking{ false } {
	microphone = memnew(InworldMicrophone);
}

InworldPlayer::~InworldPlayer() {
	if (microphone != nullptr) {
		memdelete(microphone);
		microphone = nullptr;
	}
}

void InworldPlayer::_process(double_t delta) {
	Node::_process(delta);

	static const uint32_t SEND_SIZE = (16000 / 10) * 2; // 0.1s, 16bits to 8bits
	if (microphone->audio_buffer.size() >= SEND_SIZE) {
		PackedByteArray to_send;
		to_send.resize(SEND_SIZE);
		microphone->audio_buffer.read(to_send.ptrw(), SEND_SIZE);
		target_character->send_audio(to_send);
	}
}

void InworldPlayer::set_name(String p_name) {
	name = p_name;
}

String InworldPlayer::get_name() const {
	return name;
}

void InworldPlayer::set_target_character(InworldCharacter *p_target_character) {
	if (talking) {
		_stop_talk_to_target();
	}
	_unbind_from_target();
	target_character = p_target_character;
	if (talking) {
		_start_talk_to_target();
	}
	_bind_to_target();
}

InworldCharacter *InworldPlayer::get_target_character() const {
	return target_character;
}

void InworldPlayer::set_talking(bool p_talking) {
	if (talking == p_talking) {
		return;
	}
	talking = p_talking;
	p_talking ? _start_talk_to_target() : _stop_talk_to_target();
}

bool InworldPlayer::get_talking() const {
	return talking;
}

void InworldPlayer::_start_talk_to_target() {
	if (target_character == nullptr) {
		return;
	}
	target_character->start_audio_session();
	microphone->set_hot(true);
	set_process(true);
}

void InworldPlayer::_stop_talk_to_target() {
	if (target_character == nullptr) {
		return;
	}
	target_character->stop_audio_session();
	microphone->set_hot(false);
	set_process(false);
}

void InworldPlayer::_bind_to_target() {
	if (target_character == nullptr) {
		return;
	}

	target_character->connect("message_talk", Callable(this, "on_target_message_talk"));
	target_character->connect("message_stt", Callable(this, "on_target_message_stt"));
	target_character->connect("message_emotion", Callable(this, "on_target_message_emotion"));
	target_character->connect("message_trigger", Callable(this, "on_target_message_trigger"));
	target_character->connect("message_control", Callable(this, "on_target_message_control"));
}

void InworldPlayer::_unbind_from_target() {
	if (target_character == nullptr) {
		return;
	}

	target_character->disconnect("message_talk", Callable(this, "on_target_message_talk"));
	target_character->disconnect("message_stt", Callable(this, "on_target_message_stt"));
	target_character->disconnect("message_emotion", Callable(this, "on_target_message_emotion"));
	target_character->disconnect("message_trigger", Callable(this, "on_target_message_trigger"));
	target_character->disconnect("message_control", Callable(this, "on_target_message_control"));
}

void InworldPlayer::on_target_message_talk(Ref<InworldMessageTalk> p_message_talk) {
	emit_signal("target_message_talk", p_message_talk);
}

void InworldPlayer::on_target_message_stt(Ref<InworldMessageSpeechToText> p_message_stt) {
	emit_signal("target_message_stt", p_message_stt);
}

void InworldPlayer::on_target_message_emotion(Ref<InworldMessageEmotion> p_message_emotion) {
	emit_signal("target_message_emotion", p_message_emotion);
}

void InworldPlayer::on_target_message_trigger(Ref<InworldMessageTrigger> p_message_trigger) {
	emit_signal("target_message_trigger", p_message_trigger);
}

void InworldPlayer::on_target_message_control(Ref<InworldMessageControl> p_message_control) {
	emit_signal("target_message_control", p_message_control);
}
