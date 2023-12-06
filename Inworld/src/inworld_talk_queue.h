#ifndef INWORLD_TALK_QUEUE_H
#define INWORLD_TALK_QUEUE_H

#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/templates/vector.hpp>

#include "inworld_message.h"

namespace godot {

class InworldTalkQueue : public Object {
	GDCLASS(InworldTalkQueue, Object);

protected:
	static void _bind_methods();

private:
	Vector<String> utterances;
	Vector<String> ready_utterances;
	Dictionary utterance_to_talk;

public:
	InworldTalkQueue();
	~InworldTalkQueue();

public:
	void update_text(String p_utterance_id, String p_text);
	void update_chunk(String p_utterance_id, PackedByteArray p_chunk);

	bool is_next_ready() const;
	Ref<InworldMessageTalk> pop_ready();

private:
	void _check_talk_ready(String p_utterance_id);
	Ref<InworldMessageTalk> _find_or_create(String utterance_id);
};

} // namespace godot

#endif // INWORLD_TALK_QUEUE_H
