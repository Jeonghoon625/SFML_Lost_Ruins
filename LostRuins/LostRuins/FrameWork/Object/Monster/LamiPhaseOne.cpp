#include "LamiPhaseOne.h"

LamiPhaseOne::LamiPhaseOne()
	:Monster(), attackCount(0), isUppercut(false)
{
}

void LamiPhaseOne::Spawn(Vector2f pos)
{
	position = pos;
	sprite.setPosition(position);

	findPlayerBox.setSize(Vector2f(200.f, 40.f));
	findPlayerBox.setScale(scale);
	findPlayerBox.setFillColor(Color(255, 255, 255, 80));
	findPlayerBox.setOrigin(200, 40);
	findPlayerBox.setPosition(position);

	attackRangeBox.setSize(Vector2f(51.f, 30.f));
	attackRangeBox.setScale(scale);
	attackRangeBox.setFillColor(Color(153, 0, 0, 80));
	attackRangeBox.setOrigin(30, 30);
	attackRangeBox.setPosition(position);

	hitBox.setSize(Vector2f(45.f, 30.f));
	hitBox.setScale(scale);
	hitBox.setOrigin(hitBox.getSize().x * 0.5f, hitBox.getSize().y * 0.99f);
	hitBox.setFillColor(Color(50, 50, 25, 70));
	hitBox.setPosition(position);
}

void LamiPhaseOne::AnimationUpdate()
{
	switch (currentStatus)
	{
	case MonsterStatus::STATUS_IDLE:
		if (isAlive == false)
		{
			SetStatus(MonsterStatus::STATUS_DEAD);
		}
		else if (isHit == true)
		{
			SetStatus(MonsterStatus::STATUS_HIT);
		}
		else if (isAttackPlayer == true)
		{
			SetStatus(MonsterStatus::STATUS_ATTACK);
		}
		else if (isUppercut == true)
		{
			SetStatus(MonsterStatus::STATUS_UPPERCUT);
		}
		else if (isWalk == true)
		{
			SetStatus(MonsterStatus::STATUS_WALK);
		}
		else if (isFindPlayer == true)
		{
			SetStatus(MonsterStatus::STATUS_RUN);
		}
		break;
	case MonsterStatus::STATUS_WALK:
		if (isAlive == false)
		{
			SetStatus(MonsterStatus::STATUS_DEAD);
		}
		else if (isHit == true)
		{
			SetStatus(MonsterStatus::STATUS_HIT);
		}
		else if (isFindPlayer == true)
		{
			SetStatus(MonsterStatus::STATUS_RUN);
		}
		else if (isIdle == true)
		{
			SetStatus(MonsterStatus::STATUS_IDLE);
		}
	case MonsterStatus::STATUS_RUN:
		if (isAlive == false)
		{
			SetStatus(MonsterStatus::STATUS_DEAD);
		}
		else if (isHit == true)
		{
			SetStatus(MonsterStatus::STATUS_HIT);
		}
		else if (isAttackPlayer)
		{
			SetStatus(MonsterStatus::STATUS_ATTACK);
		}
		else if (isUppercut)
		{
			SetStatus(MonsterStatus::STATUS_UPPERCUT);
		}
		break;
	case MonsterStatus::STATUS_ATTACK:
		if (isAlive == false)
		{
			SetStatus(MonsterStatus::STATUS_DEAD);
		}
		else if (isHit == true)
		{
			SetStatus(MonsterStatus::STATUS_HIT);
		}
		else if (isAttackPlayer == false)
		{
			SetStatus(MonsterStatus::STATUS_RUN);
		}
		break;
	case MonsterStatus::STATUS_UPPERCUT:
		if (isAlive == false)
		{
			SetStatus(MonsterStatus::STATUS_DEAD);
		}
		else if (isHit == true)
		{
			SetStatus(MonsterStatus::STATUS_HIT);
		}
		else if (isUppercut == false)
		{
			SetStatus(MonsterStatus::STATUS_RUN);
		}
		break;
	case MonsterStatus::STATUS_HIT:
		if (isHit == false)
		{
			SetStatus(MonsterStatus::STATUS_RUN);
		}
	case MonsterStatus::STATUS_DEAD:
		break;
	default:
		break;
	}
}

void LamiPhaseOne::SetStatus(MonsterStatus newStatus)
{
	MonsterStatus prevStatus = currentStatus;
	currentStatus = newStatus;

	switch (currentStatus)
	{
	case MonsterStatus::STATUS_IDLE:
		animation.Play(strIdle);
		break;
	case MonsterStatus::STATUS_WALK:
		animation.Play(strWalk);
		break;
	case MonsterStatus::STATUS_RUN:
		animation.Play(strRun);
		break;
	case MonsterStatus::STATUS_ATTACK:
		animation.Play(strAttack);
		break;
	case MonsterStatus::STATUS_UPPERCUT:
		animation.Play(strUppercut);
		break;
	case MonsterStatus::STATUS_HIT:
		soundHitted.play();
		animation.Play(strDamageTaken);
		break;
	case MonsterStatus::STATUS_DEAD:
		animation.Play(strDead);
		break;
	}
	sprite.setOrigin((sprite.getTextureRect().width) * 0.5f, sprite.getTextureRect().height);
}

void LamiPhaseOne::MonsterInit()
{
	strWalk = ("Lami1Walk");
	strIdle = ("Lami1Idle");
	strRun = ("Lami1Walk");
	strDead = ("Lami1Dead");
	strAttack = ("Lami1Punch");
	strAttackBlocked = ("Lami1AttackBlocked");
	strDamageTaken = ("Lami1DamageTaken");
	strUppercut = ("Lami1Uppercut");

	SetHealth(60);
	SetAtk(3);
	SetSpeed(80.f);

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

	hitBox.setSize(Vector2f(50.f, 30.f));
	hitBox.setScale(scale);
	hitBox.setOrigin(hitBox.getSize().x * 0.5f, hitBox.getSize().y * 0.99f);
	hitBox.setFillColor(Color(50, 50, 25, 70));
	hitBox.setPosition(sprite.getOrigin());

	SoundInit();

	animation.Play(strIdle);
	sprite.setOrigin((sprite.getTextureRect().width) * 0.5f, sprite.getTextureRect().height);
}

void LamiPhaseOne::ChasePlayer(Player& player, float dt)
{
	if (isAlive)
	{
		if (isFindPlayer && !isAttackPlayer && !isUppercut)
		{
			if (attackRangeBox.getGlobalBounds().intersects(player.GetHitBox().getGlobalBounds()) && attackDelay > 1.5f)
			{
				attackCount++;
				attackDelay = 0.f;
				isFindPlayer = false;

				if (attackCount > 3)
				{
					isUppercut = true;
				}
				else
				{
					isAttackPlayer = true;
				}
			}

			if (!isUppercut &&!isAttackPlayer && !isHit)
			{
				float h = player.GetPosition().x - sprite.getPosition().x;
				float v = 0.f;
				Vector2f dir(h, v);

				if (h > 0)
				{
					sprite.setScale(-1.f, 1.f);	//플레이어가 몬스터 왼쪽에 있을때
					attackRangeBox.setOrigin(attackRangeBox.getSize().x * 0.f, attackRangeBox.getSize().y * 0.99f);
					findPlayerBox.setOrigin(0.f, 40.f);
				}
				else
				{
					sprite.setScale(1.f, 1.f);	//플레이어가 몬스터 오른쪽에 있을때
					attackRangeBox.setOrigin(attackRangeBox.getSize().x, attackRangeBox.getSize().y * 0.99f);
					findPlayerBox.setOrigin(200.f, 40.f);
				}

				if (h * h > 200.f * 200.f || (sprite.getPosition().y - player.GetPosition().y) > 85 || sprite.getPosition().y - player.GetPosition().y < -50)		//플레이어의 거리가 떨어지면 플레이어 추적하는거 취소
				{
					isFindPlayer = false;
					isIdle = true;
				}
				if ((isCollideHitBox && !isCollideAttackRangeBox) == false)
				{
					position += Utils::Normalize(dir) * speed * dt;
					sprite.setPosition(position);

					findPlayerBox.setPosition(position);
					attackRangeBox.setPosition(position);
					hitBox.setPosition(position);
				}
			}
		}
	}
}

void LamiPhaseOne::Attack(float dt, int atk, Player& player, Time timeHit)
{
	if (isAlive)
	{
		if (isAttackPlayer)
		{
			attackHitDelay += dt;

			sprite.setPosition(position);
			findPlayerBox.setPosition(position);
			attackRangeBox.setPosition(position);
			hitBox.setPosition(position);

			if (attackHitDelay > 0.75f)
			{
				if (attackRangeBox.getGlobalBounds().intersects(player.GetHitBox().getGlobalBounds()))
				{
					if (sprite.getPosition().x > player.GetSprite().getPosition().x)
					{
						monsterSide = true;
					}
					else
					{
						monsterSide = false;
					}
					player.OnHitted(atk, timeHit);
				}

				attackHitDelay = 0.f;
				isAttackPlayer = false;
				isFindPlayer = true;
			}
		}
		else if (isUppercut)
		{
			attackHitDelay += dt;

			sprite.setPosition(position);
			findPlayerBox.setPosition(position);
			attackRangeBox.setPosition(position);
			hitBox.setPosition(position);

			if (attackHitDelay > 0.65f)
			{
				if (sprite.getGlobalBounds().intersects(player.GetHitBox().getGlobalBounds()))
				{
					player.OnHitted(atk, timeHit);
				}

				attackHitDelay = 0.f;
				isUppercut = false;
				attackCount = 0;
				isFindPlayer = true;
			}
		}
	}
}

bool LamiPhaseOne::OnHitted(int atk, float dt, Time timeHit)
{
	if (isAlive)
	{
		if (timeHit.asMilliseconds() - lastHit.asMilliseconds() > immuneMs)
		{
			lastHit = timeHit;
			if (health > 0)
			{
				/*animation.Play(strDamageTaken);*/
				attackDelay = 0;
				isFindPlayer = false;
				isHit = true;
				attackHitDelay = 0.f;
				isUppercut = false;
				isAttackPlayer = false;	//맞으면 공격하려던거 취소
				health -= atk;
				std::cout << "HP : " << GetHealth() << std::endl;
				return true;
			}
			else
			{
				isAlive = false;
			}
			return false;
		}
	}
}

void LamiPhaseOne::SoundInit()
{
	soundFindPlayer.setBuffer(SoundHolder::GetBuffer("sound/monster/Slime2.wav"));
	soundHitted.setBuffer(SoundHolder::GetBuffer("sound/monster/SlimeHitVoice0.wav"));
	soundDeath.setBuffer(SoundHolder::GetBuffer("sound/monster/SlimeDie0.wav"));
}
