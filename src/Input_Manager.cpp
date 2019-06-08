
#include "Input_Manager.h"


Input_Manager::Input_Manager()
{
    cout << "Instance of a Input Manager Created" << endl;

    m_iKeyStates = SDL_GetKeyboardState(NULL);
    m_bLMouseButton_Up = true;
    //m_iNumOfTimesPressed = 0;
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

bool Input_Manager::MouseOver(SDL_Rect rect) // Rename
{
	SDL_Event event;
	SDL_PollEvent(&event);

	m_iTempX = event.button.x;
	m_iTempY = event.button.y;

	if ((m_iTempX > rect.x) && (m_iTempX < (rect.x + rect.w)) &&
		(m_iTempY > rect.y) && (m_iTempY < (rect.y + rect.h)))
	{
		return true;
	}
	else
	{
		return false;
	}
	
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
	/*else
	{
		cout << "m_iKeyStates == nullptr" << endl;
		return false;
	}*/
	
}

Input_Manager::~Input_Manager()
{
    
}