#ifndef INWORLD_MESSAGE_H
#define INWORLD_MESSAGE_H

#include <godot_cpp/classes/ref_counted.hpp>

namespace godot {

class InworldMessage : public RefCounted {
	GDCLASS(InworldMessage, RefCounted);

protected:
	static void _bind_methods();

private:
	String interaction_id;
	String utterance_id;

public:
	InworldMessage();
	~InworldMessage();

	String get_interaction_id() const;
	String get_utterance_id() const;
};

class InworldMessageTalk : public InworldMessage {
	GDCLASS(InworldMessageTalk, InworldMessage)

protected:
	static void _bind_methods();

public:
	InworldMessageTalk();
	~InworldMessageTalk();

	String text;
	PackedByteArray chunk;

	String get_text() const;
	PackedByteArray get_chunk() const;

	bool get_ready() const;
};

class InworldMessageSpeechToText : public InworldMessage {
	GDCLASS(InworldMessageSpeechToText, InworldMessage)

protected:
	static void _bind_methods();

public:
	InworldMessageSpeechToText();
	~InworldMessageSpeechToText();

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
	~InworldMessageEmotion();

	StringName behavior;
	StringName strength;

	StringName get_behavior() const;
	StringName get_strength() const;
};

class InworldMessageTrigger : public InworldMessage {
	GDCLASS(InworldMessageTrigger, InworldMessage)

protected:
	static void _bind_methods();

public:
	InworldMessageTrigger();
	~InworldMessageTrigger();

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
	~InworldMessageControl();

	StringName type;

	StringName get_type() const;
};

} // namespace godot

#endif // INWORLD_MESSAGE_H
