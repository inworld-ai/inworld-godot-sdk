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
	UtilityFunctions::push_warning(String("Received Text"), __FUNCTION__, __FILE__, __LINE__);
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
		const uint8_t* data = (uint8_t*)(dataChunk.data());

		Array *dataArray = new Array();
		dataArray->resize(dataChunk.size());
		for (size_t i = 0; i < dataChunk.size(); i++)
		{
			dataArray->push_back(data[i]);
		}

		PackedByteArray *byteArray = new PackedByteArray(*dataArray);
		emit_signal(signal_name, *byteArray);
	} else {
		UtilityFunctions::push_warning(String("Missing Signal:") + signal_name, __FUNCTION__, __FILE__, __LINE__);
	}
}
