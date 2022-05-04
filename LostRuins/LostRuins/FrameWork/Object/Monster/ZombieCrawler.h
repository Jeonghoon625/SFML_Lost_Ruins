#pragma once
#include <SFML/Graphics.hpp>
#include "Monster.h"

class ZombieCrawler : public Monster
{
private:

public:
	ZombieCrawler();
	virtual void MonsterInit(int health, int atk, float speed);

	virtual void Walk(float dt);
	virtual void Run(float dt);
	virtual void Attack(float dt, int atk);
};
