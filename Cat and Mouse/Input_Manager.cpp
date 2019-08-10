
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
		//if (m_bLMouseButton_Up == true)
		//{
		//	m_bLMouseButton_Up = false;
			return true;
		//}
	}
	//m_bLMouseButton_Up = true;
	return false;
}


//bool Input_Manager::MouseOver(SDL_Rect* rect) // Rename
//{
//	SDL_Event event;
//	SDL_PollEvent(&event);
//	
//	
//		mouseRect.x = event.motion.x;
//		mouseRect.x = event.motion.y;
//		
//
//	/*if ((m_iTempX > rect.x) && (m_iTempX < (rect.x + rect.w)) &&
//		(m_iTempY > rect.y) && (m_iTempY < (rect.y + rect.h)))*/
//	if(SDL_HasIntersection(rect, &mouseRect))
//	{
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//	
//}

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