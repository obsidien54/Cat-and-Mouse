#ifndef UI_MAINMENU_H
#define UI_MAINMENU_H

#include <SDL_image.h>
#include "UI_Menu.h"
#include "AudioManager.h"
#include "TextureManager.h"
#include "SDL_Manager.h"
#include "Button.h"
#include <vector>
#include "Game.h"
#include <glm\vec2.hpp>

class UI_MainMenu : public UI_Menu
{
private:
    SDL_Rect m_rTitle, m_rHowToPlay,
    m_rStart, m_rScores, m_rQuit;

	SDL_Rect mouseHitBox;
    
	vector<Button> buttons;

	Button button1; //play button
	Button button2; //how to play button
	Button button3; //high scores button
	Button button4; //quit button
	Button button5; //main menu scores
    
public:
	Button GetButton(int buttonNumber);

	bool bHowToPlayPressed, bStartPressed, bScoresPressed, bEscPressed;

    UI_MainMenu();
    void Render (SDL_Renderer* pRenderer);

	bool IsMouseOverButton(int buttonNum);


    SDL_Rect GetRect(unsigned short i);

    ~UI_MainMenu();

};
#endif