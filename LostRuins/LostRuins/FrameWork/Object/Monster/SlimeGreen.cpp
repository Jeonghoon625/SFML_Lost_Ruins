#include "SlimeGreen.h"
#include "../../Mgr/Utils.h"
#include <functional>

SlimeGreen::SlimeGreen()
	:Monster()
{
}

void SlimeGreen::Spawn(Vector2f pos)
{
	position = pos;
	sprite.setPosition(position);

	findPlayerBox.setSize(Vector2f(200.f, 40.f));
	findPlayerBox.setScale(scale);
	findPlayerBox.setFillColor(Color(255, 255, 255, 80));
	findPlayerBox.setOrigin(200, 40);
	findPlayerBox.setPosition(position);

	attackRangeBox.setSize(Vector2f(100.f, 30.f));
	attackRangeBox.setScale(scale);
	attackRangeBox.setFillColor(Color(153, 0, 0, 80));
	attackRangeBox.setOrigin(30, 30);
	attackRangeBox.setPosition(position);

	hitBox.setSize(Vector2f(43.f, 30.f));
	hitBox.setScale(scale);
	hitBox.setOrigin(hitBox.getSize().x * 0.5f, hitBox.getSize().y * 0.99f);
	hitBox.setFillColor(Color(50, 50, 25, 70));
	hitBox.setPosition(position);
}

void SlimeGreen::MonsterInit()
{
	strWalk = ("SlimeGreenWalk");
	strIdle = ("SlimeGreenIdle");
	strRun = ("SlimeGreenWalk");
	strDead = ("SlimeGreenDead");
	strAttack = ("SlimeGreenAttack");
	strDamageTaken = ("SlimeGreenDamageTaken");
	AnimationInit(&sprite);

	SetHealth(20);
	SetAtk(3);
	SetSpeed(60.f);

	sprite.setPosition(90, 340);
	sprite.setScale(scale);
	position = sprite.getPosition();
	

	findPlayerBox.setSize(Vector2f(200.f, 40.f));
	findPlayerBox.setScale(scale);
	findPlayerBox.setFillColor(Color(255, 255, 255, 80));
	findPlayerBox.setOrigin(200, 40);
	findPlayerBox.setPosition(sprite.getOrigin());

	attackRangeBox.setSize(Vector2f(100.f, 30.f));
	attackRangeBox.setScale(scale);
	attackRangeBox.setFillColor(Color(153, 0, 0, 80));
	attackRangeBox.setOrigin(30, 30);
	attackRangeBox.setPosition(sprite.getOrigin());

	hitBox.setSize(Vector2f(43.f, 30.f));
	hitBox.setScale(scale);
	hitBox.setOrigin(hitBox.getSize().x * 0.5f, hitBox.getSize().y * 0.99f);
	hitBox.setFillColor(Color(50, 50, 25, 70));
	hitBox.setPosition(sprite.getOrigin());

	SoundInit();

	animation.Play(strIdle);
	sprite.setOrigin((sprite.getTextureRect().width) * 0.5f, sprite.getTextureRect().height);
}

void SlimeGreen::ChasePlayer(Player& player, float dt)
{
	if (isAlive)
	{
		/*animation.PlayQueue(strRun);*/
		if (isFindPlayer && !isAttackPlayer)
		{
			if (attackRangeBox.getGlobalBounds().intersects(player.GetHitBox().getGlobalBounds()) && attackDelay > 2.5f)
			{
				AttackPlayerPos = player.GetPosition();
				attackDelay = 0.f;
				/*animation.Play(strAttack);*/
				isFindPlayer = false;
				isAttackPlayer = true;
			}

			if (!isAttackPlayer)
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

void SlimeGreen::Attack(float dt, int atk, Player& player, Time timeHit)
{
	if (isAlive)
	{
		if (isAttackPlayer)
		{
			attackHitDelay += dt;
			if (attackHitDelay > 0.5f)
			{
				float h = AttackPlayerPos.x - sprite.getPosition().x;
				float v = 0.f;
				Vector2f dir(h, v);
				if (Utils::GetLength(dir) < speed * dt * 0.5f)
				{
					position.x = AttackPlayerPos.x;
				}
				else
				{
					position += Utils::Normalize(dir) * speed * 3.f * dt;
				}
			}
			sprite.setPosition(position);
			findPlayerBox.setPosition(position);
			attackRangeBox.setPosition(position);
			hitBox.setPosition(position);


			if (sprite.getGlobalBounds().intersects(player.GetHitBox().getGlobalBounds()))
			{
				player.OnHitted(atk, timeHit);
			}

			if (attackHitDelay > 19.f)
			{
				//if (attackRangeBox.getGlobalBounds().intersects(player.GetHitBox().getGlobalBounds()))
				//{
				//	if (sprite.getPosition().x > player.GetSprite().getPosition().x)
				//	{
				//		monsterSide = true;
				//	}
				//	else
				//	{
				//		monsterSide = false;
				//	}
				//	player.OnHitted(atk, timeHit);
				//	// 여기에 player.onhitted
				//}

				attackHitDelay = 0.f;
				isAttackPlayer = false;
				isFindPlayer = true;
				/*animation.Play(strRun);*/
			}
		}
	}
}

void SlimeGreen::SetStatus(MonsterStatus newStatus)
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
		animation.Play(strAttack, std::bind(&SlimeGreen::IsFinishAttack, this));
		break;
	case MonsterStatus::STATUS_HIT:
		soundHitted.play();
		animation.Play(strDamageTaken);
		break;
	case MonsterStatus::STATUS_DEAD:
		soundDeath.play();
		animation.Play(strDead);
		break;
	}
	sprite.setOrigin((sprite.getTextureRect().width) * 0.5f, sprite.getTextureRect().height);
}

void SlimeGreen::IsFinishAttack()
{
	attackHitDelay = 20.f;
}

void SlimeGreen::SoundInit()
{
	soundFindPlayer.setBuffer(SoundHolder::GetBuffer("sound/monster/Slime0.wav"));
	soundHitted.setBuffer(SoundHolder::GetBuffer("sound/monster/SlimeHitVoice0.wav"));
	soundDeath.setBuffer(SoundHolder::GetBuffer("sound/monster/SlimeDie0.wav"));
}




