#ifndef SDL_MANAGER_H
#define SDL_MANAGER_H



#include<iostream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

using namespace std;

class SDL_Manager // Manages init and quit
{
private:
    

    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;

    SDL_Manager();

public:
	bool m_bRunning;

    static SDL_Manager* GetInstance();

    bool Init(const char* title, int x, int y, int w, int h, Uint32 wflags, Uint32 rflags);
    

    SDL_Window* GetWindow() // Required??
    {
        return m_pWindow;
    }
    SDL_Renderer* GetRenderer()
    {
        return m_pRenderer;
    }
    bool& IsRunning()
    {
        return m_bRunning;
    }


    ~SDL_Manager();


};
#endif