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
	Vector<String> utterance_ids;
	Dictionary utterance_id_to_talk;

	Ref<InworldMessageTalk> current_talk;

public:
	InworldTalkQueue();
	~InworldTalkQueue();

public:
	Vector<Ref<InworldMessageTalk>> InworldTalkQueue::get_talks();

	void update_text(String p_utterance_id, String p_text);
	void update_chunk(String p_utterance_id, PackedByteArray p_chunk);

	void finish_current();

	void clear();

private:
	void _check_next_ready();
	Ref<InworldMessageTalk> _find_or_create(String utterance_id);
};

} // namespace godot

#endif // INWORLD_TALK_QUEUE_H
