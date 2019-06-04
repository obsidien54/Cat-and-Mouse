#include "Player.h"

Player::Player(SDL_Rect s, SDL_Rect d) 
{
	m_rSrc = s;
	m_rDst = d;
	center.x = center.y = 16;
	m_iAngle = 0;
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

// new animation function for mouse
void Player::animate()
{
	if (m_iFrame == m_iFrameMax)
	{
		m_iFrame = 0;
		m_iSprite++;
		if (m_iSprite == m_iSpriteMax)
		{
			m_iSprite = 0;
		}
		m_rSrc.x = m_iSprite * m_rSrc.w;
	}
	m_iFrame++;
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

void Player::SetPlayerAngle(int ang)
{
	m_iAngle = ang;
}


int Player::GetPlayerAngle()
{
	return m_iAngle;
}

int Player::GetPlayerFrame()
{
	return m_iFrame;
}

void Player::Die()
{
	m_bIsDead = true;
	m_rSrc = {};
}
