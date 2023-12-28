#ifndef INWORLD_MESSAGE_H
#define INWORLD_MESSAGE_H

#include "inworld_character.h"

#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/variant/typed_array.hpp>

namespace godot {

class InworldMessage : public RefCounted {
	GDCLASS(InworldMessage, RefCounted);

protected:
	static void _bind_methods();

public:
	InworldMessage();
	virtual ~InworldMessage();

	String interaction_id;
	String utterance_id;

	String get_interaction_id() const;
	String get_utterance_id() const;
};

class InworldMessageTalk : public InworldMessage {
	GDCLASS(InworldMessageTalk, InworldMessage)

public:
	class Viseme : public Object {
		GDCLASS(Viseme, Object)

	protected:
		static void _bind_methods();

	public:
		Viseme();
		virtual ~Viseme();

		StringName code;
		float time_stamp;

		StringName get_code() const;
		float get_time_stamp() const;
	};

protected:
	static void _bind_methods();

public:
	InworldMessageTalk();
	virtual ~InworldMessageTalk();

	String text;
	PackedByteArray chunk;
	TypedArray<Viseme> visemes;

	String get_text() const;
	PackedByteArray get_chunk() const;
	TypedArray<Viseme> get_visemes() const;

	bool get_ready() const;
};

class InworldMessageSpeechToText : public InworldMessage {
	GDCLASS(InworldMessageSpeechToText, InworldMessage)

protected:
	static void _bind_methods();

public:
	InworldMessageSpeechToText();
	virtual ~InworldMessageSpeechToText();

	String text;
	bool complete;

	String get_text() const;
	bool get_complete() const;
};

class InworldMessageEmotion : public InworldMessage {
	GDCLASS(InworldMessageEmotion, InworldMessage)

protected:
	static void _bind_methods();

public:
	InworldMessageEmotion();
	virtual ~InworldMessageEmotion();

	InworldCharacter::EmotionBehavior behavior;
	InworldCharacter::EmotionStrength strength;

	InworldCharacter::EmotionBehavior get_behavior() const;
	InworldCharacter::EmotionStrength get_strength() const;
};

class InworldMessageTrigger : public InworldMessage {
	GDCLASS(InworldMessageTrigger, InworldMessage)

protected:
	static void _bind_methods();

public:
	InworldMessageTrigger();
	virtual ~InworldMessageTrigger();

	String name;
	Dictionary params;

	String get_name() const;
	Dictionary get_params() const;
};

class InworldMessageControl : public InworldMessage {
	GDCLASS(InworldMessageControl, InworldMessage)

protected:
	static void _bind_methods();

public:
	InworldMessageControl();
	virtual ~InworldMessageControl();

	StringName type;

	StringName get_type() const;
};

} // namespace godot

#endif // INWORLD_MESSAGE_H
