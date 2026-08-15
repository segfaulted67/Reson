#pragma once

#include "miniaudio/miniaudio.h"
#include <functional>
#include <stdexcept>

namespace Reson {
	using callback = std::function<void(ma_device*, void*, const void*, ma_uint32)>;

	class Config {
	public:
		Config(ma_device_type device_type, ma_format format, ma_uint32 channels, ma_uint32 sample_rate, callback data_callback);
		~Config() = default;
	private:
		ma_device_config Init(ma_device_type device_type);
		static void DataCallback(ma_device *device, void *output, const void *input, ma_uint32 frameCount);
	private:
		ma_device_config m_device_config;
		ma_format m_format;
		ma_uint32 m_channels;
		ma_uint32 m_sample_rate;
		callback m_callback;

		friend class Device;
	};

	class Device {
	public:
		Device(Config &config);
		~Device();

		void Start();
		void Stop();
	private:
		ma_device m_device;
		ma_result m_result;
	};
}
