#ifndef UI_SCORES_H
#define UI_SCORES_H



#include "UI_Menu.h"
#include "CommonIncludes.h"
#include "TextureManager.h"
#include "SDL_Manager.h"
#include "Button.h"
#include <vector>
#include <glm\vec2.hpp>
#include <fstream>

class UI_Scores : public UI_Menu // Manages order of UI scenes
{
private:
	SDL_Rect m_rTitle, m_rBack;

	//for button functionality
	vector<Button> buttons;
	SDL_Rect mouseHitBox;
	Button m_mainMenuButton;
	static vector<int> m_scores;
	SDL_Rect scoreDisplayRect;

public:
	bool bBack;

	UI_Scores();

	//button controls
	bool IsMouseOverButton(int buttonNum);
	Button GetButton(int buttonNumber);

	void Render(SDL_Renderer* pRenderer);
	void RenderScores(SDL_Renderer* pRenderer);

	SDL_Rect GetRect(unsigned short i);

	static void RetrieveHighscores();
	static vector<int> GetHighscores();

	~UI_Scores();


};
#endif