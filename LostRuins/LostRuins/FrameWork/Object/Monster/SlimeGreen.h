#pragma once
#include <SFML/Graphics.hpp>
#include "Monster.h"

class SlimeGreen : public Monster
{
private:
	Vector2f AttackPlayerPos;
public:
	SlimeGreen();
	virtual void MonsterInit();
	virtual void ChasePlayer(Player& player, float dt);
	virtual void Attack(float dt, int atk, Player& player, Time timeHit);
	virtual void SetStatus(MonsterStatus newStatus);
	void IsFinishAttack();

};

