#ifndef INWORLD_PACKET_HANDLER_H
#define INWORLD_PACKET_HANDLER_H

#include "Packets.h"

#include <godot_cpp/classes/object.hpp>

namespace godot {

class InworldPacketHandler : public Object, public Inworld::PacketVisitor {
	GDCLASS(InworldPacketHandler, Object)

protected:
	static void _bind_methods();

public:
	InworldPacketHandler();
	virtual ~InworldPacketHandler();

public:
	virtual void Visit(const Inworld::TextEvent &Event) override;
	virtual void Visit(const Inworld::AudioDataEvent &Event) override;
	virtual void Visit(const Inworld::EmotionEvent &Event) override;
	virtual void Visit(const Inworld::CustomEvent &Event) override;
	virtual void Visit(const Inworld::ControlEvent &Event) override;
};

} // namespace godot

#endif // INWORLD_PACKET_HANDLER_H
