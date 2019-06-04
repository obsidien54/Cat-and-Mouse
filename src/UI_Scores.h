#ifndef UI_SCORES_H
#define UI_SCORES_H



#include "UI_Menu.h"


class UI_Scores : public UI_Menu // Manages order of UI scenes
{
private:
    SDL_Rect m_rTitle, m_rBack;

    
    
public:
    UI_Scores();
    //static UI_Scores* GetInstance();

    void Render(SDL_Renderer* pRenderer);

    SDL_Rect GetRect(unsigned short i);

    ~UI_Scores();


};
#endif