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
	String given_name;
	InworldCharacter *target_character;
	InworldMicrophone *microphone;
	bool talking;

public:
	InworldPlayer();
	~InworldPlayer();

	virtual void _process(double_t delta) override;

	void set_given_name(String p_given_name);
	String get_given_name() const;

	void set_target_character(InworldCharacter *p_target_character);
	InworldCharacter *get_target_character() const;

	void set_talking(bool p_talking);
	bool get_talking() const;

private:
	void _start_talk_to_target();
	void _stop_talk_to_target();
};

} // namespace godot

#endif // INWORLD_PLAYER_H
