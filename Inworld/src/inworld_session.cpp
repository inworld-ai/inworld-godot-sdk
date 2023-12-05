#include "inworld_session.h"

#include "inworld_packet_handler.h"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/os.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void InworldSession::_bind_methods() {
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
		Node{}, scene{}, auth{}, established{ false }, client{}, packet_handler{ nullptr }, agent_info_map{} {
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

void InworldSession::_ready() {
	Node::_ready();
}

void InworldSession::_process(double_t delta) {
	Node::_process(delta);
	client.Update();
}

void InworldSession::start() {
	packet_handler = memnew(InworldPacketHandler);

	Inworld::ClientOptions client_options;

	client_options.ServerUrl = "api-engine.inworld.ai:443";
	client_options.PlayerName = "Player";

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

					const String signal_name = String(agent_info.AgentId.c_str()) + "_text";
					Dictionary signal_param;
					signal_param["name"] = "text";
					signal_param["type"] = Variant::STRING;

					packet_handler->add_user_signal(signal_name, TypedArray<Dictionary>(signal_param));

					const String signal_name_audio = String(agent_info.AgentId.c_str()) + "_audio";
					Dictionary signal_param_audio;
					signal_param_audio["name"] = "audio";
					signal_param_audio["type"] = Variant::PACKED_BYTE_ARRAY;

					packet_handler->add_user_signal(signal_name_audio, TypedArray<Dictionary>(signal_param_audio));
				}

				established = true;
				emit_signal("established", established);
			});
}

void InworldSession::stop() {
	client.StopClient();

	established = false;
	emit_signal("established", established);

	if (packet_handler != nullptr) {
		memdelete(packet_handler);
		packet_handler = nullptr;
	}

	agent_info_map = {};
}

InworldSession::ConnectionState InworldSession::get_connection_state() const {
	return (InworldSession::ConnectionState)client.GetConnectionState();
}

bool InworldSession::get_established() const {
	return established;
}

void InworldSession::send_text(String p_brain, String p_text) {
	client.SendTextMessage(agent_info_map[p_brain.utf8().get_data()].AgentId, p_text.utf8().get_data());
}

void InworldSession::connect_text_events(String p_brain, const Callable &p_callable, uint32_t p_flags) {
	if (packet_handler == nullptr) {
		return;
	}
	const String signal_name = String(agent_info_map[p_brain.utf8().get_data()].AgentId.c_str()) + "_text";
	if (packet_handler->has_signal(signal_name) && !packet_handler->is_connected(signal_name, p_callable)) {
		packet_handler->connect(signal_name, p_callable, p_flags);
	}
}

void InworldSession::disconnect_text_events(String p_brain, const Callable &p_callable) {
	if (packet_handler == nullptr) {
		return;
	}
	const String signal_name = String(agent_info_map[p_brain.utf8().get_data()].AgentId.c_str()) + "_text";
	if (packet_handler->has_signal(signal_name) && packet_handler->is_connected(signal_name, p_callable)) {
		packet_handler->disconnect(signal_name, p_callable);
	}
}

void InworldSession::connect_audio_events(String p_brain, const Callable &p_callable, uint32_t p_flags) {
	if (packet_handler == nullptr) {
		return;
	}
	const String signal_name = String(agent_info_map[p_brain.utf8().get_data()].AgentId.c_str()) + "_audio";
	if (packet_handler->has_signal(signal_name) && !packet_handler->is_connected(signal_name, p_callable)) {
		packet_handler->connect(signal_name, p_callable, p_flags);
	}
}

void InworldSession::disconnect_audio_events(String p_brain, const Callable &p_callable) {
	if (packet_handler == nullptr) {
		return;
	}
	const String signal_name = String(agent_info_map[p_brain.utf8().get_data()].AgentId.c_str()) + "_audio";
	if (packet_handler->has_signal(signal_name) && packet_handler->is_connected(signal_name, p_callable)) {
		packet_handler->disconnect(signal_name, p_callable);
	}
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
