#pragma once
#include "Sprite.h"
#include <SDL.h>
#include "PowerUp.h"
#include "AudioManager.h"

class Player : public Sprite 
{
private:
	bool m_bIsPoweredUp = false, m_bIsDead = false, m_bIsMoving = false, m_bCurrentlyInWall = false, m_bEnteredWall = false;;
	int m_iDestinationX, m_iDestinationY;
	int m_iMoveSpeed = 4;
	int m_iAngle; // angle of mouse
	int m_iFrame = 0; // current frame
	int m_iSprite = 0; //sprite counter
	int m_iFrameMax = 5; //number of frames to display each sprite
	int m_iSpriteMax = 3; //number of sprites in anumation
	Ability m_ability = Ability::ENTER_WALL;

public:
	Player(SDL_Rect s, SDL_Rect d);
	SDL_Point center; // pivot point of our mouse
	
	void animate(); // animates mouse
	
	bool isMoving();
	bool isPoweredUp();
	bool isDead();
	bool isCurrentlyInWall();
	bool enteredWall();

	int GetX();
	int GetY();
	int GetDestinationX();
	int GetDestinationY();
	void SetDestinationX(int destX);
	void SetDestinationY(int destY);
	void SetMoving(bool b);
	void SetCurrentlyInWall(bool b);
	void SetEnteredWall(bool b);

	

	int GetRightEdgeTile(); //return the tile that the right edge of the sprite is located in
	int GetLeftEdgeTile(); //return the tile that the left edge of the sprite is located in
	int GetTopEdgeTile();//return the tile that the top edge of the sprite is located in
	int GetBottomEdgeTile();//return the tile that the bottom edge of the sprite is located in

	void SetPowered(bool b); 
	void SetAbility(Ability a);
	Ability GetAbility();


	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void SetPlayerSpeed(int speed); //allow us to change player speed

	void SetPlayerAngle( int ang); //angle for rotation of image
	int GetPlayerAngle();
	int GetPlayerFrame();

	void Die();
};
