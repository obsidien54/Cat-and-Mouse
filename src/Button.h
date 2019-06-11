#pragma once
#ifndef __Button__
#define __Button__

#include <glm\vec2.hpp>
#include "TextureManager.h"
#include "AudioManager.h"
#include "SDL_Manager.h"
#include <string>

//randomly spawn 5 ships on the grid
//tiles need to have a weight
//need to know what neightbours surrounding are

enum State {
	NORMAL,
	HOVER,
	NUM_OF_STATES
};

enum ButtonType {
	PLAY_BUTTON,
	HOW_TO_PLAY_BUTTON,
	HIGH_SCORES_BUTTON,
	MAIN_MENU_BUTTON,
	QUIT_BUTTON,
	RESTART_BUTTON,
	LEVELS_BUTTON,
	NUM_OF_TYPES_BUTTON
};

class Button
{
public:
	Button();
	~Button();

	//position for where button will be located as glm::vec2 coordinates
	glm::vec2 getPosition();
	void setPosition(glm::vec2 newPosition);

	//get the state of the button if it is pressed or not
	State getState();
	void setState(State newState);

	ButtonType getType();
	void setType(ButtonType newType);

	string getName();
	void setName(string name);

	SDL_Rect* getButtonRect();
	void setButtonRect(std::string name, glm::vec2 rect);

	//set up the button with all poperties
	void buttonSetUp(glm::vec2 position, ButtonType type, std::string name);

	
	void draw();

	void update();

	void clean();


private:
	//location for the button
	glm::vec2 m_position;

	ButtonType m_type;
	State m_state;
	
	//name for button to use when drawing
	string m_buttonName;

	//rectangle for button hitbox
	SDL_Rect m_pButtonRect;
};
#endif /* defined (__Button__) */
