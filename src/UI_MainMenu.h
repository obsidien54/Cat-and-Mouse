#ifndef UI_MAINMENU_H
#define UI_MAINMENU_H

#include <SDL_image.h>
#include "UI_Menu.h"

class UI_MainMenu : public UI_Menu
{
private:
    SDL_Rect m_rTitle, m_rHowToPlay,
    m_rStart, m_rScores, m_rQuit;
    
    
public:
    UI_MainMenu();
    //static UI_MainMenu* GetInstance();
	void RenderMouseOver(SDL_Renderer* pRenderer, unsigned short i);
    void Render (SDL_Renderer* pRenderer);

    SDL_Rect GetRect(unsigned short i);

    ~UI_MainMenu();

};
#endif