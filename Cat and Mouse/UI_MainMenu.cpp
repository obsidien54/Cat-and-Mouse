
#include "UI_MainMenu.h"




Button UI_MainMenu::GetButton(int buttonNumber)
{
	return buttons[buttonNumber -1];
}

UI_MainMenu::UI_MainMenu()
{
    cout << "Instance of a UI MainMenu Created" << endl;
  
	m_rTitle.x = 350;  //controls the rect's x coordinate 
	m_rTitle.y = 30; // controls the rect's y coordinte
	m_rTitle.w = 200; // controls the width of the rect
	m_rTitle.h = 100; // These are all specific to ONE TEXT Title ... Data driven design

	m_rHowToPlay.x = m_rTitle.x + 100;  //controls the rect's x coordinate 
	m_rHowToPlay.y = m_rTitle.y + 50; // controls the rect's y coordinte
	m_rHowToPlay.w = m_rTitle.w; // controls the width of the rect
	m_rHowToPlay.h = m_rTitle.h; // These are all specific to ONE TEXT Title ... Data driven design

	

	mouseHitBox = {0,0,2,2};

	//create the buttons in this menu
	button1.buttonSetUp(glm::vec2(500, 200), PLAY_BUTTON, "play");
	button2.buttonSetUp(glm::vec2(500, 260), HOW_TO_PLAY_BUTTON, "how to play");
	button3.buttonSetUp(glm::vec2(500, 320), HIGH_SCORES_BUTTON, "high scores");
	button4.buttonSetUp(glm::vec2(500, 380), QUIT_BUTTON, "quit");
	//button5.buttonSetUp(glm::vec2(450, 440), MAIN_MENU_BUTTON, "main menu");

	//add all the buttons to the button vector for easy access
	buttons.push_back(button1);
	buttons.push_back(button2);
	buttons.push_back(button3);
	buttons.push_back(button4);
	//buttons.push_back(button5);

	//lower the volume since too loud
	TheAudioManager::Instance()->setMusicVolume(128);

	//background music
	
	/*TheAudioManager::Instance()->load("Assets/sound/Ms. Pac-Man Maze Madness OST Menu.mp3",
		"Main_Menu_Background", sound_type::SOUND_MUSIC);*/


		// Video game music composed my Takashi Tateishi
	TheAudioManager::Instance()->load("Assets/sound/Andre Menu Music.mp3",
		"Main_Menu_Background", sound_type::SOUND_MUSIC);

	////music by bensound
	//TheAudioManager::Instance()->load("Assets/sound/bensound-endlessmotion.mp3",
	//	"Main_Menu_Background", sound_type::SOUND_MUSIC);

	TheAudioManager::Instance()->playMusic("Main_Menu_Background", -1);

	TheTextureManager::Instance()->load("Assets/textures/MainMenu_background.png",
		"MainMenu_background", SDL_Manager::GetInstance()->GetRenderer());
	
}



void UI_MainMenu::Render(SDL_Renderer* pRenderer)
{
	SDL_Surface* sTemp;
	SDL_Texture* tTemp;

	SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
	SDL_RenderClear(pRenderer);
	
	
	TheTextureManager::Instance()->draw("MainMenu_background",
		SDL_Manager::GetInstance()->GetRenderer(), 23 * TILESIZE, 23 * TILESIZE);
	//Title
	sTemp = TTF_RenderText_Solid(m_pDefaultFontSans, "Cat-and", White);
	tTemp = SDL_CreateTextureFromSurface(pRenderer, sTemp);
	SDL_RenderCopy(pRenderer, tTemp, NULL, &m_rTitle); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture

	SDL_FreeSurface(sTemp);
	SDL_DestroyTexture(tTemp);

	SDL_Surface* sTemp1;
	SDL_Texture* tTemp1;
	sTemp1 = TTF_RenderText_Solid(m_pDefaultFontSans, "Mouse", White);
	tTemp1 = SDL_CreateTextureFromSurface(pRenderer, sTemp1);
	SDL_RenderCopy(pRenderer, tTemp1, NULL, &m_rHowToPlay);

	SDL_FreeSurface(sTemp1);
	SDL_DestroyTexture(tTemp1);

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

	////draw the mouse hitbox to see
	//SDL_SetRenderDrawColor(pRenderer,255,225,255,255);
	//SDL_RenderFillRect(pRenderer, &mouseHitBox);
	//SDL_RenderDrawRect(pRenderer, &mouseHitBox);
    
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