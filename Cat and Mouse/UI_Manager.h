#ifndef UI_MANAGER_H
#define UI_MANAGER_H


#include <SDL.h>


#include "UI_MainMenu.h"
#include "UI_HowToPlay.h"
#include "UI_Scores.h"
#include "UI_GameOver.h"
#include "Game.h"


enum eMenu
{
	MAIN_MENU,
	HOW_TO_PLAY,
    SCORES,
	GAME_OVER,
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
    unsigned short m_iCurrentScreenIndex;

    // Encapsulation of all Menu objects
    UI_MainMenu m_pMainMenu;
    UI_HowToPlay m_pHowToPlay;
    UI_Scores m_pScores;
	UI_GameOver m_pGameOver;
    

    
    
public:
    UI_Manager();
    static UI_Manager* GetInstance();

    void Start(SDL_Renderer*, bool& bRunning, bool& bGameIsRunning);
    
    void SetScreenIndex (unsigned short);
    // A func for every menu type
    void MainMenu(SDL_Renderer*, bool& bRunning, bool &bGameIsRunning);
    void HowToPlay (SDL_Renderer*);
    void Scores (SDL_Renderer*);
	void GameOver(SDL_Renderer*, bool &bSDLRunning);

    

    ~UI_Manager();
};
#endif