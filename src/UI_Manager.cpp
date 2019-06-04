
#include "UI_Manager.h"


UI_Manager::UI_Manager()
{
    m_iCurrentScreenIndex = 0;
    //m_bWaitingForInput = true;
    //m_pInput = Input_Manager::GetInstance();
    //m_pHowToPlay = UI_HowToPlay::GetInstance();
    //m_pLevels = UI_Levels::GetInstance();
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
    
    // Displays MENU
    if (m_iCurrentScreenIndex == eType::MAIN_MENU)
    {
        MainMenu(pRenderer, bRunning);
    }
    else if (m_iCurrentScreenIndex == eType::HOW_TO_PLAY)
    {
        HowToPlay(pRenderer);
    }
    else if (m_iCurrentScreenIndex == eType::LEVELS)
    {
        Levels(pRenderer, bGameIsRunning);
    }
    else if (m_iCurrentScreenIndex == eType::SCORES)
    {
        Scores(pRenderer);
    }
    else if (m_iCurrentScreenIndex == eType::QUIT)
    {
        //Quit(pRenderer); Nothing is here right now
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

void UI_Manager::MainMenu(SDL_Renderer* pRenderer, bool& bSDLRunning)
{
    
    m_pMainMenu.Render(pRenderer);

    if (m_pInput.MouseUp_Select(m_pMainMenu.GetRect(eMain::Main_HOW_TO_PLAY))) // Potential change of scenes
    {
        
        SetScreenIndex(eType::HOW_TO_PLAY);
        cout << "Screen changed to HOW_TO_PLAY" << endl;
        
    }
    else if (m_pInput.MouseUp_Select(m_pMainMenu.GetRect(eMain::Main_LEVELS))) // Potential change of scenes
    {
        
        SetScreenIndex(eType::LEVELS);
        cout << "Screen changed to LEVELS" << endl;
    }
    else if (m_pInput.MouseUp_Select(m_pMainMenu.GetRect(eMain::Main_SCORES))) // Potential change of scenes
    {
        SetScreenIndex(eType::SCORES);
        cout << "Screen changed to HIGH_SCORES" << endl;
    }
    else if (m_pInput.MouseUp_Select(m_pMainMenu.GetRect(eMain::Main_QUIT))) // Potential change of scenes
    {
        SetScreenIndex(eType::QUIT);
        bSDLRunning = false;
        
    }
    
}

void UI_Manager::HowToPlay (SDL_Renderer* pRenderer)
{
    m_pHowToPlay.Render(pRenderer);

    if (m_pInput.MouseUp_Select(m_pHowToPlay.GetRect(eHowToPlay::HowToPlay_BACK))) // Potential change of scenes
    {
        SetScreenIndex(eType::MAIN_MENU);
        cout << "Screen changed to Main Menu" << endl;
    }
}

void UI_Manager::Levels(SDL_Renderer* pRenderer, bool& bGameIsRunning)
{
    
    m_pLevels.Render(pRenderer);

    if (m_pInput.MouseUp_Select(m_pLevels.GetRect(eLevels::Levels_LEVEL_1))) // Potential change of scenes
    {
        bGameIsRunning  = true;
        SetScreenIndex(eType::MAIN_MENU);
        cout << "Screen changed to Main Menu but not shown due to gameplay" << endl;
        
    }
    else if (m_pInput.MouseUp_Select(m_pLevels.GetRect(eLevels::Levels_BACK))) // Potential change of scenes
    {
        
        SetScreenIndex(eType::MAIN_MENU);
        cout << "Screen changed to Main Menu" << endl;
    }
    
}

void UI_Manager::Scores (SDL_Renderer* pRenderer)
{
    m_pScores.Render(pRenderer);

    if (m_pInput.MouseUp_Select(m_pScores.GetRect(eScores::Scores_BACK))) // Potential change of scenes
    {
        
        SetScreenIndex(eType::MAIN_MENU);
        cout << "Screen changed to Main Menu" << endl;
    }
}


UI_Manager::~UI_Manager()
{
    /*
    if (m_pInput != nullptr)
    {
        delete m_pInput;
    }
    if (m_pLevels != nullptr)
    {
        delete m_pLevels;
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