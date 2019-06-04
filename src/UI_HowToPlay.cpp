#include "UI_HowToPlay.h"

UI_HowToPlay::UI_HowToPlay()
{
    //cout << "Instance of a UI HowToPlay Created" << endl;
    m_rTitle.x = 100;  //controls the rect's x coordinate 
    m_rTitle.y = 100; // controls the rect's y coordinte
    m_rTitle.w = 300; // controls the width of the rect
    m_rTitle.h = 100; // These are all specific to ONE TEXT Title ... Data driven design

    m_rBack.x = m_rTitle.x + 150;  //controls the rect's x coordinate 
    m_rBack.y = m_rTitle.y + 100; // controls the rect's y coordinte
    m_rBack.w = m_rTitle.w * 0.5; // controls the width of the rect
    m_rBack.h = m_rTitle.h * 0.5; // These are all specific to ONE TEXT Title ... Data driven design

}
/*
UI_HowToPlay* UI_HowToPlay::GetInstance()
{
    static UI_HowToPlay* instance = new UI_HowToPlay();

    return instance;
}
*/


void UI_HowToPlay::Render(SDL_Renderer* pRenderer)
{
    SDL_Surface* sTemp;
    SDL_Texture* tTemp;
    
    //Title
    SDL_RenderClear(pRenderer);
    sTemp = TTF_RenderText_Solid(m_pDefaultFontSans, "How To Play", White);
    tTemp = SDL_CreateTextureFromSurface(pRenderer, sTemp);
    SDL_RenderCopy(pRenderer, tTemp, NULL, &m_rTitle); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture
    
    SDL_FreeSurface(sTemp);
    SDL_DestroyTexture(tTemp);
    SDL_Surface* sTemp1;
    SDL_Texture* tTemp1;

    // Back
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 255, 255);
    SDL_RenderDrawRect(pRenderer, &m_rBack);
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
    sTemp1 = TTF_RenderText_Solid(m_pDefaultFontSans, "Back", White);
    tTemp1 = SDL_CreateTextureFromSurface(pRenderer, sTemp1);
    SDL_RenderCopy(pRenderer, tTemp1, NULL, &m_rBack); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture
    
    SDL_FreeSurface(sTemp1);
    SDL_DestroyTexture(tTemp1);
    
    SDL_RenderPresent(pRenderer);
}

SDL_Rect UI_HowToPlay::GetRect(unsigned short i)
{
    if (i == 0)
    {
        return m_rBack;
    }
    else
    {
        cout << "SDL_Rect index not found" << endl;
		SDL_Rect temp = {};
        return temp; // FOR warning: control reaches end of non-void function
    }
}

UI_HowToPlay::~UI_HowToPlay()
{
    
}