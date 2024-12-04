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
	virtual ~InworldMicrophone();

	void set_hot(bool p_hot);
	bool get_hot() const;

	bool try_read(uint8_t *p_out, uint32_t p_size);

	friend void _on_recv_write(InworldMicrophone *microphone, uint8_t* p_input, uint32_t size);
private:
	void write(uint8_t *p_in, uint32_t p_size);

private:
	PackedByteArray buffer;
	ma_device *capture_device;
};

} // namespace godot

#endif // INWORLD_PLAYER_H
