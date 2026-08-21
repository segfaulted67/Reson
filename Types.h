#pragma once

#include <miniaudio/miniaudio.h>
#include <stdexcept>

namespace Reson {
	enum Bool {
		True = MA_TRUE,
		False = MA_FALSE,
	};

	enum DeviceType {
		Playback,
		Capture,
		Duplex,
		Loopback,
	};

	enum Format {
		Unknown,
		u8,
		s16,
		s24,
		s32,
		f32,
		Count,
	};

	inline constexpr ma_device_type ToMa(DeviceType type)
	{
		switch (type) {
		case Playback:
			return ma_device_type_playback;
		case Capture:
			return ma_device_type_capture;
		case Duplex:
			return ma_device_type_duplex;
		case Loopback:
			return ma_device_type_loopback;
		}
		throw std::invalid_argument("Invalid Device Type");
	}

	inline constexpr ma_format ToMa(Format format)
	{
		switch (format) {
		case Unknown:
			return ma_format_unknown;
		case u8:
			return ma_format_u8;
		case s16:
			return ma_format_s16;
		case s24:
			return ma_format_s24;
		case s32:
			return ma_format_s32;
		case f32:
			return ma_format_f32;
		case Count:
			return ma_format_count;
		}
		throw std::invalid_argument("Invalid Format");
	}
}
