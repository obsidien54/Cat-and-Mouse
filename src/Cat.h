#pragma once
#include "Sprite.h"
#include <SDL.h>

enum C_State {
	IDLE,
	WAITING,
	WAKEUP,
	SCATTER,
	SEEK,
	DYING,
	BACK2PEN,
	DEATH
};
enum CatDirection {
	C_UP,
	C_RIGHT,
	C_DOWN,
	C_LEFT
};


class Cat : public Sprite {
private:
	static bool m_sIsVulnerable;
	static bool m_sBlinking;
	static int m_sState;
	//bool m_bIsVulnerable = false;
	bool m_bIsDead = false, m_bIsMoving = false;
	bool m_bIsDying = false;
	int m_IDestinationX, m_IDestinationY;
	char dir;
	int m_iTargetX, m_iTargetY;
	int m_CatNum;
	int m_iSprite = 0;
	int m_iSpriteMax = 3;
	int m_iFrameMax = 6;
	int m_iFrame = 0;
	int m_iVurnerable = 0;
	int m_iDeathFrame = 0; // current death frame
	int m_iDeathSprite = 0; //death sprite counter
	int m_iDeathFrameMax = 10; //number of frames to display each death sprite
	int m_iDeathSpriteMax = 3; //number of death sprites in animation
	int m_State;
	bool checkBound;
	int m_moveSpeed;
	int DirectionPriority[4];
	//////
	void DistanceNorth();
	void DistanceEast();
	void DistanceSouth();
	void DistanceWest();
	/////
	void FleeDistanceNorth();
	void FleeDistanceEast();
	void FleeDistanceSouth();
	void FleeDistanceWest();
	void Flee();
	void ReverseDirection();
	/////
	int m_DistanceToMouseSquared();



public:

	char newDir;
	int distance;
	int frames;
	Cat(SDL_Rect s, SDL_Rect d, int cat = 0);
	void Sync();
	bool IsWhite();
	bool IsAllVulnerable();
	void SetAllVulnerable(bool b);
	void SetBlinking(bool b);
	bool GetBlinking();
	bool IsDead();
	void SetDead(bool d);
	bool IsMoving();
	char GetDir();
	void SetDir(char d);
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
	void SetState(int state);
	void SetAllState(int state);
	int GetState();
	int GetAllState();
	void SetPriority(int first, int second, int third, int forth);
	int GetPriority(int index);

	void MoveX(int dir);
	void MoveY(int dir);

	void Animate();
	void ResetCell();

	void TargetPlayer();
	void TargetScatter();
	void TargetDeath();
	void Seek();
	void Update();

	void SetDying(bool dying);
	bool IsDying();
	void Die();
	int frame;
	int frameX;
	int angle;
	SDL_Point center;

	void SetMoveSpeed(int m);
};