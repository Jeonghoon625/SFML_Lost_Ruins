#include "ZombieWalker.h"
#include "../../Mgr/Utils.h"

ZombieWalker::ZombieWalker()
	:Monster()
{
	Monster::SetHealth(20);
	Monster::SetAtk(3);
	Monster::SetSpeed(20.f);
}


void ZombieWalker::MonsterInit(int health, int atk, float speed)
{
	Monster::SetHealth(health);
	Monster::SetAtk(atk);
	Monster::SetSpeed(speed);

	sprite.setOrigin(20, 22.5f);
	sprite.setTextureRect(IntRect(0, 0, 40, 45));
	sprite.setPosition(resolution.x * 0.7f, resolution.y * 0.7f);
	position = sprite.getPosition();
		
	AnimationInit(&sprite);
}

void ZombieWalker::Walk(float dt)
{
	checkTime += dt;
	if (checkTime > 3.f)
	{
		nextMove = Utils::RandomRange(-1, 2);	//-1¿Ã∏È ø¿∏•¬  0¿Ã∏È ∏ÿ√„ 1¿Ã∏È øﬁ¬ 
		switch (nextMove)
		{
		case -1:
			sprite.setScale(1.f, 1.f);
			animation.Play("ZombieWalkerWalk");
			break;
		case 0:
			animation.Play("ZombieWalkerIdle");
			break;
		case 1:
			sprite.setScale(-1.f, 1.f);
			animation.Play("ZombieWalkerWalk");
			break;
		default:
			break;
		}
		checkTime = 0;

	}
	float h = (float)nextMove;
	float v = 0.f;
	Vector2f dir(h, v);

	position += Utils::Normalize(dir) * speed * dt;

	sprite.setPosition(position);

	
}

void ZombieWalker::Run(float dt)
{
}

void ZombieWalker::Attack(float dt, int atk)
{
}
