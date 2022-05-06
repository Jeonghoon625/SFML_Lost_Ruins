#pragma once
#include <SFML/Graphics.hpp>
#include "Monster.h"

class ZombieCrawler : public Monster
{
private:

public:
	ZombieCrawler();
	virtual void MonsterInit();

	virtual void FindPlayer(Player& player);
	virtual void ChasePlayer(Player& player, float dt);
	virtual void Walk(float dt);
	virtual void Run(float dt);
	virtual void Attack(float dt, int atk, Player& player);

	virtual bool OnHitted(int atk);
	
	

};
