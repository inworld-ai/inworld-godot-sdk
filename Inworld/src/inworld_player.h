#ifndef INWORLD_PLAYER_H
#define INWORLD_PLAYER_H

#include <godot_cpp/classes/node.hpp>

namespace godot {
class InworldCharacter;

class InworldPlayer : public Node {
	GDCLASS(InworldPlayer, Node);

protected:
	static void _bind_methods();

private:
	InworldCharacter *target_character;

public:
	InworldPlayer();
	~InworldPlayer();

	void set_target_character(InworldCharacter *p_target_character);
	InworldCharacter *get_target_character() const;
};

} // namespace godot

#endif // INWORLD_PLAYER_H
