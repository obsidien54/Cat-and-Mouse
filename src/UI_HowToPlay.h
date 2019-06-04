#ifndef UI_HOWTOPLAY_H
#define UI_HOWTOPLAY_H



#include "UI_Menu.h"


class UI_HowToPlay : public UI_Menu // Manages order of UI scenes
{
private:
    SDL_Rect m_rTitle, m_rBack;

    
    
public:
    UI_HowToPlay();
    //static UI_HowToPlay* GetInstance();

    void Render(SDL_Renderer* pRenderer);

    SDL_Rect GetRect(unsigned short i);

    ~UI_HowToPlay();


};
#endif