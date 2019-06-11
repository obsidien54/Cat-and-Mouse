#ifndef UI_SCORES_H
#define UI_SCORES_H



#include "UI_Menu.h"
#include "CommonIncludes.h"
#include "TextureManager.h"
#include "SDL_Manager.h"
#include "Button.h"
#include <vector>
#include <glm\vec2.hpp>

class UI_Scores : public UI_Menu // Manages order of UI scenes
{
private:
    SDL_Rect m_rTitle, m_rBack;

	//for button functionality
	vector<Button> buttons;
	SDL_Rect mouseHitBox;
	Button m_mainMenuButton;
    
public:
	bool bBack;

    UI_Scores();
    //static UI_Scores* GetInstance();

	//button controls
	bool IsMouseOverButton(int buttonNum);
	Button GetButton(int buttonNumber);

    void Render(SDL_Renderer* pRenderer);

    SDL_Rect GetRect(unsigned short i);

    ~UI_Scores();


};
#endif