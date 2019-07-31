#include <cmath>
#include <iostream>
#include "Game.h"
#include <fstream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "PowerUp.h"
#include "AudioManager.h"
#include "UI_Manager.h"
#include <random>
#include <ctime>


Game::Game() 
{
	m_fps = (Uint64)round(1 / (long double)FPS * 1000);
}

bool Game::Init(SDL_Renderer* m_pRenderer) 
{
	//BuildBackgroundLayer();
	BuildForegroundLayer(0);
	SetUpTileVariables(0);
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
	TheTextureManager::Instance()->load("../Assets/textures/darkk.png",
		"Darkness", SDL_Manager::GetInstance()->GetRenderer());

	TheTextureManager::Instance()->load("../Assets/textures/background.png",
		"background main", SDL_Manager::GetInstance()->GetRenderer());

	//load countdown images
	TheTextureManager::Instance()->load("../Assets/textures/countdown_5.png",
		"count 5", SDL_Manager::GetInstance()->GetRenderer());
	TheTextureManager::Instance()->load("../Assets/textures/countdown_4.png",
		"count 4", SDL_Manager::GetInstance()->GetRenderer());
	TheTextureManager::Instance()->load("../Assets/textures/countdown_3.png",
		"count 3", SDL_Manager::GetInstance()->GetRenderer());
	TheTextureManager::Instance()->load("../Assets/textures/countdown_2.png",
		"count 2", SDL_Manager::GetInstance()->GetRenderer());
	TheTextureManager::Instance()->load("../Assets/textures/countdown_1.png",
		"count 1", SDL_Manager::GetInstance()->GetRenderer());

	//LOAD IN SOUND EFFECTS
	TheAudioManager::Instance()->load("../Assets/sound/GameOver.wav",
		"GameOver", sound_type::SOUND_SFX);

	//player death sound
	TheAudioManager::Instance()->load("../Assets/sound/Death.wav",
		"Death", sound_type::SOUND_SFX);

	TheAudioManager::Instance()->load("../Assets/sound/CatDeath.wav",
		"CatDeath", sound_type::SOUND_SFX);

	//play upon level completion
	TheAudioManager::Instance()->load("../Assets/sound/Victory.wav",
		"Victory", sound_type::SOUND_SFX);

	//load the sound files that revolve around the player. WHen using them just use the audiomanager play function
	TheAudioManager::Instance()->load("../Assets/sound/Cheese.wav",
		"cheese", sound_type::SOUND_SFX);

	TheAudioManager::Instance()->load("../Assets/sound/Powerup4.wav",
		"powerup", sound_type::SOUND_SFX);

	TheAudioManager::Instance()->load("../Assets/sound/WallAbility.wav",
		"wall ability", sound_type::SOUND_SFX);

	TheAudioManager::Instance()->load("../Assets/sound/EnterWall.wav",
		"enter wall", sound_type::SOUND_SFX);

	TheAudioManager::Instance()->load("../Assets/sound/LifeUp.wav",
		"LifeUp", sound_type::SOUND_SFX);

	//countdown timer sounds
	TheAudioManager::Instance()->load("../Assets/sound/Blip_Select_High.wav",
		"Timer High", sound_type::SOUND_SFX);
	TheAudioManager::Instance()->load("../Assets/sound/Blip_Select_Low.wav",
		"Timer Low", sound_type::SOUND_SFX);

	////music from  patrickdearteaga.com by Patrick de Arteaga
	//TheAudioManager::Instance()->load("../Assets/sound/Boss Fight.mp3",
	//	"Mystery Phase", sound_type::SOUND_MUSIC);


	TheAudioManager::Instance()->load("../Assets/sound/fight.wav",
		"Mystery Phase", sound_type::SOUND_MUSIC);

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
	m_pCats[0] = new Cat({ 0, 0, SPRITESIZE, SPRITESIZE }, { TILESIZE * 11, TILESIZE * 11, TILESIZE, TILESIZE }, 0);
	m_pCats[1] = new Cat({ 192, 0, SPRITESIZE, SPRITESIZE }, { TILESIZE * 11, TILESIZE * 11, TILESIZE, TILESIZE }, 1);
	m_pCats[2] = new Cat({ 384, 0, SPRITESIZE, SPRITESIZE }, { TILESIZE * 11, TILESIZE * 11, TILESIZE, TILESIZE }, 2);
	m_pCats[3] = new Cat({ 576, 0, SPRITESIZE, SPRITESIZE }, { TILESIZE * 11, TILESIZE * 11, TILESIZE, TILESIZE }, 3);

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

void Game::SetUpTileVariables(int level)
{
	std::string varFileName = "../Assets/Level" + to_string(level) + "Variables.txt";
	//std::string varFileName = "../Assets/Level5Variables.txt";
	std::ifstream varFile(varFileName);

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

void Game::BuildForegroundLayer(int level)
{
	std::string mapFileName = "../Assets/Level" + to_string(level) + "Map.txt";
	//std::string mapFileName = "../Assets/Level5Map.txt";
	std::ifstream mapFile(mapFileName);

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

void Game::SetDarknessWidth(int i)
{
	DarknessWidth = i;
}

int Game::GetDarknessWidth()
{
	return DarknessWidth;
}

Player* Game::GetPlayer()
{
	return m_pPlayer;
}
Level* Game::GetLevel()
{
	return &m_level;
}

int Game::GetLevelNum()
{
	return m_levelNum;
}

Cat * Game::GetCat(int num)
{
	return m_pCats[num];
}
Input_Manager* Game::GetInputManager()
{
	return &m_Input;
}


void Game::Update()
{
	if (!m_isCountdown) 
	{
		if (m_levelNum > 3)
		{
			if (DarknessWidth > 3500)
			{
				DarknessWidth -= (m_levelNum-3);
			}
			else
			{
				DarknessWidth = 3600;
			}
		}
	}
	if (!m_isCountdown)
	{
		HandlePlayerAndCatInteractions();
		if (m_pPlayer->isDying() == false && !m_pCats[0]->IsDying() && !m_pCats[1]->IsDying() && !m_pCats[2]->IsDying() && !m_pCats[3]->IsDying())
		{
			m_pPlayer->update();
			UpdateCats();
		}
	}


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
	Mix_HaltMusic();
	TheAudioManager::Instance()->playMusic("Mystery Phase", 0);
}

void Game::ChangeCatsToOriginalColors()
{
	Mix_HaltMusic();
	TheAudioManager::Instance()->playMusic("Background", -1);
}

void Game::HandlePlayerAndCatInteractions() {
	// Handles player eating a cat
	
	for (int i = 0; i < 4; i++) {
		if (!m_pCats[i]->IsDead()) // check if cat is alive
		{
		// If player collides with cat..
		if (SDL_HasIntersection(m_pPlayer->GetDstP(), m_pCats[i]->GetDstP())) {
			// Destroy cat if powered up
			
				if (m_pPlayer->GetAbility() == DEFEAT_CATS)
				{
					m_pCats[i]->SetDying(true);
					TheAudioManager::Instance()->playSound("CatDeath", 0);

					if (m_pCats[i]->IsDying() == false)
					{
						m_pCats[i]->Die(); // Cats need to be respawned in the center
						for (int i = 1; i <= 10; i++)
						{
							m_scoreNum += i * 10;
							if (m_scoreNum % LIFEINCREASETHRESHOLD == 0)
							{
								IncrementLives();
							}
						}
					}
				}
				// Else player dies
				else
				{ 
					if (m_pPlayer->GetInvulnerable() == false)
					{
						m_pPlayer->SetDying(true);
						TheAudioManager::Instance()->playSound("Death", 0);
					}
					if (m_pPlayer->isDead() == true)
					{
						m_livesNum--;
						Game::GetInstance()->PlayerLost();

						if (m_livesNum == 0)
						{
							SDL_RenderClear(SDL_Manager::GetInstance()->GetRenderer());
							TheTextureManager::Instance()->draw("Game_Over",
							SDL_Manager::GetInstance()->GetRenderer(), 23 * TILESIZE, 23 * TILESIZE);
							SDL_RenderPresent(SDL_Manager::GetInstance()->GetRenderer());
							Mix_HaltMusic();
							TheAudioManager::Instance()->mixVolume(128);
							TheAudioManager::Instance()->playSound("GameOver", 1);

							ofstream outFile("../Assets/highscores.txt", ios::app);
							outFile << m_scoreNum << std::endl;


							//a delay before switching to the game over screen state after this
							SDL_Delay(3000);
							m_livesNum = 3;
							m_bRunning = false;
							m_isCountdown = true;
							m_currLevel = 0;
							m_levelNum = 1;

								//want to change the ui to the Game over screen
							UI_Scores::RetrieveHighscores();
							UI_Manager::GetInstance()->SetScreenIndex(GAME_OVER);
							Game::GetInstance()->GetPlayer()->ResetAbilityLength();
							Game::GetInstance()->GetCat(0)->ResetScatterLength();
						}
					}
				}
			}
		}
		
	}
}

void Game::IncrementLevel()
{
	m_levelNum += 1; //increase level counter by 1
	m_currLevel = rand() % 5; //choose a random level to load between 0 and 4
	//m_currLevel = 4;
	BuildForegroundLayer(m_currLevel); //build the random level
	SetUpTileVariables(m_currLevel);
	ResetCats();
	Mix_HaltMusic();
	m_pPlayer->UpdateAbilityLength();
	m_pCats[0]->UpdateScatterLength();
	TheAudioManager::Instance()->playMusic("Background", -1);
	DarknessWidth = DEFAULTDARKNESSWIDTH;
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

int Game::GetLives()
{
	return m_livesNum;
}
//increase lives by 1 if below max of 5
void Game::IncrementLives()
{
	if( m_livesNum < 5)
	{
		TheAudioManager::Instance()->playSound("LifeUp", 0);
		m_livesNum++;
	}
}

void Game::SetCountdown(bool b)
{
	m_isCountdown = b;
}

int Game::GetCurrLevel()
{
	
	return m_currLevel;
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
	

	if (m_currLevel == 0) {
		BuildForegroundLayer(1);
		m_levelNum += 1;
	}
	else {
		SDL_Delay(3000);
		Game::GetInstance()->StopRunning();
	}
}

void Game::PlayerLost()
{
	std::cout << "The player has lost" << std::endl;
	// load picture in the contructor
	// Render picture
	//m_pPlayer->SetDst(TILESIZE * 11, TILESIZE * 13);
	//std::cout << "The cat's destination x = " << m_pCats[0]->GetDestinationX() << std::endl;

	/*m_pCats[0]->SetDst(TILESIZE * 3, TILESIZE * 3);
	m_pCats[1]->SetDst(TILESIZE * 19, TILESIZE * 3);
	m_pCats[2]->SetDst(TILESIZE * 3, TILESIZE * 19);
	m_pCats[3]->SetDst(TILESIZE * 19, TILESIZE * 19);*/
	

	//std::cout << "The cat's destination x = " << m_pCats[0]->GetDestinationX() << std::endl;
	/*if (m_livesNum == 0)
	{
		SDL_RenderClear(SDL_Manager::GetInstance()->GetRenderer());
		TheTextureManager::Instance()->draw("Game_Over",
			SDL_Manager::GetInstance()->GetRenderer(), 23 * TILESIZE, 23 * TILESIZE);
		SDL_RenderPresent(SDL_Manager::GetInstance()->GetRenderer());
		Game::GetInstance()->SetScore(0);
	}*/
	//SDL_Delay(3000);
	//CreateGameObjects();

	

	if (m_currLevel == 0) {
		m_pPlayer->SetDst({ TILESIZE * 11, TILESIZE * 13, TILESIZE, TILESIZE });
		m_pPlayer->SetDestinationX(11);
		m_pPlayer->SetDestinationY(13);
		m_pPlayer->SetMoving(false);

		ResetCats();
	}
	else if (m_currLevel == 1) {
		m_pPlayer->SetDst({ TILESIZE * 11, TILESIZE * 18, TILESIZE, TILESIZE });
		m_pPlayer->SetDestinationX(11);
		m_pPlayer->SetDestinationY(18);
		m_pPlayer->SetMoving(false);

		ResetCats();
	}
	else if (m_currLevel == 2) {
		m_pPlayer->SetDst({ TILESIZE * 11, TILESIZE * 13, TILESIZE, TILESIZE });
		m_pPlayer->SetDestinationX(11);
		m_pPlayer->SetDestinationY(13);
		m_pPlayer->SetMoving(false);

		ResetCats();
	}
	else if (m_currLevel == 3) {
		m_pPlayer->SetDst({ TILESIZE * 11, TILESIZE * 13, TILESIZE, TILESIZE });
		m_pPlayer->SetDestinationX(11);
		m_pPlayer->SetDestinationY(13);
		m_pPlayer->SetMoving(false);

		ResetCats();
	}
	else if (m_currLevel == 4) {
		m_pPlayer->SetDst({ TILESIZE * 11, TILESIZE * 13, TILESIZE, TILESIZE });
		m_pPlayer->SetDestinationX(11);
		m_pPlayer->SetDestinationY(13);
		m_pPlayer->SetMoving(false);

		ResetCats();

	}
	m_pPlayer->SetAbility(NONE);
	m_pPlayer->SetSprite(0);
	m_pPlayer->SetDying(false);
	m_pPlayer->setDeath(false);
	m_pPlayer->SetInvulnerable(false);
	
}

void Game::ResetCat1()
{
	if (m_currLevel == 0) {
		m_pCats[0] = new Cat({ 0, 0, SPRITESIZE, SPRITESIZE }, { TILESIZE * 11, TILESIZE * 11, TILESIZE, TILESIZE }, 0);
		m_pCats[0]->SetPriority(CatDirection::C_UP, CatDirection::C_LEFT, CatDirection::C_DOWN, CatDirection::C_RIGHT);
	}
	else if (m_currLevel == 1) {
		m_pCats[0] = new Cat({ 0, 0, SPRITESIZE, SPRITESIZE }, { TILESIZE * 11, TILESIZE * 16, TILESIZE, TILESIZE }, 0);
		m_pCats[0]->SetPriority(CatDirection::C_UP, CatDirection::C_LEFT, CatDirection::C_DOWN, CatDirection::C_RIGHT);
	}
	else if (m_currLevel == 2) {
		m_pCats[0] = new Cat({ 0, 0, SPRITESIZE, SPRITESIZE }, { TILESIZE * 11, TILESIZE * 11, TILESIZE, TILESIZE }, 0);
		m_pCats[0]->SetPriority(CatDirection::C_UP, CatDirection::C_LEFT, CatDirection::C_DOWN, CatDirection::C_RIGHT);
	}
	else if (m_currLevel == 3) {
		m_pCats[0] = new Cat({ 0, 0, SPRITESIZE, SPRITESIZE }, { TILESIZE * 11, TILESIZE * 11, TILESIZE, TILESIZE }, 0);
		m_pCats[0]->SetPriority(CatDirection::C_UP, CatDirection::C_LEFT, CatDirection::C_DOWN, CatDirection::C_RIGHT);
	}
	else if (m_currLevel == 4) {
		m_pCats[0] = new Cat({ 0, 0, SPRITESIZE, SPRITESIZE }, { TILESIZE * 11, TILESIZE * 11, TILESIZE, TILESIZE }, 0);
		m_pCats[0]->SetPriority(CatDirection::C_UP, CatDirection::C_LEFT, CatDirection::C_DOWN, CatDirection::C_RIGHT);
	}

}
void Game::ResetCat2()
{
	if (m_currLevel == 0) {
		m_pCats[1] = new Cat({ 192, 0, SPRITESIZE, SPRITESIZE }, { TILESIZE * 11, TILESIZE * 11, TILESIZE, TILESIZE }, 1);
		m_pCats[1]->SetPriority(CatDirection::C_DOWN, CatDirection::C_LEFT, CatDirection::C_UP, CatDirection::C_RIGHT);
	}
	else if (m_currLevel == 1) {
		m_pCats[1] = new Cat({ 192, 0, SPRITESIZE, SPRITESIZE }, { TILESIZE * 11, TILESIZE * 16, TILESIZE, TILESIZE }, 1);
		m_pCats[1]->SetPriority(CatDirection::C_DOWN, CatDirection::C_LEFT, CatDirection::C_UP, CatDirection::C_RIGHT);
	}
	else if (m_currLevel == 2) {
		m_pCats[1] = new Cat({ 192, 0, SPRITESIZE, SPRITESIZE }, { TILESIZE * 11, TILESIZE * 11, TILESIZE, TILESIZE }, 1);
		m_pCats[1]->SetPriority(CatDirection::C_DOWN, CatDirection::C_LEFT, CatDirection::C_UP, CatDirection::C_RIGHT);
	}
	else if (m_currLevel == 3) {
		m_pCats[1] = new Cat({ 192, 0, SPRITESIZE, SPRITESIZE }, { TILESIZE * 11, TILESIZE * 11, TILESIZE, TILESIZE }, 1);
		m_pCats[1]->SetPriority(CatDirection::C_DOWN, CatDirection::C_LEFT, CatDirection::C_UP, CatDirection::C_RIGHT);
	}
	else if (m_currLevel == 4) {
		m_pCats[1] = new Cat({ 192, 0, SPRITESIZE, SPRITESIZE }, { TILESIZE * 11, TILESIZE * 11, TILESIZE, TILESIZE }, 1);
		m_pCats[1]->SetPriority(CatDirection::C_DOWN, CatDirection::C_LEFT, CatDirection::C_UP, CatDirection::C_RIGHT);
	}

}
void Game::ResetCat3()
{
	if (m_currLevel == 0) {
		m_pCats[2] = new Cat({ 2 * 192 , 0, SPRITESIZE, SPRITESIZE }, { TILESIZE * 11, TILESIZE * 11, TILESIZE, TILESIZE }, 2);
		m_pCats[2]->SetPriority(CatDirection::C_DOWN, CatDirection::C_RIGHT, CatDirection::C_UP, CatDirection::C_LEFT);
	}
	else if (m_currLevel == 1) {
		m_pCats[2] = new Cat({ 2 * 192 , 0, SPRITESIZE, SPRITESIZE }, { TILESIZE * 11, TILESIZE * 16, TILESIZE, TILESIZE }, 2);
		m_pCats[2]->SetPriority(CatDirection::C_DOWN, CatDirection::C_RIGHT, CatDirection::C_UP, CatDirection::C_LEFT);
	}
	else if (m_currLevel == 2) {
		m_pCats[2] = new Cat({ 2 * 192 , 0, SPRITESIZE, SPRITESIZE }, { TILESIZE * 11, TILESIZE * 11, TILESIZE, TILESIZE }, 2);
		m_pCats[2]->SetPriority(CatDirection::C_DOWN, CatDirection::C_RIGHT, CatDirection::C_UP, CatDirection::C_LEFT);
	}
	else if (m_currLevel == 3) {
		m_pCats[2] = new Cat({ 2 * 192 , 0, SPRITESIZE, SPRITESIZE }, { TILESIZE * 11, TILESIZE * 11, TILESIZE, TILESIZE }, 2);
		m_pCats[2]->SetPriority(CatDirection::C_DOWN, CatDirection::C_RIGHT, CatDirection::C_UP, CatDirection::C_LEFT);
	}
	else if (m_currLevel == 4) {
		m_pCats[2] = new Cat({ 2 * 192 , 0, SPRITESIZE, SPRITESIZE }, { TILESIZE * 11, TILESIZE * 11, TILESIZE, TILESIZE }, 2);
		m_pCats[2]->SetPriority(CatDirection::C_DOWN, CatDirection::C_RIGHT, CatDirection::C_UP, CatDirection::C_LEFT);
	}
}
void Game::ResetCat4()
{
	if (m_currLevel == 0) {
		m_pCats[3] = new Cat({ 3 * 192 , 0, SPRITESIZE, SPRITESIZE }, { TILESIZE * 11, TILESIZE * 11, TILESIZE, TILESIZE }, 3);
		m_pCats[3]->SetPriority(CatDirection::C_UP, CatDirection::C_RIGHT, CatDirection::C_DOWN, CatDirection::C_LEFT);
	}
	else if (m_currLevel == 1) {
		m_pCats[3] = new Cat({ 3 * 192 , 0, SPRITESIZE, SPRITESIZE }, { TILESIZE * 11, TILESIZE * 16, TILESIZE, TILESIZE }, 3);
		m_pCats[3]->SetPriority(CatDirection::C_UP, CatDirection::C_RIGHT, CatDirection::C_DOWN, CatDirection::C_LEFT);
	}
	else if (m_currLevel == 2) {
		m_pCats[3] = new Cat({ 3 * 192 , 0, SPRITESIZE, SPRITESIZE }, { TILESIZE * 11, TILESIZE * 11, TILESIZE, TILESIZE }, 3);
		m_pCats[3]->SetPriority(CatDirection::C_UP, CatDirection::C_RIGHT, CatDirection::C_DOWN, CatDirection::C_LEFT);
	}
	else if (m_currLevel == 3) {
		m_pCats[3] = new Cat({ 3 * 192 , 0, SPRITESIZE, SPRITESIZE }, { TILESIZE * 11, TILESIZE * 11, TILESIZE, TILESIZE }, 3);
		m_pCats[3]->SetPriority(CatDirection::C_UP, CatDirection::C_RIGHT, CatDirection::C_DOWN, CatDirection::C_LEFT);
	}
	else if (m_currLevel == 4) {
		m_pCats[3] = new Cat({ 3 * 192 , 0, SPRITESIZE, SPRITESIZE }, { TILESIZE * 11, TILESIZE * 11, TILESIZE, TILESIZE }, 3);
		m_pCats[3]->SetPriority(CatDirection::C_UP, CatDirection::C_RIGHT, CatDirection::C_DOWN, CatDirection::C_LEFT);
	}
}
void Game::ResetCats()
{
	//reset cats to fit the level
	ResetCat1();
	ResetCat2();
	ResetCat3();
	ResetCat4();
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
	//// draw background tile map
	//for (int row = 0; row < ROWS; row++)
	//{
	//	for (int col = 0; col < COLS; col++) {
	//		SDL_RenderCopy(m_pRenderer, m_pTileTexture, m_bg.m_Map[row][col].GetSrcP(), m_bg.m_Map[row][col].GetDstP());
	//	}
	//}

	//full background image, need to render level map overtop
	TheTextureManager::Instance()->draw("background main",
		SDL_Manager::GetInstance()->GetRenderer(), 23 * TILESIZE, 23 * TILESIZE);

	//// Render map
	for (int row = 0; row < ROWS; row++) {
		for (int col = 0; col < COLS; col++) {
			SDL_RenderCopy(m_pRenderer, m_pTileTexture, m_level.m_Map[row][col].GetSrcP(), m_level.m_Map[row][col].GetDstP());
		}
	}
	//update cat sprites before render
	m_pCats[0]->Animate();
	m_pCats[1]->Animate();
	m_pCats[2]->Animate();
	m_pCats[3]->Animate();

	// Render cats
	for (int i = 0; i < 4; i++) 
	{
			SDL_RenderCopyEx(m_pRenderer, m_pGhostsTexture, m_pCats[i]->GetSrcP(), m_pCats[i]->GetDstP(), m_pCats[i]->angle, &m_pCats[i]->center, SDL_FLIP_NONE);
	}

	if(GetLevelNum() > 3) //only show the darkenss from 4th level on
	{
		TheTextureManager::Instance()->draw("Darkness", Game::GetInstance()->GetPlayer()->GetDst().x + 16 - (DarknessWidth / 2), Game::GetInstance()->GetPlayer()->GetDst().y + 16 - (DarknessWidth / 2), DarknessWidth, DarknessWidth, m_pRenderer, SDL_FLIP_NONE);
	}
	//TheTextureManager::Instance()->draws("Darkness", Game::GetInstance()->GetPlayer()->GetDst().x + 16, Game::GetInstance()->GetPlayer()->GetDst().y + 16, DarknessWidth, DarknessWidth, m_pRenderer, SDL_FLIP_NONE, false);

	m_pPlayer->animate();


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

	////temp rectangle for targeting square
	//SDL_Rect targetSquare = { m_pCats[3]->GetTargetX() * 32,  m_pCats[3]->GetTargetY() * 32, 32,32 };
	//SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 0, 0);
	//SDL_RenderFillRect(m_pRenderer, &targetSquare);
	//SDL_RenderDrawRect(m_pRenderer, &targetSquare);

	//render the countdown
	m_RenderCountdown();

	SDL_RenderPresent(m_pRenderer);
}

void Game::m_RenderCountdown()
{
	//render out the timer
	if (m_isCountdown)
	{
		if (m_countdownFrame < 60)
		{
			TheTextureManager::Instance()->draw("count 5", 368, 250,
				SDL_Manager::GetInstance()->GetRenderer(), true);
			if(m_countdownFrame == 59)
			{
				TheAudioManager::Instance()->playSound("Timer Low", 0);
			}
			m_countdownFrame++;
		}
		else if (m_countdownFrame < 120)
		{
			TheTextureManager::Instance()->draw("count 4", 368, 250,
				SDL_Manager::GetInstance()->GetRenderer(), true);
			if (m_countdownFrame == 119)
			{
				TheAudioManager::Instance()->playSound("Timer Low", 0);
			}
			m_countdownFrame++;
		}
		else if (m_countdownFrame < 180)
		{
			TheTextureManager::Instance()->draw("count 3", 368, 250,
				SDL_Manager::GetInstance()->GetRenderer(), true);
			if (m_countdownFrame == 179)
			{
				TheAudioManager::Instance()->playSound("Timer Low", 0);
			}
			m_countdownFrame++;
		}
		else if (m_countdownFrame < 240)
		{
			TheTextureManager::Instance()->draw("count 2", 368, 250,
				SDL_Manager::GetInstance()->GetRenderer(), true);
			if (m_countdownFrame == 239)
			{
				TheAudioManager::Instance()->playSound("Timer Low", 0);
			}
			m_countdownFrame++;
		}
		else if (m_countdownFrame < 300)
		{
			TheTextureManager::Instance()->draw("count 1", 368, 250,
				SDL_Manager::GetInstance()->GetRenderer(), true);
			if (m_countdownFrame == 299)
			{
				TheAudioManager::Instance()->playSound("Timer High", 0);
			}
			m_countdownFrame++;
		}
		else
		{
			//leave the loop of the timer
			m_isCountdown = false;
			m_countdownFrame = 0;
		}
	}
}

void Game::HandleEvents() {
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			m_bRunning = false;
			m_livesNum = 3;
			m_currLevel = 0;
			m_levelNum = 1;
			//m_scoreNum = 0;
			Mix_HaltMusic();
			TheAudioManager::Instance()->playMusic("Main_Menu_Background", -1); //play the main menu background since returning to it
			m_isCountdown = true;
			Game::GetInstance()->GetPlayer()->ResetAbilityLength();
			Game::GetInstance()->GetCat(0)->ResetScatterLength();
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
	//SetScore(0);
	//SDL_DestroyWindow(m_pWindow);
	//SDL_DestroyRenderer(m_pRenderer);
	//IMG_Quit();
	//SDL_Quit();
}

