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
		RefCounted{}, routing{}, packet_id{} {
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
	ClassDB::bind_method(D_METHOD("get_phonemes"), &InworldEventDataAudio::get_phonemes);

	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "phonemes"), "", "get_phonemes");
}

TypedArray<InworldEventDataAudio::Phoneme> InworldEventDataAudio::get_phonemes() const {
	return phonemes;
}

InworldEventDataAudio::InworldEventDataAudio() :
		InworldEventData{}, phonemes{} {
}

InworldEventDataAudio::~InworldEventDataAudio() {
	for (uint32_t i = 0; i < phonemes.size(); ++i) {
		InworldEventDataAudio::Phoneme *phoneme = Object::cast_to<InworldEventDataAudio::Phoneme>(&*phonemes[i]);
		memdelete(phoneme);
	}
}

void InworldEventDataAudio::Phoneme::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_code"), &InworldEventDataAudio::Phoneme::get_code);
	ClassDB::bind_method(D_METHOD("get_time_stamp"), &InworldEventDataAudio::Phoneme::get_time_stamp);

	ADD_PROPERTY(PropertyInfo(Variant::STRING_NAME, "code"), "", "get_code");
	ADD_PROPERTY(PropertyInfo(Variant::STRING_NAME, "time_stamp"), "", "get_time_stamp");
}

InworldEventDataAudio::Phoneme::Phoneme() :
		Object{}, code{}, time_stamp{} {
}

InworldEventDataAudio::Phoneme::~Phoneme() {
}

StringName InworldEventDataAudio::Phoneme::get_code() const {
	return code;
}

float InworldEventDataAudio::Phoneme::get_time_stamp() const {
	return time_stamp;
}

void InworldEventEmotion::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_behavior"), &InworldEventEmotion::get_behavior);
	ClassDB::bind_method(D_METHOD("get_strength"), &InworldEventEmotion::get_strength);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "behavior"), "", "get_behavior");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "strength"), "", "get_strength");
}

InworldEventEmotion::InworldEventEmotion() :
		InworldEvent{}, behavior{ InworldCharacter::EmotionBehavior::NEUTRAL }, strength{ InworldCharacter::EmotionStrength::NORMAL } {
}

InworldEventEmotion::~InworldEventEmotion() {
}

InworldCharacter::EmotionBehavior InworldEventEmotion::get_behavior() const {
	return behavior;
}

InworldCharacter::EmotionStrength InworldEventEmotion::get_strength() const {
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

void InworldEventSceneStatus::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_name"), &InworldEventSceneStatus::get_name);
	ClassDB::bind_method(D_METHOD("get_description"), &InworldEventSceneStatus::get_description);
	ClassDB::bind_method(D_METHOD("get_display_name"), &InworldEventSceneStatus::get_display_name);

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "name"), "", "get_name");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "description"), "", "get_description");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "display_name"), "", "get_display_name");
}

InworldEventSceneStatus::InworldEventSceneStatus() :
		InworldEvent{}, name{ "Unknown" }, description{ "Unknown" }, display_name{ "Unknown" }, agent_infos{} {
}

InworldEventSceneStatus::~InworldEventSceneStatus() {
}

String InworldEventSceneStatus::get_name() const {
	return name;
}

String InworldEventSceneStatus::get_description() const {
	return description;
}

String InworldEventSceneStatus::get_display_name() const {
	return display_name;
}
