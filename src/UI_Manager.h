#ifndef UI_MANAGER_H
#define UI_MANAGER_H


#include <SDL.h>

#include "Input_Manager.h"

#include "UI_MainMenu.h"
#include "UI_Levels.h"
#include "UI_HowToPlay.h"
#include "UI_Scores.h"


enum eType
{
	MAIN_MENU,
    HOW_TO_PLAY,
    LEVELS,
    SCORES,
    QUIT,
	NUM_OF_TYPES
};
enum eMain
{
    Main_HOW_TO_PLAY,
    Main_LEVELS,
    Main_SCORES,
    Main_QUIT,
	Main_NUM_OF_TYPES
};
enum eHowToPlay
{
    HowToPlay_BACK,
	HowToPlay_NUM_OF_TYPES
};
enum eLevels
{
    Levels_LEVEL_1,
    Levels_BACK,
	Levels_NUM_OF_TYPES
};
enum eScores
{
    Scores_BACK,
	Scores_NUM_OF_TYPES
};
using namespace std;

class UI_Manager // Manages order of UI scenes
{
private:
    unsigned short m_iCurrentScreenIndex;
    //bool m_bWaitingForInput;
    Input_Manager m_pInput;

    // Encapsulation of all Menu objects
    UI_MainMenu m_pMainMenu;
    UI_Levels m_pLevels;
    UI_HowToPlay m_pHowToPlay;
    UI_Scores m_pScores;
    

    
    
public:
    UI_Manager();
    //static UI_Manager* GetInstance();

    void Start(SDL_Renderer*, bool& bRunning, bool& bGameIsRunning);
    
    void SetScreenIndex (unsigned short);
    // A func for every menu type
    void MainMenu(SDL_Renderer*, bool& bRunning);
    void HowToPlay (SDL_Renderer*);
    void Levels (SDL_Renderer*, bool& bRunning);
    void Scores (SDL_Renderer*);

    

    ~UI_Manager();
};
#endif