#include "inworld_player.h"

#include "inworld_character.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void InworldPlayer::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_target_character", "target_character"), &InworldPlayer::set_target_character);
	ClassDB::bind_method(D_METHOD("get_target_character"), &InworldPlayer::get_target_character);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "target_character", PROPERTY_HINT_NODE_TYPE, "InworldCharacter"), "set_target_character", "get_target_character");
}

InworldPlayer::InworldPlayer() :
		Node(), target_character(nullptr) {
}

InworldPlayer::~InworldPlayer() {
}

void InworldPlayer::set_target_character(InworldCharacter *p_target_character) {
	target_character = p_target_character;
}

InworldCharacter *InworldPlayer::get_target_character() const {
	return target_character;
}
