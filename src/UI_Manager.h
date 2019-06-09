#ifndef UI_MANAGER_H
#define UI_MANAGER_H


#include <SDL.h>

#include "Input_Manager.h"

#include "UI_MainMenu.h"
#include "UI_HowToPlay.h"
#include "UI_Scores.h"


enum eMenu
{
	MAIN_MENU,
	HOW_TO_PLAY,
    SCORES,
	NUM_OF_MENUS
};
enum eMainButtons
{
    Main_HOW_TO_PLAY,
    Main_START,
    Main_SCORES,
	Main_NUM_OF_BUTTONS
};
enum eHowToPlayButtons
{
    HowToPlay_BACK,
	HowToPlay_NUM_OF_BUTTONS
};
enum eScoresButtons
{
    Scores_BACK,
	Scores_NUM_OF_BUTTONS
};
using namespace std;

class UI_Manager // Manages order of UI scenes
{
private:
	//SDL_Scancode aMainMenuButtonScanCodes[eMainButtons::Main_NUM_OF_BUTTONS];
    unsigned short m_iCurrentScreenIndex;
    //bool m_bWaitingForInput;
    Input_Manager m_pInput;

    // Encapsulation of all Menu objects
    UI_MainMenu m_pMainMenu;
    UI_HowToPlay m_pHowToPlay;
    UI_Scores m_pScores;
    

    
    
public:
    UI_Manager();
    //static UI_Manager* GetInstance();

    void Start(SDL_Renderer*, bool& bRunning, bool& bGameIsRunning);
    
    void SetScreenIndex (unsigned short);
    // A func for every menu type
    void MainMenu(SDL_Renderer*, bool& bRunning, bool &bGameIsRunning);
    void HowToPlay (SDL_Renderer*);
    void Scores (SDL_Renderer*);

    

    ~UI_Manager();
};
#endif