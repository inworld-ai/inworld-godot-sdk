#ifndef INWORLD_SESSION_H
#define INWORLD_SESSION_H

#include "Client.h"
#include "Types.h"

#include <godot_cpp/classes/node.hpp>

#include <string>
#include <unordered_map>

namespace godot {
class InworldPacketHandler;

class InworldSession : public Node {
	GDCLASS(InworldSession, Node);

protected:
	static void _bind_methods();

public:
	enum ConnectionState {
		IDLE = 0,
		CONNECTING = 1,
		CONNECTED = 2,
		FAILED = 3,
		PAUSED = 4,
		DISCONNECTED = 5,
		RECONNECTING = 6,
	};

private:
	String scene;
	String auth;
	bool established;

public:
	InworldSession();
	~InworldSession();

	virtual void _ready() override;
	virtual void _process(double_t delta) override;

public:
	void start();
	void stop();

	ConnectionState get_connection_state() const;
	bool get_established() const;

	void send_text(String p_brain, String p_text);
	void send_trigger(String p_brain, String p_name, Dictionary p_params);
  void start_audio_session(String p_brain);
	void stop_audio_session(String p_brain);
	void send_audio(String p_brain, const std::string& p_data);

#define DECLARE_CONNECT_EVENTS(Type)                                                                \
	void connect_##Type##_events(String p_brain, const Callable &p_callable, uint32_t p_flags = 0); \
	void disconnect_##Type##_events(String p_brain, const Callable &p_callable);

	DECLARE_CONNECT_EVENTS(text)
	DECLARE_CONNECT_EVENTS(audio)
	DECLARE_CONNECT_EVENTS(emotion)
	DECLARE_CONNECT_EVENTS(trigger)
	DECLARE_CONNECT_EVENTS(control)

#undef DECLARE_CONNECT_EVENTS

private:
	void set_scene(String p_scene);
	String get_scene() const;
	void set_auth(String p_auth);
	String get_auth() const;

private:
	Inworld::Client client;
	InworldPacketHandler *packet_handler;
	std::unordered_map<std::string, Inworld::AgentInfo> agent_info_map;
};

} // namespace godot

VARIANT_ENUM_CAST(InworldSession::ConnectionState)

#endif // INWORLD_SESSION_H
