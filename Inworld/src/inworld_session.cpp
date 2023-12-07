#include "inworld_session.h"

#include "inworld_packet_handler.h"
#include "inworld_player.h"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/os.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void InworldSession::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_player", "player"), &InworldSession::set_player);
	ClassDB::bind_method(D_METHOD("get_player"), &InworldSession::get_player);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "player", PROPERTY_HINT_NODE_TYPE, "InworldPlayer"), "set_player", "get_player");

	ClassDB::bind_method(D_METHOD("set_scene", "scene"), &InworldSession::set_scene);
	ClassDB::bind_method(D_METHOD("get_scene"), &InworldSession::get_scene);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "scene"), "set_scene", "get_scene");

	ClassDB::bind_method(D_METHOD("set_auth", "auth"), &InworldSession::set_auth);
	ClassDB::bind_method(D_METHOD("get_auth"), &InworldSession::get_auth);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "auth"), "set_auth", "get_auth");

	ClassDB::bind_method(D_METHOD("start"), &InworldSession::start);
	ClassDB::bind_method(D_METHOD("stop"), &InworldSession::stop);

	ClassDB::bind_method(D_METHOD("get_connection_state"), &InworldSession::get_connection_state);
	ADD_SIGNAL(MethodInfo("connection_state_changed", PropertyInfo(Variant::INT, "connection_state")));

	ClassDB::bind_method(D_METHOD("get_connected"), &InworldSession::get_connected);
	ADD_SIGNAL(MethodInfo("connected", PropertyInfo(Variant::BOOL, "connected")));

	ClassDB::bind_method(D_METHOD("get_established"), &InworldSession::get_established);
	ADD_SIGNAL(MethodInfo("established", PropertyInfo(Variant::BOOL, "established")));

	BIND_ENUM_CONSTANT(IDLE);
	BIND_ENUM_CONSTANT(CONNECTING);
	BIND_ENUM_CONSTANT(CONNECTED);
	BIND_ENUM_CONSTANT(FAILED);
	BIND_ENUM_CONSTANT(PAUSED);
	BIND_ENUM_CONSTANT(DISCONNECTED);
	BIND_ENUM_CONSTANT(RECONNECTING);
}

InworldSession::InworldSession() :
		Node{}, player{ nullptr }, scene{}, auth{}, established{ false }, connected{ false }, client{}, packet_handler{ nullptr }, agent_info_map{} {
	Inworld::SdkInfo sdk_info{
		"godot",
		std::string(((String)Engine::get_singleton()->get_version_info()["string"]).utf8()),
		"1.0.0",
		std::string(OS::get_singleton()->get_name().utf8()),
	};

	client.InitClient(
			sdk_info,
			[this](Inworld::Client::ConnectionState p_connection_state) {
				const InworldSession::ConnectionState connection_state = (InworldSession::ConnectionState)p_connection_state;
				set_process(connection_state != ConnectionState::IDLE);

				emit_signal("connection_state_changed", connection_state);

				const bool new_connected = connection_state == ConnectionState::CONNECTED;
				if (connected != new_connected) {
					connected = new_connected;
					emit_signal("connected", connected);
				}

				if (connection_state == ConnectionState::DISCONNECTED) {
					client.ResumeClient();
				}
			},
			[this](std::shared_ptr<Inworld::Packet> Packet) {
				if (this->packet_handler != nullptr) {
					Packet->Accept(*this->packet_handler);
				}
			});
}

InworldSession::~InworldSession() {
	stop();
	client.DestroyClient();
}

void InworldSession::_process(double_t delta) {
	Node::_process(delta);
	client.Update();
}

void InworldSession::start() {
	packet_handler = memnew(InworldPacketHandler);

	Inworld::ClientOptions client_options;

	client_options.ServerUrl = "api-engine.inworld.ai:443";

	client_options.PlayerName = player == nullptr ? "Player" : player->get_name().utf8().get_data();
	client_options.SceneName = scene.utf8().get_data();
	client_options.Base64 = auth.utf8().get_data();

	client_options.Capabilities.Text = true;
	client_options.Capabilities.Audio = true;
	client_options.Capabilities.Emotions = true;
	client_options.Capabilities.Interruptions = true;
	client_options.Capabilities.Triggers = true;
	client_options.Capabilities.EmotionStreaming = true;
	client_options.Capabilities.LoadSceneInSession = true;

	client.StartClient(
			client_options, {},
			[this](const std::vector<Inworld::AgentInfo> &p_agent_infos) {
				for (const Inworld::AgentInfo &agent_info : p_agent_infos) {
					agent_info_map[agent_info.BrainName] = agent_info;

					const String signal_prefix = String(agent_info.AgentId.c_str());

#define DEFINE_USER_SIGNAL(Type)                                                                                            \
	{                                                                                                                       \
		Dictionary signal_param;                                                                                            \
		signal_param["name"] = #Type;                                                                                       \
		signal_param["type"] = Variant::OBJECT;                                                                             \
		packet_handler->add_user_signal(signal_prefix + String("_") + String(#Type), TypedArray<Dictionary>(signal_param)); \
	}

					DEFINE_USER_SIGNAL(text);
					DEFINE_USER_SIGNAL(audio);
					DEFINE_USER_SIGNAL(emotion);
					DEFINE_USER_SIGNAL(trigger);
					DEFINE_USER_SIGNAL(control);

#undef DEFINE_USER_SIGNAL
				}

				established = true;
				emit_signal("established", established);
			});
}

void InworldSession::stop() {
	established = false;
	emit_signal("established", established);

	client.StopClient();

	if (packet_handler != nullptr) {
		memdelete(packet_handler);
		packet_handler = nullptr;
	}

	agent_info_map = {};
}

InworldSession::ConnectionState InworldSession::get_connection_state() const {
	return (InworldSession::ConnectionState)client.GetConnectionState();
}

bool InworldSession::get_connected() const {
	return get_connection_state() == InworldSession::ConnectionState::CONNECTED && get_established();
}

bool InworldSession::get_established() const {
	return established;
}

String InworldSession::get_name(String p_brain) const {
	std::optional<Inworld::AgentInfo> agent = get_agent_from_brain(p_brain);
	return agent.has_value() ? String(agent.value().GivenName.c_str()) : String{};
}

void InworldSession::send_text(String p_brain, String p_text) {
	std::optional<Inworld::AgentInfo> agent = get_agent_from_brain(p_brain);
	if (!agent.has_value()) {
		return;
	}
	client.SendTextMessage(agent.value().AgentId, p_text.utf8().get_data());
}

void InworldSession::send_trigger(String p_brain, String p_name, Dictionary p_params) {
	std::optional<Inworld::AgentInfo> agent = get_agent_from_brain(p_brain);
	if (!agent.has_value()) {
		return;
	}
	std::unordered_map<std::string, std::string> map;
	for (int64_t i = 0; i < p_params.size(); ++i) {
		const String key = p_params.keys()[i].stringify();
		const String value = p_params.values()[i].stringify();
		map[key.utf8().get_data()] = value.utf8().get_data();
	}
	client.SendCustomEvent(agent.value().AgentId, p_name.utf8().get_data(), map);
}

void InworldSession::start_audio_session(String p_brain) {
	std::optional<Inworld::AgentInfo> agent = get_agent_from_brain(p_brain);
	if (!agent.has_value()) {
		return;
	}
	client.StartAudioSession(agent.value().AgentId);
}

void InworldSession::stop_audio_session(String p_brain) {
	std::optional<Inworld::AgentInfo> agent = get_agent_from_brain(p_brain);
	if (!agent.has_value()) {
		return;
	}
	client.StopAudioSession(agent.value().AgentId);
}

void InworldSession::send_audio(String p_brain, PackedByteArray &p_data) {
	std::optional<Inworld::AgentInfo> agent = get_agent_from_brain(p_brain);
	if (!agent.has_value()) {
		return;
	}
	std::string data((char *)p_data.ptrw(), p_data.size());
	client.SendSoundMessage(agent.value().AgentId, data);
}

void InworldSession::cancel_response(String p_brain, String p_interaction_id, Vector<String> p_utterance_ids) {
	std::optional<Inworld::AgentInfo> agent = get_agent_from_brain(p_brain);
	if (!agent.has_value()) {
		return;
	}
	std::vector<std::string> utterance_ids;
	for (const String &utterance_id : p_utterance_ids) {
		utterance_ids.push_back(utterance_id.utf8().get_data());
	}
	client.CancelResponse(agent.value().AgentId, p_interaction_id.utf8().get_data(), utterance_ids);
}

#define DEFINE_CONNECT_EVENTS(Type)                                                                                 \
	void InworldSession::connect_##Type##_events(String p_brain, const Callable &p_callable, uint32_t p_flags) {    \
		if (packet_handler == nullptr) {                                                                            \
			return;                                                                                                 \
		}                                                                                                           \
		const String signal_name = String(agent_info_map[p_brain.utf8().get_data()].AgentId.c_str()) + "_" + #Type; \
		if (packet_handler->has_signal(signal_name) && !packet_handler->is_connected(signal_name, p_callable)) {    \
			packet_handler->connect(signal_name, p_callable, p_flags);                                              \
		}                                                                                                           \
	}                                                                                                               \
                                                                                                                    \
	void InworldSession::disconnect_##Type##_events(String p_brain, const Callable &p_callable) {                   \
		if (packet_handler == nullptr) {                                                                            \
			return;                                                                                                 \
		}                                                                                                           \
		const String signal_name = String(agent_info_map[p_brain.utf8().get_data()].AgentId.c_str()) + "_" + #Type; \
		if (packet_handler->has_signal(signal_name) && packet_handler->is_connected(signal_name, p_callable)) {     \
			packet_handler->disconnect(signal_name, p_callable);                                                    \
		}                                                                                                           \
	}

DEFINE_CONNECT_EVENTS(text)
DEFINE_CONNECT_EVENTS(audio)
DEFINE_CONNECT_EVENTS(emotion)
DEFINE_CONNECT_EVENTS(trigger)
DEFINE_CONNECT_EVENTS(control)

#undef DEFINE_CONNECT_EVENTS

void InworldSession::set_player(InworldPlayer *p_player) {
	player = p_player;
}

InworldPlayer *InworldSession::get_player() const {
	return player;
}

void InworldSession::set_scene(String p_scene) {
	scene = p_scene;
}

String InworldSession::get_scene() const {
	return scene;
}

void InworldSession::set_auth(String p_auth) {
	auth = p_auth;
}
String InworldSession::get_auth() const {
	return auth;
}

std::optional<Inworld::AgentInfo> InworldSession::get_agent_from_brain(String p_brain) const {
	std::optional<Inworld::AgentInfo> agent;
	const std::string brain = p_brain.utf8().get_data();
	if (agent_info_map.find(brain) != agent_info_map.end()) {
		agent = agent_info_map[brain];
	}
	return agent;
}
