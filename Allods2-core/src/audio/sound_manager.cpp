#include "sound_manager.h"


namespace Allods2 {namespace sound {

	gau_Manager* SoundManager::m_Manager = nullptr;
	ga_Mixer* SoundManager::m_Mixer = nullptr;

	std::vector<Sound*> SoundManager::m_Sounds;

	void SoundManager::Init() {
		gc_initialize(0);
		m_Manager = gau_manager_create();
		m_Mixer = gau_manager_mixer(m_Manager);
	}

	Sound* SoundManager::Add(Sound* sound) {
		m_Sounds.push_back(sound);
		return sound;
	}

	Sound* SoundManager::Get(const std::string& name) {
		for (Sound* sound : m_Sounds) {
			if (sound->GetName() == name)
				return sound;
		}
		return nullptr;
	}

	void SoundManager::Clean() {
		for (gc_uint32 i = 0; i < m_Sounds.size(); i++)
			delete m_Sounds[i];

		    gau_manager_destroy(m_Manager);
		    gc_shutdown();
	}

	void SoundManager::Update() {
		gau_manager_update(m_Manager);
	}

} }