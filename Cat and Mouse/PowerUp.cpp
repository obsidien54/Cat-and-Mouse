#include <random>
#include "PowerUp.h"


PowerUp::PowerUp()
{
}


PowerUp::~PowerUp()
{
}


Ability PowerUp::GenerateRandomAbility()
{
	Ability ability = static_cast<Ability>(1 + rand() % (Ability::NUM_OF_ABILITIES - 1));
	return ability;
}

void PowerUp::RemovePlayerPower()
{
}

std::string PowerUp::ConvertAbilityToString(Ability a)
{
	switch (a) {
		case Ability::NONE: return "None"; break;
		case Ability::DEFEAT_CATS: return "Defeat Cats"; break;
		case Ability::ENTER_WALL: return "Enter Walls"; break;
	}
}
