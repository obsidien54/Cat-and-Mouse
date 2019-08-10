#include "SDL_Manager.h"


SDL_Manager::SDL_Manager()
{
    cout << "SDL Instance Created" << endl;
    m_bRunning = true;
    
    
}

SDL_Manager* SDL_Manager::GetInstance()
{
    static SDL_Manager* instance = new SDL_Manager();

    return instance;
}

bool SDL_Manager::Init(const char* title, int x, int y, int w, int h, Uint32 wflags, Uint32 rflags)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) // SDL_INIT_EVENTS | SDL_INIT_VIDEO
    {
        m_pWindow = SDL_CreateWindow(title, x, y, w * TILESIZE, h * TILESIZE, wflags);

        if (m_pWindow != nullptr)
        {
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, rflags);

            if (m_pRenderer != nullptr)
            {
                
                if (IMG_Init(IMG_INIT_PNG) != 0)
                {
                    if (TTF_Init() != -1)
                    {
                        return 0;
                    }
                    else
                    {
                        cout << "TTF_Init failed to initialize. \nSDL_ttf Error: " << TTF_GetError() << endl;
                        return 1;
                    }
                    
                }
                else
                {
                    cout << "IMG_Init failed to initialize. \nSDL_image Error: " << IMG_GetError() << endl;
                    return 1;
                }
            }
            else 
            {
                cout << "SDL Renderer failed to initialize." << endl;
                return 1;
            }
        }
        else
        {
            cout << "SDL Window failed to initialize." << endl;
            return 1;
        }
    }
    else
    {
        cout << "SDL failed to initialize." << endl;
        return 1;
    }

    
}




SDL_Manager::~SDL_Manager()
{
    // This can be in a SDL_Manager::Quit();
    //Deinitialize individual systems
    TTF_Quit();
    IMG_Quit();
    SDL_QuitSubSystem(SDL_INIT_EVENTS);
    
    if (m_pRenderer != nullptr)
    {
        SDL_DestroyRenderer(m_pRenderer);
    }

    if (m_pWindow != nullptr)
    {
        SDL_DestroyWindow(m_pWindow);
    }

    

    SDL_Quit();
}