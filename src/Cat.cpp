#include "Cat.h"

Cat::Cat(SDL_Rect s, SDL_Rect d) {
	m_rSrc = s;
	m_rDst = d;
	dir = 'd';
	angle = 0;
	center.x = center.y = 16;
}


bool Cat::isVulnerable() { return m_bIsVulnerable; }
bool Cat::isDead() { return m_bIsDead; }

char Cat::getDir() { return dir; }

void Cat::setDir(char d) { dir = d; }

int Cat::GetX() { return m_rDst.x / 32; }

int Cat::GetY() { return m_rDst.y / 32; }

int Cat::GetDestinationX() { return m_IDestinationX; }

int Cat::GetDestinationY() { return m_IDestinationY; }

int Cat::GetTargetX() { return 0; }

int Cat::GetTargetY() { return 0; }

void Cat::SetTargetX(int x) { m_iTargetX = x; }

void Cat::SetTargetY(int y) { m_iTargetY = y; }

void Cat::SetDestinationX(int destX) { m_IDestinationX = destX; }

void Cat::SetDestinationY(int destY) { m_IDestinationY = destY; }

void Cat::SetMoving(bool b) { m_bIsMoving = b; }

void Cat::MoveX(int dir)
{
	m_rDst.x += dir;
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
	m_rDst.y += dir;
	if (dir > 0)
	{
		angle = 0;
	}
	else if (dir < 0)
	{
		angle = 180;
	}
}

bool Cat::isMoving() { return m_bIsMoving; }

void Cat::SetVulnerable(bool b)
{
	if (b) {
		m_bIsVulnerable = true;
		if (!m_bIsDead) {
			m_rSrc = { 128, 0, 32, 32 };
		}
	}
	else {
		m_bIsVulnerable = false;
	}
}

void Cat::Die() {
	m_bIsDead = true;
	m_rSrc = {};
}