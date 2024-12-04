#include "inworld_packet_handler.h"
#include "ai/inworld/packets/packets.pb.h"

#include "inworld_event.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void InworldPacketHandler::_bind_methods() {
}

InworldPacketHandler::InworldPacketHandler() {
}

InworldPacketHandler::~InworldPacketHandler() {
}

void translate_inworld_actor(const Inworld::Actor &p_original, InworldEventActor &p_new) {
	switch (p_original._Type) {
		case InworldPackets::Actor_Type::Actor_Type_PLAYER:
			p_new.type = StringName("Player");
			break;
		case InworldPackets::Actor_Type::Actor_Type_AGENT:
			p_new.type = StringName("Agent");
			break;
		default:
			p_new.type = StringName("Unknown");
			break;
	}
	p_new.name = String(p_original._Name.c_str());
}

void translate_inworld_routing(const Inworld::Routing &p_original, InworldEventRouting &p_new) {
	translate_inworld_actor(p_original._Source, p_new.source);
	translate_inworld_actor(p_original._Target, p_new.target);
}

void translate_inworld_packet_id(const Inworld::PacketId &p_original, InworldEventPacketId &p_new) {
	p_new.uid = String(p_original._UID.c_str());
	p_new.interaction_id = String(p_original._InteractionId.c_str());
	p_new.utterance_id = String(p_original._UtteranceId.c_str());
}

void translate_inworld_packet(const Inworld::Packet &p_original, InworldEvent &p_new) {
	translate_inworld_packet_id(p_original._PacketId, p_new.packet_id);
	translate_inworld_routing(p_original._Routing, p_new.routing);
}

template <typename TOrig, typename TNew>
void translate_event(const TOrig &p_original, TNew &p_new);

template <>
void translate_event<Inworld::TextEvent, InworldEventText>(const Inworld::TextEvent &p_original, InworldEventText &p_new) {
	translate_inworld_packet(p_original, p_new);
	p_new.text = String(p_original.GetText().c_str());
	p_new.complete = p_original.IsFinal();
}

template <>
void translate_event<Inworld::DataEvent, InworldEventData>(const Inworld::DataEvent &p_original, InworldEventData &p_new) {
	translate_inworld_packet(p_original, p_new);
	auto &chunk = p_original.GetDataChunk();
	p_new.chunk.resize(chunk.size());
	memcpy(p_new.chunk.ptrw(), chunk.data(), chunk.size());
}

template <>
void translate_event<Inworld::AudioDataEvent, InworldEventDataAudio>(const Inworld::AudioDataEvent &p_original, InworldEventDataAudio &p_new) {
	translate_event<Inworld::DataEvent, InworldEventData>(p_original, p_new);
	for(const auto& phoneme_info : p_original.GetPhonemeInfos()) {
		InworldEventDataAudio::Phoneme *phoneme = memnew(InworldEventDataAudio::Phoneme);
		phoneme->code = StringName(phoneme_info.Code.c_str());
		phoneme->time_stamp = phoneme_info.Timestamp;
		p_new.phonemes.push_back(Variant(phoneme));
	}
}

template <>
void translate_event<Inworld::EmotionEvent, InworldEventEmotion>(const Inworld::EmotionEvent &p_original, InworldEventEmotion &p_new) {
	translate_inworld_packet(p_original, p_new);
	switch (p_original.GetEmotionalBehavior()) {
		case InworldPackets::EmotionEvent_SpaffCode_AFFECTION:
			p_new.behavior = InworldCharacter::EmotionBehavior::AFFECTION;
			break;
		case InworldPackets::EmotionEvent_SpaffCode_ANGER:
			p_new.behavior = InworldCharacter::EmotionBehavior::ANGER;
			break;
		case InworldPackets::EmotionEvent_SpaffCode_BELLIGERENCE:
			p_new.behavior = InworldCharacter::EmotionBehavior::BELLIGERENCE;
			break;
		case InworldPackets::EmotionEvent_SpaffCode_CONTEMPT:
			p_new.behavior = InworldCharacter::EmotionBehavior::CONTEMPT;
			break;
		case InworldPackets::EmotionEvent_SpaffCode_CRITICISM:
			p_new.behavior = InworldCharacter::EmotionBehavior::CRITICISM;
			break;
		case InworldPackets::EmotionEvent_SpaffCode_DEFENSIVENESS:
			p_new.behavior = InworldCharacter::EmotionBehavior::DEFENSIVENESS;
			break;
		case InworldPackets::EmotionEvent_SpaffCode_DISGUST:
			p_new.behavior = InworldCharacter::EmotionBehavior::DISGUST;
			break;
		case InworldPackets::EmotionEvent_SpaffCode_DOMINEERING:
			p_new.behavior = InworldCharacter::EmotionBehavior::DOMINEERING;
			break;
		case InworldPackets::EmotionEvent_SpaffCode_HUMOR:
			p_new.behavior = InworldCharacter::EmotionBehavior::HUMOR;
			break;
		case InworldPackets::EmotionEvent_SpaffCode_INTEREST:
			p_new.behavior = InworldCharacter::EmotionBehavior::INTEREST;
			break;
		case InworldPackets::EmotionEvent_SpaffCode_JOY:
			p_new.behavior = InworldCharacter::EmotionBehavior::JOY;
			break;
		case InworldPackets::EmotionEvent_SpaffCode_NEUTRAL:
			p_new.behavior = InworldCharacter::EmotionBehavior::NEUTRAL;
			break;
		case InworldPackets::EmotionEvent_SpaffCode_SADNESS:
			p_new.behavior = InworldCharacter::EmotionBehavior::SADNESS;
			break;
		case InworldPackets::EmotionEvent_SpaffCode_STONEWALLING:
			p_new.behavior = InworldCharacter::EmotionBehavior::STONEWALLING;
			break;
		case InworldPackets::EmotionEvent_SpaffCode_SURPRISE:
			p_new.behavior = InworldCharacter::EmotionBehavior::SURPRISE;
			break;
		case InworldPackets::EmotionEvent_SpaffCode_TENSE_HUMOR:
			p_new.behavior = InworldCharacter::EmotionBehavior::TENSE;
			break;
		case InworldPackets::EmotionEvent_SpaffCode_TENSION:
			p_new.behavior = InworldCharacter::EmotionBehavior::TENSION;
			break;
		case InworldPackets::EmotionEvent_SpaffCode_VALIDATION:
			p_new.behavior = InworldCharacter::EmotionBehavior::VALIDATION;
			break;
		case InworldPackets::EmotionEvent_SpaffCode_WHINING:
			p_new.behavior = InworldCharacter::EmotionBehavior::WHINING;
			break;
		default:
			p_new.behavior = InworldCharacter::EmotionBehavior::NEUTRAL;
			break;
	}

	switch (p_original.GetStrength()) {
		case InworldPackets::EmotionEvent_Strength_WEAK:
			p_new.strength = InworldCharacter::EmotionStrength::WEAK;
			break;
		case InworldPackets::EmotionEvent_Strength_NORMAL:
			p_new.strength = InworldCharacter::EmotionStrength::NORMAL;
			break;
		case InworldPackets::EmotionEvent_Strength_STRONG:
			p_new.strength = InworldCharacter::EmotionStrength::STRONG;
			break;
		default:
			p_new.strength = InworldCharacter::EmotionStrength::NORMAL;
			break;
	}
}

template <>
void translate_event<Inworld::CustomEvent, InworldEventTrigger>(const Inworld::CustomEvent &p_original, InworldEventTrigger &p_new) {
	translate_inworld_packet(p_original, p_new);
	p_new.name = String(p_original.GetName().c_str());
	for (const auto &param : p_original.GetParams()) {
		p_new.params[String(param.first.c_str())] = String(param.second.c_str());
	}
}

template <>
void translate_event<Inworld::ControlEvent, InworldEventControl>(const Inworld::ControlEvent &p_original, InworldEventControl &p_new) {
	translate_inworld_packet(p_original, p_new);
	switch (p_original.GetControlAction()) {
		case InworldPackets::ControlEvent_Action_INTERACTION_END:
			p_new.type = StringName("InteractionEnd");
			break;
		default:
			p_new.type = StringName("Unknown");
	}
}

template <>
void translate_event<Inworld::ControlEventCurrentSceneStatus, InworldEventSceneStatus>(const Inworld::ControlEventCurrentSceneStatus& p_original, InworldEventSceneStatus& p_new)
{
	translate_inworld_packet(p_original, p_new);
	p_new.name = String(p_original.GetSceneName().c_str());
	p_new.description = String(p_original.GetSceneDescription().c_str());
	p_new.display_name = String(p_original.GetSceneDisplayName().c_str());
	p_new.agent_infos = p_original.GetAgentInfos();
}

template <typename TOrig, typename TNew>
Ref<TNew> make_event(const TOrig &p_original_event) {
	Ref<TNew> new_event;
	new_event.instantiate();
	translate_event<TOrig, TNew>(p_original_event, *new_event.ptr());
	return new_event;
}

#define DEFINE_HANDLER_EVENT(Original, New, Type)                                       \
	void InworldPacketHandler::Visit(const Original &p_event) {                         \
		Ref<New> event = make_event<Original, New>(p_event);                            \
		String source_signal_name = event.ptr()->get_source_actor_name() + "_" + #Type; \
		if (has_signal(source_signal_name)) {                                           \
			call_deferred("emit_signal", source_signal_name, event);                                     \
		}                                                                               \
		String target_signal_name = event.ptr()->get_target_actor_name() + "_" + #Type; \
		if (has_signal(target_signal_name)) {                                           \
			call_deferred("emit_signal", target_signal_name, event);                                     \
		}                                                                               \
	}

DEFINE_HANDLER_EVENT(Inworld::TextEvent, InworldEventText, text)
DEFINE_HANDLER_EVENT(Inworld::AudioDataEvent, InworldEventDataAudio, audio)
DEFINE_HANDLER_EVENT(Inworld::EmotionEvent, InworldEventEmotion, emotion)
DEFINE_HANDLER_EVENT(Inworld::CustomEvent, InworldEventTrigger, trigger)
DEFINE_HANDLER_EVENT(Inworld::ControlEvent, InworldEventControl, control)

void InworldPacketHandler::Visit(const Inworld::ControlEventCurrentSceneStatus &p_event) {
	Ref<InworldEventSceneStatus> event = make_event<Inworld::ControlEventCurrentSceneStatus, InworldEventSceneStatus>(p_event);
	if (has_signal("scene_status")) {
		call_deferred("emit_signal", "scene_status", event);
	}
}

#undef DEFINE_HANDLER
