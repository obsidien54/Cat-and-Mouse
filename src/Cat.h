#pragma once
#include "Sprite.h"
#include <SDL.h>

class Cat : public Sprite {
private:
	bool m_bIsVulnerable = false, m_bIsDead = false, m_bIsMoving = false;
	int m_IDestinationX, m_IDestinationY;
	char dir;
	int m_iTargetX, m_iTargetY;


public:
	Cat(SDL_Rect s, SDL_Rect d);
	bool isVulnerable();
	bool isDead();
	bool isMoving();
	char getDir();
	void setDir(char d);
	int GetX();
	int GetY();
	int GetDestinationX();
	int GetDestinationY();
	int GetTargetX();
	int GetTargetY();
	void SetTargetX(int x);
	void SetTargetY(int y);
	void SetDestinationX(int destX);
	void SetDestinationY(int destY);
	void SetMoving(bool b);

	void MoveX(int dir);
	void MoveY(int dir);

	void SetVulnerable(bool b);
	void Die();
	int frame;
	int frameX;
	int angle;
	SDL_Point center;
};