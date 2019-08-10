#ifndef UI_LEVELS_H
#define UI_LEVELS_H

#include "UI_Menu.h"


class UI_Levels : public UI_Menu // Manages order of UI scenes
{
private:
    SDL_Rect m_rTitle, m_rLevel1, m_rBack;

    
    
public:
    UI_Levels();
    //static UI_Levels* GetInstance();

    void Render(SDL_Renderer* pRenderer);

    SDL_Rect GetRect(unsigned short i);

    ~UI_Levels();


};
#endif