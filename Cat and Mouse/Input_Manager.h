#ifndef INPUT_Manager_H
#define INPUT_Manager_H

#include<iostream>
#include <glm\vec2.hpp>
#include <SDL.h>

class Input_Manager // Manages order of INPUT scenes
{
private:
    const Uint8* m_iKeyStates; // this is for the game loop
    SDL_Event event;
    
	SDL_Rect mouseRect;

    int m_iTempX, m_iTempY;


public:
    bool MouseUp_Select(SDL_Rect rect);
    bool KeyDown(SDL_Scancode c);

	Input_Manager();
	~Input_Manager();

};

#endif