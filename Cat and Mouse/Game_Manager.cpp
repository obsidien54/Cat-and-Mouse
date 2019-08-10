

#include "Game_Manager.h"

Game_Manager::Game_Manager()
{
    m_bRunning = false;
    m_iCurrentLevel = ONE;
    m_fps = (Uint32)round(1 / (long double)FPS * 1000);
}
/*
Game_Manager* Game_Manager::GetInstance()
{
    static Game_Manager* instance = new Game_Manager();

    return instance;
}
*/
void Game_Manager::Start()
{
    if (m_iCurrentLevel == ONE)
    {
        Level1();
    }
    else if (m_iCurrentLevel == TWO)
    {
        Level3();
    }
    else if (m_iCurrentLevel == THREE)
    {
        Level3();
    }
    else
    {
        cout << "Current Level not found." << endl;
    }
}

void Game_Manager::Level1()
{
    /*
    while () // GameLoop goes here
    {
        // 60 FPS Wake()
        // Render Map and characters
        // Get Input
        // Update Movement of all objects and their interactions
        // 60 FPS Sleep ()
    }
    // Updates High Scores
    // Goes to Levels Menu
    */
}

void Game_Manager::Level2()
{

}

void Game_Manager::Level3()
{

}

void Game_Manager::Wake()
{
	m_start = SDL_GetTicks();
}

void Game_Manager::Sleep()
{
	m_end = SDL_GetTicks();
	m_delta = m_end - m_start;

	if (m_delta < m_fps)
    {
		SDL_Delay(m_fps - m_delta);
	}
}



Game_Manager::~Game_Manager()
{

}