
#include "Input_Manager.h"


Input_Manager::Input_Manager()
{
   std::cout << "Instance of a Input Manager Created" << std::endl;

   m_iKeyStates = SDL_GetKeyboardState(NULL);
   mouseRect.w = 2;
   mouseRect.h = 2;
	
}

bool Input_Manager::MouseUp_Select(SDL_Rect rect) // Rename
{
	
	SDL_Event event;
	SDL_PollEvent(&event);

	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		
			return true;
	}
	return false;
}



bool Input_Manager::KeyDown(SDL_Scancode c)
{
	SDL_PumpEvents();

	if (m_iKeyStates != nullptr) 
    {
		if (m_iKeyStates[c] == true) 
        {
			return true;
		}
		else 
		{
			return false;
		}
	}
}



Input_Manager::~Input_Manager()
{
    
}