#include "register_types.h"

#include "inworld_character.h"
#include "inworld_event.h"
#include "inworld_message.h"
#include "inworld_microphone.h"
#include "inworld_packet_handler.h"
#include "inworld_player.h"
#include "inworld_session.h"
#include "inworld_talk_queue.h"

#include "Utils/Log.h"

#include <gdextension_interface.h>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

auto LogInfoCallback = [](const char *msg) {
	UtilityFunctions::print(String(msg));
};

auto LogWarnCallback = [](const char *msg) {
	// UtilityFunctions::printwarn(String(msg)); - missing warn function?
	UtilityFunctions::push_warning(String(msg), __FUNCTION__, __FILE__, __LINE__);
};

auto LogErrorCallback = [](const char *msg) {
	UtilityFunctions::printerr(String(msg));
	UtilityFunctions::push_error(String(msg), __FUNCTION__, __FILE__, __LINE__);
};

void initialize_inworld_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	ClassDB::register_class<InworldSession>();
	ClassDB::register_class<InworldPacketHandler>();
	ClassDB::register_class<InworldCharacter>();
	ClassDB::register_class<InworldPlayer>();

	ClassDB::register_class<InworldMicrophone>();

	ClassDB::register_abstract_class<InworldEvent>();
	ClassDB::register_class<InworldEventText>();
	ClassDB::register_class<InworldEventData>();
	ClassDB::register_class<InworldEventDataAudio>();
	ClassDB::register_class<InworldEventDataAudio::Phoneme>();
	ClassDB::register_class<InworldEventEmotion>();
	ClassDB::register_class<InworldEventTrigger>();
	ClassDB::register_class<InworldEventControl>();
	ClassDB::register_class<InworldEventSceneStatus>();

	ClassDB::register_abstract_class<InworldMessage>();
	ClassDB::register_class<InworldMessageTalk>();
	ClassDB::register_class<InworldMessageTalk::Viseme>();
	ClassDB::register_class<InworldMessageSpeechToText>();
	ClassDB::register_class<InworldMessageEmotion>();
	ClassDB::register_class<InworldMessageTrigger>();
	ClassDB::register_class<InworldMessageControl>();

	ClassDB::register_class<InworldTalkQueue>();

	Inworld::SetLogCallbacks(LogInfoCallback, LogWarnCallback, LogErrorCallback);
}

void uninitialize_inworld_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	Inworld::ClearLogCallbacks();
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
