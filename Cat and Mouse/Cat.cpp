#include "Cat.h"
#include "Game.h"
#include <iostream>
#include <vector>

int Cat::m_sState = C_State::WAITING;
bool Cat::m_sIsVulnerable = false;
bool Cat::m_sBlinking = false;
int Cat::m_ScatterLength = 780;
void Cat::UpdateScatterLength()
{
	if (m_ScatterLength - (Game::GetInstance()->GetLevelNum() * 30) < 180)
	{
		m_ScatterLength = 180;
	}
	else
	{
		m_ScatterLength = m_ScatterLength - (Game::GetInstance()->GetLevelNum() * 50);
	}
}

Cat::Cat(SDL_Rect s, SDL_Rect d, int cat) {
	m_rSrc = s;
	m_rDst = d;
	dir = 'w';
	m_moveSpeed = 2;
	angle = 0;
	center.x = center.y = m_rDst.w / 2;
	SetState(C_State::WAITING);
	checkBound = false;
	SetDying(false);
	SetDead(false);
	frames = 0;
	m_CatNum = cat;
}

void Cat::Sync()
{
	if (GetState() != GetAllState())
	{
		SetState(GetAllState());
		frames = 0;
	}
}


bool Cat::IsAllVulnerable()
{
	return m_sIsVulnerable;
}

void Cat::SetAllVulnerable(bool b)
{
	if (IsAllVulnerable() != b)
	{
		Game::GetInstance()->GetCat(0)->setReverse(true);
		Game::GetInstance()->GetCat(1)->setReverse(true);
		Game::GetInstance()->GetCat(2)->setReverse(true);
		Game::GetInstance()->GetCat(3)->setReverse(true);
	}
	m_sIsVulnerable = b;
}

void Cat::SetBlinking(bool b)
{
	m_sBlinking = b;
}

bool Cat::GetBlinking()
{
	return m_sBlinking;
}

bool Cat::IsDead() { return m_bIsDead; }

void Cat::SetDead(bool d)
{
	m_bIsDead = d;
}

char Cat::GetDir() { return dir; }

void Cat::SetDir(char d) { dir = d; }

int Cat::GetX() { return (m_rDst.x + m_rDst.w / 2) / m_rDst.w; }

int Cat::GetY() { return (m_rDst.y + m_rDst.h / 2) / m_rDst.h; }

int Cat::GetDestinationX() { return m_IDestinationX; }

int Cat::GetDestinationY() { return m_IDestinationY; }

int Cat::GetTargetX() { return m_iTargetX; }

int Cat::GetTargetY() { return m_iTargetY; }

void Cat::SetTargetX(int x) { m_iTargetX = x; }

void Cat::SetTargetY(int y) { m_iTargetY = y; }

void Cat::SetDestinationX(int destX) { m_IDestinationX = destX; }

void Cat::SetDestinationY(int destY) { m_IDestinationY = destY; }

void Cat::SetMoving(bool b) { m_bIsMoving = b; }

bool Cat::IsMoving() { return m_bIsMoving; }

void Cat::Animate()
{
	if (GetState() == C_State::DEATH)
	{
		return;
	}
	if (m_bIsDying != true) //if cat is not in dying animation
	{
		if (m_iFrame == m_iFrameMax)
		{
			m_iFrame = 0;
			m_iSprite++;
			if (m_iSprite == m_iSpriteMax)
			{
				m_iSprite = 0;
				m_rSrc.x = m_CatNum * 192 + (m_iSprite * m_rSrc.w);
			}

			if ((GetState() == C_State::SCATTER || GetState() == C_State::SEEK) && IsAllVulnerable())
			{
				if (GetBlinking())
				{

					if (m_iVurnerable == 0)
					{
						m_rSrc.x = 4 * 192 + (m_iSprite * m_rSrc.w);
						m_iVurnerable = 1;
					}
					else
					{
						m_rSrc.x = m_CatNum * 192 + (m_iSprite * m_rSrc.w);
						m_iVurnerable = 0;
					}
				}
				else
				{
					m_rSrc.x = 4 * 192 + (m_iSprite * m_rSrc.w);
				}
			}
			else
			{
				m_rSrc.x = m_CatNum * 192 + (m_iSprite * m_rSrc.w);
			}
		}
		m_iFrame++;
	}
	else if (m_bIsDying == true) //if cat is in dying animation
	{
		if (m_iDeathFrame == m_iDeathFrameMax)
		{
			m_iDeathFrame = 0;
			m_iDeathSprite++;
			if (m_iDeathSprite == m_iDeathSpriteMax)
			{
				m_iDeathSprite = 0;
				m_bIsDying = false; //get out of dying animation
				this->Die();
			}
			m_rSrc.x = 5 * 192 + (m_iDeathSprite * m_rSrc.w); //choose among the death animations
		}
		m_iDeathFrame++;
	}
}

void Cat::ResetCell() { m_iSprite = 0; m_iFrame = 0; }

void Cat::SetState(int state) { m_State = state; }

void Cat::SetAllState(int state)
{
	m_sState = state;
}
int Cat::GetState() { return m_State; }

int Cat::GetAllState()
{
	return m_sState;
}

void Cat::SetPriority(int first, int second, int third, int forth)
{
	DirectionPriority[0] = first;
	DirectionPriority[1] = second;
	DirectionPriority[2] = third;
	DirectionPriority[3] = forth;
}

int Cat::GetPriority(int index) { return DirectionPriority[index]; }

void Cat::MoveX(int dir)
{
	m_rDst.x += dir * m_moveSpeed;
	if (dir > 0)
	{
		angle = 270;
	}
	else if (dir < 0)
	{
		angle = 90;
	}
}

void Cat::MoveY(int dir)
{
	m_rDst.y += dir * m_moveSpeed;
	if (dir > 0)
	{
		angle = 0;
	}
	else if (dir < 0)
	{
		angle = 180;
	}
}

void Cat::ReverseDirection()
{
	//return;
	switch (GetDir())
	{
	case 'w':
		SetDir('s');
		break;
	case 'd':
		SetDir('a');
		break;
	case 'a':
		SetDir('d');
		break;
	case 's':
		SetDir('w');
		break;
	}
}

void Cat::TargetPlayer()
{
	switch (m_CatNum)
	{
	case 0: //first cat will target the player directly
		SetTargetX(Game::GetInstance()->GetPlayer()->GetX());
		SetTargetY(Game::GetInstance()->GetPlayer()->GetY());
		break;
	case 1:
		if (Game::GetInstance()->GetPlayer()->GetPlayerAngle() == 0) //if the player is moving up
		{
			SetTargetX(Game::GetInstance()->GetPlayer()->GetX());
			SetTargetY(Game::GetInstance()->GetPlayer()->GetY() - 4);
		}
		else if (Game::GetInstance()->GetPlayer()->GetPlayerAngle() == 90) //if the player is moving right
		{
			SetTargetX(Game::GetInstance()->GetPlayer()->GetX() + 4);
			SetTargetY(Game::GetInstance()->GetPlayer()->GetY());
		}
		else if (Game::GetInstance()->GetPlayer()->GetPlayerAngle() == 180) //if the player is moving down
		{
			SetTargetX(Game::GetInstance()->GetPlayer()->GetX());
			SetTargetY(Game::GetInstance()->GetPlayer()->GetY() + 4);
		}
		else if (Game::GetInstance()->GetPlayer()->GetPlayerAngle() == 270) //if the player is moving left
		{
			SetTargetX(Game::GetInstance()->GetPlayer()->GetX() - 4);
			SetTargetY(Game::GetInstance()->GetPlayer()->GetY());
		}
		break;
	case 2:
		//find the tile 2 spaces ahead of the mouse
		int tempTileX, tempTileY;
		if (Game::GetInstance()->GetPlayer()->GetPlayerAngle() == 0) //if the player is moving up
		{
			tempTileX = (Game::GetInstance()->GetPlayer()->GetX());
			tempTileY = (Game::GetInstance()->GetPlayer()->GetY() - 2);
		}
		else if (Game::GetInstance()->GetPlayer()->GetPlayerAngle() == 90) //if the player is moving right
		{
			tempTileX = (Game::GetInstance()->GetPlayer()->GetX() + 2);
			tempTileY = (Game::GetInstance()->GetPlayer()->GetY());
		}
		else if (Game::GetInstance()->GetPlayer()->GetPlayerAngle() == 180) //if the player is moving down
		{
			tempTileX = (Game::GetInstance()->GetPlayer()->GetX());
			tempTileY = (Game::GetInstance()->GetPlayer()->GetY() + 2);
		}
		else if (Game::GetInstance()->GetPlayer()->GetPlayerAngle() == 270) //if the player is moving left
		{
			tempTileX = (Game::GetInstance()->GetPlayer()->GetX() - 2);
			tempTileY = (Game::GetInstance()->GetPlayer()->GetY());
		}

		//create the "vector between the first cat and the tile 2 ahead of the mouse"
		int vectorX, vectorY;
		vectorX = tempTileX - Game::GetInstance()->GetCat(0)->GetX();
		vectorY = tempTileY - Game::GetInstance()->GetCat(0)->GetY();

		//add the vector to the tile 2 ahead of the cat
		int targetX, targetY;
		targetX = tempTileX + vectorX;
		targetY = tempTileY + vectorY;


		//set the targets for the cat
		SetTargetX(targetX);
		SetTargetY(targetY);

		break;
	case 3:

		if (m_DistanceToMouseSquared() >= 64) //if more than 8 tiles away (since using squared distance 8 squared is 64)
		{
			SetTargetX(Game::GetInstance()->GetPlayer()->GetX());
			SetTargetY(Game::GetInstance()->GetPlayer()->GetY());
		}
		else
		{
			SetTargetX(21);
			SetTargetY(21);
		}
		break;
	}
}

void Cat::TargetScatter()
{
	switch (m_CatNum)
	{
	case 0:
		SetTargetX(1);
		SetTargetY(1);
		break;
	case 1:
		SetTargetX(1);
		SetTargetY(21);
		break;
	case 2:
		SetTargetX(21);
		SetTargetY(1);
		break;
	case 3:
		SetTargetX(21);
		SetTargetY(21);
		break;

	}
}

void Cat::TargetDeath()
{
	switch (Game::GetInstance()->GetCurrLevel())
	{
	case 1 :
		SetTargetX(11);
		SetTargetY(14);
		break;
	default:
		SetTargetX(11);
		SetTargetY(9);
		break;
	}
	SetTargetX(11);
	SetTargetY(9);
}

// helper function for seek
void Cat::DistanceNorth()
{
	// if North is not an obstacle and if the direction is the opposite of the checking direction to prevent U-turn
	int temp = 0;
	if (!(Game::GetInstance()->GetLevel()->m_Map[GetY() - 1][GetX()].isObstacle()) && GetDir() != 's')
	{
		temp = 0;// reseting and checking the distance
		temp += (GetTargetX() - GetX()) * (GetTargetX() - GetX());
		temp += (GetTargetY() - (GetY() - 1)) * (GetTargetY() - (GetY() - 1));
		//std::cout << "CAT CHECK NORTH :" << temp << std::endl;
		if (distance > temp)
		{
			distance = temp;
			newDir = 'w';
		}
	}
}
// helper function for seek
void Cat::DistanceEast()
{
	// if East is not an obstacle and if the direction is the opposite of the checking direction to prevent U-turn
	if (!(Game::GetInstance()->GetLevel()->m_Map[GetY()][GetX() + 1].isObstacle()) && GetDir() != 'a')
	{
		int temp = 0;
		temp += (GetTargetX() - (GetX() + 1)) * (GetTargetX() - (GetX() + 1));
		temp += (GetTargetY() - GetY()) * (GetTargetY() - GetY());
		//std::cout << "CAT CHECK EAST :" << temp << std::endl;
		if (distance > temp)
		{
			distance = temp;
			newDir = 'd';
		}
	}
}
// helper function for seek
void Cat::DistanceSouth()
{
	// if South is not an obstacle and if the direction is the opposite of the checking direction to prevent U-turn
	if (!(Game::GetInstance()->GetLevel()->m_Map[GetY() + 1][GetX()].isObstacle()) && GetDir() != 'w')
	{
		int temp = 0;
		temp += (GetTargetX() - GetX()) * (GetTargetX() - GetX());
		temp += (GetTargetY() - (GetY() + 1)) * (GetTargetY() - (GetY() + 1));
		//std::cout << "CAT CHECK SOUTH :" << temp << std::endl;
		if (distance > temp)
		{
			distance = temp;
			newDir = 's';
		}
	}
}
// helper function for seek
void Cat::DistanceWest()
{
	// if West is not an obstacle and if the direction is the opposite of the checking direction to prevent U-turn
	if (!(Game::GetInstance()->GetLevel()->m_Map[GetY()][GetX() - 1].isObstacle()) && !(GetDir() == 'd'))
	{
		int temp = 0;
		temp += (GetTargetX() - (GetX() - 1)) * (GetTargetX() - (GetX() - 1));
		temp += (GetTargetY() - GetY()) * (GetTargetY() - GetY());
		//std::cout << "CAT CHECK WEST :" << temp << std::endl;
		if (distance > temp)
		{
			distance = temp;
			newDir = 'a';
		}
	}
}
//// flee

void Cat::FleeDistanceNorth()
{
	// if North is not an obstacle and if the direction is the opposite of the checking direction to prevent U-turn
	int temp = 0;
	if (!(Game::GetInstance()->GetLevel()->m_Map[GetY() - 1][GetX()].isObstacle()) && GetDir() != 's')
	{
		temp = 0;// reseting and checking the distance
		temp += (GetTargetX() - GetX()) * (GetTargetX() - GetX());
		temp += (GetTargetY() - (GetY() - 1)) * (GetTargetY() - (GetY() - 1));
		//std::cout << "CAT CHECK NORTH :" << temp << std::endl;
		if (distance < temp)
		{
			distance = temp;
			newDir = 'w';
		}
	}
}
// helper function for seek
void Cat::FleeDistanceEast()
{
	// if East is not an obstacle and if the direction is the opposite of the checking direction to prevent U-turn
	if (!(Game::GetInstance()->GetLevel()->m_Map[GetY()][GetX() + 1].isObstacle()) && GetDir() != 'a')
	{
		int temp = 0;
		temp += (GetTargetX() - (GetX() + 1)) * (GetTargetX() - (GetX() + 1));
		temp += (GetTargetY() - GetY()) * (GetTargetY() - GetY());
		//std::cout << "CAT CHECK EAST :" << temp << std::endl;
		if (distance < temp)
		{
			distance = temp;
			newDir = 'd';
		}
	}
}
// helper function for seek
void Cat::FleeDistanceSouth()
{
	// if South is not an obstacle and if the direction is the opposite of the checking direction to prevent U-turn
	if (!(Game::GetInstance()->GetLevel()->m_Map[GetY() + 1][GetX()].isObstacle()) && GetDir() != 'w')
	{
		int temp = 0;
		temp += (GetTargetX() - GetX()) * (GetTargetX() - GetX());
		temp += (GetTargetY() - (GetY() + 1)) * (GetTargetY() - (GetY() + 1));
		//std::cout << "CAT CHECK SOUTH :" << temp << std::endl;
		if (distance < temp)
		{
			distance = temp;
			newDir = 's';
		}
	}
}
// helper function for seek
void Cat::FleeDistanceWest()
{
	// if West is not an obstacle and if the direction is the opposite of the checking direction to prevent U-turn
	if (!(Game::GetInstance()->GetLevel()->m_Map[GetY()][GetX() - 1].isObstacle()) && !(GetDir() == 'd'))
	{
		int temp = 0;
		temp += (GetTargetX() - (GetX() - 1)) * (GetTargetX() - (GetX() - 1));
		temp += (GetTargetY() - GetY()) * (GetTargetY() - GetY());
		//std::cout << "CAT CHECK WEST :" << temp << std::endl;
		if (distance < temp)
		{
			distance = temp;
			newDir = 'a';
		}
	}
}

void Cat::Flee()
{
	distance = 0;
	int temp = 0;
	// Check if the square cat is on is an intersection
	if (!IsMoving())
	{
		if (!checkBound) {
			if (Game::GetInstance()->GetLevel()->m_Map[GetY()][GetX()].isIntersection())
			{
				checkBound = true;
				for (int dirPriority = 0; dirPriority < 4; dirPriority++)
				{
					switch (GetPriority(dirPriority))
					{
					case 0:
						FleeDistanceNorth();
						break;
					case 1:
						FleeDistanceEast();
						break;
					case 2:
						FleeDistanceSouth();
						break;
					case 3:
						FleeDistanceWest();
						break;
					}
				}
				SetDir(newDir);
				newDir = 'q';
			}
		}
	}
	// if not moving then move in a direction
	if (!IsMoving()) {
		if (GetDir() == 'w') {
			// If not an obstacle then sets the new destination square
			if (!Game::GetInstance()->GetLevel()->m_Map[GetY() - 1][GetX()].isObstacle()) {
				SetDestinationY(GetDst().y - 32);
				SetDestinationX(GetDst().x);
				SetMoving(true);
			}
			else // if Obstacle it will check for another route 
			{//need to edit to take in direction priority
				if (!Game::GetInstance()->GetLevel()->m_Map[GetY()][GetX() + 1].isObstacle())
				{
					SetDir('d');
				}
				else if (!Game::GetInstance()->GetLevel()->m_Map[GetY()][GetX() - 1].isObstacle())
				{
					SetDir('a');
				}
				else
				{
					SetDir('s');
				}
			}
		}
		else if (GetDir() == 's') {
			if (!Game::GetInstance()->GetLevel()->m_Map[GetY() + 1][GetX()].isObstacle()) {
				SetDestinationY(GetDst().y + 32);
				SetDestinationX(GetDst().x);
				SetMoving(true);
			}
			else
			{//need to edit to take in direction priority
				if (!Game::GetInstance()->GetLevel()->m_Map[GetY()][GetX() - 1].isObstacle())
				{
					SetDir('a');
				}
				else if (!Game::GetInstance()->GetLevel()->m_Map[GetY()][GetX() + 1].isObstacle())
				{
					SetDir('d');
				}
				else
				{
					SetDir('w');
				}
			}
		}
		else if (GetDir() == 'a') {
			if (!Game::GetInstance()->GetLevel()->m_Map[GetY()][GetX() - 1].isObstacle())
			{
				SetDestinationX(GetDst().x - 32);
				SetDestinationY(GetDst().y);
				SetMoving(true);
			}
			else
			{//need to edit to take in direction priority
				if (!Game::GetInstance()->GetLevel()->m_Map[GetY() - 1][GetX()].isObstacle())
				{
					SetDir('w');
				}
				else if (!Game::GetInstance()->GetLevel()->m_Map[GetY() + 1][GetX()].isObstacle())
				{
					SetDir('s');
				}
				else
				{
					SetDir('d');
				}
			}
		}
		else if (GetDir() == 'd') {
			if (!Game::GetInstance()->GetLevel()->m_Map[GetY()][GetX() + 1].isObstacle()) {
				SetDestinationX(GetDst().x + 32);
				SetDestinationY(GetDst().y);
				SetMoving(true);
			}
			else
			{//need to edit to take in direction priority
				if (!Game::GetInstance()->GetLevel()->m_Map[GetY() - 1][GetX()].isObstacle())
				{
					SetDir('w');
				}
				else if (!Game::GetInstance()->GetLevel()->m_Map[GetY() + 1][GetX()].isObstacle())
				{
					SetDir('s');
				}
				else
				{
					SetDir('a');
				}
			}
		}
	}
	// if moving continue moving till
	if (IsMoving()) {
		//Animate(); //moved to game render function
		if (GetDestinationX() > GetDst().x) {
			MoveX(1);
		}
		else if (GetDestinationX() < GetDst().x) {
			MoveX(-1);
		}
		else if (GetDestinationY() > GetDst().y) {
			MoveY(1);
		}
		else if (GetDestinationY() < GetDst().y) {
			MoveY(-1);
		}
		// if cat has gotten to destination then set moving to false
		else if (GetDestinationX() == GetDst().x && GetDestinationY() == GetDst().y) {
			SetMoving(false);
		}
	}
	if (!Game::GetInstance()->GetLevel()->m_Map[GetY()][GetX()].isIntersection() && checkBound)
	{
		checkBound = false;
	}
}

void Cat::setReverse(bool b)
{
	if (m_reverse == true && b == true)
	{
		m_reverse = false;
		return;
	}
	m_reverse = b;
}

bool Cat::getReverse()
{
	return m_reverse;
}

void Cat::TransistionReverse()
{
	if (!IsMoving())
	{
		ReverseDirection();
		setReverse(false);
		
	}
}



//// end flee

//retrun the squared distance form the cat to the mouse
int Cat::m_DistanceToMouseSquared()
{
	int distance;
	distance = (Game::GetInstance()->GetPlayer()->GetX() - GetX())* (Game::GetInstance()->GetPlayer()->GetX() - GetX()) +
		(Game::GetInstance()->GetPlayer()->GetY() - GetY())* (Game::GetInstance()->GetPlayer()->GetY() - GetY());
	return distance;
}

void Cat::Seek()
{
	distance = 999999;
	int temp = 0;
	// Check if the square cat is on is an intersection
	if (!IsMoving())
	{
		if (!checkBound) {
			if (Game::GetInstance()->GetLevel()->m_Map[GetY()][GetX()].isIntersection())
			{
				checkBound = true;
				for (int dirPriority = 0; dirPriority < 4; dirPriority++)
				{
					switch (GetPriority(dirPriority))
					{
					case 0:
						DistanceNorth();
						break;
					case 1:
						DistanceEast();
						break;
					case 2:
						DistanceSouth();
						break;
					case 3:
						DistanceWest();
						break;
					}
				}
				SetDir(newDir);
				newDir = 'q';
			}
		}
	}
	// if not moving then move in a direction
	if (!IsMoving()) {
		if (GetDir() == 'w') {
			// If not an obstacle then sets the new destination square
			if (!Game::GetInstance()->GetLevel()->m_Map[GetY() - 1][GetX()].isObstacle()) {
				SetDestinationY(GetDst().y - 32);
				SetDestinationX(GetDst().x);
				SetMoving(true);
			}
			else // if Obstacle it will check for another route 
			{
				if (!Game::GetInstance()->GetLevel()->m_Map[GetY()][GetX() + 1].isObstacle())
				{
					SetDir('d');
				}
				else if (!Game::GetInstance()->GetLevel()->m_Map[GetY()][GetX() - 1].isObstacle())
				{
					SetDir('a');
				}
				else
				{
					SetDir('s');
				}
			}
		}
		else if (GetDir() == 's') {
			if (!Game::GetInstance()->GetLevel()->m_Map[GetY() + 1][GetX()].isObstacle()) {
				SetDestinationY(GetDst().y + 32);
				SetDestinationX(GetDst().x);
				SetMoving(true);
			}
			else
			{
				if (!Game::GetInstance()->GetLevel()->m_Map[GetY()][GetX() - 1].isObstacle())
				{
					SetDir('a');
				}
				else if (!Game::GetInstance()->GetLevel()->m_Map[GetY()][GetX() + 1].isObstacle())
				{
					SetDir('d');
				}
				else
				{
					SetDir('w');
				}
			}
		}
		else if (GetDir() == 'a') {
			if (!Game::GetInstance()->GetLevel()->m_Map[GetY()][GetX() - 1].isObstacle())
			{
				SetDestinationX(GetDst().x - 32);
				SetDestinationY(GetDst().y);
				SetMoving(true);
			}
			else
			{//need to edit to take in direction priority
				if (!Game::GetInstance()->GetLevel()->m_Map[GetY() - 1][GetX()].isObstacle())
				{
					SetDir('w');
				}
				else if (!Game::GetInstance()->GetLevel()->m_Map[GetY() + 1][GetX()].isObstacle())
				{
					SetDir('s');
				}
				else
				{
					SetDir('d');
				}
			}
		}
		else if (GetDir() == 'd') {
			if (!Game::GetInstance()->GetLevel()->m_Map[GetY()][GetX() + 1].isObstacle()) {
				SetDestinationX(GetDst().x + 32);
				SetDestinationY(GetDst().y);
				SetMoving(true);
			}
			else
			{//need to edit to take in direction priority
				if (!Game::GetInstance()->GetLevel()->m_Map[GetY() - 1][GetX()].isObstacle())
				{
					SetDir('w');
				}
				else if (!Game::GetInstance()->GetLevel()->m_Map[GetY() + 1][GetX()].isObstacle())
				{
					SetDir('s');
				}
				else
				{
					SetDir('a');
				}
			}
		}
	}
	// if moving continue moving till
	if (IsMoving()) {
		if (GetDestinationX() > GetDst().x) {
			MoveX(1);
		}
		else if (GetDestinationX() < GetDst().x) {
			MoveX(-1);
		}
		else if (GetDestinationY() > GetDst().y) {
			MoveY(1);
		}
		else if (GetDestinationY() < GetDst().y) {
			MoveY(-1);
		}
		// if cat has gotten to destination then set moving to false
		else if (GetDestinationX() == GetDst().x && GetDestinationY() == GetDst().y) {
			SetMoving(false);
		}
	}
	if (!Game::GetInstance()->GetLevel()->m_Map[GetY()][GetX()].isIntersection() && checkBound)
	{
		checkBound = false;
	}
}


void Cat::SetDying(bool dying)
{
	m_bIsDying = dying;
}

bool Cat::IsDying()
{
	return m_bIsDying;
}

void Cat::Update()
{
	if (getReverse())
	{
		TransistionReverse();
		if (getReverse())
		{
			if (IsMoving()) {
				if (GetDestinationX() > GetDst().x) {
					MoveX(1);
				}
				else if (GetDestinationX() < GetDst().x) {
					MoveX(-1);
				}
				else if (GetDestinationY() > GetDst().y) {
					MoveY(1);
				}
				else if (GetDestinationY() < GetDst().y) {
					MoveY(-1);
				}
				// if cat has gotten to destination then set moving to false
				else if (GetDestinationX() == GetDst().x && GetDestinationY() == GetDst().y) {
					SetMoving(false);
				}
			}
			return;
		}
	}

	switch (GetState())
	{
	case C_State::IDLE:
		break;
	case C_State::WAITING:
		switch (Game::GetInstance()->GetCurrLevel())
		{
		case 0:
			if (Game::GetInstance()->GetPlayer()->getNumCheese() < 137 - (m_CatNum * 10))
			{
				SetDestinationY(GetDst().y - 64);
				SetDestinationX(GetDst().x);
				SetState(C_State::WAKEUP);
				SetDir('w');
			}
			break;
		case 1:
			if (Game::GetInstance()->GetPlayer()->getNumCheese() < 174 - (m_CatNum * 10))
			{
				SetDestinationY(GetDst().y - 64);
				SetDestinationX(GetDst().x);
				SetState(C_State::WAKEUP);
				SetDir('w');
			}
			break;
		case 2:
			if (Game::GetInstance()->GetPlayer()->getNumCheese() < 141 - (m_CatNum * 10))
			{
				SetDestinationY(GetDst().y - 64);
				SetDestinationX(GetDst().x);
				SetState(C_State::WAKEUP);
				SetDir('w');
			}
			break;
		case 3:
			if (Game::GetInstance()->GetPlayer()->getNumCheese() < 162 - (m_CatNum * 10))
			{
				SetDestinationY(GetDst().y - 64);
				SetDestinationX(GetDst().x);
				SetState(C_State::WAKEUP);
				SetDir('w');
			}
			break;
		case 4:
			if (Game::GetInstance()->GetPlayer()->getNumCheese() < 135 - (m_CatNum * 10))
			{
				SetDestinationY(GetDst().y - 64);
				SetDestinationX(GetDst().x);
				SetState(C_State::WAKEUP);
				SetDir('w');
			}
			break;
		case 5:
			if (Game::GetInstance()->GetPlayer()->getNumCheese() < 255 - (m_CatNum * 10))
			{
				SetDestinationY(GetDst().y - 64);
				SetDestinationX(GetDst().x);
				SetState(C_State::WAKEUP);
				SetDir('w');
			}
			break;
		}
		break;
	case C_State::WAKEUP:
		SetMoving(true);
		if (IsMoving()) {
			if (GetDestinationX() > GetDst().x) {
				MoveX(1);
			}
			else if (GetDestinationX() < GetDst().x) {
				MoveX(-1);
			}
			else if (GetDestinationY() > GetDst().y) {
				MoveY(1);
			}
			else if (GetDestinationY() < GetDst().y) {
				MoveY(-1);
			}
			// if cat has gotten to destination then set moving to false
			else if (GetDestinationX() == GetDst().x && GetDestinationY() == GetDst().y) {
				SetMoving(false);
				SetState(C_State::SCATTER);
				SetAllState(C_State::SCATTER);
				frames = 0;
			}
		}
		break;
	case C_State::SCATTER:
		Sync();
		if (IsAllVulnerable())
		{
			TargetScatter();
			Seek();
		}
		else {
			if (frames >= m_ScatterLength)
			{
				SetAllState(C_State::SEEK);
			}
			else
			{
				frames++;
				TargetScatter();
				Seek();
			}
		}
		break;
	case C_State::SEEK:
		Sync();
		if (IsAllVulnerable())
		{
			TargetScatter();
			Seek();
		}
		else {

			if (frames >= 1500)
			{
				SetAllState(C_State::SCATTER);
			}
			else
			{
				frames++;
				TargetPlayer();
				Seek();
			}
		}
		break;
	case C_State::DYING:
		TargetDeath();
		Seek();
		if (!IsMoving())
		{
			SetMoveSpeed(8);
			if (GetX() == GetTargetX() && GetY() == GetTargetY())
			{
				cout << "CAT " << m_CatNum << " back to pen" << endl;
				SetState(C_State::BACK2PEN);
				frames = 0;
				SetDestinationY(GetDst().y + 64);
				SetDestinationX(GetDst().x);
			}
		}
		break;
	case C_State::BACK2PEN:
		SetMoving(true);
		if (IsMoving()) {
			if (GetDestinationX() > GetDst().x) {
				MoveX(1);
			}
			else if (GetDestinationX() < GetDst().x) {
				MoveX(-1);
			}
			else if (GetDestinationY() > GetDst().y) {
				MoveY(1);
			}
			else if (GetDestinationY() < GetDst().y) {
				MoveY(-1);
			}
			// if cat has gotten to destination then set moving to false
			else if (GetDestinationX() == GetDst().x && GetDestinationY() == GetDst().y) {
				SetMoving(false);
				SetState(C_State::DEATH);
				frames = 0;
				SetMoveSpeed(2);
			}
		}
		break;
	case C_State::DEATH:
		frames++;
		if (frames >= 600)
		{
			cout << "CAT " << m_CatNum << " RESPAWN" << endl;

			dir = 'w';
			m_moveSpeed = 2;
			angle = 0;
			SetState(C_State::WAITING);
			checkBound = false;
			SetDying(false);
			SetDead(false);
			frames = 0;
			m_iSprite = 0;
			m_iFrame = 0;
			SetDead(false);
			SetDestinationY(GetDst().y - 32);
			SetDestinationX(GetDst().x);
			SetState(C_State::WAKEUP);
		}
		break;
	}

}


void Cat::Die()
{
	SetDead(true);
	SetState(C_State::DYING);
}

void Cat::SetMoveSpeed(int m)
{
	m_moveSpeed = m;
}

