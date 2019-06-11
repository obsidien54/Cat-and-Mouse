#ifndef UI_HOWTOPLAY_H
#define UI_HOWTOPLAY_H



#include "UI_Menu.h"
#include "Button.h"
#include <vector>
#include <glm\vec2.hpp>

class UI_HowToPlay : public UI_Menu // Manages order of UI scenes
{
private:
    SDL_Rect m_rTitle, m_rBack;

	vector<Button> buttons;
	SDL_Rect mouseHitBox;
	Button m_mainMenuButton;
    
public:
	bool bBack;

    UI_HowToPlay();
    //static UI_HowToPlay* GetInstance();

	//button controls
	bool IsMouseOverButton(int buttonNum);
	Button GetButton(int buttonNumber);

    void Render(SDL_Renderer* pRenderer);

    SDL_Rect GetRect(unsigned short i);

    ~UI_HowToPlay();


};
#endif