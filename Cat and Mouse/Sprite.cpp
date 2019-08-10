#include "Sprite.h"

Sprite::Sprite() {}
Sprite::Sprite(SDL_Rect s, SDL_Rect d) {
	m_rSrc = s;
	m_rDst = d;
}
Sprite::~Sprite() {}

SDL_Rect Sprite::GetSrc() { return m_rSrc; }
SDL_Rect Sprite::GetDst() { return m_rDst; }
SDL_Rect* Sprite::GetSrcP() { return &m_rSrc; }
SDL_Rect* Sprite::GetDstP() { return &m_rDst; }

void Sprite::SetSrc(char c) {
	if (c == 'B' || c == 'i') // Blank Tile
		m_rSrc = { 448,128,64,64 };
	else if (c == 'A' || c == 'W') // Straight Verticle Walls
		m_rSrc = { 192,0,64,64 };
	else if (c == 'H') // Straight Horizontal Walls
		m_rSrc = { 128,0,64,64 };
	else if (c == 'O') // Power Up Tile
		m_rSrc = { 320,128,64,64 };
	else if (c == 'P' || c == 'I') // Pellet Tile
		m_rSrc = { 384,128,64,64 };
	else if (c == 'G') // Grass Tiles
		m_rSrc = { 0,0,64,64 };
	else if (c == '1') //lower roof
		m_rSrc = { 0,64,64,64 };
	else if (c == '2') //Left Roof
		m_rSrc = { 64,64,64,64 };
	else if (c == '3')//upper roof
		m_rSrc = { 128,64,64,64 };
	else if (c == '4') //Right Roof
		m_rSrc = { 192,64,64,64 };
	else if (c == '5') //bottom-left roof
		m_rSrc = { 256,64,64,64 };
	else if (c == '6') //bottom-right Roof
		m_rSrc = { 320,64,64,64 };
	else if (c == '7')//top-right roof
		m_rSrc = { 384,64,64,64 };
	else if (c == '8') //top-left Roof
		m_rSrc = { 448,64,64,64 };
	else if (c == '!') //top-right wall
		m_rSrc = { 256,0,64,64 };
	else if (c == '@') //bottom-right wall
		m_rSrc = { 320,0,64,64 };
	else if (c == '#')//bottom-left wall
		m_rSrc = { 384,0,64,64 };
	else if (c == '$') //top-left wall
		m_rSrc = { 448,0,64,64 };
	else if (c == '%') //right wall T
		m_rSrc = { 0,128,64,64 };
	else if (c == '^') //left wall T
		m_rSrc = { 64,128,64,64 };
	else if (c == '&')//bottom wall T
		m_rSrc = { 128,128,64,64 };
	else if (c == '*') //top wall T
		m_rSrc = { 192,128,64,64 };
	else if (c == 'F')//Floor tiles
		m_rSrc = { 64, 0, 64, 64 };
	else
	{
		m_rSrc = { 96,0,32,32 };
	}
}

void Sprite::SetSrc(SDL_Rect src) {
	m_rSrc = src;
}

void Sprite::SetDst(SDL_Rect d) { 
	m_rDst = d; 
}

void Sprite::SetDst(int x, int y)
{
	m_rDst.x = x;
	m_rDst.y = y;
}