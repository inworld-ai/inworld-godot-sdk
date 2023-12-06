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
	ClassDB::bind_method(D_METHOD("get_ready"), &InworldMessageTalk::get_ready);

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "text"), "", "get_text");
	ADD_PROPERTY(PropertyInfo(Variant::PACKED_BYTE_ARRAY, "chunk"), "", "get_chunk");
}

InworldMessageTalk::InworldMessageTalk() :
		InworldMessage(), text(), chunk() {
}

InworldMessageTalk::~InworldMessageTalk() {
}

String InworldMessageTalk::get_text() const {
	return text;
}

PackedByteArray InworldMessageTalk::get_chunk() const {
	return chunk;
}

bool InworldMessageTalk::get_ready() const {
	return !text.is_empty() && !chunk.is_empty();
}

void InworldMessageSpeechToText::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_text"), &InworldMessageSpeechToText::get_text);
	ClassDB::bind_method(D_METHOD("get_complete"), &InworldMessageSpeechToText::get_complete);

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "text"), "", "get_text");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "complete"), "", "get_complete");
}

InworldMessageSpeechToText::InworldMessageSpeechToText() :
		InworldMessage(), text(), complete(false) {
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

	ADD_PROPERTY(PropertyInfo(Variant::STRING_NAME, "behavior"), "", "get_behavior");
	ADD_PROPERTY(PropertyInfo(Variant::STRING_NAME, "strength"), "", "get_strength");
}

InworldMessageEmotion::InworldMessageEmotion() :
		InworldMessage(), behavior("Neutral"), strength("Normal") {
}

InworldMessageEmotion::~InworldMessageEmotion() {
}

StringName InworldMessageEmotion::get_behavior() const {
	return behavior;
}

StringName InworldMessageEmotion::get_strength() const {
	return strength;
}

void InworldMessageTrigger::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_name"), &InworldMessageTrigger::get_name);
	ClassDB::bind_method(D_METHOD("get_params"), &InworldMessageTrigger::get_params);

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "name"), "", "get_name");
	ADD_PROPERTY(PropertyInfo(Variant::DICTIONARY, "params"), "", "get_params");
}

InworldMessageTrigger::InworldMessageTrigger() :
		InworldMessage(), name(), params() {
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
		InworldMessage(), type("Unknown") {
}

InworldMessageControl::~InworldMessageControl() {
}

StringName InworldMessageControl::get_type() const {
	return type;
}
