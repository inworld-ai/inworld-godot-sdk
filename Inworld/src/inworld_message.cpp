/**
 * Copyright 2023 Theai, Inc. (DBA Inworld)
 *
 * Use of this source code is governed by the Inworld.ai Software Development Kit License Agreement
 * that can be found in the LICENSE.md file or at https://www.inworld.ai/sdk-license
 */

#include "inworld_message.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void InworldMessage::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_interaction_id"), &InworldMessage::get_interaction_id);
	ClassDB::bind_method(D_METHOD("get_utterance_id"), &InworldMessage::get_utterance_id);

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "interaction_id"), "", "get_interaction_id");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "utterance_id"), "", "get_utterance_id");
}

InworldMessage::InworldMessage() :
		RefCounted(), interaction_id(), utterance_id() {
}

InworldMessage::~InworldMessage() {
}

String InworldMessage::get_interaction_id() const {
	return interaction_id;
}

String InworldMessage::get_utterance_id() const {
	return utterance_id;
}

void InworldMessageTalk::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_text"), &InworldMessageTalk::get_text);
	ClassDB::bind_method(D_METHOD("get_chunk"), &InworldMessageTalk::get_chunk);
	ClassDB::bind_method(D_METHOD("get_visemes"), &InworldMessageTalk::get_visemes);
	ClassDB::bind_method(D_METHOD("get_ready"), &InworldMessageTalk::get_ready);

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "text"), "", "get_text");
	ADD_PROPERTY(PropertyInfo(Variant::PACKED_BYTE_ARRAY, "chunk"), "", "get_chunk");
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "visemes"), "", "get_visemes");
}

InworldMessageTalk::InworldMessageTalk() :
		InworldMessage{}, text{}, chunk{}, visemes{} {
}

InworldMessageTalk::~InworldMessageTalk() {
	for(uint32_t i = 0; i < visemes.size(); ++i) {
		InworldMessageTalk::Viseme *viseme = Object::cast_to<InworldMessageTalk::Viseme>(&*visemes[i]);
		memdelete(viseme);
	}
}

String InworldMessageTalk::get_text() const {
	return text;
}

PackedByteArray InworldMessageTalk::get_chunk() const {
	return chunk;
}

TypedArray<InworldMessageTalk::Viseme> InworldMessageTalk::get_visemes() const {
	return visemes;
}

bool InworldMessageTalk::get_ready() const {
	return !text.is_empty() && !chunk.is_empty();
}

void InworldMessageTalk::Viseme::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_code"), &InworldMessageTalk::Viseme::get_code);
	ClassDB::bind_method(D_METHOD("get_time_stamp"), &InworldMessageTalk::Viseme::get_time_stamp);

	ADD_PROPERTY(PropertyInfo(Variant::STRING_NAME, "code"), "", "get_code");
	ADD_PROPERTY(PropertyInfo(Variant::STRING_NAME, "time_stamp"), "", "get_time_stamp");
}

InworldMessageTalk::Viseme::Viseme() :
		Object{}, code{}, time_stamp{} {
}

InworldMessageTalk::Viseme::~Viseme() {
}

StringName InworldMessageTalk::Viseme::get_code() const {
	return code;
}

float InworldMessageTalk::Viseme::get_time_stamp() const {
	return time_stamp;
}


void InworldMessageSpeechToText::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_text"), &InworldMessageSpeechToText::get_text);
	ClassDB::bind_method(D_METHOD("get_complete"), &InworldMessageSpeechToText::get_complete);

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "text"), "", "get_text");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "complete"), "", "get_complete");
}

InworldMessageSpeechToText::InworldMessageSpeechToText() :
		InworldMessage{}, text{}, complete{ false } {
}

InworldMessageSpeechToText::~InworldMessageSpeechToText() {
}

String InworldMessageSpeechToText::get_text() const {
	return text;
}

bool InworldMessageSpeechToText::get_complete() const {
	return complete;
}

void InworldMessageEmotion::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_behavior"), &InworldMessageEmotion::get_behavior);
	ClassDB::bind_method(D_METHOD("get_strength"), &InworldMessageEmotion::get_strength);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "behavior"), "", "get_behavior");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "strength"), "", "get_strength");
}

InworldMessageEmotion::InworldMessageEmotion() :
		InworldMessage{}, behavior{ InworldCharacter::EmotionBehavior::NEUTRAL }, strength{ InworldCharacter::EmotionStrength::NORMAL } {
}

InworldMessageEmotion::~InworldMessageEmotion() {
}

InworldCharacter::EmotionBehavior InworldMessageEmotion::get_behavior() const {
	return behavior;
}

InworldCharacter::EmotionStrength InworldMessageEmotion::get_strength() const {
	return strength;
}

void InworldMessageTrigger::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_name"), &InworldMessageTrigger::get_name);
	ClassDB::bind_method(D_METHOD("get_params"), &InworldMessageTrigger::get_params);

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "name"), "", "get_name");
	ADD_PROPERTY(PropertyInfo(Variant::DICTIONARY, "params"), "", "get_params");
}

InworldMessageTrigger::InworldMessageTrigger() :
		InworldMessage{}, name{}, params{} {
}

InworldMessageTrigger::~InworldMessageTrigger() {
}

String InworldMessageTrigger::get_name() const {
	return name;
}

Dictionary InworldMessageTrigger::get_params() const {
	return params;
}

void InworldMessageControl::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_type"), &InworldMessageControl::get_type);

	ADD_PROPERTY(PropertyInfo(Variant::STRING_NAME, "type"), "", "get_type");
}

InworldMessageControl::InworldMessageControl() :
		InworldMessage{}, type{ "Unknown" } {
}

InworldMessageControl::~InworldMessageControl() {
}

StringName InworldMessageControl::get_type() const {
	return type;
}
