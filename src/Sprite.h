#pragma once
#include <SDL.h>

class Sprite {
protected:
	SDL_Rect m_rSrc; // Source Rect
	SDL_Rect m_rDst; // Destination Rect

public:
	Sprite();
	Sprite(SDL_Rect s, SDL_Rect d);
	~Sprite();
	
	SDL_Rect GetSrc();
	SDL_Rect GetDst();
	SDL_Rect* GetSrcP();
	SDL_Rect* GetDstP();

	void SetSrc(char c);
	void SetSrc(SDL_Rect src);
	void SetDst(SDL_Rect d);

	void SetDst(int x, int y);
	
};