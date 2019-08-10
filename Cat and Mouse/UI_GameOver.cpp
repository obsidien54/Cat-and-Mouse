#include "UI_GameOver.h"
#include "UI_Scores.h"

Button UI_GameOver::GetButton(int buttonNumber)
{
	return buttons[buttonNumber - 1];
}

UI_GameOver::UI_GameOver()
{
	cout << "Instance of UI Game over Created" << endl;

	mouseHitBox = { 0,0,2,2 };

	//create the buttons in this menu
	button1.buttonSetUp(glm::vec2(90, 50), MAIN_MENU_BUTTON, "main menu");
	button2.buttonSetUp(glm::vec2(650, 50), QUIT_BUTTON, "quit");

	//add all the buttons to the button vector for easy access
	buttons.push_back(button1);
	buttons.push_back(button2);

	TheTextureManager::Instance()->load("../Cat and Mouse/Assets/textures/Game_Over.png",
		"game over", SDL_Manager::GetInstance()->GetRenderer());

}



void UI_GameOver::Render(SDL_Renderer* pRenderer)
{

	SDL_RenderClear(pRenderer);

	TheTextureManager::Instance()->draw("game over",
		SDL_Manager::GetInstance()->GetRenderer(), 23 * TILESIZE, 23 * TILESIZE);

	////check if mouse if over the button
	SDL_Event event;
	SDL_PollEvent(&event);
	if (event.type == SDL_MOUSEMOTION)
	{
		mouseHitBox.x = event.button.x;
		mouseHitBox.y = event.button.y;
	}
	else
	{
		SDL_PushEvent(&event);
	}

	for (int i = 0; i < buttons.size(); i++) //for every button in buttons draw it
	{
		if (SDL_HasIntersection(buttons[i].getButtonRect(), &mouseHitBox))
		{
			buttons[i].setState(HOVER); //change the state
			//std::cout << "hovering over button" << std::endl;
		}
		else
		{
			buttons[i].setState(NORMAL);
		}
	}


	//draw the buttons
	for (auto button : buttons) //for every button in buttons draw it
	{
		button.draw();
	}

	RenderScores(pRenderer);


	////draw the mouse hitbox to see
	//SDL_SetRenderDrawColor(pRenderer,255,225,255,255);
	//SDL_RenderFillRect(pRenderer, &mouseHitBox);
	//SDL_RenderDrawRect(pRenderer, &mouseHitBox);

	SDL_RenderPresent(pRenderer);
}

void UI_GameOver::RenderScores(SDL_Renderer* pRenderer) {
	SDL_Surface* sTemp;
	SDL_Texture* tTemp;

	SDL_SetRenderDrawColor(pRenderer, 0, 0, 255, 100);
	SDL_Rect backgroundRect = { 220, 0, 300, 250 };
	SDL_RenderFillRect(pRenderer, &backgroundRect);
	SDL_RenderDrawRect(pRenderer, &backgroundRect);

	vector<int> m_scores = UI_Scores::GetHighscores();
	SDL_Rect scoreDisplayRect;

	for (int i = 0; i < 5; i++) {
		std::string scoreToText;

		if (m_scores[i] == 0) {
			scoreToText = std::to_string(i + 1) + "-----";
		}
		else {
			scoreToText = std::to_string(i + 1) + ": " + std::to_string(m_scores[i]);
		}


		sTemp = TTF_RenderText_Solid(m_pDefaultFontSans, scoreToText.c_str(), White);
		tTemp = SDL_CreateTextureFromSurface(pRenderer, sTemp);
		scoreDisplayRect.x = 230;
		scoreDisplayRect.y = 50 * i;
		SDL_QueryTexture(tTemp, NULL, NULL, &scoreDisplayRect.w, &scoreDisplayRect.h);

		SDL_RenderCopy(pRenderer, tTemp, NULL, &scoreDisplayRect);

		SDL_FreeSurface(sTemp);
		SDL_DestroyTexture(tTemp);
	}

	for (int i = 5; i < 10; i++) {
		std::string scoreToText;

		if (m_scores[i] == 0) {
			scoreToText = std::to_string(i + 1) + "-----";
		}
		else {
			scoreToText = std::to_string(i + 1) + ": " + std::to_string(m_scores[i]);
		}

		sTemp = TTF_RenderText_Solid(m_pDefaultFontSans, scoreToText.c_str(), White);
		tTemp = SDL_CreateTextureFromSurface(pRenderer, sTemp);
		scoreDisplayRect.x = 390;
		scoreDisplayRect.y = 50 * (i - 5);
		SDL_QueryTexture(tTemp, NULL, NULL, &scoreDisplayRect.w, &scoreDisplayRect.h);


		SDL_RenderCopy(pRenderer, tTemp, NULL, &scoreDisplayRect);

		SDL_FreeSurface(sTemp);
		SDL_DestroyTexture(tTemp);
	}

	int score = Game::GetInstance()->GetScore();
	std::string scoreToText = "Your score: " + std::to_string(score);

	scoreDisplayRect.x = 240;
	scoreDisplayRect.y = 330;

	sTemp = TTF_RenderText_Solid(m_pDefaultFontSans, scoreToText.c_str(), White);
	tTemp = SDL_CreateTextureFromSurface(pRenderer, sTemp);
	SDL_QueryTexture(tTemp, NULL, NULL, &scoreDisplayRect.w, &scoreDisplayRect.h);
	SDL_RenderCopy(pRenderer, tTemp, NULL, &scoreDisplayRect);

	SDL_FreeSurface(sTemp);
	SDL_DestroyTexture(tTemp);

}

bool UI_GameOver::IsMouseOverButton(int buttonNum)
{
	return SDL_HasIntersection(buttons[buttonNum].getButtonRect(), &mouseHitBox);
}




UI_GameOver::~UI_GameOver()
{

}