#include "inworldsession.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include <string>

#include "Client.h"
#include "Utils/Log.h"

namespace godot
{

  void InworldSession::_bind_methods()
  {
    ClassDB::bind_method(D_METHOD("start_session"), &InworldSession::start_session);
    ClassDB::bind_method(D_METHOD("send_text"), &InworldSession::send_text);

    ADD_SIGNAL(MethodInfo("got_text", PropertyInfo(Variant::OBJECT, "node"), PropertyInfo(Variant::STRING, "message")));
    ADD_SIGNAL(MethodInfo("got_connected", PropertyInfo(Variant::OBJECT, "node")));

    ClassDB::bind_method(D_METHOD("set_character", "character"), &InworldSession::set_character);
    ClassDB::bind_method(D_METHOD("get_character"), &InworldSession::get_character);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "character"), "set_character", "get_character");

    ClassDB::bind_method(D_METHOD("set_apikey", "apikey"), &InworldSession::set_apikey);
    ClassDB::bind_method(D_METHOD("get_apikey"), &InworldSession::get_apikey);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "apikey"), "set_apikey", "get_apikey");

    ClassDB::bind_method(D_METHOD("set_apisecret", "apisecret"), &InworldSession::set_apisecret);
    ClassDB::bind_method(D_METHOD("get_apisecret"), &InworldSession::get_apisecret);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "apisecret"), "set_apisecret", "get_apisecret");
  }

  InworldSession::InworldSession()
  {
    bConnected = false;
    
    Inworld::LogSetLoggerCallback([](const char *msg, int severity)
                                  {
    switch (severity) {
    case 0:
      UtilityFunctions::print(String(msg));
      break;
    case 1:
      //UtilityFunctions::printwarn(String(msg)); - missing warn function?
      UtilityFunctions::push_warning(String(msg), __FUNCTION__, __FILE__, __LINE__);
      break;
    case 2:
      UtilityFunctions::printerr(String(msg));
      UtilityFunctions::push_error(String(msg), __FUNCTION__, __FILE__, __LINE__);
      break;
    default:
      break;
    } });
  }

  InworldSession::~InworldSession() {}

  void InworldSession::_process(double_t delta)
  {
    Node::_process(delta);
    _client.Update();
  }

  void InworldSession::start_session()
  {
    set_process(true);

    Inworld::ClientOptions _client_options;

    _client_options.ServerUrl = "api-engine.inworld.ai:443";
    _client_options.PlayerName = "Player";

    _client_options.SceneName = character.utf8().get_data();
    _client_options.ApiKey = apikey.utf8().get_data();
    _client_options.ApiSecret = apisecret.utf8().get_data();

    _client_options.Capabilities.Animations = false;
    _client_options.Capabilities.Text = true;
    _client_options.Capabilities.Audio = true;
    _client_options.Capabilities.Emotions = true;
    _client_options.Capabilities.Gestures = true;
    _client_options.Capabilities.Interruptions = true;
    _client_options.Capabilities.Triggers = true;
    _client_options.Capabilities.EmotionStreaming = true;
    _client_options.Capabilities.SilenceEvents = true;
    _client_options.Capabilities.PhonemeInfo = true;
    _client_options.Capabilities.LoadSceneInSession = true;

    _client.InitClient(
        "Godot",
        "1.0.0",
        [this](Inworld::Client::ConnectionState ConnectionState)
        {
          std::string Error;
          int32_t Code;
          _client.GetConnectionError(Error, Code);

          Inworld::Log("Connection state: %d. Error: %s", static_cast<uint32_t>(ConnectionState), ARG_STR(Error));

          if (ConnectionState == Inworld::Client::ConnectionState::Disconnected)
          {
            _client.ResumeClient();
          }
        },
        [this](std::shared_ptr<Inworld::Packet> Packet)
        {
          Packet->Accept(*this);
        });

    Inworld::SessionInfo _session_info;
    _client.StartClient(_client_options, _session_info,
                        [this](std::vector<Inworld::AgentInfo> AgentInfos)
                        {
                          bConnected = true;
                          _agent_infos = AgentInfos;
                          emit_signal("got_connected", this);
                        });
  }

  void InworldSession::send_text(String text)
  {
    _client.SendTextMessage(_agent_infos[0].AgentId, text.utf8().get_data());
  }

  void InworldSession::Visit(const Inworld::TextEvent &Event)
  {
    Inworld::Log("%s: Text: %s", ARG_STR(Event._Routing._Source._Name), ARG_STR(Event.GetText()));
    emit_signal("got_text", this, String(Event.GetText().c_str()));
  }

  void InworldSession::Visit(const Inworld::CustomEvent &Event)
  {
    Inworld::Log("%s: Custom: %s", ARG_STR(Event._Routing._Source._Name), ARG_STR(Event.GetName()));
  }

  void InworldSession::Visit(const Inworld::CustomGestureEvent &Event)
  {
    Inworld::Log("%s: Custom gesture: %s", ARG_STR(Event._Routing._Source._Name), ARG_STR(Event.GetCustomGesture()));
  }

  void InworldSession::Visit(const Inworld::CancelResponseEvent &Event)
  {
  }

  void InworldSession::Visit(const Inworld::EmotionEvent &Event)
  {
    Inworld::Log("%s: Emotion: Behavior %d, Strengths %d", ARG_STR(Event._Routing._Source._Name), (int32_t)Event.GetEmotionalBehavior(), (int32_t)Event.GetStrength());
  }

  void InworldSession::Visit(const Inworld::ControlEvent &Event)
  {
    Inworld::Log("%s: Control: %d", ARG_STR(Event._Routing._Source._Name), (int32_t)Event.GetControlAction());
  }

  void InworldSession::Visit(const Inworld::SilenceEvent &Event)
  {
    Inworld::Log("%s: Silence: Duration %f", ARG_STR(Event._Routing._Source._Name), Event.GetDuration());
  }

  void InworldSession::Visit(const Inworld::DataEvent &Event)
  {
    Inworld::Log("%s: Data: Size %d", ARG_STR(Event._Routing._Source._Name), Event.GetDataChunk().size());
  }

}
