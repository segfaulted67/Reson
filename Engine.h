#pragma once

#include "miniaudio/miniaudio.h"
#include "Utils.h"
#include <stdexcept>

namespace Reson {
	class Engine {
	public:
		Engine();
		~Engine();
		ma_result GetResult() const;
	private:
		ma_engine m_engine;
		ma_result m_result;

		friend class Sound;
	};
}
