#pragma once
#include <SFML/Graphics.hpp>
#include "Monster.h"

class ZombieWalker : public Monster
{
private:

public:
	ZombieWalker();
	virtual void MonsterInit();
};

