
#include "UI_MainMenu.h"




Button UI_MainMenu::GetButton(int buttonNumber)
{
	return buttons[buttonNumber -1];
}

UI_MainMenu::UI_MainMenu()
{
    cout << "Instance of a UI MainMenu Created" << endl;


	mouseHitBox = {0,0,20,20};

	//create the buttons in this menu
	m_playButton.buttonSetUp(glm::vec2(368, 200), PLAY_BUTTON, "play");
	m_howToPlayButton.buttonSetUp(glm::vec2(368, 260), HOW_TO_PLAY_BUTTON, "how to play");
	m_highScoresButton.buttonSetUp(glm::vec2(368, 320), HIGH_SCORES_BUTTON, "high scores");
	m_quitButton.buttonSetUp(glm::vec2(368, 380), QUIT_BUTTON, "quit");
	

	//add all the buttons to the button vector for easy access
	buttons.push_back(m_playButton);
	buttons.push_back(m_howToPlayButton);
	buttons.push_back(m_highScoresButton);
	buttons.push_back(m_quitButton);

	//lower the volume since too loud
	TheAudioManager::Instance()->setMusicVolume(20);

	//background music
	//music by bensound
	TheAudioManager::Instance()->load("../Assets/sound/bensound-endlessmotion.mp3",
		"Background", sound_type::SOUND_MUSIC);

	TheAudioManager::Instance()->playMusic("Background", -1);
}



void UI_MainMenu::Render(SDL_Renderer* pRenderer)
{
	SDL_Surface* sTemp;
	SDL_Texture* tTemp;

	SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
	SDL_RenderClear(pRenderer);

	//Title
	sTemp = TTF_RenderText_Solid(m_pDefaultFontSans, "Main Menu", White);
	tTemp = SDL_CreateTextureFromSurface(pRenderer, sTemp);
	SDL_RenderCopy(pRenderer, tTemp, NULL, &m_rTitle); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture

	SDL_FreeSurface(sTemp);
	SDL_DestroyTexture(tTemp);



	//check if mouse if over the button
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
	for(auto button: buttons ) //for every button in buttons draw it
	{
		button.draw();
	}
	/*button1.draw();
	button2.draw();
	button3.draw();
	button4.draw();
	*/

	//draw the mouse hitbox to see
	SDL_SetRenderDrawColor(pRenderer,255,225,255,255);
	SDL_RenderFillRect(pRenderer, &mouseHitBox);
	SDL_RenderDrawRect(pRenderer, &mouseHitBox);
    
    SDL_RenderPresent(pRenderer);
}

bool UI_MainMenu::IsMouseOverButton(int buttonNum)
{
	return SDL_HasIntersection(buttons[buttonNum].getButtonRect(), &mouseHitBox);
}

SDL_Rect UI_MainMenu::GetRect(unsigned short i)
{
    if (i == 0)
    {
        return m_rHowToPlay;
    }
    else if (i == 1)
    {
        return m_rStart;
    }
    else if (i == 2)
    {
        return m_rScores;
    }
    else
    {
        cout << "SDL_Rect index not found" << endl;
		SDL_Rect temp = {};
        return temp; // FOR warning: control reaches end of non-void function
    }
}


UI_MainMenu::~UI_MainMenu()
{
    
}