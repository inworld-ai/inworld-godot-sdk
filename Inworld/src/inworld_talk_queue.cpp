#include "inworld_talk_queue.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void InworldTalkQueue::_bind_methods() {
	ClassDB::bind_method(D_METHOD("finish_current"), &InworldTalkQueue::finish_current);

	ADD_SIGNAL(MethodInfo("next_ready", PropertyInfo(Variant::OBJECT, "talk")));
}

InworldTalkQueue::InworldTalkQueue() :
		Object{}, utterance_ids{}, utterance_id_to_talk{}, current_talk{} {
}

InworldTalkQueue::~InworldTalkQueue() {
}

Vector<Ref<InworldMessageTalk>> InworldTalkQueue::get_talks() {
	Vector<Ref<InworldMessageTalk>> talks;
	if (current_talk.is_valid()) {
		talks.push_back(current_talk);
	}
	for (const String &utterance_id : utterance_ids) {
		Ref<InworldMessageTalk> message_talk = utterance_id_to_talk[utterance_id];
		talks.push_back(message_talk);
	}
	return talks;
}

void InworldTalkQueue::update_text(String p_interaction_id, String p_utterance_id, String p_text) {
	_find_or_create(p_interaction_id, p_utterance_id)->text = p_text;
	_check_next_ready();
}

void InworldTalkQueue::update_audio(String p_interaction_id, String p_utterance_id, PackedByteArray p_chunk, TypedArray<InworldMessageTalk::Viseme> p_visemes) {
	_find_or_create(p_interaction_id, p_utterance_id)->chunk = p_chunk;
	_find_or_create(p_interaction_id, p_utterance_id)->visemes = p_visemes;
	_check_next_ready();
}

void InworldTalkQueue::finish_current() {
	current_talk = Ref<InworldMessageTalk>{};
	_check_next_ready();
}

void InworldTalkQueue::clear() {
	utterance_ids.clear();
	utterance_id_to_talk.clear();
	finish_current();
}

void InworldTalkQueue::_check_next_ready() {
	if (current_talk.is_valid()) {
		return;
	}
	if (utterance_ids.is_empty()) {
		return;
	}
	Ref<InworldMessageTalk> message_talk = utterance_id_to_talk[utterance_ids[0]];
	if (message_talk->get_ready()) {
		current_talk = message_talk;
		utterance_id_to_talk.erase(utterance_ids[0]);
		utterance_ids.remove_at(0);
		emit_signal("next_ready", current_talk);
	}
}

Ref<InworldMessageTalk> InworldTalkQueue::_find_or_create(String p_interaction_id, String p_utterance_id) {
	Ref<InworldMessageTalk> message_talk;
	if (utterance_id_to_talk.has(p_utterance_id)) {
		message_talk = utterance_id_to_talk[p_utterance_id];
	} else {
		message_talk.instantiate();
		message_talk->interaction_id = p_interaction_id;
		message_talk->utterance_id = p_utterance_id;

		utterance_ids.push_back(p_utterance_id);
		utterance_id_to_talk[p_utterance_id] = message_talk;
	}
	return message_talk;
}
