#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include "Input_Manager.h"
#include "TextureManager.h"
#include "SDL_Manager.h"

#include "Player.h"
#include "Cat.h"
#include <string>
#include "Level.h"
#define FPS 60
#define ROWS 23
#define COLS 23
#define TILESIZE 32
#define SPRITESIZE 64
#define LIFEINCREASETHRESHOLD 3000 //how much score you need to get a life

class Player;

class Game {
private:

	Input_Manager m_Input;
	Game();
	
	// Game Engine Variables
	bool m_bRunning;
	Uint32 m_start, m_end, m_delta, m_fps, m_abilityStartTimer;
	
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

	//countdown variables
	bool m_isCountdown = true;
	int m_countdownFrame = 0;
	void m_RenderCountdown();

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
	SDL_Rect m_textRectLevel = { 320,10 };
	//Score
	std::string m_fontTextScore;
	SDL_Surface* m_pTextSurfaceScore;
	SDL_Texture* m_pTextTextureScore;
	SDL_Rect m_textRectScore = { 580,10 };
	
public:
	static Game* GetInstance() {
		static Game* instance = new Game();
		return instance;
	}
	Player* GetPlayer();
	Level* GetLevel();
	Cat* GetCat(int num);
	Input_Manager* GetInputManager();

	bool Init(SDL_Renderer* m_pRenderer);
	void CreateGameObjects();
	void SetUpTileVariables();
	void SetUpTileVariables(int level);
	void BuildForegroundLayer();
	void BuildForegroundLayer(int level);
	void BuildBackgroundLayer();
	bool Running() { return m_bRunning; }
	void Update();
	void Render(SDL_Renderer* m_pRenderer);
	void HandleEvents();
	void ChangeCatsToWhite();
	void ChangeCatsToOriginalColors();
	void HandlePlayerAndCatInteractions();
	
	void IncrementLevel();
	void IncrementScore(int score);
	void SetScore(int score);
	int GetScore();
	void SetAbilityStartTimer(Uint32 time);
	Uint32 GetAbilityStartTimer();

	int GetLives();
	void IncrementLives();

	//alter the countdown settings
	void SetCountdown(bool b);

	int GetCurrLevel(); //get the currentl level map we are at

	void GamePaused();
	void PlayerWon();
	void PlayerLost();

	void ResetCat1();
	void ResetCat2();
	void ResetCat3();
	void ResetCat4();
	void ResetCats();

	void UpdateCats();
	void Clean();
	void Wake();
	void Sleep();
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
