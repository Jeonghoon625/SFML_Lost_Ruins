#include "ZombieCrawler.h"
#include "../../Mgr/Utils.h"

ZombieCrawler::ZombieCrawler()
	:Monster()
{
	Monster::SetHealth(20);
	Monster::SetAtk(3);
	Monster::SetSpeed(30.f);
}

void ZombieCrawler::MonsterInit()
{
	strDemageTaken = ("ZombieCrawlerDemageTaken");

	Monster::SetHealth(20);
	Monster::SetAtk(3);
	Monster::SetSpeed(30.f);
	sprite.setOrigin(15.f,24.f);
	sprite.setPosition(resolution.x * 0.3f, resolution.y * 0.5f);
	sprite.setScale(scale);
	position = sprite.getPosition();
	AnimationInit(&sprite);

	findPlayerBox.setSize(Vector2f(200.f, 40.f));
	findPlayerBox.setScale(scale);
	findPlayerBox.setFillColor(Color(255, 255, 255, 80));
	findPlayerBox.setOrigin(200, 40);
	findPlayerBox.setPosition(sprite.getOrigin());

	attackRangeBox.setSize(Vector2f(30.f, 30.f));
	attackRangeBox.setScale(scale);
	attackRangeBox.setFillColor(Color(153, 0, 0, 80));
	attackRangeBox.setOrigin(30, 30);
	attackRangeBox.setPosition(sprite.getOrigin());

	hitBox.setSize(Vector2f(43.f, 30.f));
	hitBox.setScale(scale);
	hitBox.setOrigin(21.5f, 30.f);
	hitBox.setFillColor(Color(50, 50, 25, 70));
	hitBox.setPosition(sprite.getOrigin());
}

void ZombieCrawler::FindPlayer(Player& player)
{
	if (!isFindPlayer)
	{
		if (findPlayerBox.getGlobalBounds().intersects(player.GetHitBox().getGlobalBounds()))
		{
			isFindPlayer = true;

			sprite.setOrigin(17.f, 24);		//좀비 크러울러 걸을때 발 좌표가 17.f, 47임
			animation.Play("ZombieCrawlerWalk");
		}
	}
}

void ZombieCrawler::ChasePlayer(Player& player, float dt)
{
	if (isFindPlayer && !isAttackPlayer)
	{
		if (attackRangeBox.getGlobalBounds().intersects(player.GetHitBox().getGlobalBounds()))
		{
			sprite.setOrigin(18.f, 23);		//공격할때 좀비 크러울러 발 끝 좌표19,23
			animation.Play("ZombieCrawlerAttack");
			isAttackPlayer = true;
		}

		if (!isAttackPlayer)
		{
			float h = player.GetPosition().x - sprite.getPosition().x;
			float v = 0.f;
			Vector2f dir(h, v);

			position += (Utils::Normalize(dir) * speed) * 1.0f * dt;
			sprite.setPosition(position);
			findPlayerBox.setPosition(position);
			attackRangeBox.setPosition(position);
			hitBox.setPosition(position);

			if (h > 0)
			{
				sprite.setScale(-3.f, 3.f);	//플레이어가 몬스터 왼쪽에 있을때
				findPlayerBox.setOrigin(0.f, 40.f);
				attackRangeBox.setOrigin(0, 30);
			}
			else
			{
				sprite.setScale(3.f, 3.f);	//플레이어가 몬스터 오른쪽에 있을때
				findPlayerBox.setOrigin(200.f, 40.f);
				attackRangeBox.setOrigin(30, 30);
			}

			if (h * h > 500 * 500)		//플레이어의 거리가 떨어지면 플레이어 추적하는거 취소
			{
				isFindPlayer = false;
			}
		}
	}
}

void ZombieCrawler::Walk(float dt)
{
	if (!isFindPlayer)
	{
		checkTime += dt;
		if (checkTime > 3.f)
		{
			nextMove = Utils::RandomRange(-1, 2);	//-1이면 오른쪽 0이면 멈춤 1이면 왼쪽
			switch (nextMove)
			{
			case -1:
				sprite.setScale(3.f, 3.f);
				animation.Play("ZombieCrawlerWalk");
				sprite.setOrigin(15.f, 24.f);
				findPlayerBox.setOrigin(200.f, 40.f);
				attackRangeBox.setOrigin(30, 30);
				break;
			case 0:
				animation.Play("ZombieCrawlerIdle");
				break;
			case 1:
				sprite.setScale(-3.f, 3.f);
				animation.Play("ZombieCrawlerWalk");
				sprite.setOrigin(15.f, 24);
				findPlayerBox.setOrigin(0.f, 40.f);
				attackRangeBox.setOrigin(0, 30);
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
		findPlayerBox.setPosition(position);
		attackRangeBox.setPosition(position); 
		hitBox.setPosition(position);
	}
}

void ZombieCrawler::Run(float dt)
{
}

void ZombieCrawler::Attack(float dt, int atk, Player& player)
{
	if (isAttackPlayer)
	{
		attackDelay += dt;
		if (attackDelay > 1.5f)
		{
			//여기에 함수 추가해서 플레이어 Onhitted 나 set 함수 써서 hp 깎이면 됨 ㅇ.
			attackDelay = 0.f;
			isAttackPlayer = false;
			sprite.setOrigin(15.f, 23);	//뛸 때 좀비 크러울러 발 끝 좌표 15,23
			animation.Play("ZombieCrawlerWalk");
		}
	}
}

bool ZombieCrawler::OnHitted(int atk)
{
	if (health > 0)
	{
		animation.Play(strDemageTaken);
		health -= atk;
		return true;
	}
}
