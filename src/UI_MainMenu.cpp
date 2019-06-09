
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

    m_rLevels.x = m_rHowToPlay.x;  //controls the rect's x coordinate 
    m_rLevels.y = m_rHowToPlay.y + 60; // controls the rect's y coordinte
    m_rLevels.w = m_rHowToPlay.w; // controls the width of the rect
    m_rLevels.h = m_rHowToPlay.h; // These are all specific to ONE TEXT Title ... Data driven design
    
    m_rScores.x = m_rHowToPlay.x;  //controls the rect's x coordinate 
    m_rScores.y = m_rLevels.y + 60; // controls the rect's y coordinte
    m_rScores.w = m_rHowToPlay.w; // controls the width of the rect
    m_rScores.h = m_rHowToPlay.h; // These are all specific to ONE TEXT Title ... Data driven design
    
    m_rQuit.x = m_rHowToPlay.x;  //controls the rect's x coordinate 
    m_rQuit.y = m_rScores.y + 60; // controls the rect's y coordinte
    m_rQuit.w = m_rHowToPlay.w; // controls the width of the rect
    m_rQuit.h = m_rHowToPlay.h; // These are all specific to ONE TEXT Title ... Data driven design

	//create the buttons in this menu
	
	button1.setPosition(glm::vec2(368,150));
	button1.setType(PLAY_BUTTON);
	button2.setPosition(glm::vec2(368, 300));
	button2.setType(HOW_TO_PLAY_BUTTON);
	button3.setPosition(glm::vec2(368, 450));
	button3.setType(MAIN_MENU_BUTTON);

	//lower the volume since too loud
	TheAudioManager::Instance()->setMusicVolume(20);

	//background music
	//music by bensound
	TheAudioManager::Instance()->load("../Assets/sound/bensound-endlessmotion.mp3",
		"Background", sound_type::SOUND_MUSIC);

	TheAudioManager::Instance()->playMusic("Background", -1);

}




void UI_MainMenu::Render(SDL_Renderer* pRenderer)
{
    SDL_Surface* sTemp;
    SDL_Texture* tTemp;

    
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
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 255, 150);
    SDL_RenderDrawRect(pRenderer, &m_rHowToPlay);
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
    sTemp1 = TTF_RenderText_Solid(m_pDefaultFontSans, "How to Play", White);
    tTemp1 = SDL_CreateTextureFromSurface(pRenderer, sTemp1);
    SDL_RenderCopy(pRenderer, tTemp1, NULL, &m_rHowToPlay); // you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture
    
    SDL_FreeSurface(sTemp1);
    SDL_DestroyTexture(tTemp1);
    SDL_Surface* sTemp2;
    SDL_Texture* tTemp2;

    // Levels
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 255, 150);
    SDL_RenderDrawRect(pRenderer, &m_rLevels);
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
    sTemp2 = TTF_RenderText_Solid(m_pDefaultFontSans, "Levels", White);
    tTemp2 = SDL_CreateTextureFromSurface(pRenderer, sTemp2);
    SDL_RenderCopy(pRenderer, tTemp2, NULL, &m_rLevels); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture
    
    SDL_FreeSurface(sTemp2);
    SDL_DestroyTexture(tTemp2);
    SDL_Surface* sTemp3;
    SDL_Texture* tTemp3;

    // High Scores
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 255, 150);
    SDL_RenderDrawRect(pRenderer, &m_rScores);
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
    sTemp3 = TTF_RenderText_Solid(m_pDefaultFontSans, "High Scores", White);
    tTemp3 = SDL_CreateTextureFromSurface(pRenderer, sTemp3);
    SDL_RenderCopy(pRenderer, tTemp3, NULL, &m_rScores); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture
        // Displays MENU

    SDL_FreeSurface(sTemp3);
    SDL_DestroyTexture(tTemp3);
    SDL_Surface* sTemp4;
    SDL_Texture* tTemp4;

    // Quit    if (m_iCurrentScreenIndex == eType::MAIN_MENU)
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 255, 150);
    SDL_RenderDrawRect(pRenderer, &m_rQuit);
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
    sTemp4 = TTF_RenderText_Solid(m_pDefaultFontSans, "Quit", White);
    tTemp4 = SDL_CreateTextureFromSurface(pRenderer, sTemp4);
    SDL_RenderCopy(pRenderer, tTemp4, NULL, &m_rQuit); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture
    
    SDL_FreeSurface(sTemp4);
    SDL_DestroyTexture(tTemp4);


	button1.draw();
	button2.draw();
	button3.draw();

    
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
        return m_rLevels;
    }
    else if (i == 2)
    {
        return m_rScores;
    }
    else if (i == 3)
    {
        return m_rQuit;
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