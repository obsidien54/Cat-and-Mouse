#include "Player.h"

Player::Player(SDL_Rect s, SDL_Rect d)
{
	m_rSrc = s;
	m_rDst = d;
	center.x = center.y = 16;
	m_iAngle = 0;
}


bool Player::isPoweredUp()
{
	return m_bIsPoweredUp;
}
bool Player::isDead()
{
	return m_bIsDead;
}

int Player::GetX()
{
	return m_rDst.x / 32;
}
int Player::GetY()
{
	return m_rDst.y / 32;
}

int Player::GetRightEdgeTile()
{
	return (m_rDst.x % 32 == 0 ? m_rDst.x / 32 : m_rDst.x / 32 + 1);
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
	m_rDst.y -= m_IMoveSpeed;
}

void Player::MoveDown()
{
	SetPlayerAngle(180);
	m_rDst.y += m_IMoveSpeed;
}

void Player::MoveLeft()
{
	SetPlayerAngle(270);
	m_rDst.x -= m_IMoveSpeed;
}

void Player::MoveRight()
{
	SetPlayerAngle(90);
	m_rDst.x += m_IMoveSpeed;
}

void Player::SetPlayerSpeed(int speed)
{
	m_IMoveSpeed = speed;
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
