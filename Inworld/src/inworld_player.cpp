#include "inworld_player.h"

#include "inworld_character.h"
#include "inworld_microphone.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void InworldPlayer::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_target_character", "target_character"), &InworldPlayer::set_target_character);
	ClassDB::bind_method(D_METHOD("get_target_character"), &InworldPlayer::get_target_character);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "target_character", PROPERTY_HINT_NODE_TYPE, "InworldCharacter"), "set_target_character", "get_target_character");

	ClassDB::bind_method(D_METHOD("set_talking", "talking"), &InworldPlayer::set_talking);
	ClassDB::bind_method(D_METHOD("get_talking"), &InworldPlayer::get_talking);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "talking"), "set_talking", "get_talking");
}

InworldPlayer::InworldPlayer() :
		Node(), target_character(nullptr), microphone(nullptr) {
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

void InworldPlayer::set_target_character(InworldCharacter *p_target_character) {
	if (talking) {
		_stop_talk_to_target();
	}
	target_character = p_target_character;
	if (talking) {
		_start_talk_to_target();
	}
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
