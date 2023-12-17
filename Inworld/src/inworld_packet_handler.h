/**
 * Copyright 2023 Theai, Inc. (DBA Inworld)
 *
 * Use of this source code is governed by the Inworld.ai Software Development Kit License Agreement
 * that can be found in the LICENSE.md file or at https://www.inworld.ai/sdk-license
 */

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
	virtual void Visit(const Inworld::AudioDataEvent &Event) override;
	virtual void Visit(const Inworld::EmotionEvent &Event) override;
	virtual void Visit(const Inworld::CustomEvent &Event) override;
	virtual void Visit(const Inworld::ControlEvent &Event) override;
};

} // namespace godot

#endif // INWORLD_PACKET_HANDLER_H
