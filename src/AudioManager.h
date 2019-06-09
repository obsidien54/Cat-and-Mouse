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

//************LIST OF AUDIO FILES AND LOCATIONS BEING USED************//
// UI_MainMenu.cpp contains the background music and its implementation
//player.cpp contains the loading of the powerup and the cheese pickup sound effect
//powerup and cheese pickup are played in game.cpp where the mouse eats the cheese or there is a pickup done

class AudioManager {
public:
	static AudioManager* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new AudioManager();
			return s_pInstance;
		}
		return s_pInstance;
	}

	//volume from 0-128
	void setMusicVolume(int volume); 

	bool load(std::string fileName, std::string id, sound_type type);
	void playSound(std::string id, int loop);
	void playMusic(std::string id, int loop);
private:
	static AudioManager* s_pInstance;

	std::map<std::string, Mix_Chunk*> m_sfxs;
	std::map<std::string, Mix_Music*> m_music;

	AudioManager();
	~AudioManager();

	AudioManager(const AudioManager&);

};
typedef AudioManager TheAudioManager;

#endif /* defined (__SoundManager__) */
