#ifndef INWORLD_PLAYER_H
#define INWORLD_PLAYER_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/thread.hpp>

namespace godot {
class InworldCharacter;
class InworldMicrophone;

class InworldMessageTalk;
class InworldMessageSpeechToText;
class InworldMessageEmotion;
class InworldMessageTrigger;
class InworldMessageControl;

class InworldPlayer : public Node {
	GDCLASS(InworldPlayer, Node);

protected:
	static void _bind_methods();

private:
	String name;
	InworldCharacter *target_character;
	InworldMicrophone *microphone;
	bool talking;

public:
	InworldPlayer();
	~InworldPlayer();

	virtual void _process(double_t delta) override;

	void set_name(String p_name);
	String get_name() const;

	void set_target_character(InworldCharacter *p_target_character);
	InworldCharacter *get_target_character() const;

	void set_talking(bool p_talking);
	bool get_talking() const;

private:
	void _start_talk_to_target();
	void _stop_talk_to_target();

	void _bind_to_target();
	void _unbind_from_target();

	void on_target_message_talk(Ref<InworldMessageTalk> p_message_talk);
	void on_target_message_stt(Ref<InworldMessageSpeechToText> p_message_stt);
	void on_target_message_emotion(Ref<InworldMessageEmotion> p_message_emotion);
	void on_target_message_trigger(Ref<InworldMessageTrigger> p_message_trigger);
	void on_target_message_control(Ref<InworldMessageControl> p_message_control);
};

} // namespace godot

#endif // INWORLD_PLAYER_H
