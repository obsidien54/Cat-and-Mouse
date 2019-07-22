#include <cmath>
#include <iostream>
#include "Game.h"
#include <fstream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"

#define ROWS 31
#define COLS 31

Game::Game() {
	m_fps = (Uint32)round(1 / (long double)FPS * 1000);
}

bool Game::Init(const char* title, int xpos, int ypos, int width, int height, int flags) {
	// Attempt to initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) { // 0 is error code meaning success
		std::cout << "SDL init success!" << std::endl;
		// Initialize window
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (m_pWindow != nullptr) { // Window init success
			std::cout << "Window creation successful!" << std::endl;
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

			if (m_pRenderer != nullptr) { // Renderer init success
				std::cout << "Renderer creation success!" << std::endl;

				if (IMG_Init(IMG_INIT_PNG) != 0) {
					// Create pixel maps.
					SDL_Surface* tileSurface = IMG_Load("Assets/textures/Tiles.png");
					SDL_Surface* playerSurface = IMG_Load("Assets/textures/mouse.png");
					SDL_Surface* ghostsSurface = IMG_Load("Assets/textures/Cats.png");
					m_pTileTexture = SDL_CreateTextureFromSurface(m_pRenderer, tileSurface);
					m_pPlayerTexture = SDL_CreateTextureFromSurface(m_pRenderer, playerSurface);
					m_pGhostsTexture = SDL_CreateTextureFromSurface(m_pRenderer, ghostsSurface);
					SDL_FreeSurface(tileSurface);
					SDL_FreeSurface(playerSurface);
					SDL_FreeSurface(ghostsSurface);
					std::cout << "Pixel maps creation success!" << std::endl;
				}
				else {
					return 1; // Image init fail
				}
			}
			else {
				std::cout << "Renderer init fail!" << std::endl;
				return false; //Renderer init fail
			}
		}
		else {
			std::cout << "Window init fail!" << std::endl;
			return false; // Window init fail
		}
	}
	else {
		std::cout << "SDL init fail!" << std::endl;
		return false; // SDL init fail
	}
	// build background layer
	std::ifstream bgFile("Assets/bg.txt");
	for (int row = 0; row < ROWS; row++) {
		for (int col = 0; col < COLS; col++) {
			char i;
			bgFile >> i;
			m_bg.m_Map[row][col].SetSrc(i);
			m_bg.m_Map[row][col].SetTileVariables(i);
			m_bg.m_Map[row][col].SetDst({ 32 * col, 32 * row, 32, 32 });
		}
	}
	bgFile.close();
	// Build tilemap
	std::ifstream mapFile("Assets/Level0.txt");
	for (int row = 0; row < ROWS; row++) {
		for (int col = 0; col < COLS; col++) {
			char temp;
			mapFile >> temp;
			m_level.m_Map[row][col].SetSrc(temp);
			m_level.m_Map[row][col].SetTileVariables(temp);
			m_level.m_Map[row][col].SetDst({ 32 * col, 32 * row, 32, 32 });
		}
	}
	mapFile.close();

	m_iKeyStates = SDL_GetKeyboardState(NULL);
	// Spawn Player and Ghosts
	// Starting coordinate: 15, 17
	m_pPlayer = new Player({ 0, 0, 32, 32 }, { 32 * 15, 32 * 17, 32, 32 });
	m_pCats[0] = new Cat({ 0, 0, 32, 32 }, { 32 * 14, 32 * 15, 32, 32 });
	m_pCats[1] = new Cat({ 96, 0, 32, 32 }, { 32 * 15, 32 * 15, 32, 32 });
	m_pCats[2] = new Cat({ 192, 0, 32, 32 }, { 32 * 16, 32 * 15, 32, 32 });
	m_pCats[3] = new Cat({ 288, 0, 32, 32 }, { 32 * 10, 32 * 8, 32, 32 });
	m_bRunning = true;
	return true;
}

bool Game::KeyDown(SDL_Scancode c) {
	if (m_iKeyStates != nullptr) {
		if (m_iKeyStates[c] == true) {
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}

void Game::Update() {
	PlayerGhostsInteractions();
	PlayerMovements();
	CatMovements();
	//For debugging purposes
	/*cout << "Is Moving: " <<  m_pPlayer->isMoving() << endl;
	cout << "Destination X: " << m_pPlayer->GetDestinationX() << endl;
	cout << "Rect X: " << m_pPlayer->GetDst().x << endl;
	cout << "Destination Y: " << m_pPlayer->GetDestinationY() << endl;
	cout << "Rect Y: " << m_pPlayer->GetDst().y << endl;*/
}

void Game::PlayerGhostsInteractions() {
	if (m_pPlayer->isPoweredUp()) {
		// Player is only powered up for 10 seconds
		if (SDL_GetTicks() - m_powerUpStartTimer > 10000) {
			m_pPlayer->SetPowered(false);

			// After 10 seconds, return ghosts to their original state
			for (int i = 0; i < 4; i++) {
				m_pCats[i]->SetVulnerable(false);
				if (!m_pCats[i]->isDead()) {
					m_pCats[i]->SetSrc({ i * 32, 0, 32, 32 });
				}
			}
		}
	}

	// Handles player eating a mystery cheese
	if (m_level.m_Map[m_pPlayer->GetY()][m_pPlayer->GetX()].isPowerUp() /*&& !m_pPlayer->isMoving()*/) {
		m_pPlayer->SetPowered(true);
		// Change tile to a normal blank tile with its associated variables
		m_level.m_Map[m_pPlayer->GetY()][m_pPlayer->GetX()].SetSrc('B');
		m_level.m_Map[m_pPlayer->GetY()][m_pPlayer->GetX()].SetTileVariables('B');

		m_powerUpStartTimer = SDL_GetTicks();

		// Make cats vulnerable
		for (int i = 0; i < 4; i++) {
			m_pCats[i]->SetVulnerable(true);
		}
	}

	// Handles player eating a cat
	for (int i = 0; i < 4; i++) {
		// If player collides with cat..
		if (SDL_HasIntersection(m_pPlayer->GetDstP(), m_pCats[i]->GetDstP()) /*&& !m_pPlayer->isMoving()*/) {
			// Destroy cat if powered up
			if (!m_pCats[i]->isDead())
			{
				if (m_pPlayer->isPoweredUp())
				{
					m_pCats[i]->Die();
				}
				// Else player dies
				else
				{
					m_pPlayer->Die();
					m_bRunning = false;
				}
			}
		}
	}
}

// Tile based movement with obstacle detection
void Game::PlayerMovements() {
	// Player eating a pellet
	if (m_level.m_Map[m_pPlayer->GetY()][m_pPlayer->GetX()].isPoint())
	{
		// Change tile to a normal blank tile with its associated variables
		m_level.m_Map[m_pPlayer->GetY()][m_pPlayer->GetX()].SetSrc('B');
		m_level.m_Map[m_pPlayer->GetY()][m_pPlayer->GetX()].SetTileVariables('B');
	}



	//player movement input handling

	if (!m_pPlayer->isDead())
	{
		if (KeyDown(SDL_SCANCODE_W))
		{
			if (!m_level.m_Map[m_pPlayer->GetBottomEdgeTile() - 1][m_pPlayer->GetRightEdgeTile()].isObstacle() &&
				!m_level.m_Map[m_pPlayer->GetBottomEdgeTile() - 1][m_pPlayer->GetLeftEdgeTile()].isObstacle()) //check that the right and left are clear for the character to move up
			{

				m_pPlayer->MoveUp();
			}
		}
		else if (KeyDown(SDL_SCANCODE_S))
		{
			if (!m_level.m_Map[m_pPlayer->GetTopEdgeTile() + 1][m_pPlayer->GetRightEdgeTile()].isObstacle() &&
				!m_level.m_Map[m_pPlayer->GetTopEdgeTile() + 1][m_pPlayer->GetLeftEdgeTile()].isObstacle()) //check that the right and left are clear for the character to move down
			{

				m_pPlayer->MoveDown();
			}
		}
		if (KeyDown(SDL_SCANCODE_A))
		{
			if (!m_level.m_Map[m_pPlayer->GetBottomEdgeTile()][m_pPlayer->GetRightEdgeTile() - 1].isObstacle() &&
				!m_level.m_Map[m_pPlayer->GetTopEdgeTile()][m_pPlayer->GetRightEdgeTile() - 1].isObstacle())
			{

				m_pPlayer->MoveLeft();
			}
		}
		else if (KeyDown(SDL_SCANCODE_D))
		{
			if (!m_level.m_Map[m_pPlayer->GetBottomEdgeTile()][m_pPlayer->GetLeftEdgeTile() + 1].isObstacle() &&
				!m_level.m_Map[m_pPlayer->GetTopEdgeTile()][m_pPlayer->GetLeftEdgeTile() + 1].isObstacle())
			{


				m_pPlayer->MoveRight();
			}
		}
		else if (KeyDown(SDL_SCANCODE_ESCAPE))
		{
			m_bRunning = false;
		}

	}

	m_pPlayer->animate();
}

void Game::CatMovements()
{
	int CATINDEX = 3;
	int distance = 99999;
	int temp = 0;
	// Check if the square cat is on is an intersection
	if (m_level.m_Map[m_pCats[CATINDEX]->GetY()][m_pCats[CATINDEX]->GetX()].isIntersection())
	{
		// if north is not an obstacle and if the direction is the opposite of the checking direction to prevent U-turn
		if (!m_level.m_Map[m_pCats[CATINDEX]->GetY() - 1][m_pCats[CATINDEX]->GetX()].isObstacle() && m_pCats[CATINDEX]->getDir() != 's')
		{
			temp = 0;// reseting and checking the distance
			temp += (m_pPlayer->GetX() - m_pCats[CATINDEX]->GetX())*(m_pPlayer->GetX() - m_pCats[CATINDEX]->GetX());
			temp += (m_pPlayer->GetY() - (m_pCats[CATINDEX]->GetY() - 1))*(m_pPlayer->GetY() - (m_pCats[CATINDEX]->GetY() - 1));
			if (distance > temp)
			{
				distance = temp;
				m_pCats[CATINDEX]->setDir('w');
			}
		}
		// if east is not an obstacle and if the direction is the opposite of the checking direction to prevent U-turn
		if (!m_level.m_Map[m_pCats[CATINDEX]->GetY()][m_pCats[CATINDEX]->GetX() + 1].isObstacle() && m_pCats[CATINDEX]->getDir() != 'a')
		{
			temp = 0;
			temp += (m_pPlayer->GetX() - (m_pCats[CATINDEX]->GetX() + 1))*(m_pPlayer->GetX() - (m_pCats[CATINDEX]->GetX() + 1));
			temp += (m_pPlayer->GetY() - m_pCats[CATINDEX]->GetY())*(m_pPlayer->GetY() - m_pCats[CATINDEX]->GetY());
			if (distance > temp)
			{
				distance = temp;
				m_pCats[CATINDEX]->setDir('d');
			}
		}
		// if south is not an obstacle and if the direction is the opposite of the checking direction to prevent U-turn
		if (!m_level.m_Map[m_pCats[CATINDEX]->GetY() + 1][m_pCats[CATINDEX]->GetX()].isObstacle() && m_pCats[CATINDEX]->getDir() != 'w')
		{
			temp = 0;
			temp += (m_pPlayer->GetX() - m_pCats[CATINDEX]->GetX())*(m_pPlayer->GetX() - m_pCats[CATINDEX]->GetX());
			temp += (m_pPlayer->GetY() - (m_pCats[CATINDEX]->GetY() + 1))*(m_pPlayer->GetY() - (m_pCats[CATINDEX]->GetY() + 1));
			if (distance > temp)
			{
				distance = temp;
				m_pCats[CATINDEX]->setDir('s');
			}
		}
		// if west is not an obstacle and if the direction is the opposite of the checking direction to prevent U-turn
		if (!m_level.m_Map[m_pCats[CATINDEX]->GetY()][m_pCats[CATINDEX]->GetX() - 1].isObstacle() && m_pCats[CATINDEX]->getDir() != 'd')
		{
			temp = 0;
			temp += (m_pPlayer->GetX() - (m_pCats[CATINDEX]->GetX() - 1))*(m_pPlayer->GetX() - (m_pCats[CATINDEX]->GetX() - 1));
			temp += (m_pPlayer->GetY() - m_pCats[CATINDEX]->GetY())*(m_pPlayer->GetY() - m_pCats[CATINDEX]->GetY());
			if (distance > temp)
			{
				distance = temp;
				m_pCats[CATINDEX]->setDir('a');
			}
		}
	}
	// if not moving then move in a direction
	if (!m_pCats[CATINDEX]->isDead() && !m_pCats[CATINDEX]->isMoving()) {
		if (m_pCats[CATINDEX]->getDir() == 'w') {
			// If not an obstacle then sets the new destination square
			if (!m_level.m_Map[m_pCats[CATINDEX]->GetY() - 1][m_pCats[CATINDEX]->GetX()].isObstacle()) {
				m_pCats[CATINDEX]->SetDestinationY(m_pCats[CATINDEX]->GetDst().y - 32);
				m_pCats[CATINDEX]->SetDestinationX(m_pCats[CATINDEX]->GetDst().x);
				m_pCats[CATINDEX]->SetMoving(true);
			}
			else // if Obstacle it will check for another route
			{
				if (!m_level.m_Map[m_pCats[CATINDEX]->GetY()][m_pCats[CATINDEX]->GetX() + 1].isObstacle())
				{
					m_pCats[CATINDEX]->setDir('d');
				}
				else if (!m_level.m_Map[m_pCats[CATINDEX]->GetY()][m_pCats[CATINDEX]->GetX() - 1].isObstacle())
				{
					m_pCats[CATINDEX]->setDir('a');
				}
				else
				{
					m_pCats[CATINDEX]->setDir('s');
				}
			}
		}
		else if (m_pCats[CATINDEX]->getDir() == 's') {
			if (!m_level.m_Map[m_pCats[CATINDEX]->GetY() + 1][m_pCats[CATINDEX]->GetX()].isObstacle()) {
				m_pCats[CATINDEX]->SetDestinationY(m_pCats[CATINDEX]->GetDst().y + 32);
				m_pCats[CATINDEX]->SetDestinationX(m_pCats[CATINDEX]->GetDst().x);
				m_pCats[CATINDEX]->SetMoving(true);
			}
			else
			{
				if (!m_level.m_Map[m_pCats[CATINDEX]->GetY()][m_pCats[CATINDEX]->GetX() - 1].isObstacle())
				{
					m_pCats[CATINDEX]->setDir('a');
				}
				else if (!m_level.m_Map[m_pCats[CATINDEX]->GetY()][m_pCats[CATINDEX]->GetX() + 1].isObstacle())
				{
					m_pCats[CATINDEX]->setDir('d');
				}
				else
				{
					m_pCats[CATINDEX]->setDir('w');
				}
			}
		}
		else if (m_pCats[CATINDEX]->getDir() == 'a') {
			if (!m_level.m_Map[m_pCats[CATINDEX]->GetY()][m_pCats[CATINDEX]->GetX() - 1].isObstacle())
			{
				m_pCats[CATINDEX]->SetDestinationX(m_pCats[CATINDEX]->GetDst().x - 32);
				m_pCats[CATINDEX]->SetDestinationY(m_pCats[CATINDEX]->GetDst().y);
				m_pCats[CATINDEX]->SetMoving(true);
			}
			else
			{
				if (!m_level.m_Map[m_pCats[CATINDEX]->GetY() - 1][m_pCats[CATINDEX]->GetX()].isObstacle())
				{
					m_pCats[CATINDEX]->setDir('w');
				}
				else if (!m_level.m_Map[m_pCats[CATINDEX]->GetY() + 1][m_pCats[CATINDEX]->GetX()].isObstacle())
				{
					m_pCats[CATINDEX]->setDir('s');
				}
				else
				{
					m_pCats[CATINDEX]->setDir('d');
				}
			}
		}
		else if (m_pCats[CATINDEX]->getDir() == 'd') {
			if (!m_level.m_Map[m_pCats[CATINDEX]->GetY()][m_pCats[CATINDEX]->GetX() + 1].isObstacle()) {
				m_pCats[CATINDEX]->SetDestinationX(m_pCats[CATINDEX]->GetDst().x + 32);
				m_pCats[CATINDEX]->SetDestinationY(m_pCats[CATINDEX]->GetDst().y);
				m_pCats[CATINDEX]->SetMoving(true);
			}
			else
			{
				if (!m_level.m_Map[m_pCats[CATINDEX]->GetY() - 1][m_pCats[CATINDEX]->GetX()].isObstacle())
				{
					m_pCats[CATINDEX]->setDir('w');
				}
				else if (!m_level.m_Map[m_pCats[CATINDEX]->GetY() + 1][m_pCats[CATINDEX]->GetX()].isObstacle())
				{
					m_pCats[CATINDEX]->setDir('s');
				}
				else
				{
					m_pCats[CATINDEX]->setDir('a');
				}
			}
		}
	}
	// if moving continue moving till
	if (m_pCats[CATINDEX]->isMoving()) {
		if (m_pCats[CATINDEX]->GetDestinationX() > m_pCats[CATINDEX]->GetDst().x) {
			m_pCats[CATINDEX]->MoveX(1);
		}
		else if (m_pCats[CATINDEX]->GetDestinationX() < m_pCats[CATINDEX]->GetDst().x) {
			m_pCats[CATINDEX]->MoveX(-1);
		}
		else if (m_pCats[CATINDEX]->GetDestinationY() > m_pCats[CATINDEX]->GetDst().y) {
			m_pCats[CATINDEX]->MoveY(1);
		}
		else if (m_pCats[CATINDEX]->GetDestinationY() < m_pCats[CATINDEX]->GetDst().y) {
			m_pCats[CATINDEX]->MoveY(-1);
		}
		// if cat has gotten to destination then set moving to false
		else if (m_pCats[CATINDEX]->GetDestinationX() == m_pCats[CATINDEX]->GetDst().x && m_pCats[CATINDEX]->GetDestinationY() == m_pCats[CATINDEX]->GetDst().y) {
			m_pCats[CATINDEX]->SetMoving(false);
		}

	}

}

void Game::Render() {
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
		SDL_RenderCopyEx(m_pRenderer, m_pGhostsTexture, m_pCats[i]->GetSrcP(), m_pCats[i]->GetDstP(), m_pCats[i]->angle, &m_pCats[i]->center, SDL_FLIP_NONE);
	}

	// Render player
	SDL_RenderCopyEx(m_pRenderer, m_pPlayerTexture, m_pPlayer->GetSrcP(), m_pPlayer->GetDstP(), m_pPlayer->GetPlayerAngle(), &m_pPlayer->center, SDL_FLIP_NONE);

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
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	IMG_Quit();
	SDL_Quit();
}

