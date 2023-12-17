/**
 * Copyright 2023 Theai, Inc. (DBA Inworld)
 *
 * Use of this source code is governed by the Inworld.ai Software Development Kit License Agreement
 * that can be found in the LICENSE.md file or at https://www.inworld.ai/sdk-license
 */

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
	Vector<Ref<InworldMessageTalk>> get_talks();

	void update_text(String p_interaction_id, String p_utterance_id, String p_text);
	void update_audio(String p_interaction_id, String p_utterance_id, PackedByteArray p_chunk, TypedArray<InworldMessageTalk::Viseme> p_visemes);

	void finish_current();

	void clear();

private:
	void _check_next_ready();
	Ref<InworldMessageTalk> _find_or_create(String p_interaction_id, String utterance_id);
};

} // namespace godot

#endif // INWORLD_TALK_QUEUE_H
