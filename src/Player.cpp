#include "Player.h"
#include <iostream>

void Player::m_HandlePlayerAbilities()
{
	switch (GetAbility()) {
	case Ability::NONE:
		return;
		break;
	case Ability::DEFEAT_CATS:
		if (SDL_GetTicks() - Game::GetInstance()->GetAbilityStartTimer() > m_AbilityLength)
		{
			SetAbility(Ability::NONE);
			Game::GetInstance()->ChangeCatsToOriginalColors();
			Game::GetInstance()->GetCat(0)->SetAllVulnerable(false);
			Game::GetInstance()->GetCat(0)->SetBlinking(false);

			std::cout << "Defeat Cats Ability Expired" << std::endl;
		}
		else if (SDL_GetTicks() - Game::GetInstance()->GetAbilityStartTimer() > m_AbilityLength - 3000)
		{
			Game::GetInstance()->GetCat(0)->SetBlinking(true);
		}
		break;
	case Ability::ENTER_WALL:
		
		// Remove ability after one time use
		if (!isMoving() && !isCurrentlyInWall()) {
			if (enteredWall()) {
				SetCurrentlyInWall(false);
				SetEnteredWall(false);
				SetAbility(Ability::NONE);
				sprite = 0;
				std::cout << "Enter Walls Ability Expired" << std::endl;
			}
			if (Game::GetInstance()->GetInputManager()->KeyDown(SDL_SCANCODE_RETURN)) {
				Level* Level = Game::GetInstance()->GetLevel();

				switch (GetPlayerAngle()) {
				case 0: // facing up
					if (Level->m_Map[GetY() - 1][GetX()].isEnterableWall()) {
						SetDestinationY(GetDst().y - TILESIZE);
						SetDestinationX(GetDst().x);
						SetMoving(true);
						SetCurrentlyInWall(true);
						SetEnteredWall(true);
						TheAudioManager::Instance()->playSound("enter wall", 0);
					}
					break;
				case 180: // facing down
					if (Level->m_Map[GetY() + 1][GetX()].isEnterableWall()) {
						SetDestinationY(GetDst().y + TILESIZE);
						SetDestinationX(GetDst().x);
						SetMoving(true);
						SetCurrentlyInWall(true);
						SetEnteredWall(true);
						TheAudioManager::Instance()->playSound("enter wall", 0);
					}
					break;
				case 90: // facing right
					if (Level->m_Map[GetY()][GetX() + 1].isEnterableWall()) {
						SetDestinationX(GetDst().x + TILESIZE);
						SetDestinationY(GetDst().y);
						SetMoving(true);
						SetCurrentlyInWall(true);
						SetEnteredWall(true);
						TheAudioManager::Instance()->playSound("enter wall", 0);
					}
					break;
				case 270: // facing left
					if (Level->m_Map[GetY()][GetX() - 1].isEnterableWall()) {
						SetDestinationX(GetDst().x - TILESIZE);
						SetDestinationY(GetDst().y);
						SetMoving(true);
						SetCurrentlyInWall(true);
						SetEnteredWall(true);
						TheAudioManager::Instance()->playSound("enter wall", 0);
					}
					break;
				}
			}
		}
		break;
	}
}

void Player::m_HandleMovement()
{
	m_HandleWarping();
	m_HandleEatingCheese();
	m_HandleEatingMysteryCheese();
	m_MovePlayer();
	//animate();
}

void Player::m_HandleWarping()
{
	Level* Level = Game::GetInstance()->GetLevel();
	if (Level->m_Map[GetY()][GetX()].isLeftWarpTile() && !isMoving()) {
		SetDst({ TILESIZE * 19 - m_iMoveSpeed, TILESIZE * 11, TILESIZE, TILESIZE });
		SetDestinationX(18 * TILESIZE);
		SetMoving(true);
	}
	else if (Level->m_Map[GetY()][GetX()].isRightWarpTile() && !isMoving()) {
		SetDst({ TILESIZE * 3 - TILESIZE, TILESIZE * 11, TILESIZE, TILESIZE });
		SetDestinationX(4 * TILESIZE);
		SetMoving(true);
	}

}

void Player::m_HandleEatingCheese() {
	// Player eating cheese
	Level* Level = Game::GetInstance()->GetLevel();
	if (Level->m_Map[GetY()][GetX()].isPoint())
	{
		// Change tile to a normal blank tile with its associated variables
		Level->m_Map[GetY()][GetX()].SetSrc('B');

		if (Level->m_Map[GetY()][GetX()].isIntersection()) 
		{
			Level->m_Map[GetY()][GetX()].SetTileVariables('I');
		}
		else {
			Level->m_Map[GetY()][GetX()].SetTileVariables('F');
		}
		Game::GetInstance()->IncrementScore(10);
		m_UpdateLives();
		setNumCheese(getNumCheese() - 1);
		TheAudioManager::Instance()->mixVolume(85);
		TheAudioManager::Instance()->playSound("cheese", 0);
		
	}

	if (getNumCheese() <= 0)
	{
		TheAudioManager::Instance()->playSound("Victory", 0);
		m_GoToNextLevel();
	}
}

void Player::m_HandleEatingMysteryCheese() {
	Level* Level = Game::GetInstance()->GetLevel();
	// Handles player eating a mystery cheese
	if (Level->m_Map[GetY()][GetX()].isPowerUp())
	{
		// Change tile to a normal blank tile with its associated variables
		Level->m_Map[GetY()][GetX()].SetSrc('B');
		Level->m_Map[GetY()][GetX()].SetTileVariables('F');
		Game::GetInstance()->IncrementScore(10); //increase score when eating mystery cheese
		m_UpdateLives();
		Game::GetInstance()->IncrementScore(10); //increase score when eating mystery cheese
		m_UpdateLives();
		setNumCheese(getNumCheese()-1);


		

		// Grant player a random ability and start the timer
		Game::GetInstance()->SetAbilityStartTimer(SDL_GetTicks());
		SetAbility(PowerUp::GenerateRandomAbility());
		std::cout << "Your current ability: " << (GetAbility() == DEFEAT_CATS ? "Defeat Cats" : "Enter Walls") << std::endl;

		if (GetAbility() == DEFEAT_CATS) 
		{
			Game::GetInstance()->ChangeCatsToWhite();
			Game::GetInstance()->GetCat(0)->SetAllVulnerable(true);
			Game::GetInstance()->GetCat(0)->SetBlinking(false);
			TheAudioManager::Instance()->playSound("powerup", 0); //play sound effect for mystery cheese
		}
		if (GetAbility() == ENTER_WALL) 
		{
			Game::GetInstance()->ChangeCatsToOriginalColors();
			Game::GetInstance()->GetCat(0)->SetAllVulnerable(false);
			Game::GetInstance()->GetCat(0)->SetBlinking(false);
			TheAudioManager::Instance()->playSound("wall ability", 0); //play sound effect for mystery cheese
		}
	}
	if (getNumCheese() <= 0) 
	{
		m_GoToNextLevel();
	}
}

void Player::m_MovePlayer()
{
	Input_Manager* InputManager = Game::GetInstance()->GetInputManager();
	Level* Level = Game::GetInstance()->GetLevel();
	//player movement input handling: set the destination for the players
	if (!isDead()) {
		if (InputManager->KeyDown(SDL_SCANCODE_W)) {
			if (!isMoving()) {
				SetPlayerAngle(0);
				if (!Level->m_Map[GetY() - 1][GetX()].isObstacle() || isCurrentlyInWall()) {
					SetDestinationY(GetDst().y - TILESIZE);
					SetDestinationX(GetDst().x);
					SetMoving(true);
				}
			}
		}
		else if (InputManager->KeyDown(SDL_SCANCODE_S)) {
			if (!isMoving()) {
				SetPlayerAngle(180);
				if (!Level->m_Map[GetY() + 1][GetX()].isObstacle() || isCurrentlyInWall()) {
					SetDestinationY(GetDst().y + TILESIZE);
					SetDestinationX(GetDst().x);
					SetMoving(true);
				}
			}
		}
		else if (InputManager->KeyDown(SDL_SCANCODE_A)) {
			if (!isMoving()) {
				SetPlayerAngle(270);
				if (!Level->m_Map[GetY()][GetX() - 1].isObstacle() || isCurrentlyInWall())
				{
					SetDestinationX(GetDst().x - TILESIZE);
					SetDestinationY(GetDst().y);
					SetMoving(true);
				}
			}
		}
		else if (InputManager->KeyDown(SDL_SCANCODE_D)) {
			if (!isMoving()) {
				SetPlayerAngle(90);
				if (!Level->m_Map[GetY()][GetX() + 1].isObstacle() || isCurrentlyInWall()) {
					SetDestinationX(GetDst().x + TILESIZE);
					SetDestinationY(GetDst().y);
					SetMoving(true);
				}
			}
		}
	}

	//move to destination
	if (isMoving()) {
		if (GetDestinationX() > GetDst().x) {
			MoveRight();
		}
		else if (GetDestinationX() < GetDst().x) {
			MoveLeft();
		}
		else if (GetDestinationY() > GetDst().y) {
			MoveDown();
		}
		else if (GetDestinationY() < GetDst().y) {
			MoveUp();
		}
		else if (GetDestinationX() == GetDst().x && GetDestinationY() == GetDst().y) {
			SetMoving(false);

			if (!Level->m_Map[GetY()][GetX()].isEnterableWall()) {
				SetCurrentlyInWall(false);
			}
		}
	}
	
}

void Player::m_GoToNextLevel()
{
	Game::GetInstance()->IncrementLevel();
	//set the num of cheese based on which level map we are at
	if (Game::GetInstance()->GetCurrLevel() == 0)
	{
		m_numCheese = 136;
		m_rDst = { TILESIZE * 11, TILESIZE * 13, TILESIZE, TILESIZE };
		m_iDestinationX = 11;
		m_iDestinationY = 13;
		
	}
	else if (Game::GetInstance()->GetCurrLevel() == 1)
	{
		m_numCheese = 173;
		m_rDst = { TILESIZE * 11, TILESIZE * 18, TILESIZE, TILESIZE };
		m_iDestinationX = 11;
		m_iDestinationY = 18;
	}
	else if (Game::GetInstance()->GetCurrLevel() == 2)
	{
		m_numCheese = 140;
		m_rDst = { TILESIZE * 11, TILESIZE * 13, TILESIZE, TILESIZE };
		m_iDestinationX = 11;
		m_iDestinationY = 13;
	}
	else if (Game::GetInstance()->GetCurrLevel() == 3)
	{
		m_numCheese = 162;
		m_rDst = { TILESIZE * 11, TILESIZE * 13, TILESIZE, TILESIZE };
		m_iDestinationX = 11;
		m_iDestinationY = 13;
	}
	else if (Game::GetInstance()->GetCurrLevel() == 4)
	{
		m_numCheese = 134;
		m_rDst = { TILESIZE * 11, TILESIZE * 13, TILESIZE, TILESIZE };
		m_iDestinationX = 11;
		m_iDestinationY = 13;
	}
	else if (Game::GetInstance()->GetCurrLevel() == 5)
	{
		m_numCheese = 254;
		m_rDst = { TILESIZE * 11, TILESIZE * 13, TILESIZE, TILESIZE };
		m_iDestinationX = 11;
		m_iDestinationY = 13;
	}
	SDL_Delay(2000);
	//enable the coundown mechanism
	Game::GetInstance()->SetCountdown(true);


	//m_rDst = { TILESIZE * 11, TILESIZE * 13, TILESIZE, TILESIZE };
	//m_iDestinationX = 11;
	//m_iDestinationY = 13;
	m_bIsMoving = false;

}

void Player::m_UpdateLives()
{
	if (Game::GetInstance()->GetScore() % LIFEINCREASETHRESHOLD == 0)
	{
		//increase lives by 1
		Game::GetInstance()->IncrementLives(); //has built in check to make sure lives are less than 5

	}
}

void Player::UpdateAbilityLength()
{
	if (m_AbilityLength - (Game::GetInstance()->GetLevelNum() * 500) < 6000)
	{
		m_AbilityLength = 6000;
	}
	else
	{
		m_AbilityLength = m_AbilityLength - (Game::GetInstance()->GetLevelNum() * 500);
	}
}

Player::Player(SDL_Rect s, SDL_Rect d)
{
	m_rSrc = s;
	m_rDst = d;
	center.x = center.y = 16;
	m_iAngle = 0;
	m_ability = NONE;
}

bool Player::isMoving()
{
	return m_bIsMoving;
}
bool Player::isPoweredUp()
{ 
	return m_bIsPoweredUp; 
}

bool Player::isDead() 
{ 
	return m_bIsDead; 
}
void Player::setDeath(bool d)
{
	m_bIsDead = d;
}
bool Player::isDying()
{
	return m_bIsDying;
}

bool Player::isCurrentlyInWall()
{
	return m_bCurrentlyInWall;
}
bool Player::enteredWall()
{
	return m_bEnteredWall;
}

int Player::GetX() 
{ 
	return m_rDst.x / 32;
}
int Player::GetY() 
{ 
	return m_rDst.y / 32; 
}

int Player::GetDestinationX()
{
	return m_iDestinationX;
}
int Player::GetDestinationY()
{
	return m_iDestinationY;
}
void Player::SetDestinationX(int destX)
{
	m_iDestinationX = destX;
}
void Player::SetDestinationY(int destY)
{
	m_iDestinationY = destY;
}
void Player::SetMoving(bool b)
{
	m_bIsMoving = b;
}
void Player::SetCurrentlyInWall(bool b)
{
	m_bCurrentlyInWall = b;
}
void Player::SetEnteredWall(bool b)
{
	m_bEnteredWall = b;
}
int Player::GetRightEdgeTile()
{
	return (m_rDst.x %32 ==0 ? m_rDst.x / 32: m_rDst.x /32 +1);
}
int Player::GetLeftEdgeTile()
{
	return m_rDst.x / 32;
}
int Player::GetTopEdgeTile()
{
	return m_rDst.y / 32;
}
int Player::GetBottomEdgeTile()
{
	return (m_rDst.y % 32 == 0 ? m_rDst.y / 32 : m_rDst.y / 32 + 1);
}
void Player::SetPowered(bool b) 
{ 
	m_bIsPoweredUp = b; 
}
void Player::SetAbility(Ability a)
{
	m_ability = a;
}
Ability Player::GetAbility()
{
	return m_ability;
}

void Player::update()
{
	if (m_bIsDying == false) //only update when player not in dying animation
	{
		m_HandlePlayerAbilities();
		m_HandleMovement();
	}
	
}

// new animation function for mouse
void Player::animate()
{

	if (m_bIsDying == false && m_ability != ENTER_WALL) //if player is not in dying animation
	{
		PlayAnim(0,3,5);
	}
	else if (m_bIsDying == true && m_ability !=DEFEAT_CATS) //if player is in dying animation
	{
		
		PlayAnim(4,10,5);
		cout << sprite << endl;
		if (sprite==9)
		{
			m_bIsDead = true;
		}
	}
	else if (m_bIsDying == false && m_ability == ENTER_WALL)
	{
		PlayAnim(11, 14, 5);
	}
}

void Player::PlayAnim(int start, int end, int fps) // plays an animation
{
	if (frame==fps)
	{
		frame = 0;
		sprite++;
		if (sprite>=end)
		{
			sprite = start;
		}
		m_rSrc.x = sprite * m_rSrc.w;
	}
	frame++;
}

void Player::MoveUp()
{
		SetPlayerAngle(0);
		m_rDst.y -= m_iMoveSpeed;
}
void Player::MoveDown()
{
		SetPlayerAngle(180);
		m_rDst.y += m_iMoveSpeed;
}
void Player::MoveLeft()
{
		SetPlayerAngle(270);
		m_rDst.x -= m_iMoveSpeed;
}
void Player::MoveRight()
{
		SetPlayerAngle(90);
		m_rDst.x += m_iMoveSpeed;
}

void Player::SetPlayerSpeed(int speed)
{
	m_iMoveSpeed = speed;
}

void Player::SetDying(bool dying)
{
	m_bIsDying = dying;
}

void Player::SetInvulnerable(bool vuln)
{
	m_bInvulnerable = vuln;
}
bool Player::GetInvulnerable()
{
	return m_bInvulnerable;
}

void Player::SetPlayerAngle(int ang)
{
	m_iAngle = ang;
}
int Player::GetPlayerAngle()
{
	return m_iAngle;
}

void Player::setNumCheese(int num)
{
	m_numCheese = num;
}
int Player::getNumCheese()
{
	return m_numCheese;
}

void Player::Die()
{
	m_bIsDead = true;
	m_rSrc = {};
	
}
