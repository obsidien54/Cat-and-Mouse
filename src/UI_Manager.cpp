
#include "UI_Manager.h"


UI_Manager::UI_Manager()
{
    m_iCurrentScreenIndex = 0;
    //m_bWaitingForInput = true;
    //m_pInput = Input_Manager::GetInstance();
    //m_pHowToPlay = UI_HowToPlay::GetInstance();
    //m_pScores = UI_Scores::GetInstance();
	
	

    cout << "Instance of a UI Manager Created" << endl;
}
/*
UI_Manager* UI_Manager::GetInstance()
{
    static UI_Manager* instance = new UI_Manager();

    return instance;
}
*/


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


	if (m_pInput.KeyDown(SDL_SCANCODE_1)) // Potential change of scenes
	{
		SetScreenIndex(eMenu::HOW_TO_PLAY); // Via enums
	}
	if (m_pInput.KeyDown(SDL_SCANCODE_2))
	{
		bGameIsRunning = true;
		cout << "Game will start" << endl;
	}
	if (m_pInput.KeyDown(SDL_SCANCODE_3))
	{
		SetScreenIndex(eMenu::SCORES); // Via enums
	}


	if (m_pInput.KeyDown(SDL_SCANCODE_ESCAPE))
	{
		bSDLRunning = false;
	}
}

void UI_Manager::HowToPlay (SDL_Renderer* pRenderer)
{
    m_pHowToPlay.Render(pRenderer);

	if (m_pInput.KeyDown(SDL_SCANCODE_1)) // Via Enum indexes
	{
		//m_pMainMenu.RenderMouseOver(pRenderer, i); Not Implemented in other classes
		//cout << "MouseOver Detected" << endl;

		SetScreenIndex(eMenu::MAIN_MENU); // Via enums
		cout << "Screen changed" << endl;
	}
	
}

void UI_Manager::Scores (SDL_Renderer* pRenderer)
{
    m_pScores.Render(pRenderer);

	if (m_pInput.KeyDown(SDL_SCANCODE_1)) // Via Enum indexes
	{
		//m_pMainMenu.RenderMouseOver(pRenderer, i);
		//cout << "MouseOver Detected" << endl;

			
		SetScreenIndex(eMenu::MAIN_MENU); // Via enums
		cout << "Screen changed" << endl;
			
	}
	
}


UI_Manager::~UI_Manager()
{
    /*
    if (m_pInput != nullptr)
    {
        delete m_pInput;
    }
    if (m_pHowToPlay != nullptr)
    {
        delete m_pHowToPlay;
    }
    if (m_pScores != nullptr)
    {
        delete m_pScores;
    }
    */
}