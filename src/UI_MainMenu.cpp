
#include "UI_MainMenu.h"


UI_MainMenu::UI_MainMenu()
{
    cout << "Instance of a UI MainMenu Created" << endl;
    m_rTitle.x = 100;  //controls the rect's x coordinate 
    m_rTitle.y = 100; // controls the rect's y coordinte
    m_rTitle.w = 300; // controls the width of the rect
    m_rTitle.h = 100; // These are all specific to ONE TEXT Title ... Data driven design

    m_rHowToPlay.x = m_rTitle.x + 150;  //controls the rect's x coordinate 
    m_rHowToPlay.y = m_rTitle.y + 100; // controls the rect's y coordinte
    m_rHowToPlay.w = m_rTitle.w * 0.5; // controls the width of the rect
    m_rHowToPlay.h = m_rTitle.h * 0.5; // These are all specific to ONE TEXT Title ... Data driven design

    m_rStart.x = m_rHowToPlay.x;  //controls the rect's x coordinate 
    m_rStart.y = m_rHowToPlay.y + 60; // controls the rect's y coordinte
    m_rStart.w = m_rHowToPlay.w; // controls the width of the rect
    m_rStart.h = m_rHowToPlay.h; // These are all specific to ONE TEXT Title ... Data driven design
    
    m_rScores.x = m_rHowToPlay.x;  //controls the rect's x coordinate 
    m_rScores.y = m_rStart.y + 60; // controls the rect's y coordinte
    m_rScores.w = m_rHowToPlay.w; // controls the width of the rect
    m_rScores.h = m_rHowToPlay.h; // These are all specific to ONE TEXT Title ... Data driven design
    
    m_rQuit.x = m_rHowToPlay.x;  //controls the rect's x coordinate 
    m_rQuit.y = m_rScores.y + 60; // controls the rect's y coordinte
    m_rQuit.w = m_rHowToPlay.w; // controls the width of the rect
    m_rQuit.h = m_rHowToPlay.h; // These are all specific to ONE TEXT Title ... Data driven design

}

void UI_MainMenu::RenderMouseOver(SDL_Renderer* pRenderer, unsigned short i)
{
	SDL_SetRenderDrawColor(pRenderer, 0, 0, 255, 150);

	if (i == 0)
	{
		// How to Play
		SDL_RenderDrawRect(pRenderer, &m_rHowToPlay);
	}
	else if (i == 1)
	{
		// Start
		SDL_RenderDrawRect(pRenderer, &m_rStart);

	}
	else if (i == 2)
	{
		// Scores
		SDL_RenderDrawRect(pRenderer, &m_rScores);
	}

	SDL_RenderPresent;
}


void UI_MainMenu::Render(SDL_Renderer* pRenderer)
{
    SDL_Surface* sTemp;
    SDL_Texture* tTemp;

	SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
    SDL_RenderClear(pRenderer);

    //Title
    sTemp = TTF_RenderText_Solid(m_pDefaultFontSans, "Main Menu", White);
    tTemp = SDL_CreateTextureFromSurface(pRenderer, sTemp);
    SDL_RenderCopy(pRenderer, tTemp, NULL, &m_rTitle); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture
    
    SDL_FreeSurface(sTemp);
    SDL_DestroyTexture(tTemp);
    SDL_Surface* sTemp1;
    SDL_Texture* tTemp1;
    
    
    // How to Play
    sTemp1 = TTF_RenderText_Solid(m_pDefaultFontSans, "1. How to Play", White);
    tTemp1 = SDL_CreateTextureFromSurface(pRenderer, sTemp1);
    SDL_RenderCopy(pRenderer, tTemp1, NULL, &m_rHowToPlay); // you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture
    
    SDL_FreeSurface(sTemp1);
    SDL_DestroyTexture(tTemp1);
    SDL_Surface* sTemp2;
    SDL_Texture* tTemp2;

    // Start
    sTemp2 = TTF_RenderText_Solid(m_pDefaultFontSans, "2. Start", White);
    tTemp2 = SDL_CreateTextureFromSurface(pRenderer, sTemp2);
    SDL_RenderCopy(pRenderer, tTemp2, NULL, &m_rStart); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture
    
    SDL_FreeSurface(sTemp2);
    SDL_DestroyTexture(tTemp2);
    SDL_Surface* sTemp3;
    SDL_Texture* tTemp3;

    // High Scores
    sTemp3 = TTF_RenderText_Solid(m_pDefaultFontSans, "3. High Scores", White);
    tTemp3 = SDL_CreateTextureFromSurface(pRenderer, sTemp3);
    SDL_RenderCopy(pRenderer, tTemp3, NULL, &m_rScores); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture
        

    SDL_FreeSurface(sTemp3);
    SDL_DestroyTexture(tTemp3);
    //SDL_Surface* sTemp4;
    //SDL_Texture* tTemp4;

    //// Quit
    //sTemp4 = TTF_RenderText_Solid(m_pDefaultFontSans, "Quit", White);
    //tTemp4 = SDL_CreateTextureFromSurface(pRenderer, sTemp4);
    //SDL_RenderCopy(pRenderer, tTemp4, NULL, &m_rQuit); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture
    //
    //SDL_FreeSurface(sTemp4);
    //SDL_DestroyTexture(tTemp4);

    
    SDL_RenderPresent(pRenderer);
}

SDL_Rect UI_MainMenu::GetRect(unsigned short i)
{
    if (i == 0)
    {
        return m_rHowToPlay;
    }
    else if (i == 1)
    {
        return m_rStart;
    }
    else if (i == 2)
    {
        return m_rScores;
    }
    else
    {
        cout << "SDL_Rect index not found" << endl;
		SDL_Rect temp = {};
        return temp; // FOR warning: control reaches end of non-void function
    }
}


UI_MainMenu::~UI_MainMenu()
{
    
}