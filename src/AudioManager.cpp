#include "AudioManager.h"
#include <iostream>
using namespace std;
AudioManager* AudioManager::AudioList = nullptr;

AudioManager::AudioManager()
{

	Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096);
	Mix_AllocateChannels(16);

	Jump = Mix_LoadWAV("../Assets/sounds/Jump.wav");
	PowerUp = Mix_LoadWAV("../Assets/sounds/POWERUP.WAV");
	Select = Mix_LoadWAV("../Assets/sounds/Select.wav");
	Pause = Mix_LoadWAV("../Assets/sounds/Pause.wav");
	Pellet = Mix_LoadWAV("../Assets/sounds/Pellet.wav");
	Return = Mix_LoadWAV("../Assets/sounds/Return.wav");
	if (!Jump)
	{
		cout << "JUMP ERROR!" << endl;
	}
	if (!PowerUp)
	{
		cout << "POWERUP ERROR!" << endl;
	}
	if (!Select)
	{
		cout << "SELECT ERROR!" << endl;
	}
	if (!Pause)
	{
		cout << "PAUSE ERROR!" << endl;
	}
	if (!Pellet)
	{
		cout << "PELLET ERROR!" << endl;
		cout << Mix_GetError() << std::endl;
	}
	if (!Return)
	{
		cout << "RETURN ERROR!" << endl;
	}

	Mix_VolumeMusic(100);
	Mix_Volume(-1, 128);

}

bool AudioManager::load(std::string fileName, std::string id, sound_type type)
{
	if (type == SOUND_MUSIC)
	{
		Mix_Music* pMusic = Mix_LoadMUS(fileName.c_str());
		if (pMusic == 0)
		{
			std::cout << "Could not load music: ERROR - " << Mix_GetError() << std::endl;
			return false;
		}

		return true;
	}
	else if (type == SOUND_SFX)
	{
		Mix_Chunk* pChunk = Mix_LoadWAV(fileName.c_str());
		if (pChunk == 0)
		{
			std::cout << "Could not load SFX: ERROR - " << Mix_GetError() << std::endl;
			return false;
		}

		m_sfxs[id] = pChunk;
		return true;
	}
	return false;
}

AudioManager* AudioManager::GetInstance()
{
	if (AudioList == nullptr)
	{
		AudioList = new AudioManager;

	}
	return AudioList;
}


void AudioManager::_Jump()
{
	Mix_PlayChannel(3, Jump, 0);
}
void AudioManager::_Select()
{
	Mix_PlayChannel(1, Select, 0);
}
void AudioManager::_Return()
{
	Mix_PlayChannel(5, Return, 0);
}
void AudioManager::_Pause()
{
	Mix_PlayChannel(2, Pause, 0);

}
void AudioManager::_PowerUp()
{
	Mix_PlayChannel(4, PowerUp, 0);
}
void AudioManager::_Pellet()
{
	Mix_PlayChannel(1, Pellet, 0);
}

AudioManager::~AudioManager()
{
}




