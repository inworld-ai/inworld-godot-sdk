#include "inworld_packet_handler.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void InworldPacketHandler::_bind_methods() {
}

InworldPacketHandler::InworldPacketHandler() {
}

InworldPacketHandler::~InworldPacketHandler() {
}

void InworldPacketHandler::Visit(const Inworld::TextEvent &Event) {
	const String signal_name = String(Event._Routing._Source._Name.c_str()) + "_text";
	if (has_signal(signal_name)) {
		emit_signal(signal_name, String(Event.GetText().c_str()));
	} else {
		UtilityFunctions::push_warning(String("Missing Signal:") + signal_name, __FUNCTION__, __FILE__, __LINE__);
	}
}
