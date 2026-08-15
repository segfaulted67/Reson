#pragma once

#include "miniaudio/miniaudio.h"
#include "Engine.h"
#include "Utils.h"
#include <string>
#include <stdexcept>

namespace Reson {
	class Sound {
	public:
		Sound(Engine &engine, const std::string &path);
		~Sound();

		void Start();
		void Stop();
		void Restart();

		void SetVolume(float volume = 1.0f);
		int GetVolume();
		ma_bool32 IsPlaying();
		ma_bool32 AtEnd();
		ma_bool32 IsLoop();
		void Loop(Bool loop = True);
		float GetPitch();

		ma_result GetResult() const;
	private:
		ma_sound m_sound;
		ma_result m_result;
		std::string m_path;
	};
}
