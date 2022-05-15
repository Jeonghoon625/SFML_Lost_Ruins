#pragma once
#include <SFML/Graphics.hpp>
#include "Monster.h"

class GoblinAttacker :public Monster
{
private:

public:
	GoblinAttacker();

	virtual void Spawn(Vector2f pos);
	virtual void MonsterInit();
	virtual void SoundInit();
};