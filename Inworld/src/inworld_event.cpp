#include "inworld_packet_handler.h"

#include "inworld_event.h"

#include "Types.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void InworldEvent::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_source_actor_type"), &InworldEvent::get_source_actor_type);
	ClassDB::bind_method(D_METHOD("get_source_actor_name"), &InworldEvent::get_source_actor_name);
	ClassDB::bind_method(D_METHOD("get_target_actor_type"), &InworldEvent::get_target_actor_type);
	ClassDB::bind_method(D_METHOD("get_target_actor_name"), &InworldEvent::get_target_actor_name);

	ADD_PROPERTY(PropertyInfo(Variant::STRING_NAME, "source_actor_type"), "", "get_source_actor_type");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "source_actor_name"), "", "get_source_actor_name");
	ADD_PROPERTY(PropertyInfo(Variant::STRING_NAME, "target_actor_type"), "", "get_target_actor_type");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "target_actor_name"), "", "get_target_actor_name");

	ClassDB::bind_method(D_METHOD("get_uid"), &InworldEvent::get_uid);
	ClassDB::bind_method(D_METHOD("get_interaction_id"), &InworldEvent::get_interaction_id);
	ClassDB::bind_method(D_METHOD("get_utterance_id"), &InworldEvent::get_utterance_id);

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "uid"), "", "get_uid");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "interaction_id"), "", "get_interaction_id");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "utterance_id"), "", "get_utterance_id");
}

InworldEvent::InworldEvent() :
		RefCounted(), routing(), packet_id() {
}

InworldEvent::~InworldEvent() {
}

StringName InworldEvent::get_source_actor_type() {
	return routing.source.type;
}

String InworldEvent::get_source_actor_name() {
	return routing.source.name;
}

StringName InworldEvent::get_target_actor_type() {
	return routing.target.type;
}

String InworldEvent::get_target_actor_name() {
	return routing.target.name;
}

String InworldEvent::get_uid() {
	return packet_id.uid;
}

String InworldEvent::get_interaction_id() {
	return packet_id.interaction_id;
}

String InworldEvent::get_utterance_id() {
	return packet_id.utterance_id;
}

void InworldEventText::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_text"), &InworldEventText::get_text);
	ClassDB::bind_method(D_METHOD("get_complete"), &InworldEventText::get_complete);

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "text"), "", "get_text");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "complete"), "", "get_complete");
}

InworldEventText::InworldEventText() :
		InworldEvent{}, text{}, complete{ false } {
}

InworldEventText::~InworldEventText() {
}

String InworldEventText::get_text() const {
	return text;
}

bool InworldEventText::get_complete() const {
	return complete;
}

void InworldEventData::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_chunk"), &InworldEventData::get_chunk);

	ADD_PROPERTY(PropertyInfo(Variant::PACKED_BYTE_ARRAY, "chunk"), "", "get_chunk");
}

InworldEventData::InworldEventData() :
		InworldEvent{}, chunk{} {
}

InworldEventData::~InworldEventData() {
}

PackedByteArray InworldEventData::get_chunk() const {
	return chunk;
}

void InworldEventDataAudio::_bind_methods() {
}

InworldEventDataAudio::InworldEventDataAudio() :
		InworldEventData{} {
}

InworldEventDataAudio::~InworldEventDataAudio() {
}

void InworldEventEmotion::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_behavior"), &InworldEventEmotion::get_behavior);
	ClassDB::bind_method(D_METHOD("get_strength"), &InworldEventEmotion::get_strength);

	ADD_PROPERTY(PropertyInfo(Variant::STRING_NAME, "behavior"), "", "get_behavior");
	ADD_PROPERTY(PropertyInfo(Variant::STRING_NAME, "strength"), "", "get_strength");
}

InworldEventEmotion::InworldEventEmotion() :
		InworldEvent{}, behavior{ "Neutral" }, strength{ "Normal" } {
}

InworldEventEmotion::~InworldEventEmotion() {
}

StringName InworldEventEmotion::get_behavior() const {
	return behavior;
}

StringName InworldEventEmotion::get_strength() const {
	return strength;
}

void InworldEventTrigger::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_name"), &InworldEventTrigger::get_name);
	ClassDB::bind_method(D_METHOD("get_params"), &InworldEventTrigger::get_params);

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "name"), "", "get_name");
	ADD_PROPERTY(PropertyInfo(Variant::DICTIONARY, "parmas"), "", "get_params");
}

InworldEventTrigger::InworldEventTrigger() :
		InworldEvent{}, name{}, params{} {
}

InworldEventTrigger::~InworldEventTrigger() {
}

String InworldEventTrigger::get_name() const {
	return name;
}

Dictionary InworldEventTrigger::get_params() const {
	return params;
}

void InworldEventControl::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_type"), &InworldEventControl::get_type);

	ADD_PROPERTY(PropertyInfo(Variant::STRING_NAME, "type"), "", "get_type");
}

InworldEventControl::InworldEventControl() :
		InworldEvent{}, type{ "Unknown" } {
}

InworldEventControl::~InworldEventControl() {
}

StringName InworldEventControl::get_type() const {
	return type;
}
