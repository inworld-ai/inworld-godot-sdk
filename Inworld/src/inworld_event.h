#ifndef INWORLD_EVENT_H
#define INWORLD_EVENT_H

#include "inworld_character.h"

#include "Packets.h"

#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/variant/typed_array.hpp>

namespace godot {

struct InworldEventActor {
	StringName type;
	String name;
};

struct InworldEventRouting {
	InworldEventActor source;
	InworldEventActor target;
};

struct InworldEventPacketId {
	String uid;
	String utterance_id;
	String interaction_id;
};

struct InworldAgentInfo {
	String brain_name;
	String agent_id;
	String given_name;
};

class InworldEvent : public RefCounted {
	GDCLASS(InworldEvent, RefCounted)

protected:
	static void _bind_methods();

public:
	InworldEvent();
	virtual ~InworldEvent();

	InworldEventRouting routing;
	InworldEventPacketId packet_id;

	StringName get_source_actor_type();
	String get_source_actor_name();

	StringName get_target_actor_type();
	String get_target_actor_name();

	String get_uid();
	String get_interaction_id();
	String get_utterance_id();
};

class InworldEventText : public InworldEvent {
	GDCLASS(InworldEventText, InworldEvent)

protected:
	static void _bind_methods();

public:
	InworldEventText();
	virtual ~InworldEventText();

	String text;
	bool complete;

	String get_text() const;
	bool get_complete() const;
};

class InworldEventData : public InworldEvent {
	GDCLASS(InworldEventData, InworldEvent)

protected:
	static void _bind_methods();

public:
	InworldEventData();
	virtual ~InworldEventData();

	PackedByteArray chunk;

	PackedByteArray get_chunk() const;
};

class InworldEventDataAudio : public InworldEventData {
	GDCLASS(InworldEventDataAudio, InworldEventData)

public:
	class Phoneme : public Object {
		GDCLASS(Phoneme, Object)

	protected:
		static void _bind_methods();

	public:
		Phoneme();
		virtual ~Phoneme();

		StringName code;
		float time_stamp;

		StringName get_code() const;
		float get_time_stamp() const;
	};

protected:
	static void _bind_methods();

public:
	InworldEventDataAudio();
	~InworldEventDataAudio();

	TypedArray<Phoneme> phonemes;

	TypedArray<Phoneme> get_phonemes() const;
};

class InworldEventEmotion : public InworldEvent {
	GDCLASS(InworldEventEmotion, InworldEvent)

protected:
	static void _bind_methods();

public:
	InworldEventEmotion();
	virtual ~InworldEventEmotion();

	InworldCharacter::EmotionBehavior behavior;
	InworldCharacter::EmotionStrength strength;

	InworldCharacter::EmotionBehavior get_behavior() const;
	InworldCharacter::EmotionStrength get_strength() const;
};

class InworldEventTrigger : public InworldEvent {
	GDCLASS(InworldEventTrigger, InworldEvent)

protected:
	static void _bind_methods();

public:
	InworldEventTrigger();
	virtual ~InworldEventTrigger();

	String name;
	Dictionary params;

	String get_name() const;
	Dictionary get_params() const;
};

class InworldEventControl : public InworldEvent {
	GDCLASS(InworldEventControl, InworldEvent)

protected:
	static void _bind_methods();

public:
	InworldEventControl();
	virtual ~InworldEventControl();

	StringName type;

	StringName get_type() const;
};

class InworldEventSceneStatus : public InworldEvent {
	GDCLASS(InworldEventSceneStatus, InworldEvent)

protected:
	static void _bind_methods();

public:
	InworldEventSceneStatus();
	virtual ~InworldEventSceneStatus();

	String name;
	String description;
	String display_name;
	std::vector<Inworld::AgentInfo> agent_infos;

	String get_name() const;
	String get_description() const;
	String get_display_name() const;
};

} // namespace godot

#endif // INWORLD_EVENT_H
