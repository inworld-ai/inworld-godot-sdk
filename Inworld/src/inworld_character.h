#ifndef INWORLD_CHARACTER_H
#define INWORLD_CHARACTER_H

#include <godot_cpp/classes/node.hpp>

namespace godot {
class InworldSession;

class InworldCharacter : public Node {
	GDCLASS(InworldCharacter, Node);

protected:
	static void _bind_methods();

private:
	String brain;
	InworldSession *session;

public:
	InworldCharacter();
	~InworldCharacter();

	void set_brain(String p_brain);
	String get_brain() const;

	void set_session(InworldSession *p_session);
	InworldSession *get_session() const;

	void send_text(String p_text);
	void send_trigger(String p_name, Dictionary p_params);
	void on_text_event(String p_text);

private:
	void bind_brain_to_session();
	void unbind_brain_from_session();
	void on_session_established(bool p_established);
};

} // namespace godot

#endif // INWORLD_CHARACTER_H
