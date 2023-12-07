#include "inworld_talk_queue.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void InworldTalkQueue::_bind_methods() {
	ClassDB::bind_method(D_METHOD("is_next_ready"), &InworldTalkQueue::is_next_ready);
	ClassDB::bind_method(D_METHOD("pop_next_ready"), &InworldTalkQueue::pop_next_ready);

	ADD_SIGNAL(MethodInfo("next_ready"));
	ADD_SIGNAL(MethodInfo("next_popped", PropertyInfo(Variant::OBJECT, "talk")));
}

InworldTalkQueue::InworldTalkQueue() :
		Object{} {
}

InworldTalkQueue::~InworldTalkQueue() {
}

void InworldTalkQueue::update_text(String p_utterance_id, String p_text) {
	_find_or_create(p_utterance_id)->text = p_text;
	_check_talk_ready(p_utterance_id);
}

void InworldTalkQueue::update_chunk(String p_utterance_id, PackedByteArray p_chunk) {
	_find_or_create(p_utterance_id)->chunk = p_chunk;
	_check_talk_ready(p_utterance_id);
}

void InworldTalkQueue::_check_talk_ready(String p_utterance_id) {
	if (ready_utterances.find(p_utterance_id) == -1) {
		Ref<InworldMessageTalk> message_talk = utterance_to_talk[utterances[0]];
		std::string str = std::to_string(message_talk->chunk.size());
		if (message_talk->get_ready()) {
			ready_utterances.push_back(p_utterance_id);
			if (p_utterance_id == utterances[0]) {
				emit_signal("next_ready");
			}
		}
	}
}

Ref<InworldMessageTalk> InworldTalkQueue::_find_or_create(String p_utterance_id) {
	Ref<InworldMessageTalk> message_talk;
	if (utterance_to_talk.has(p_utterance_id)) {
		message_talk = utterance_to_talk[p_utterance_id];
	} else {
		message_talk.instantiate();
		utterances.push_back(p_utterance_id);
		utterance_to_talk[p_utterance_id] = message_talk;
	}
	return message_talk;
}

bool InworldTalkQueue::is_next_ready() const {
	if (utterances.is_empty()) {
		return false;
	}
	Ref<InworldMessageTalk> next = utterance_to_talk[utterances[0]];
	return next->get_ready();
}

Ref<InworldMessageTalk> InworldTalkQueue::pop_next_ready() {
	Ref<InworldMessageTalk> message_talk;
	if (is_next_ready()) {
		message_talk = utterance_to_talk[utterances[0]];
		utterance_to_talk.erase(utterances[0]);
		ready_utterances.erase(utterances[0]);
		utterances.remove_at(0);
		emit_signal("next_popped", message_talk);
	}
	return message_talk;
}
