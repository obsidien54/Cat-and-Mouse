#include "Button.h"

#include "GLM/gtx/rotate_vector.hpp"


//pass in the name of the button type to have its assets for the button
Button::Button()
{
	setState(NORMAL);
	m_position = glm::vec2(0.0f, 0.0f);

}

Button::~Button()
{
}

glm::vec2 Button::getPosition()
{
	return m_position;
}

void Button::setPosition(glm::vec2 newPosition)
{
	m_position = newPosition;
}

State Button::getState()
{
	return m_state;
}

void Button::setState(State newState)
{
	m_state = newState;
}

ButtonType Button::getType()
{
	return m_type;
}

void Button::setType(ButtonType newType)
{
	m_type = newType;
	switch (newType)
	{
	case ButtonType::HOW_TO_PLAY_BUTTON:
		TheTextureManager::Instance()->load("../Cat and Mouse/Assets/textures/button_how_to_play.png",
			"how to play", SDL_Manager::GetInstance()->GetRenderer());

		TheTextureManager::Instance()->load("../Cat and Mouse/Assets/textures/button_how_to_play_large.png",
			"how to play large", SDL_Manager::GetInstance()->GetRenderer());
		setName("how to play");
		break;
	case ButtonType::MAIN_MENU_BUTTON:
		TheTextureManager::Instance()->load("../Cat and Mouse/Assets/textures/button_main_menu.png",
			"main menu", SDL_Manager::GetInstance()->GetRenderer());

		TheTextureManager::Instance()->load("../Cat and Mouse/Assets/textures/button_main_menu_large.png",
			"main menu large", SDL_Manager::GetInstance()->GetRenderer());
		setName("main menu");
		break;
	case ButtonType::PLAY_BUTTON:
		TheTextureManager::Instance()->load("../Cat and Mouse/Assets/textures/button_play.png",
			"play", SDL_Manager::GetInstance()->GetRenderer());

		TheTextureManager::Instance()->load("../Cat and Mouse/Assets/textures/button_play_large.png",
			"play large", SDL_Manager::GetInstance()->GetRenderer());
		setName("play");
		break;
	case ButtonType::QUIT_BUTTON:
		TheTextureManager::Instance()->load("../Cat and Mouse/Assets/textures/button_quit.png",
			"quit", SDL_Manager::GetInstance()->GetRenderer());

		TheTextureManager::Instance()->load("../Cat and Mouse/Assets/textures/button_quit_large.png",
			"quit large", SDL_Manager::GetInstance()->GetRenderer());
		setName("quit");
		break;
	case ButtonType::HIGH_SCORES_BUTTON:
		TheTextureManager::Instance()->load("../Cat and Mouse/Assets/textures/button_high_scores.png",
			"high scores", SDL_Manager::GetInstance()->GetRenderer());

		TheTextureManager::Instance()->load("../Cat and Mouse/Assets/textures/button_high_scores_large.png",
			"high scores large", SDL_Manager::GetInstance()->GetRenderer());
		setName("high scores");
		break;
	case ButtonType::LEVELS_BUTTON:
		TheTextureManager::Instance()->load("../Cat and Mouse/Assets/textures/button_levels.png",
			"levels", SDL_Manager::GetInstance()->GetRenderer());

		TheTextureManager::Instance()->load("../Cat and Mouse/Assets/textures/button_levels_large.png",
			"levels large", SDL_Manager::GetInstance()->GetRenderer());
		setName("levels");
		break;
	}
}

string Button::getName()
{
	return m_buttonName;
}

void Button::setName(string name)
{
	m_buttonName = name;
}

SDL_Rect * Button::getButtonRect()
{
	return &m_pButtonRect;
}

void Button::setButtonRect(std::string name, glm::vec2 rect)
{
	glm::vec2 buttonSize;
	buttonSize = TheTextureManager::Instance()->getTextureSize(name);

	m_pButtonRect.x = (int)(rect.x - buttonSize.x * 0.5);//converrt from middle of the button to the outer edge
	m_pButtonRect.y = (int)(rect.y - buttonSize.y * 0.5);
	m_pButtonRect.w = (int)(buttonSize.x);
	m_pButtonRect.h = (int)(buttonSize.y);
}

void Button::buttonSetUp(glm::vec2 position, ButtonType type, std::string name)
{
	setPosition(position);
	setType(type);
	setButtonRect(name, position);
}

void Button::draw()
{
	int xComponent = (int)(getPosition().x);
	int yComponent = (int)(getPosition().y);

	switch (getState()) //draw the button depending on which state it is in
	{
	case State::NORMAL:
		TheTextureManager::Instance()->draw(getName(), xComponent, yComponent,
			SDL_Manager::GetInstance()->GetRenderer(), 0, 255, true);
		break;

	case State::HOVER:
		TheTextureManager::Instance()->draw(getName() + " large", xComponent, yComponent,
			SDL_Manager::GetInstance()->GetRenderer(), 0, 255, true);
		break;
	}
	
}

void Button::update()
{
	
}

void Button::clean()
{
}
