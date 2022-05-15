#pragma once
#include <SFML/Graphics.hpp>
#include "Monster.h"

using namespace sf;

class LamiPhaseOne :public Monster
{
private:
	string strUppercut;
	int attackCount;
	bool isUppercut;
public:
	LamiPhaseOne();

	virtual void Spawn(Vector2f pos);

	virtual void AnimationUpdate();
	virtual void SetStatus(MonsterStatus newStatus);

	virtual void MonsterInit();
	virtual void ChasePlayer(Player& player, float dt);
	virtual void Attack(float dt, int atk, Player& player, Time timeHit);
	virtual bool OnHitted(int atk, float dt, Time timeHit);

	virtual void SoundInit();
};

