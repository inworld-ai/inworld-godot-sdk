#ifndef INWORLD_PLAYER_H
#define INWORLD_PLAYER_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/thread.hpp>

namespace godot {
class InworldCharacter;
class InworldMicrophone;

class InworldPlayer : public Node {
	GDCLASS(InworldPlayer, Node);

protected:
	static void _bind_methods();

private:
	InworldCharacter *target_character;
	InworldMicrophone *microphone;

public:
	InworldPlayer();
	~InworldPlayer();

	virtual void _process(double_t delta) override;

	void set_target_character(InworldCharacter *p_target_character);
	InworldCharacter *get_target_character() const;

	void set_talking(bool p_talking);
	bool get_talking() const;
};

} // namespace godot

#endif // INWORLD_PLAYER_H
