#include "GoblinAttacker.h"

GoblinAttacker::GoblinAttacker()
	:Monster()
{
	Monster::SetHealth(20);
	Monster::SetAtk(3);
	Monster::SetSpeed(50.f);
}

void GoblinAttacker::MonsterInit()
{
	strDemageTaken = ("GoblinAttackerDemageTaken");

	sprite.setOrigin(23.f, 30);		//고블린 발 끝 좌표 23,30
	sprite.setPosition(resolution.x * 0.3f, resolution.y * 0.5f);
	sprite.setScale(scale);
	position = sprite.getPosition();


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

void GoblinAttacker::FindPlayer(Player& player)
{
	if (!isFindPlayer)
	{
		if (findPlayerBox.getGlobalBounds().intersects(player.GetHitBox().getGlobalBounds()))
		{
			isFindPlayer = true;

			sprite.setOrigin(23.f, 47);		//고블린 뛸때 발 좌표가 23.f, 47임
			animation.Play("GoblinAttackerRun");
		}
	}
}

void GoblinAttacker::ChasePlayer(Player& player, float dt)
{
	if (isFindPlayer && !isAttackPlayer)
	{
		if (attackRangeBox.getGlobalBounds().intersects(player.GetHitBox().getGlobalBounds()))
		{
			sprite.setOrigin(20.f, 38);		//공격할때 고블린 발 끝 좌표 20,38
			animation.Play("GoblinAttackerAttack");
			isAttackPlayer = true;
		}

		if (!isAttackPlayer)
		{
			float h = player.GetPosition().x - sprite.getPosition().x;
			float v = 0.f;
			Vector2f dir(h, v);

			position += (Utils::Normalize(dir) * speed) * 2.f * dt;
			sprite.setPosition(position);

			findPlayerBox.setPosition(position);
			attackRangeBox.setPosition(position);
			hitBox.setPosition(position);

			if (h > 0)
			{
				sprite.setScale(-3.f, 3.f);	//플레이어가 몬스터 왼쪽에 있을때
				attackRangeBox.setOrigin(0, 30);
				findPlayerBox.setOrigin(0.f, 40.f);
			}
			else
			{
				sprite.setScale(3.f, 3.f);	//플레이어가 몬스터 오른쪽에 있을때
				attackRangeBox.setOrigin(30, 30);
				findPlayerBox.setOrigin(200.f, 40.f);
			}

			if (h * h > 500.f * 500.f)		//플레이어의 거리가 떨어지면 플레이어 추적하는거 취소
			{
				isFindPlayer = false;
			}
		}
	}
}

void GoblinAttacker::Walk(float dt)
{
	if (!isFindPlayer)
	{
		checkTime += dt;
		if (checkTime > 3.f)
		{
			checkTime = 0;
			nextMove = Utils::RandomRange(-1, 2);	//-1이면 오른쪽 0이면 멈춤 1이면 왼쪽
			switch (nextMove)
			{
			case -1:
				sprite.setScale(3.f, 3.f);
				animation.Play("GoblinAttackerWalk");
				sprite.setOrigin(23.f, 30);
				findPlayerBox.setOrigin(200.f, 40.f);
				attackRangeBox.setOrigin(30, 30);
				break;
			case 0:
				animation.Play("GoblinAttackerIdle");
				sprite.setOrigin(23.f, 30);
				break;
			case 1:
				sprite.setScale(-3.f, 3.f);
				animation.Play("GoblinAttackerWalk");
				sprite.setOrigin(23.f, 30);
				findPlayerBox.setOrigin(0.f, 40.f);
				attackRangeBox.setOrigin(0, 30);
				break;
			default:
				break;
			}
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

void GoblinAttacker::Run(float dt)
{
}

void GoblinAttacker::Attack(float dt, int atk, Player& player)
{
	if (isAttackPlayer)
	{
		attackDelay += dt;
		if (attackDelay > 1.5f)
		{
			//여기에 함수 추가해서 플레이어 Onhitted 나 set 함수 써서 hp 깎이면 됨 ㅇ.
			attackDelay = 0.f;
			isAttackPlayer = false;
			sprite.setOrigin(21.f, 46.f);	//뛸 때  발 끝 좌표 21 46
			animation.Play("GoblinAttackerRun");
		}
	}
}

bool GoblinAttacker::OnHitted(int atk)
{
	if (health > 0)
	{
		animation.Play(strDemageTaken);
		health -= atk;
		return true;
	}
}
