#include "UI_HowToPlay.h"

UI_HowToPlay::UI_HowToPlay()
{
    //cout << "Instance of a UI HowToPlay Created" << endl;
	m_rTitle.x = 350;  //controls the rect's x coordinate 
	m_rTitle.y = 30; // controls the rect's y coordinte
	m_rTitle.w = 200; // controls the width of the rect
	m_rTitle.h = 100; // These are all specific to ONE TEXT Title ... Data driven design

   

	mouseHitBox = { 0,0,2,2 };
	m_mainMenuButton.buttonSetUp(glm::vec2(368, 570), MAIN_MENU_BUTTON, "main menu");
	buttons.push_back(m_mainMenuButton);
}

bool UI_HowToPlay::IsMouseOverButton(int buttonNum)
{
	return SDL_HasIntersection(buttons[buttonNum].getButtonRect(), &mouseHitBox);
}

Button UI_HowToPlay::GetButton(int buttonNumber)
{
	return buttons[buttonNumber - 1];
}

void UI_HowToPlay::Render(SDL_Renderer* pRenderer)
{
    SDL_Surface* sTemp;
    SDL_Texture* tTemp;

	SDL_RenderClear(pRenderer);
	
	TheTextureManager::Instance()->draw("MainMenu_background",
		SDL_Manager::GetInstance()->GetRenderer(), 23 * TILESIZE, 23 * TILESIZE);

    //Title
    
    sTemp = TTF_RenderText_Solid(m_pDefaultFontSans, "How To Play", White);
    tTemp = SDL_CreateTextureFromSurface(pRenderer, sTemp);
    SDL_RenderCopy(pRenderer, tTemp, NULL, &m_rTitle); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture
    
    SDL_FreeSurface(sTemp);
    SDL_DestroyTexture(tTemp);
    SDL_Surface* sTemp1;
    SDL_Texture* tTemp1;

    // Back
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 255, 255);
    SDL_RenderDrawRect(pRenderer, &m_rBack);
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
    sTemp1 = TTF_RenderText_Solid(m_pDefaultFontSans, "4. Back", White);
    tTemp1 = SDL_CreateTextureFromSurface(pRenderer, sTemp1);
    SDL_RenderCopy(pRenderer, tTemp1, NULL, &m_rBack); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture
    
    SDL_FreeSurface(sTemp1);
    SDL_DestroyTexture(tTemp1);
    
	//draw the buttons and their state
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
	//SDL_SetRenderDrawColor(pRenderer, 255, 225, 255, 255);
	//SDL_RenderFillRect(pRenderer, &mouseHitBox);
	//SDL_RenderDrawRect(pRenderer, &mouseHitBox);

    SDL_RenderPresent(pRenderer);
}

SDL_Rect UI_HowToPlay::GetRect(unsigned short i)
{
    if (i == 0)
    {
        return m_rBack;
    }
    else
    {
        cout << "SDL_Rect index not found" << endl;
		SDL_Rect temp = {};
        return temp; // FOR warning: control reaches end of non-void function
    }
}

UI_HowToPlay::~UI_HowToPlay()
{
    
}