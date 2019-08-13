#include "UI_Levels.h"

UI_Levels::UI_Levels()
{
    m_rTitle.x = 100;  //controls the rect's x coordinate 
    m_rTitle.y = 100; // controls the rect's y coordinte
    m_rTitle.w = 300; // controls the width of the rect
    m_rTitle.h = 100; // These are all specific to ONE TEXT Title ... Data driven design

    m_rLevel1.x = m_rTitle.x + 150;  //controls the rect's x coordinate 
    m_rLevel1.y = m_rTitle.y + 100; // controls the rect's y coordinte
    m_rLevel1.w = m_rTitle.w * 0.5; // controls the width of the rect
    m_rLevel1.h = m_rTitle.h * 0.5; // These are all specific to ONE TEXT Title ... Data driven design

    m_rBack.x = m_rLevel1.x;  //controls the rect's x coordinate 
    m_rBack.y = m_rLevel1.y + 50; // controls the rect's y coordinte
    m_rBack.w = m_rLevel1.w; // controls the width of the rect
    m_rBack.h = m_rLevel1.h; // These are all specific to ONE TEXT Title ... Data driven design
}


void UI_Levels::Render(SDL_Renderer* pRenderer)
{
    SDL_Surface* sTemp;
    SDL_Texture* tTemp;

    //Title
    SDL_RenderClear(pRenderer);
    sTemp = TTF_RenderText_Solid(m_pDefaultFontSans, "Levels", White);
    tTemp = SDL_CreateTextureFromSurface(pRenderer, sTemp);
    SDL_RenderCopy(pRenderer, tTemp, NULL, &m_rTitle); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture
    
    SDL_FreeSurface(sTemp);
    SDL_DestroyTexture(tTemp);
    SDL_Surface* sTemp1;
    SDL_Texture* tTemp1;

    // Level1
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 255, 255);
    SDL_RenderDrawRect(pRenderer, &m_rLevel1);
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
    sTemp1 = TTF_RenderText_Solid(m_pDefaultFontSans, "Level 1", White);
    tTemp1 = SDL_CreateTextureFromSurface(pRenderer, sTemp1);
    SDL_RenderCopy(pRenderer, tTemp1, NULL, &m_rLevel1); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture
    
    SDL_FreeSurface(sTemp1);
    SDL_DestroyTexture(tTemp1);
    SDL_Surface* sTemp2;
    SDL_Texture* tTemp2;

    // Back
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 255, 255);
    SDL_RenderDrawRect(pRenderer, &m_rBack);
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
    sTemp2 = TTF_RenderText_Solid(m_pDefaultFontSans, "Back", White);
    tTemp2 = SDL_CreateTextureFromSurface(pRenderer, sTemp2);
    SDL_RenderCopy(pRenderer, tTemp2, NULL, &m_rBack); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture
    
    SDL_FreeSurface(sTemp2);
    SDL_DestroyTexture(tTemp2);
    
    SDL_RenderPresent(pRenderer);
}

SDL_Rect UI_Levels::GetRect(unsigned short i)
{
    if (i == 0)
    {
        return m_rLevel1;
    }
    else if (i == 1)
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

UI_Levels::~UI_Levels()
{
    
}