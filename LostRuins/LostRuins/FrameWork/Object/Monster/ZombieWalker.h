#pragma once
#include <SFML/Graphics.hpp>
#include "Monster.h"

class ZombieWalker : public Monster
{
private:

public:
	ZombieWalker();
	void SetPosition(float x, float y);
	virtual void MonsterInit();

	virtual void SoundInit();
};

