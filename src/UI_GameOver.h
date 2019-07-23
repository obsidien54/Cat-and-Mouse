#pragma once

#include <SDL_image.h>
#include "UI_Menu.h"
#include "AudioManager.h"
#include "TextureManager.h"
#include "SDL_Manager.h"
#include "Button.h"
#include <vector>
#include "Game.h"
#include <glm\vec2.hpp>

class UI_GameOver : public UI_Menu
{
private:

	SDL_Rect mouseHitBox;

	vector<Button> buttons;

	Button button1; //main menu button
	Button button2; //quit button

public:
	Button GetButton(int buttonNumber);


	UI_GameOver();
	void Render(SDL_Renderer* pRenderer);
	void RenderScores(SDL_Renderer* pRenderer);

	bool IsMouseOverButton(int buttonNum);


	~UI_GameOver();

};