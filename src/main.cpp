#include "SDL_Manager.h"
#include "UI_Manager.h"
#include "Game_Manager.h"
#include "Game.h"
#include <Windows.h>
#include <SDL_ttf.h>

int main (int argc, char* argv[])
{
	AllocConsole();
	freopen("CON", "w", stdout);

    SDL_Manager* pSDL = SDL_Manager::GetInstance();
    
    if (pSDL->Init("Cat and Mouse", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 736, 736, 
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL, // SDL_WINDOW_BORDERLESS |
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE) != 0)
    {
        cout << "pSDL->Init failed" << endl;
        return 1;
    }

    UI_Manager pUI;
    Game_Manager pGame;
	Game* game = Game::GetInstance();

    SDL_SetRenderDrawColor(pSDL->GetRenderer(), 0, 0, 0, 255); // Can it be within another function
    

	while (pSDL->IsRunning())
	{
		pUI.Start(pSDL->GetRenderer(), pSDL->IsRunning(), pGame.IsRunning());
		// Renders Current Screen
		// Input is asked for within Menu
		// Changes current Screen

		if (pGame.IsRunning()) // Recieves which level was selected
		{
			cout << "Instance of Game will run" << endl;
			cout << "This is an infinite loop." << endl;
			if (game->Init("Cat and Mouse", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 23, 23, 0) == false) {
				return 1;
			}

			while (game->Running()) {
				game->Wake();
				game->HandleEvents();
				game->Update();
				game->Render();
				if (game->Running()) {
					game->Sleep();
				}
			}
			game->Clean();
			pGame.m_bRunning = false;
			//pSDL->m_bRunning = false;

			//pGame.Start();
			// Look to pGame->Level1()
			// turn bGameIsRunning back to false after the game loop
		}
		SDL_Delay(20);

	}

    //Decontructing
    if (pSDL != nullptr)
    {
        delete pSDL;
    }
    
    return 0;
}
