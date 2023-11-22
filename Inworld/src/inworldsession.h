#ifndef INWORLD_SESSION_H
#define INWORLD_SESSION_H

#include <godot_cpp/classes/node.hpp>

#include "Client.h"
#include "Packets.h"

namespace godot
{

  class InworldSession : public Node, public Inworld::PacketVisitor
  {
    GDCLASS(InworldSession, Node)

  private:
    bool bConnected;

    String character;
    String apikey;
    String apisecret;

    Inworld::Client _client;

    std::vector<Inworld::AgentInfo> _agent_infos;

  protected:
    static void _bind_methods();

  public:
    InworldSession();
    ~InworldSession();

    void _process(double_t delta) override;

    void start_session();
    void send_text(String text);

    String get_character() const
    {
      return character;
    }
    void set_character(String in_character)
    {
      character = in_character;
    }

    String get_apikey() const
    {
      return apikey;
    }
    void set_apikey(String in_apikey)
    {
      apikey = in_apikey;
    }

    String get_apisecret() const
    {
      return apisecret;
    }
    void set_apisecret(String in_apisecret)
    {
      apisecret = in_apisecret;
    }

    virtual void Visit(const Inworld::TextEvent &Event) override;
    virtual void Visit(const Inworld::DataEvent &Event) override;
    virtual void Visit(const Inworld::SilenceEvent &Event) override;
    virtual void Visit(const Inworld::ControlEvent &Event) override;
    virtual void Visit(const Inworld::EmotionEvent &Event) override;
    virtual void Visit(const Inworld::CancelResponseEvent &Event) override;
    virtual void Visit(const Inworld::CustomGestureEvent &Event) override;
    virtual void Visit(const Inworld::CustomEvent &Event) override;
  };

}

#endif // INWORLD_SESSION_H
