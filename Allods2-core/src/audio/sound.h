#pragma once

#include <iostream>
#include <string>
#include "../utils/stringutils.h"
#include <gorilla/ga.h>
#include <gorilla/gau.h>

struct ga_Sound;
struct ga_Handle;

namespace Allods2 {namespace sound {

	class Sound {
	private:

		std::string m_Name;
		std::string m_Filename;
		
		gc_uint32 m_Count;
		ga_Sound* m_Sound;
		ga_Handle* m_Handle;
		int32_t m_Position;

		bool m_Playing;
		float m_Gain;
	public:
		Sound(const std::string& name, const std::string& filename);
		~Sound();

		void Play();
		void Loop();
		void Pause();
		void Resume();
		void Stop();
		
		void SetGain(float gain);
		
		inline const bool IsPlaying() const { return m_Playing; }
		inline const float GetGain() const { return m_Gain; }
		inline const std::string& GetName() const { return m_Name; }
		inline const std::string& GetFileName() const { return m_Filename; }

		friend void destroy_on_finish(ga_Handle* in_handle, void* in_context);
		friend void loop_on_finish(ga_Handle* in_handle, void* in_context);

	};

} }