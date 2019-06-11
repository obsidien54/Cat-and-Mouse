#include <cmath>
#include <iostream>
#include "Game.h"
#include <fstream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "PowerUp.h"
#include "AudioManager.h"
#include <random>
#include <ctime>


Game::Game() 
{
	m_fps = (Uint64)round(1 / (long double)FPS * 1000);
}

bool Game::Init(SDL_Renderer* m_pRenderer) 
{
	BuildBackgroundLayer();
	BuildForegroundLayer();
	SetUpTileVariables();
	srand(time(0));

	CreateGameObjects();

	m_bRunning = true;


	SDL_Surface* tileSurface = IMG_Load("../Assets/textures/Tiles.png");
	SDL_Surface* playerSurface = IMG_Load("../Assets/textures/mouse.png");
	SDL_Surface* ghostsSurface = IMG_Load("../Assets/textures/Cats.png");
	m_pTileTexture = SDL_CreateTextureFromSurface(m_pRenderer, tileSurface);
	m_pPlayerTexture = SDL_CreateTextureFromSurface(m_pRenderer, playerSurface);
	m_pGhostsTexture = SDL_CreateTextureFromSurface(m_pRenderer, ghostsSurface);
	SDL_FreeSurface(tileSurface);
	SDL_FreeSurface(playerSurface);
	SDL_FreeSurface(ghostsSurface);
	if (m_pTileTexture != nullptr) // One of the pointers are checked as an example
	{
		std::cout << "Pixel maps creation success!" << std::endl;
	}
	TheTextureManager::Instance()->load("../Assets/textures/Game_Over.png",
		"Game_Over", SDL_Manager::GetInstance()->GetRenderer());
					
	m_pFont = TTF_OpenFont("../Assets/text/junegull.ttf", 24);
	std::cout << "Font creation success!" << std::endl;
	

	return true;
}

void Game::BuildBackgroundLayer()
{
	// build background layer
	std::ifstream bgFile("../Assets/bg.txt");
	if (!bgFile) {
		std::cout << "bg file not detected" << std::endl;
	}

	for (int row = 0; row < ROWS; row++) {
		for (int col = 0; col < COLS; col++) {
			char i;
			bgFile >> i;
			m_bg.m_Map[row][col].SetSrc(i);
			m_bg.m_Map[row][col].SetDst({ TILESIZE * col, TILESIZE * row, TILESIZE, TILESIZE });
		}
	}
	bgFile.close();
}

void Game::CreateGameObjects()
{
	// Spawn Player and Ghosts
	m_pPlayer = new Player({ 0, 0, SPRITESIZE, SPRITESIZE }, { TILESIZE * 11, TILESIZE * 13, TILESIZE, TILESIZE });
	m_pCats[0] = new Cat({ 0, 0, SPRITESIZE, SPRITESIZE }, { TILESIZE * 3, TILESIZE * 3, TILESIZE, TILESIZE });
	m_pCats[1] = new Cat({ 192, 0, SPRITESIZE, SPRITESIZE }, { TILESIZE * 19, TILESIZE * 3, TILESIZE, TILESIZE });
	m_pCats[2] = new Cat({ 384, 0, SPRITESIZE, SPRITESIZE }, { TILESIZE * 3, TILESIZE * 19, TILESIZE, TILESIZE });
	m_pCats[3] = new Cat({ 576, 0, SPRITESIZE, SPRITESIZE }, { TILESIZE * 19, TILESIZE * 19, TILESIZE, TILESIZE });

	m_pCats[0]->SetPriority(CatDirection::C_UP, CatDirection::C_LEFT, CatDirection::C_DOWN, CatDirection::C_RIGHT);
	m_pCats[1]->SetPriority(CatDirection::C_DOWN, CatDirection::C_LEFT, CatDirection::C_UP, CatDirection::C_RIGHT);
	m_pCats[2]->SetPriority(CatDirection::C_DOWN, CatDirection::C_RIGHT, CatDirection::C_UP, CatDirection::C_LEFT);
	m_pCats[3]->SetPriority(CatDirection::C_UP, CatDirection::C_RIGHT, CatDirection::C_DOWN, CatDirection::C_LEFT);
}


void Game::SetUpTileVariables()
{
	std::ifstream varFile("../Assets/Level0Variables.txt");
	for (int row = 0; row < ROWS; row++) {
		for (int col = 0; col < COLS; col++) {
			char temp;
			varFile >> temp;
			m_level.m_Map[row][col].SetTileVariables(temp);
		}
	}
	varFile.close();
}

void Game::BuildForegroundLayer()
{
	// Build tilemap

	std::ifstream mapFile("../Assets/Level0Map.txt");
	if (!mapFile) {
		std::cout << "bg file not detected" << std::endl;
	}

	for (int row = 0; row < ROWS; row++) {
		for (int col = 0; col < COLS; col++) {
			char temp;
			mapFile >> temp;
			m_level.m_Map[row][col].SetSrc(temp);
			m_level.m_Map[row][col].SetDst({ TILESIZE * col, TILESIZE * row, TILESIZE, TILESIZE });
		}
	}
	mapFile.close();
}

Player* Game::GetPlayer()
{
	return m_pPlayer;
}
Level* Game::GetLevel()
{
	return &m_level;
}

Input_Manager* Game::GetInputManager()
{
	return &m_Input;
}


void Game::Update() {
	HandlePlayerAndCatInteractions();
	m_pPlayer->update();
	UpdateCats();

	//std::cout << "Currently In Wall " << m_pPlayer->isCurrentlyInWall() << std::endl;
	//For debugging purposes
	/*cout << "Is Moving: " <<  m_pPlayer->isMoving() << endl;
	cout << "Destination X: " << m_pPlayer->GetDestinationX() << endl;
	cout << "Rect X: " << m_pPlayer->GetDst().x << endl;
	cout << "Destination Y: " << m_pPlayer->GetDestinationY() << endl;
	cout << "Rect Y: " << m_pPlayer->GetDst().y << endl;*/
}

void Game::ChangeCatsToWhite()
{
	if (!m_pCats[0]->IsWhite())
	{
		for (int i = 0; i < 4; i++)
		{
			m_pCats[i]->ResetCell();
			m_pCats[i]->SetSrc({ 768,0,SPRITESIZE,SPRITESIZE });
		}
	}
}

void Game::ChangeCatsToOriginalColors()
{
	for (int i = 0; i < 4; i++)
	{
		if (!m_pCats[i]->IsDead())
		{
			m_pCats[i]->ResetCell();
			m_pCats[i]->SetSrc({ i * 192,0,SPRITESIZE,SPRITESIZE });  //turn cats back to original color
		}
	}
}

void Game::HandlePlayerAndCatInteractions() {
	// Handles player eating a cat
	for (int i = 0; i < 4; i++) {
		// If player collides with cat..
		if (SDL_HasIntersection(m_pPlayer->GetDstP(), m_pCats[i]->GetDstP())) {
			// Destroy cat if powered up
			if (!m_pCats[i]->IsDead())
			{
				if (m_pPlayer->GetAbility() == Ability::DEFEAT_CATS)
				{
					m_pCats[i]->Die(); // Cats need to be respawned in the center
					m_scoreNum += 100;
				}
				// Else player dies
				else
				{
					Game::GetInstance()->PlayerLost();
					m_livesNum -= 1;
					if (m_livesNum == 0)
					{
						SDL_RenderClear(SDL_Manager::GetInstance()->GetRenderer());
						TheTextureManager::Instance()->draw("Game_Over",
							SDL_Manager::GetInstance()->GetRenderer(), 23 * TILESIZE, 23 * TILESIZE);
						SDL_RenderPresent(SDL_Manager::GetInstance()->GetRenderer());
						Game::GetInstance()->SetScore(0);

						SDL_Delay(3000);
						Game::GetInstance()->SetScore(Game::GetInstance()->GetScore() - 400);
						m_pPlayer->Die();
						m_livesNum = 2;
						m_bRunning = false;
					}
				}
			}
		}
	}
}

void Game::IncrementScore(int score)
{
	m_scoreNum += score;
}
void Game::SetScore(int score)
{
	m_scoreNum = score;
}
int Game::GetScore()
{
	return m_scoreNum;
}

void Game::SetAbilityStartTimer(Uint32 time)
{
	m_abilityStartTimer = time;
}

Uint32 Game::GetAbilityStartTimer()
{
	return m_abilityStartTimer;
}

void Game::GamePaused()
{
	SDL_Event event;
	bool temp = false;

	while (SDL_PollEvent(&event) != 0 && !temp)
	{
		if (event.type == SDL_KEYDOWN)
		{
			temp = true;
		}
	}
}

void Game::PlayerWon()
{
	std::cout << "The player has won" << std::endl;
	// load picture in the contructor
	// Render picture
	SDL_Delay(3000);
	Game::GetInstance()->SetScore(Game::GetInstance()->GetScore() - 400);
	Game::GetInstance()->StopRunning();
}

void Game::PlayerLost()
{
	std::cout << "The player has lost" << std::endl;
	// load picture in the contructor
	// Render picture
	m_pPlayer->SetDst(TILESIZE * 11, TILESIZE * 13);
	std::cout << "The cat's destination x = " << m_pCats[0]->GetDestinationX() << std::endl;

	m_pCats[0]->SetDst(TILESIZE * 3, TILESIZE * 3);
	m_pCats[1]->SetDst(TILESIZE * 19, TILESIZE * 3);
	m_pCats[2]->SetDst(TILESIZE * 3, TILESIZE * 19);
	m_pCats[3]->SetDst(TILESIZE * 19, TILESIZE * 19);
	

	std::cout << "The cat's destination x = " << m_pCats[0]->GetDestinationX() << std::endl;
	if (m_livesNum == 0)
	{
		SDL_RenderClear(SDL_Manager::GetInstance()->GetRenderer());
		TheTextureManager::Instance()->draw("Game_Over",
			SDL_Manager::GetInstance()->GetRenderer(), 23 * TILESIZE, 23 * TILESIZE);
		SDL_RenderPresent(SDL_Manager::GetInstance()->GetRenderer());
		Game::GetInstance()->SetScore(0);
	}
	SDL_Delay(3000);
	
}


void Game::UpdateCats()
{
	m_pCats[0]->Update();
	m_pCats[1]->Update();
	m_pCats[2]->Update();
	m_pCats[3]->Update();
}

void Game::Render(SDL_Renderer* m_pRenderer) {
	SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
	SDL_RenderClear(m_pRenderer);
	// draw background tile map
	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLS; col++) {
			SDL_RenderCopy(m_pRenderer, m_pTileTexture, m_bg.m_Map[row][col].GetSrcP(), m_bg.m_Map[row][col].GetDstP());
		}
	}
	// Render map
	for (int row = 0; row < ROWS; row++) {
		for (int col = 0; col < COLS; col++) {
			SDL_RenderCopy(m_pRenderer, m_pTileTexture, m_level.m_Map[row][col].GetSrcP(), m_level.m_Map[row][col].GetDstP());
		}
	}

	// Render ghosts
	for (int i = 0; i < 4; i++) {
		SDL_RenderCopyEx(m_pRenderer, m_pGhostsTexture, m_pCats[i]->GetSrcP(), m_pCats[i]->GetDstP(),m_pCats[i]->angle,&m_pCats[i]->center,SDL_FLIP_NONE);
	}

	// Render player
	SDL_RenderCopyEx(m_pRenderer, m_pPlayerTexture, m_pPlayer->GetSrcP(), m_pPlayer->GetDstP(),m_pPlayer->GetPlayerAngle(),&m_pPlayer->center,SDL_FLIP_NONE);

	//render text
	//lives text creation
	m_fontTextLives = "Lives: " + std::to_string(m_livesNum);
	m_pTextSurfaceLives = TTF_RenderText_Solid(m_pFont, m_fontTextLives.c_str(), m_colour);
	m_pTextTextureLives = SDL_CreateTextureFromSurface(m_pRenderer, m_pTextSurfaceLives);
	SDL_FreeSurface(m_pTextSurfaceLives);
	SDL_QueryTexture(m_pTextTextureLives, NULL, NULL, &m_textRectLives.w, &m_textRectLives.h);
	//level text creation
	m_fontTextLevel = "Level: " + std::to_string(m_levelNum);
	m_pTextSurfaceLevel = TTF_RenderText_Solid(m_pFont, m_fontTextLevel.c_str(), m_colour);
	m_pTextTextureLevel = SDL_CreateTextureFromSurface(m_pRenderer, m_pTextSurfaceLevel);
	SDL_FreeSurface(m_pTextSurfaceLevel);
	SDL_QueryTexture(m_pTextTextureLevel, NULL, NULL, &m_textRectLevel.w, &m_textRectLevel.h);
	//score text creation
	m_fontTextScore = "Score: " + std::to_string(m_scoreNum);
	m_pTextSurfaceScore = TTF_RenderText_Solid(m_pFont, m_fontTextScore.c_str(), m_colour);
	m_pTextTextureScore = SDL_CreateTextureFromSurface(m_pRenderer, m_pTextSurfaceScore);
	SDL_FreeSurface(m_pTextSurfaceScore);
	SDL_QueryTexture(m_pTextTextureScore, NULL, NULL, &m_textRectScore.w, &m_textRectScore.h);
	//render out the texts
	SDL_RenderCopy(m_pRenderer, m_pTextTextureLives, NULL, &m_textRectLives);
	SDL_RenderCopy(m_pRenderer, m_pTextTextureLevel, NULL, &m_textRectLevel);
	SDL_RenderCopy(m_pRenderer, m_pTextTextureScore, NULL, &m_textRectScore);

	//destroy the textures so we can create new ones
	SDL_DestroyTexture(m_pTextTextureLives);
	SDL_DestroyTexture(m_pTextTextureLevel);
	SDL_DestroyTexture(m_pTextTextureScore);

	SDL_RenderPresent(m_pRenderer);
}

void Game::HandleEvents() {
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			m_bRunning = false;
			break;
		}
	}
}

void Game::Wake() {
	m_start = SDL_GetTicks();
}

void Game::Sleep() {
	m_end = SDL_GetTicks();
	m_delta = m_end - m_start;
	if (m_delta < m_fps) {
		SDL_Delay(m_fps - m_delta);
	}
}

void Game::Clean() {
	std::cout << "Cleaning game. Bye!" << std::endl;
	SDL_DestroyTexture(m_pTileTexture);
	SDL_DestroyTexture(m_pPlayerTexture);
	//SDL_DestroyWindow(m_pWindow);
	//SDL_DestroyRenderer(m_pRenderer);
	//IMG_Quit();
	//SDL_Quit();
}

