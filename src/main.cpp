#include "SDL_Manager.h"
#include "UI_Manager.h"
#include "Input_Manager.h"
#include "Game_Manager.h"
#include "Game.h"
#include <Windows.h>
#include <SDL_ttf.h>

int main (int argc, char* argv[])
{
	AllocConsole();
	freopen("CON", "w", stdout);

    SDL_Manager* pSDL = SDL_Manager::GetInstance();
    
    if (pSDL->Init("Cat and Mouse", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 23, 23, 
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL, // SDL_WINDOW_BORDERLESS |
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE) != 0)
    {
        cout << "pSDL->Init failed" << endl;
        return 1;
    }

    UI_Manager pUI;
	Game* game = Game::GetInstance();
	
    
	Input_Manager mInput;

	while (pSDL->IsRunning())
	{

		pUI.Start(pSDL->GetRenderer(), pSDL->IsRunning(), game->IsRunningByRef());
		
		if (game->Running()) 
		{
			
			if (game->Init(pSDL->GetRenderer()))
			{
				return 1;
			}

			while (game->Running()) { 
				game->Wake();
				game->HandleEvents();
				game->Update();
				game->Render(pSDL->GetRenderer());
				if (game->Running()) {
					game->Sleep();
				}
			}
			game->Clean();
			game->StopRunning();
		}
		SDL_Delay(200); // This allows the menu to function normally

	}

    //Decontructing
	if (game != nullptr)
	{
		delete game;
	}
    if (pSDL != nullptr)
    {
        delete pSDL;
    }
    
    return 0;
}
