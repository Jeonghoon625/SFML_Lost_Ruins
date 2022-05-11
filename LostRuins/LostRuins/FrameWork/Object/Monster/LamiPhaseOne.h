#pragma once
#include <SFML/Graphics.hpp>
#include "Monster.h"

using namespace sf;

class LamiPhaseOne :public Monster
{
private:
	string strUppercut;
	int attackCount;
public:
	LamiPhaseOne();

	virtual void MonsterInit();
	virtual void ChasePlayer(Player& player, float dt);
	virtual void Attack(float dt, int atk, Player& player);
};

