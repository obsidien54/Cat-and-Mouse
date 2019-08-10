#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <iostream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
//#include "Player.h"
//#include "Cat.h"
//#include <string>
//#include "Level.h"
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
    

	//SDL_Texture* m_pTileTexture;
	//SDL_Texture* m_pPickupTexture;
	//SDL_Texture* m_pPlayerTexture;
	//SDL_Texture* m_pGhostsTexture;

	//// Game Object Variables
	//Player* m_pPlayer; // Point to Player object
	//Cat* m_pCats[4];

	//// Game Variables
	//int m_currLevel = 0;
	//Level m_level;
	//Level m_bg;
	////Scoring and level Tracking
	//int m_scoreNum = 0;
	//int m_levelNum = 1;
	//int m_livesNum = 3;
	////font
	//TTF_Font* m_pFont;
	//SDL_Color m_colour = { 255,255,255 };
	////Lives font
	//std::string m_fontTextLives;
	//SDL_Surface* m_pTextSurfaceLives;
	//SDL_Texture* m_pTextTextureLives;
	//SDL_Rect m_textRectLives = { 10,10 };
	////Level
	//std::string m_fontTextLevel;
	//SDL_Surface* m_pTextSurfaceLevel;
	//SDL_Texture* m_pTextTextureLevel;
	//SDL_Rect m_textRectLevel = { 700,10 };
	////Score
	//std::string m_fontTextScore;
	//SDL_Surface* m_pTextSurfaceScore;
	//SDL_Texture* m_pTextTextureScore;
	//SDL_Rect m_textRectScore = { 1320,10 };
	
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