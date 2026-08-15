#include "Engine.h"

namespace Reson {
	Engine::Engine()
	{
		m_result = ma_engine_init(nullptr, &m_engine);
		if (m_result != MA_SUCCESS) {
			ma_engine_uninit(&m_engine);
			throw std::runtime_error("Failed to initialize engine");
		}
	}

	Engine::~Engine()
	{
		ma_engine_uninit(&m_engine);
	}

	ma_result Engine::GetResult() const
	{
		return m_result;
	}
}
