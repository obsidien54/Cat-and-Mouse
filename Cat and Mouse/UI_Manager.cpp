
#include "UI_Manager.h"


UI_Manager::UI_Manager()
{
    m_iCurrentScreenIndex = 0;

	TheAudioManager::Instance()->load("Assets/sound/12 - Crash Man (1).wav",
		"Background", sound_type::SOUND_MUSIC);

	TheAudioManager::Instance()->load("Assets/sound/Button.wav",
		"Button", sound_type::SOUND_SFX);


    cout << "Instance of a UI Manager Created" << endl;
}

UI_Manager* UI_Manager::GetInstance()
{
    static UI_Manager* instance = new UI_Manager();

    return instance;
}



void UI_Manager::Start(SDL_Renderer* pRenderer, bool& bRunning, bool& bGameIsRunning)
{

	SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
    // Displays MENU
	
	if (m_iCurrentScreenIndex == eMenu::MAIN_MENU)
	{
		MainMenu(pRenderer, bRunning, bGameIsRunning);
	}
	else if (m_iCurrentScreenIndex == eMenu::HOW_TO_PLAY)
	{
		HowToPlay(pRenderer);
	}
	else if (m_iCurrentScreenIndex == eMenu::SCORES)
	{
		Scores(pRenderer);
	}
	else if (m_iCurrentScreenIndex == eMenu::GAME_OVER)
	{
		/*cout << "switched to game over";*/
		GameOver(pRenderer, bRunning);
	}
	else
	{
		cout << "Menu Option not found" << endl;
	}
}

void UI_Manager::SetScreenIndex (unsigned short i) // Use initializer list
{
    m_iCurrentScreenIndex = i;
}

void UI_Manager::MainMenu(SDL_Renderer* pRenderer, bool &bSDLRunning, bool &bGameIsRunning)
{
	
    m_pMainMenu.Render(pRenderer);
	SDL_Event event;

	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				cout << "clicking" << endl;
				if (m_pMainMenu.GetButton(1).getState() == HOVER)
				{
					TheAudioManager::Instance()->playSound("Button", 0);
					bGameIsRunning = true;
					TheAudioManager::Instance()->playMusic("Background", -1);
					Game::GetInstance()->SetScore(0);
					

					cout << "Game will start" << endl;
				}
				if (m_pMainMenu.GetButton(2).getState() == HOVER)
				{
					TheAudioManager::Instance()->playSound("Button", 0);
					SetScreenIndex(eMenu::HOW_TO_PLAY);
				}
				if (m_pMainMenu.GetButton(3).getState() == HOVER)
				{
					TheAudioManager::Instance()->playSound("Button", 0);
					UI_Scores::RetrieveHighscores();
					SetScreenIndex(eMenu::SCORES); // Via enums
				}
				if (m_pMainMenu.GetButton(4).getState() == HOVER)
				{
					TheAudioManager::Instance()->playSound("Button", 0);
					bSDLRunning = false;
				}
			}
		}
		if (event.type == SDL_QUIT)
		{
			bSDLRunning = false;
		}
	}
}

void UI_Manager::HowToPlay (SDL_Renderer* pRenderer)
{
    m_pHowToPlay.Render(pRenderer);

	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_MOUSEBUTTONDOWN:
			
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				cout << "clicking" << endl;
				if (m_pHowToPlay.GetButton(1).getState() == HOVER)
				{
					TheAudioManager::Instance()->playSound("Button", 0);
					SetScreenIndex(eMenu::MAIN_MENU); // Via enums
					cout << "Screen changed" << endl;
				}

			}
			break;
		}
	}


}

void UI_Manager::Scores (SDL_Renderer* pRenderer)
{
    m_pScores.Render(pRenderer);

	
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_MOUSEBUTTONDOWN:

			if (event.button.button == SDL_BUTTON_LEFT)
			{
				cout << "clicking" << endl;
				if (m_pScores.GetButton(1).getState() == HOVER)
				{
					TheAudioManager::Instance()->playSound("Button", 0);
					SetScreenIndex(eMenu::MAIN_MENU); // Via enums
					cout << "Screen changed" << endl;
				}

			}
			break;
		}
	}

}

void UI_Manager::GameOver(SDL_Renderer * pRenderer, bool &bSDLRunning)
{
	m_pGameOver.Render(pRenderer);

	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			bSDLRunning = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				cout << "clicking" << endl;
				if (m_pGameOver.GetButton(1).getState() == HOVER)
				{
					TheAudioManager::Instance()->playSound("Button", 0);
					SetScreenIndex(eMenu::MAIN_MENU); // Via enums
					TheAudioManager::Instance()->playMusic("Main_Menu_Background", -1);
					cout << "Screen changed" << endl;
				}
				else if (m_pGameOver.GetButton(2).getState() == HOVER)
				{
					TheAudioManager::Instance()->playSound("Button", 0);
					bSDLRunning = false;
				}
			}
			break;
		}
	}
}


UI_Manager::~UI_Manager()
{
  
}