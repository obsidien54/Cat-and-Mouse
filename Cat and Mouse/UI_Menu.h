#ifndef UI_MENU_H
#define UI_MENU_H


#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>

using namespace std;


class UI_Menu // Manages order of UI scenes
{
protected:
    TTF_Font* m_pDefaultFontSans;
    SDL_Color White;
    
public:
    UI_Menu();
    
    //void Render(SDL_Renderer* pRenderer); // Virtual function to override?

    ~UI_Menu();


};
#endif