#pragma once
#include <SFML/Graphics.hpp>
#include "Monster.h"

class GoblinAttacker :public Monster
{
private:

public:
	GoblinAttacker();

	virtual void MonsterInit();
};