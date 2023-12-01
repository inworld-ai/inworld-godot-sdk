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
	~InworldPacketHandler();

public:
	virtual void Visit(const Inworld::TextEvent &Event) override;
};

} // namespace godot

#endif // INWORLD_PACKET_HANDLER_H
