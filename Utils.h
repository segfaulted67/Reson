#pragma once

#include <iostream>
#include <cstdlib>
#include <numbers>
#include "miniaudio/miniaudio.h"

#define CHECK_SUCCESS(x, func, uinit)			\
	do {										\
		x = func;								\
		if (x != MA_SUCCESS) { 					\
			uinit;								\
			return x;							\
		}										\
	} while (0)

namespace Reson {
	constexpr float Pi = std::numbers::pi;
	constexpr float TwoPi = 2.0 * std::numbers::pi;

	enum Bool {
		True = MA_TRUE,
		False = MA_FALSE,
	};
	enum DeviceType {
		Playback = ma_device_type_playback,
		Capture = ma_device_type_capture,
		Duplex = ma_device_type_duplex,
		Loopback = ma_device_type_loopback
	};
	enum Format {
		Unknown = ma_format_unknown,
		u8 = ma_format_u8,
		s16 = ma_format_s16,
		s24 = ma_format_s24,
		s32 = ma_format_s32,
		f32 = ma_format_f32,
		Count = ma_format_count
	};
}
