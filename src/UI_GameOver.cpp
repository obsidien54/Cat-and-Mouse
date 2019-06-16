#include "UI_GameOver.h"

Button UI_GameOver::GetButton(int buttonNumber)
{
	return buttons[buttonNumber - 1];
}

UI_GameOver::UI_GameOver()
{
	cout << "Instance of UI Game over Created" << endl;

	m_rTitle.x = 350;  //controls the rect's x coordinate 
	m_rTitle.y = 30; // controls the rect's y coordinte
	m_rTitle.w = 200; // controls the width of the rect
	m_rTitle.h = 100; // These are all specific to ONE TEXT Title ... Data driven design




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
	//cout << "at game over screen";
	SDL_Surface* sTemp;
	SDL_Texture* tTemp;

	SDL_RenderClear(pRenderer);


	TheTextureManager::Instance()->draw("game over",
		SDL_Manager::GetInstance()->GetRenderer(), 23 * TILESIZE, 23 * TILESIZE);
	
	//Title
	sTemp = TTF_RenderText_Solid(m_pDefaultFontSans, "Game Over", White);
	tTemp = SDL_CreateTextureFromSurface(pRenderer, sTemp);
	SDL_RenderCopy(pRenderer, tTemp, NULL, &m_rTitle); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture

	SDL_FreeSurface(sTemp);
	SDL_DestroyTexture(tTemp);


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

SDL_Rect UI_GameOver::GetRect(unsigned short i)
{
	if (i == 0)
	{
		return m_rTitle;
	}
	else
	{
		cout << "SDL_Rect index not found" << endl;
		SDL_Rect temp = {};
		return temp; // FOR warning: control reaches end of non-void function
	}
}


UI_GameOver::~UI_GameOver()
{

}