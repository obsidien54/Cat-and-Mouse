#include "UI_GameOver.h"

Button UI_GameOver::GetButton(int buttonNumber)
{
	return buttons[buttonNumber - 1];
}

UI_GameOver::UI_GameOver()
{
	cout << "Instance of UI Game over Created" << endl;

	mouseHitBox = { 0,0,2,2 };

	//create the buttons in this menu
	button1.buttonSetUp(glm::vec2(300, 350), MAIN_MENU_BUTTON, "main menu");
	button2.buttonSetUp(glm::vec2(500, 350), QUIT_BUTTON, "quit");

	//add all the buttons to the button vector for easy access
	buttons.push_back(button1);
	buttons.push_back(button2);	

	TheTextureManager::Instance()->load("../Assets/textures/Game_Over.png",
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

	for (int i = 0; i < buttons.size(); i++) //for every button in buttons draw it
	{
		if (SDL_HasIntersection(buttons[i].getButtonRect(), &mouseHitBox))
		{
			buttons[i].setState(HOVER); //change the state
			std::cout << "hovering over button" << std::endl;
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

	////draw the mouse hitbox to see
	//SDL_SetRenderDrawColor(pRenderer,255,225,255,255);
	//SDL_RenderFillRect(pRenderer, &mouseHitBox);
	//SDL_RenderDrawRect(pRenderer, &mouseHitBox);

	SDL_RenderPresent(pRenderer);
}

bool UI_GameOver::IsMouseOverButton(int buttonNum)
{
	return SDL_HasIntersection(buttons[buttonNum].getButtonRect(), &mouseHitBox);
}




UI_GameOver::~UI_GameOver()
{

}