#include "ZombieCrawler.h"
#include "../../Mgr/Utils.h"

ZombieCrawler::ZombieCrawler()
	:Monster()
{
	Monster::SetHealth(20);
	Monster::SetAtk(3);
	Monster::SetSpeed(30.f);
}

void ZombieCrawler::MonsterInit(int health, int atk, float speed)
{
	Monster::SetHealth(health);
	Monster::SetAtk(atk);
	Monster::SetSpeed(speed);

	sprite.setOrigin(20, 10);
	sprite.setTextureRect(IntRect(0, 0, 40, 20));
	sprite.setPosition(resolution.x * 0.3f, resolution.y * 0.3f);
	position = sprite.getPosition();

	AnimationInit(&sprite);
}

void ZombieCrawler::Walk(float dt)
{
	checkTime += dt;
	if (checkTime > 3.f)
	{
		nextMove = Utils::RandomRange(-1, 2);	//-1¿Ã∏È ø¿∏•¬  0¿Ã∏È ∏ÿ√„ 1¿Ã∏È øﬁ¬ 
		switch (nextMove)
		{
		case -1:
			sprite.setScale(1.f, 1.f);
			animation.Play("ZombieCrawlerWalk");
			break;
		case 0:
			animation.Play("ZombieCrawlerIdle");
			break;
		case 1:
			sprite.setScale(-1.f, 1.f);
			animation.Play("ZombieCrawlerWalk");
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

void ZombieCrawler::Run(float dt)
{
}

void ZombieCrawler::Attack(float dt, int atk)
{
}
