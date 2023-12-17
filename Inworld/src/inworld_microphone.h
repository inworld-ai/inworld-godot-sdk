/**
 * Copyright 2023 Theai, Inc. (DBA Inworld)
 *
 * Use of this source code is governed by the Inworld.ai Software Development Kit License Agreement
 * that can be found in the LICENSE.md file or at https://www.inworld.ai/sdk-license
 */

#ifndef INWORLD_MICROPHONE_H
#define INWORLD_MICROPHONE_H

#include <godot_cpp/classes/mutex.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/templates/vector.hpp>

struct ma_device;

namespace godot {

class InworldMicrophone : public Object {
	GDCLASS(InworldMicrophone, Object);

protected:
	static void _bind_methods();

public:
	InworldMicrophone();
	~InworldMicrophone();

	void set_hot(bool p_hot);
	bool get_hot() const;

	struct AudioBuffer {
	public:
		uint32_t size() const;
		void read(uint8_t *p_out, uint32_t p_size);
		void write(uint8_t *p_in, uint32_t p_size);

	private:
		Mutex mutex;
		PackedByteArray buffer;
	} audio_buffer;

private:
	ma_device *capture_device;
};

} // namespace godot

#endif // INWORLD_PLAYER_H
