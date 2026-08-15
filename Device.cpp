#include "Device.h"

namespace Reson {
	Config::Config(ma_device_type device_type, ma_format format, ma_uint32 channels, ma_uint32 sample_rate, callback data_callback)
		: m_format(format), m_channels(channels), m_sample_rate(sample_rate), m_callback(std::move(data_callback))
	{
		m_device_config = Init(device_type);
		m_device_config.playback.format = m_format;
		m_device_config.playback.channels = m_channels;
		m_device_config.sampleRate = m_sample_rate;
		m_device_config.dataCallback = DataCallback;
		m_device_config.pUserData = this;
	}

	ma_device_config Config::Init(ma_device_type device_type)
	{
		return ma_device_config_init(device_type);
	}

	void Config::DataCallback(ma_device *device, void *output, const void *input, ma_uint32 frameCount)
	{
		auto *config = static_cast<Config*>(device->pUserData);
		config->m_callback(device, output, input, frameCount);
	}

	Device::Device(Config &config)
	{
		m_result = ma_device_init(nullptr, &config.m_device_config, &m_device);
		if (m_result != MA_SUCCESS) {
			throw std::runtime_error("Unable to initialize device");
		}
	}

	Device::~Device()
	{
		ma_device_uninit(&m_device);
	}

	void Device::Start()
	{
		ma_device_start(&m_device);
	}

	void Device::Stop()
	{
		ma_device_stop(&m_device);
	}
}
