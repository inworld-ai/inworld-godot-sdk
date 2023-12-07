#ifndef INWORLD_CHARACTER_H
#define INWORLD_CHARACTER_H

#include <godot_cpp/classes/node.hpp>

#include "inworld_talk_queue.h"

namespace godot {
class InworldSession;
class InworldEventText;
class InworldEventDataAudio;
class InworldEventEmotion;
class InworldEventTrigger;
class InworldEventControl;

class InworldCharacter : public Node {
	GDCLASS(InworldCharacter, Node);

protected:
	static void _bind_methods();

private:
	String brain;
	InworldSession *session;
	Vector<String> pending_interaction_ids;
	Vector<String> canceled_interaction_ids;
	InworldTalkQueue *talk_queue;
	bool wants_audio_session;

public:
	InworldCharacter();
	~InworldCharacter();

	void set_brain(String p_brain);
	String get_brain() const;

	String get_name() const;

	void set_session(InworldSession *p_session);
	InworldSession *get_session() const;

	void send_text(String p_text);
	void send_trigger(String p_name, Dictionary p_params);
	void start_audio_session();
	void stop_audio_session();
	void send_audio(PackedByteArray p_data);

	void interrupt();

	void _on_event(InworldEvent *p_event);
	bool _is_event_canceled(InworldEvent *p_event);

	void on_event_text(Ref<InworldEventText> p_event_text);
	void on_event_audio(Ref<InworldEventDataAudio> p_event_audio);
	void on_event_emotion(Ref<InworldEventEmotion> p_event_emotion);
	void on_event_trigger(Ref<InworldEventTrigger> p_event_trigger);
	void on_event_control(Ref<InworldEventControl> p_event_control);

private:
	void finish_current_message_talk();
	void on_talk_queue_next_talk_ready(Ref<InworldMessageTalk> p_message_talk);

	void bind_brain_to_session();
	void unbind_brain_from_session();
	void on_session_established(bool p_established);
	void on_session_connected(bool p_connected);
};

} // namespace godot

#endif // INWORLD_CHARACTER_H
