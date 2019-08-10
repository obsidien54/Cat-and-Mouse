#pragma once
#include <string>

enum Ability { NONE, DEFEAT_CATS, ENTER_WALL, NUM_OF_ABILITIES };

class PowerUp
{
public:
	PowerUp();
	~PowerUp();

	static Ability GenerateRandomAbility();
	static void RemovePlayerPower();
	static std::string ConvertAbilityToString(Ability a);
};

