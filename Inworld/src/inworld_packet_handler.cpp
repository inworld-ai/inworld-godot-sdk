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

void InworldPacketHandler::Visit(const Inworld::AudioDataEvent &Event) {
	const String signal_name = String(Event._Routing._Source._Name.c_str()) + "_audio";
	if (has_signal(signal_name)) {
		std::string dataChunk = Event.GetDataChunk();
		uint8_t* data = (uint8_t*)(dataChunk.data());
		size_t dataSize = dataChunk.size();
		PackedByteArray *byteArray = new PackedByteArray();
		byteArray->resize(dataSize);
		for (size_t i = 0; i < dataSize; i++)
		{
			byteArray->push_back(data[i]);
		}

		emit_signal(signal_name, *byteArray);
	} else {
		UtilityFunctions::push_warning(String("Missing Signal:") + signal_name, __FUNCTION__, __FILE__, __LINE__);
	}
}
