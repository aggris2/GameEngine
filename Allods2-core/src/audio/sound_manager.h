#pragma once

#include "sound.h"
#include <vector>
//#define GAU_THREAD_POLICY_MULTI 2
#include <gorilla/ga.h>
#include <gorilla/gau.h>

struct gau_Manager;
struct ga_Mixer;

namespace Allods2 {namespace sound {

	class SoundManager {
	private:
		friend class Sound;

		static gau_Manager* m_Manager;
		static ga_Mixer* m_Mixer;

		static std::vector<Sound*> m_Sounds;
	public:
		static void Init();
		static Sound* Add(Sound* sound);
		static Sound* Get(const std::string& name);
		static void Update();
		static void Clean();
	private:
		SoundManager() { }
	};

} }