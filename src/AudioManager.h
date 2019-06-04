#pragma once
#ifndef __SoundManager__
#define __SoundManager__

// Core Libraries
#include <iostream>
#include <string>
#include <map> 

#include <SDL_mixer.h>

enum sound_type
{
	SOUND_MUSIC = 0,
	SOUND_SFX = 1
};

class AudioManager {
public:

	AudioManager();

	bool load(std::string fileName, std::string id, sound_type type);

	static AudioManager* AudioList;

	Mix_Music* sMusic = nullptr;

	Mix_Chunk* Jump = nullptr;
	Mix_Chunk* Select = nullptr;
	Mix_Chunk* Return = nullptr;
	Mix_Chunk* Pause = nullptr;
	Mix_Chunk* PowerUp = nullptr;
	Mix_Chunk* Pellet = nullptr;


	/*static AudioManager* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new AudioManager();
			return s_pInstance;
		}
		return s_pInstance;
	}*/




	static AudioManager* Audiolist;

	std::map<std::string, Mix_Chunk*> m_sfxs;
	

	static AudioManager * GetInstance();
	void _Jump();
	void _Select();
	void _Return();
	void _Pause();
	void _PowerUp();
	void _Pellet();
	~AudioManager();

	//AudioManager(const AudioManager&);
};

typedef AudioManager TheAudioManager;

#endif /* defined (__SoundManager__) */
