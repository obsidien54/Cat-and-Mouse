#ifndef UI_MAINMENU_H
#define UI_MAINMENU_H

#include <SDL_image.h>
#include "UI_Menu.h"
#include "AudioManager.h"
#include "TextureManager.h"
#include "SDL_Manager.h"
#include "Button.h"

class UI_MainMenu : public UI_Menu
{
private:
    

    SDL_Rect m_rTitle, m_rHowToPlay,
    m_rLevels, m_rScores, m_rQuit;
    
	Button button1;
	Button button2;
	Button button3;
    
public:
    UI_MainMenu();
    //static UI_MainMenu* GetInstance();

    void Render (SDL_Renderer* pRenderer);

    SDL_Rect GetRect(unsigned short i);

    ~UI_MainMenu();

};
#endif