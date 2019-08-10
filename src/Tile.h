#pragma once
#include "Sprite.h"
#include <SDL.h>

class Tile : public Sprite {
private:
	bool m_bIsObstacle, m_bIsPoint, m_bIsPowerUp, m_bIsIntersection, m_bIsEnterableWall, m_bIsLeftWarp, m_bIsRightWarp, m_bIsTopLeftWarp, m_bIsTopRightWarp, m_bIsBottomLeftWarp, m_bIsBottomRightWarp;

public:
	Tile();
	Tile(SDL_Rect s, SDL_Rect d);
	bool isObstacle();
	bool isPoint();
	bool isPowerUp();
	bool isIntersection();
	bool isEnterableWall(); 
	bool isLeftWarpTile();
	bool isRightWarpTile();
	bool isTopLeftWarpTile();
	bool isTopRightWarpTile();
	bool isBottomLeftWarpTile();
	bool isBottomRightWarpTile();

	void SetTileVariables(char c);
};