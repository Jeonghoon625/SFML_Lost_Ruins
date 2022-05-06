#include "ZombieWalker.h"
#include "../../Mgr/Utils.h"

ZombieWalker::ZombieWalker()
	:Monster()
{
	Monster::SetHealth(20);
	Monster::SetAtk(3);
	Monster::SetSpeed(20.f);
}


void ZombieWalker::MonsterInit()
{
	strDemageTaken = ("ZombieWalkerDemageTaken");

	Monster::SetHealth(20);
	Monster::SetAtk(3);
	Monster::SetSpeed(20.f);
	sprite.setOrigin(17.f, 45.f);
	sprite.setPosition(resolution.x * 0.5f, resolution.y * 0.4f);
	sprite.setScale(scale);
	position = sprite.getPosition();
		
	AnimationInit(&sprite);

	findPlayerBox.setSize(Vector2f(200.f, 40.f));
	findPlayerBox.setOrigin(200, 40);
	findPlayerBox.setScale(scale);
	findPlayerBox.setFillColor(Color::White);
	findPlayerBox.setPosition(sprite.getOrigin());

	attackRangeBox.setSize(Vector2f(30.f, 30.f));
	attackRangeBox.setOrigin(30, 30);
	attackRangeBox.setScale(scale);
	attackRangeBox.setFillColor(Color::Blue);
	attackRangeBox.setPosition(sprite.getOrigin());

	hitBox.setSize(Vector2f(43.f, 30.f));
	hitBox.setOrigin(21.5f, 30.f);
	hitBox.setScale(scale);
	hitBox.setFillColor(Color(50, 50, 25, 70));
	hitBox.setPosition(sprite.getOrigin());
}

void ZombieWalker::FindPlayer(Player& player)
{
	if (!isFindPlayer)
	{
		if (findPlayerBox.getGlobalBounds().intersects(player.GetHitBox().getGlobalBounds()))
		{
			isFindPlayer = true;

			sprite.setOrigin(21.f, 46.f);		//좀비 워커 뛸때 발 좌표가 21.f, 46임
			animation.Play("ZombieWalkerWalk");
		}
	}
}

void ZombieWalker::ChasePlayer(Player& player, float dt)
{
	if (isFindPlayer && !isAttackPlayer)
	{
		if (attackRangeBox.getGlobalBounds().intersects(player.GetHitBox().getGlobalBounds()))
		{
			sprite.setOrigin(19.f, 45);		//공격할때 좀비워커 발 끝 좌표 19 45
			animation.Play("ZombieWalkerAttack");
			isAttackPlayer = true;
		}

		if (!isAttackPlayer)
		{
			float h = player.GetPosition().x - sprite.getPosition().x;
			float v = 0.f;
			Vector2f dir(h, v);

			position += (Utils::Normalize(dir) * speed) * 1.f * dt;
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

void ZombieWalker::Walk(float dt)
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
				animation.Play("ZombieWalkerWalk");
				sprite.setOrigin(21.f, 46.f);
				findPlayerBox.setOrigin(200.f, 40.f);
				attackRangeBox.setOrigin(30, 30);
				break;
			case 0:
				animation.Play("ZombieWalkerIdle");
				break;
			case 1:
				sprite.setScale(-3.f, 3.f);
				animation.Play("ZombieWalkerWalk");
				sprite.setOrigin(21.f, 46.f);
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

void ZombieWalker::Run(float dt)
{
}

void ZombieWalker::Attack(float dt, int atk, Player& player)
{
	if (isAttackPlayer)
	{
		attackDelay += dt;
		if (attackDelay > 1.5f)
		{
			//여기에 함수 추가해서 플레이어 Onhitted 나 set 함수 써서 hp 깎이면 됨 ㅇ.
			attackDelay = 0.f;
			isAttackPlayer = false;
			sprite.setOrigin(19.f, 45.f);	//뛸 때  발 끝 좌표 21 46
			animation.Play("ZombieWalkerWalk");
		}
	}
}

bool ZombieWalker::OnHitted(int atk)
{
	if (health > 0)
	{
		animation.Play(strDemageTaken);
		health -= atk;
		return true;
	}
}

