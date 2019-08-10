#include "Tile.h"

Tile::Tile() {}
Tile::Tile(SDL_Rect s, SDL_Rect d) {
	m_rSrc = s;
	m_rDst = d;
}
bool Tile::isObstacle() { return m_bIsObstacle; }
bool Tile::isPoint() { return m_bIsPoint; }
bool Tile::isPowerUp() { return m_bIsPowerUp; }
bool Tile::isIntersection() { return m_bIsIntersection; }

bool Tile::isEnterableWall()
{
	return m_bIsEnterableWall;
}

bool Tile::isLeftWarpTile()
{
	return m_bIsLeftWarp;
}

bool Tile::isRightWarpTile()
{
	return m_bIsRightWarp;
}

bool Tile::isTopLeftWarpTile()
{
	return m_bIsTopLeftWarp;
}

bool Tile::isTopRightWarpTile()
{
	return m_bIsTopRightWarp;
}

bool Tile::isBottomLeftWarpTile()
{
	return m_bIsBottomLeftWarp;
}

bool Tile::isBottomRightWarpTile()
{
	return m_bIsBottomRightWarp;
}

void Tile::SetTileVariables(char c) {
/*VARIABLE MEANINGS:
  ! = TILES WHERE THE PLAYER CAN NEVER WALK ON
  O = CHEESE TILES
  F = FLOOR TILES
  I = INTERSECTIONS
  H = PELLET/INTERSECTION HYBRIDS
  W = ENTERABLE WALLS
  P = POWERUPS	
  L = LEFT WARP TILE
  R = RIGHT WARP TILE							*/

	switch (c) {
	case 'O':
		m_bIsObstacle = false;
		m_bIsPoint = true;
		m_bIsPowerUp = false;
		m_bIsIntersection = false;
		m_bIsEnterableWall = false;
		m_bIsLeftWarp = false;
		m_bIsRightWarp = false;
		m_bIsTopLeftWarp = false;
		m_bIsTopRightWarp = false;
		m_bIsBottomLeftWarp = false;
		m_bIsBottomRightWarp = false;
		break;
	case 'F':
		m_bIsObstacle = false;
		m_bIsPoint = false;
		m_bIsPowerUp = false;
		m_bIsIntersection = false;
		m_bIsEnterableWall = false;
		m_bIsLeftWarp = false;
		m_bIsRightWarp = false;
		m_bIsTopLeftWarp = false;
		m_bIsTopRightWarp = false;
		m_bIsBottomLeftWarp = false;
		m_bIsBottomRightWarp = false;
		break;
	case 'P':
		m_bIsObstacle = false;
		m_bIsPoint = false;
		m_bIsPowerUp = true;
		m_bIsIntersection = false;
		m_bIsEnterableWall = false;
		m_bIsLeftWarp = false;
		m_bIsRightWarp = false;
		m_bIsTopLeftWarp = false;
		m_bIsTopRightWarp = false;
		m_bIsBottomLeftWarp = false;
		m_bIsBottomRightWarp = false;
		break;
	case 'I':
		m_bIsObstacle = false;
		m_bIsPoint = false;
		m_bIsPowerUp = false;
		m_bIsIntersection = true;
		m_bIsEnterableWall = false;
		m_bIsLeftWarp = false;
		m_bIsRightWarp = false;
		m_bIsTopLeftWarp = false;
		m_bIsTopRightWarp = false;
		m_bIsBottomLeftWarp = false;
		m_bIsBottomRightWarp = false;
		break;
	case 'H':
		m_bIsObstacle = false;
		m_bIsPoint = true;
		m_bIsPowerUp = false;
		m_bIsIntersection = true;
		m_bIsEnterableWall = false;
		m_bIsLeftWarp = false;
		m_bIsRightWarp = false;
		m_bIsTopLeftWarp = false;
		m_bIsTopRightWarp = false;
		m_bIsBottomLeftWarp = false;
		m_bIsBottomRightWarp = false;
		break;
	case 'W':
		m_bIsObstacle = true;
		m_bIsPoint = false;
		m_bIsPowerUp = false;
		m_bIsIntersection = false;
		m_bIsEnterableWall = true;
		m_bIsLeftWarp = false;
		m_bIsRightWarp = false;
		m_bIsTopLeftWarp = false;
		m_bIsTopRightWarp = false;
		m_bIsBottomLeftWarp = false;
		m_bIsBottomRightWarp = false;
		break;
	case '!':
		m_bIsObstacle = true;
		m_bIsPoint = false;
		m_bIsPowerUp = false;
		m_bIsIntersection = false;
		m_bIsEnterableWall = false;
		m_bIsLeftWarp = false;
		m_bIsRightWarp = false;
		m_bIsTopLeftWarp = false;
		m_bIsTopRightWarp = false;
		m_bIsBottomLeftWarp = false;
		m_bIsBottomRightWarp = false;
		break;
	case 'L':
		m_bIsObstacle = false;
		m_bIsPoint = false;
		m_bIsPowerUp = false;
		m_bIsIntersection = false;
		m_bIsEnterableWall = false;
		m_bIsLeftWarp = true;
		m_bIsRightWarp = false;
		m_bIsTopLeftWarp = false;
		m_bIsTopRightWarp = false;
		m_bIsBottomLeftWarp = false;
		m_bIsBottomRightWarp = false;
		break;
	case 'R':
		m_bIsObstacle = false;
		m_bIsPoint = false;
		m_bIsPowerUp = false;
		m_bIsIntersection = false;
		m_bIsEnterableWall = false;
		m_bIsLeftWarp = false;
		m_bIsRightWarp = true;
		m_bIsTopLeftWarp = false;
		m_bIsTopRightWarp = false;
		m_bIsBottomLeftWarp = false;
		m_bIsBottomRightWarp = false;
		break;
	case 't':
		m_bIsObstacle = false;
		m_bIsPoint = false;
		m_bIsPowerUp = false;
		m_bIsIntersection = false;
		m_bIsEnterableWall = false;
		m_bIsLeftWarp = false;
		m_bIsRightWarp = false;
		m_bIsTopLeftWarp = true;
		m_bIsTopRightWarp = false;
		m_bIsBottomLeftWarp = false;
		m_bIsBottomRightWarp = false;
		break;
	case 'T':
		m_bIsObstacle = false;
		m_bIsPoint = false;
		m_bIsPowerUp = false;
		m_bIsIntersection = false;
		m_bIsEnterableWall = false;
		m_bIsLeftWarp = false;
		m_bIsRightWarp = false;
		m_bIsTopLeftWarp = false;
		m_bIsTopRightWarp = true;
		m_bIsBottomLeftWarp = false;
		m_bIsBottomRightWarp = false;
		break;
	case 'b':
		m_bIsObstacle = false;
		m_bIsPoint = false;
		m_bIsPowerUp = false;
		m_bIsIntersection = false;
		m_bIsEnterableWall = false;
		m_bIsLeftWarp = false;
		m_bIsRightWarp = false;
		m_bIsTopLeftWarp = false;
		m_bIsTopRightWarp = false;
		m_bIsBottomLeftWarp = true;
		m_bIsBottomRightWarp = false;
		break;
	case 'B':
		m_bIsObstacle = false;
		m_bIsPoint = false;
		m_bIsPowerUp = false;
		m_bIsIntersection = false;
		m_bIsEnterableWall = false;
		m_bIsLeftWarp = false;
		m_bIsRightWarp = false;
		m_bIsTopLeftWarp = false;
		m_bIsTopRightWarp = false;
		m_bIsBottomLeftWarp = false;
		m_bIsBottomRightWarp = true;
		break;
	}
}