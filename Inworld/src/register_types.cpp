#include "register_types.h"

#include "inworld_character.h"
#include "inworld_packet_handler.h"
#include "inworld_player.h"
#include "inworld_session.h"

#include "Utils/Log.h"

#include <gdextension_interface.h>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

auto LogCallback = [](const char *msg, int severity) {
	switch (severity) {
		case 0:
			UtilityFunctions::print(String(msg));
			break;
		case 1:
			// UtilityFunctions::printwarn(String(msg)); - missing warn function?
			UtilityFunctions::push_warning(String(msg), __FUNCTION__, __FILE__, __LINE__);
			break;
		case 2:
			UtilityFunctions::printerr(String(msg));
			UtilityFunctions::push_error(String(msg), __FUNCTION__, __FILE__, __LINE__);
			break;
		default:
			break;
	}
};

void initialize_inworld_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	ClassDB::register_class<InworldSession>();
	ClassDB::register_class<InworldPacketHandler>();
	ClassDB::register_class<InworldCharacter>();
	ClassDB::register_class<InworldPlayer>();

	Inworld::LogSetLoggerCallback(LogCallback);
}

void uninitialize_inworld_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	Inworld::LogClearLoggerCallback();
}

extern "C" {
// Initialization.
GDExtensionBool GDE_EXPORT inworld_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
	godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

	init_obj.register_initializer(initialize_inworld_module);
	init_obj.register_terminator(uninitialize_inworld_module);
	init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

	return init_obj.init();
}
}