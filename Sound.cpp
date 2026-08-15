#include "Sound.h"

namespace Reson {
	Sound::Sound(Engine &engine, const std::string &path)
		: m_path(path)
	{
		m_result = ma_sound_init_from_file(&engine.m_engine, path.c_str(), 0, NULL, NULL, &m_sound);
		if (m_result != MA_SUCCESS) {
			ma_sound_uninit(&m_sound);
			throw std::runtime_error("Failed to initialize sound");
		}
	}

	Sound::~Sound()
	{
		ma_sound_uninit(&m_sound);
	}

	void Sound::Start()
	{
		m_result = ma_sound_start(&m_sound);
	}

	void Sound::Stop()
	{
		m_result = ma_sound_stop(&m_sound);
	}

	void Sound::Restart()
	{
		m_result = ma_sound_seek_to_pcm_frame(&m_sound, 0);
	}

	void Sound::SetVolume(float volume)
	{
		ma_sound_set_volume(&m_sound, volume);
	}

	int Sound::GetVolume()
	{
		return static_cast<int>(ma_sound_get_volume(&m_sound) * 100);
	}

	ma_bool32 Sound::IsPlaying()
	{
		return ma_sound_is_playing(&m_sound);
	}

	ma_bool32 Sound::AtEnd()
	{
		return ma_sound_at_end(&m_sound);
	}

	ma_bool32 Sound::IsLoop()
	{
		return ma_sound_is_looping(&m_sound);
	}

	void Sound::Loop(Bool loop)
	{
		ma_sound_set_looping(&m_sound, loop);
	}

	float Sound::GetPitch()
	{
		return ma_sound_get_pitch(&m_sound);
	}

	ma_result Sound::GetResult() const
	{
		return m_result;
	}
}
