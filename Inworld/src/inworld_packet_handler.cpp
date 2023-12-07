#include "inworld_packet_handler.h"

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
		case InworldPakets::Actor_Type::Actor_Type_PLAYER:
			p_new.type = "Player";
			break;
		case InworldPakets::Actor_Type::Actor_Type_AGENT:
			p_new.type = "Agent";
			break;
		default:
			p_new.type = "Unknown";
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
}

template <>
void translate_event<Inworld::EmotionEvent, InworldEventEmotion>(const Inworld::EmotionEvent &p_original, InworldEventEmotion &p_new) {
	translate_inworld_packet(p_original, p_new);
	switch (p_original.GetEmotionalBehavior()) {
		case ai::inworld::packets::EmotionEvent_SpaffCode_AFFECTION:
			p_new.behavior = StringName("Affection");
			break;
		case ai::inworld::packets::EmotionEvent_SpaffCode_ANGER:
			p_new.behavior = StringName("Anger");
			break;
		case ai::inworld::packets::EmotionEvent_SpaffCode_BELLIGERENCE:
			p_new.behavior = StringName("Belligerence");
			break;
		case ai::inworld::packets::EmotionEvent_SpaffCode_CONTEMPT:
			p_new.behavior = StringName("Contempt");
			break;
		case ai::inworld::packets::EmotionEvent_SpaffCode_CRITICISM:
			p_new.behavior = StringName("Criticism");
			break;
		case ai::inworld::packets::EmotionEvent_SpaffCode_DISGUST:
			p_new.behavior = StringName("Disgust");
			break;
		case ai::inworld::packets::EmotionEvent_SpaffCode_DOMINEERING:
			p_new.behavior = StringName("Domineering");
			break;
		case ai::inworld::packets::EmotionEvent_SpaffCode_HUMOR:
			p_new.behavior = StringName("Humor");
			break;
		case ai::inworld::packets::EmotionEvent_SpaffCode_INTEREST:
			p_new.behavior = StringName("Interest");
			break;
		case ai::inworld::packets::EmotionEvent_SpaffCode_JOY:
			p_new.behavior = StringName("Joy");
			break;
		case ai::inworld::packets::EmotionEvent_SpaffCode_SADNESS:
			p_new.behavior = StringName("Sadness");
			break;
		case ai::inworld::packets::EmotionEvent_SpaffCode_STONEWALLING:
			p_new.behavior = StringName("Stonewalling");
			break;
		case ai::inworld::packets::EmotionEvent_SpaffCode_SURPRISE:
			p_new.behavior = StringName("Surprise");
			break;
		case ai::inworld::packets::EmotionEvent_SpaffCode_TENSE_HUMOR:
			p_new.behavior = StringName("Tense");
			break;
		case ai::inworld::packets::EmotionEvent_SpaffCode_TENSION:
			p_new.behavior = StringName("Tension");
			break;
		case ai::inworld::packets::EmotionEvent_SpaffCode_VALIDATION:
			p_new.behavior = StringName("Validation");
			break;
		case ai::inworld::packets::EmotionEvent_SpaffCode_WHINING:
			p_new.behavior = StringName("Whining");
			break;
		default:
			p_new.behavior = StringName("Neutral");
			break;
	}

	switch (p_original.GetStrength()) {
		case ai::inworld::packets::EmotionEvent_Strength_WEAK:
			p_new.strength = StringName("Weak");
			break;
		case ai::inworld::packets::EmotionEvent_Strength_NORMAL:
			p_new.strength = StringName("Normal");
			break;
		case ai::inworld::packets::EmotionEvent_Strength_STRONG:
			p_new.strength = StringName("Strong");
			break;
		default:
			p_new.strength = StringName("Unspecified");
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
		case ai::inworld::packets::ControlEvent_Action_INTERACTION_END:
			p_new.type = StringName("InteractionEnd");
			break;
		default:
			p_new.type = StringName("Unknown");
	}
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
			emit_signal(source_signal_name, event);                                     \
		}                                                                               \
		String target_signal_name = event.ptr()->get_target_actor_name() + "_" + #Type; \
		if (has_signal(target_signal_name)) {                                           \
			emit_signal(target_signal_name, event);                                     \
		}                                                                               \
	}

DEFINE_HANDLER_EVENT(Inworld::TextEvent, InworldEventText, text)
DEFINE_HANDLER_EVENT(Inworld::AudioDataEvent, InworldEventDataAudio, audio)
DEFINE_HANDLER_EVENT(Inworld::EmotionEvent, InworldEventEmotion, emotion)
DEFINE_HANDLER_EVENT(Inworld::CustomEvent, InworldEventTrigger, trigger)
DEFINE_HANDLER_EVENT(Inworld::ControlEvent, InworldEventControl, control)

#undef DEFINE_HANDLER
