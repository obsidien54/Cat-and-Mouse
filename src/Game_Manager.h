#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <iostream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#define FPS 60

using namespace std;

enum Levels
{
    ONE,
    TWO,
    THREE,
    NUM_OF_LEVELS
};

class Game_Manager
{
private:
    
    unsigned short m_iCurrentLevel;
    Uint32 m_start, m_end, m_delta, m_fps; //  m_powerUpStartTimer;	 
    
    
	
public:
	bool m_bRunning;

    Game_Manager();
    //static Game_Manager* GetInstance();

    void Start ();

    void Level1();
    void Level2();
    void Level3();

    bool& IsRunning()
    {
        return m_bRunning;
    }

    void Wake(); // FPS
	void Sleep(); // FPS
    ~Game_Manager();
};

#endif