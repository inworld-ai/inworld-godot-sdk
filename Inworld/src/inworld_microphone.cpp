#include "inworld_microphone.h"

#include <godot_cpp/core/class_db.hpp>

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

using namespace godot;

void _on_recv_audio(ma_device *p_device, void *p_output, const void *p_input, ma_uint32 p_frame_count) {
	InworldMicrophone::AudioBuffer *audio_buffer = (InworldMicrophone::AudioBuffer *)p_device->pUserData;
	audio_buffer->write((uint8_t *)p_input, (uint32_t)p_frame_count * 2);
}

void InworldMicrophone::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_hot", "hot"), &InworldMicrophone::set_hot);
	ClassDB::bind_method(D_METHOD("get_hot"), &InworldMicrophone::get_hot);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "hot"), "set_hot", "get_hot");
}

InworldMicrophone::InworldMicrophone() :
		Object{}, capture_device{ nullptr } {
	capture_device = new ma_device;
	ma_device_config device_config;
	device_config = ma_device_config_init(ma_device_type_capture);
	device_config.capture.format = ma_format_s16;
	device_config.capture.channels = 1;
	device_config.sampleRate = 16000;
	device_config.dataCallback = _on_recv_audio;
	device_config.pUserData = &audio_buffer;

	if (ma_device_init(NULL, &device_config, capture_device) != MA_SUCCESS) {
		UtilityFunctions::push_warning(String("Failed to init audio capture device!"), __FUNCTION__, __FILE__, __LINE__);
		capture_device = nullptr;
	}
}

InworldMicrophone::~InworldMicrophone() {
	if (capture_device != nullptr) {
		ma_device_uninit(capture_device);
		delete capture_device;
		capture_device = nullptr;
	}
}

void InworldMicrophone::set_hot(bool p_hot) {
	if (p_hot == (bool)ma_device_is_started(capture_device)) {
		return;
	}
	p_hot ? ma_device_start(capture_device) : ma_device_stop(capture_device);
}

bool InworldMicrophone::get_hot() const {
	return (bool)ma_device_is_started(capture_device);
}

uint32_t InworldMicrophone::AudioBuffer::size() const {
	return buffer.size();
}

#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

void InworldMicrophone::AudioBuffer::read(uint8_t *p_out, uint32_t p_size) {
	if (mutex.try_lock()) {
		uint32_t to_read = min(buffer.size(), p_size);
		memcpy(p_out, buffer.ptrw(), to_read);

		memcpy(buffer.ptrw(), buffer.ptrw() + to_read, (buffer.size() - to_read));
		buffer.resize(buffer.size() - to_read);
		mutex.unlock();
	}
}

void InworldMicrophone::AudioBuffer::write(uint8_t *p_in, uint32_t p_size) {
	mutex.lock();
	uint32_t prev_size = buffer.size();
	buffer.resize(buffer.size() + p_size);
	memcpy(buffer.ptrw() + prev_size, p_in, p_size);
	mutex.unlock();
}
