#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "Player.h"
#include "Cat.h"
#include <string>
#include "Level.h"
#define FPS 60

class Game {
private:
	Game();
	

	// Game Engine Variables
	bool m_bRunning;
	const Uint8* m_iKeyStates;
	Uint32 m_start, m_end, m_delta, m_fps, m_powerUpStartTimer;
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	
	SDL_Texture* m_pTileTexture;
	SDL_Texture* m_pPickupTexture;
	SDL_Texture* m_pPlayerTexture;
	SDL_Texture* m_pGhostsTexture;

	// Game Object Variables
	Player* m_pPlayer; // Point to Player object
	Cat* m_pCats[4];

	// Game Variables
	int m_currLevel = 0;
	Level m_level;
	Level m_bg;
	//Scoring and level Tracking
	int m_scoreNum = 0;
	int m_levelNum = 1;
	int m_livesNum = 3;
	//font
	TTF_Font* m_pFont;
	SDL_Color m_colour = { 255,255,255 };
	//Lives font
	std::string m_fontTextLives;
	SDL_Surface* m_pTextSurfaceLives;
	SDL_Texture* m_pTextTextureLives;
	SDL_Rect m_textRectLives = { 10,10 };
	//Level
	std::string m_fontTextLevel;
	SDL_Surface* m_pTextSurfaceLevel;
	SDL_Texture* m_pTextTextureLevel;
	SDL_Rect m_textRectLevel = { 700,10 };
	//Score
	std::string m_fontTextScore;
	SDL_Surface* m_pTextSurfaceScore;
	SDL_Texture* m_pTextTextureScore;
	SDL_Rect m_textRectScore = { 1320,10 };
	
public:
	static Game* GetInstance() {
		static Game* instance = new Game();
		return instance;
	}
	Player* GetPlayer();
	Level* GetLevel();

	bool Init(SDL_Renderer* m_pRenderer);
	bool Running() { return m_bRunning; }
	void Update();
	void Render(SDL_Renderer* m_pRenderer);
	void HandleEvents();
	void HandlePlayerAbilities();
	void PlayerCatsInteractions();
	void PlayerMovements();
	void CatMovements();
	void Clean();
	void Wake();
	void Sleep();
	bool KeyDown(SDL_Scancode c);
	bool& IsRunningByRef()
	{
		return m_bRunning;
	}
	void StopRunning()
	{
		m_bRunning = false;
	}
	~Game() {};
};