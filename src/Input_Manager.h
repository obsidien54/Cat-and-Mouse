#ifndef INPUT_Manager_H
#define INPUT_Manager_H

#include<iostream>

#include <SDL.h>

using namespace std;

class Input_Manager // Manages order of INPUT scenes
{
private:
    const Uint8* m_iKeyStates; // this is for the game loop
    SDL_Event event;
    //unsigned short m_iNumOfTimesPressed;
    bool m_bLMouseButton_Up;

    int m_iTempX, m_iTempY;


    

public:
    Input_Manager();
    //static Input_Manager* GetInstance();
	bool MouseOver(SDL_Rect rect);
    bool MouseUp_Select(SDL_Rect rect);
    bool KeyDown(SDL_Scancode c);


    ~Input_Manager();


};
#endif