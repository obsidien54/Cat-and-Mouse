#include "UI_Menu.h"

UI_Menu::UI_Menu()
{
    m_pDefaultFontSans = TTF_OpenFont("../Assets/text/open-sans/OpenSans-Regular.ttf", 24);
    if (m_pDefaultFontSans == nullptr) 
    { 
        cout << "Sans TTF_Font failed to initialize. \nSDL_ttf Error: " << TTF_GetError() << endl;

    }
    White = {255, 255, 255};
    
}


UI_Menu::~UI_Menu()
{
      
}