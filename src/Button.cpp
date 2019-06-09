#include "Button.h"

#include "GLM/gtx/rotate_vector.hpp"


//pass in the name of the button type to have its assets for the button
Button::Button()
{
	setState(NORMAL);
	m_position = glm::vec2(0.0f, 0.0f);

	//load in textures required for the button of specific type
	
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

void Button::setType(ButtonType newState)
{
	m_type = newState;
	switch (newState)
	{
	case ButtonType::HOW_TO_PLAY_BUTTON:
		TheTextureManager::Instance()->load("../Assets/textures/button_how_to_play.png",
			"how to play", SDL_Manager::GetInstance()->GetRenderer());

		TheTextureManager::Instance()->load("../Assets/textures/button_how_to_play_large.png",
			"how to play large", SDL_Manager::GetInstance()->GetRenderer());
		setName("how to play");
		break;
	case ButtonType::MAIN_MENU_BUTTON:
		TheTextureManager::Instance()->load("../Assets/textures/button_main_menu.png",
			"main menu", SDL_Manager::GetInstance()->GetRenderer());

		TheTextureManager::Instance()->load("../Assets/textures/button_main_menu_large.png",
			"main menu large", SDL_Manager::GetInstance()->GetRenderer());
		setName("main menu");
		break;
	case ButtonType::PLAY_BUTTON:
		TheTextureManager::Instance()->load("../Assets/textures/button_play.png",
			"play", SDL_Manager::GetInstance()->GetRenderer());

		TheTextureManager::Instance()->load("../Assets/textures/button_play_large.png",
			"play large", SDL_Manager::GetInstance()->GetRenderer());
		setName("play");
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

void Button::draw()
{
	int xComponent = getPosition().x;
	int yComponent = getPosition().y;

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