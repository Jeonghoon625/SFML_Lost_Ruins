#include "LamiPhaseTwo.h"
#include "../../Mgr/Utils.h"
#include <functional>

LamiPhaseTwo::LamiPhaseTwo()
	:Monster()

{
	isAttackPlayer = false;
	isNearAttackPlayer = false;
	isMiddleAttackPlayer = false;
	isFarAttackPlayer = false;
	isAlive = true;
	isIdle = true;
	isHit = false;
	isLeft = false;
	isRight = false;
	isFar = false;
	isDiving = false;
	isReappearing = false;
	diveOn = false;
	ReappearOn = false;
	atk = 3;
	attackHitDelay = 0.f;
	punchCount = 0;
	diveCount = 0;
}

void LamiPhaseTwo::MonsterInit()
{
	AnimationInit(&sprite);
	strIdle = ("Lami2Idle");
	strDiving = "Lami2Diving";
	strReappearing = "Lami2Reappearing";
	strReappearingToIdle = "Lami2Reappearing";

	animation.Play(strIdle);

	sprite.setOrigin((sprite.getTextureRect().width) * 0.5f, sprite.getTextureRect().height * 0.5f);
	sprite.setPosition(200.f, resolution.y * 0.7f);
	originalPos = sprite.getPosition();

	sprite.setScale(scale);


	leftEye.Init(0, sprite);
	rightEye.Init(1, sprite);
	

	SetHealth(START_HEALTH);
	SetAtk(3);
	SetSpeed(50.f);


	position = sprite.getPosition();

	findPlayerBox.setSize(Vector2f(200.f, 40.f));
	findPlayerBox.setScale(scale);
	findPlayerBox.setFillColor(Color(255, 255, 255, 80));
	findPlayerBox.setOrigin(200, 40);
	findPlayerBox.setPosition(sprite.getOrigin());

	attackRangeBox.setSize(Vector2f(60.f, 150.f));
	attackRangeBox.setScale(scale);
	attackRangeBox.setFillColor(Color(153, 0, 0, 80));
	attackRangeBox.setOrigin(attackRangeBox.getSize().x * 0.5, attackRangeBox.getSize().y);
	attackRangeBox.setPosition(sprite.getOrigin());

	attackRangeLeftBox.setSize(Vector2f(40.f, 150.f));
	attackRangeLeftBox.setScale(scale);
	attackRangeLeftBox.setFillColor(Color(153, 0, 0, 80));
	attackRangeLeftBox.setOrigin(attackRangeLeftBox.getSize().x * 1, attackRangeBox.getSize().y);
	attackRangeLeftBox.setPosition(sprite.getOrigin().x - 90.f, sprite.getOrigin().y);

	attackRangeRightBox.setSize(Vector2f(40.f, 150.f));
	attackRangeRightBox.setScale(scale);
	attackRangeRightBox.setFillColor(Color(153, 0, 0, 80));
	attackRangeRightBox.setOrigin(attackRangeRightBox.getSize().x * 0, attackRangeBox.getSize().y);
	attackRangeRightBox.setPosition(sprite.getOrigin().x + 90.f, sprite.getOrigin().y);


	hitBox.setSize(Vector2f(60.f, 100.f));
	hitBox.setScale(scale);
	hitBox.setOrigin(hitBox.getSize().x * 0.5f, hitBox.getSize().y * 0.99f);
	hitBox.setFillColor(Color(0, 0, 200, 70));
	hitBox.setPosition(sprite.getOrigin());



	leftHand.Init(Vector2f(sprite.getGlobalBounds().left + 35, sprite.getGlobalBounds().top + 17), 0);
	rightHand.Init(Vector2f(sprite.getGlobalBounds().left + 89, sprite.getGlobalBounds().top + 17), 1);
}

void LamiPhaseTwo::Spawn(Vector2f pos)
{
	sprite.setPosition(pos);
	position = sprite.getPosition();
	originalPos = pos;
}

void LamiPhaseTwo::Walk(float dt, Player& player)
{

	if (!isAttackPlayer && !isDiving && !isReappearing)
	{
		sprite.setOrigin((sprite.getTextureRect().width * 0.5f), sprite.getTextureRect().height * 0.5f);
		float h = player.GetPosition().x - sprite.getPosition().x;
		float v = 0.f;
		Vector2f dir(h, v);
		if (Utils::GetLength(dir) < speed * dt * 0.5f)
		{
			position = Vector2f(player.GetPosition().x,position.y);
		}
		else
		{
			position += Utils::Normalize(dir) * speed * dt;
		}
		sprite.setPosition(position);
		findPlayerBox.setPosition(position);
		attackRangeBox.setPosition(position);
		attackRangeLeftBox.setPosition(position.x - attackRangeBox.getSize().x * 1.5f, position.y);
		attackRangeRightBox.setPosition(position.x + attackRangeBox.getSize().x * 1.5f, position.y);
		hitBox.setPosition(position);
	}
}

void LamiPhaseTwo::AnimationUpdate()
{
	switch (currentStatus)
	{
	case Lami2Status::STATUS_IDLE:
		if (isAlive == false)
		{
			SetStatus(Lami2Status::STATUS_DEAD);
		}
		else if (isIdle == true)
		{
			SetStatus(Lami2Status::STATUS_IDLE);
			leftHand.SetStatus(Lami2Status::STATUS_IDLE);

		}
		else if (isFarAttackPlayer == true && isFar == true)
		{
			SetStatus(Lami2Status::STATUS_ATTACK_FAR);
			leftHand.SetStatus(Lami2Status::STATUS_ATTACK_FAR);
			rightHand.SetStatus(Lami2Status::STATUS_ATTACK_FAR);
		}
		else if (isMiddleAttackPlayer == true && isLeft == true)
		{
			SetStatus(Lami2Status::STATUS_ATTACK_MIDDLE);
			leftHand.SetStatus(Lami2Status::STATUS_ATTACK_MIDDLE);
		}
		else if (isMiddleAttackPlayer == true && isRight == true)
		{
			SetStatus(Lami2Status::STATUS_ATTACK_MIDDLE);
			rightHand.SetStatus(Lami2Status::STATUS_ATTACK_MIDDLE);
		}
		else if (isNearAttackPlayer == true && isLeft == true)
		{
			SetStatus(Lami2Status::STATUS_ATTACK_NEAR);
			leftHand.SetStatus(Lami2Status::STATUS_ATTACK_NEAR);
		}
		else if (isNearAttackPlayer == true && isRight == true)
		{
			SetStatus(Lami2Status::STATUS_ATTACK_NEAR);
			rightHand.SetStatus(Lami2Status::STATUS_ATTACK_NEAR);
		}
		else if (isDiving == true && isReappearing == false)
		{
			SetStatus(Lami2Status::STATUS_DIVING);
			leftHand.SetStatus(Lami2Status::STATUS_DIVING);
			rightHand.SetStatus(Lami2Status::STATUS_DIVING);
			leftEye.SetStatus(Lami2Status::STATUS_DIVING, sprite);
			rightEye.SetStatus(Lami2Status::STATUS_DIVING, sprite);
		}
		break;
	case Lami2Status::STATUS_ATTACK_NEAR:
		if (isNearAttackPlayer == false)
		{
			SetStatus(Lami2Status::STATUS_IDLE);
		}
		break;
	case Lami2Status::STATUS_ATTACK_MIDDLE:
		if (isMiddleAttackPlayer == false)
		{
			SetStatus(Lami2Status::STATUS_IDLE);
		}
		break;
	case Lami2Status::STATUS_ATTACK_FAR:
		if (isFarAttackPlayer == false)
		{
			SetStatus(Lami2Status::STATUS_IDLE);
		}
		break;
	case Lami2Status::STATUS_DIVING:
		if (isDiving == false)
		{
			SetStatus(Lami2Status::STATUS_REAPPEARING);	//여기 작업중
			leftHand.SetStatus(Lami2Status::STATUS_REAPPEARING);
			rightHand.SetStatus(Lami2Status::STATUS_REAPPEARING);
			leftEye.SetStatus(Lami2Status::STATUS_REAPPEARING, sprite);
			rightEye.SetStatus(Lami2Status::STATUS_REAPPEARING, sprite);
		}
		break;
	case Lami2Status::STATUS_REAPPEARING:
		if (isReappearing == false)
		{
			SetStatus(Lami2Status::STATUS_IDLE);
			leftEye.SetStatus(Lami2Status::STATUS_REAPPEARINGTOIDLE, sprite);
			rightEye.SetStatus(Lami2Status::STATUS_REAPPEARINGTOIDLE, sprite);
		}
		break;
	case Lami2Status::STATUS_DEAD:
		if (isAlive == false)
		{
			SetStatus(Lami2Status::STATUS_DEAD);
		}
		break;
	default:
		break;
	}
}

void LamiPhaseTwo::SetStatus(Lami2Status newStatus)
{
	Lami2Status prevStatus = currentStatus;
	currentStatus = newStatus;

	switch (currentStatus)
	{
	case Lami2Status::STATUS_IDLE:
		if (prevStatus == Lami2Status::STATUS_REAPPEARING)
		{
			/*animation.Play(strReappearingToIdle);*/
			animation.Play(strReappearingToIdle, std::bind(&LamiPhaseTwo::EyeSetIdleStatus, this));
		}
		else
		{
			animation.PlayQueue(strIdle);
		}
		break;
	case Lami2Status::STATUS_DIVING:
		animation.Play(strDiving, std::bind(&LamiPhaseTwo::SetDive, this));
		break;
	case Lami2Status::STATUS_REAPPEARING:
		animation.Play(strReappearing, std::bind(&LamiPhaseTwo::SetIdle, this));
		break;
	case Lami2Status::STATUS_DEAD:
		animation.Play(strDead);
		break;
	default:
		break;
	}
}

void LamiPhaseTwo::Attack(float dt, int atk, Player& player, Time timeHit)
{
	if (isAlive && !isDiving)
	{
		if (!isAttackPlayer)
		{
			attackDelay += dt;
			if (attackRangeBox.getGlobalBounds().intersects(player.GetHitBox().getGlobalBounds()) && attackDelay > 0.5f)
			{
				punchCount++;
				if (punchCount < 3)
				{
					if (attackRangeBox.getGlobalBounds().left + (attackRangeBox.getGlobalBounds().width * 0.5f) >= player.GetHitBox().getPosition().x)
					{
						isLeft = true;
					}
					else
					{
						isRight = true;
					}
					isNearAttackPlayer = true;
				}
				else
				{
					punchCount = 0;
					isFar = true;
					isFarAttackPlayer = true;
				}
				isIdle = false;
				attackDelay = 0.f;
				isFindPlayer = false;
				isAttackPlayer = true;
			}
			else if (attackRangeLeftBox.getGlobalBounds().intersects(player.GetHitBox().getGlobalBounds()) && attackDelay > 0.5f)
			{
				isIdle = false;
				isMiddleAttackPlayer = true;
				isLeft = true;
				attackDelay = 0.f;
				isFindPlayer = false;
				isAttackPlayer = true;
			}
			else if (attackRangeRightBox.getGlobalBounds().intersects(player.GetHitBox().getGlobalBounds()) && attackDelay > 0.5f)
			{
				isIdle = false;
				isMiddleAttackPlayer = true;
				isRight = true;
				attackDelay = 0.f;
				isFindPlayer = false;
				isAttackPlayer = true;
			}
		}
		else if (isAttackPlayer)
		{
			if (isLeft && leftHand.GetIsAttacking() == false)
			{
				if (leftHand.GetSprite().getGlobalBounds().intersects(player.GetHitBox().getGlobalBounds()))
				{
					player.OnHitted(atk, timeHit);
				}

				attackHitDelay = 0.f;
				isIdle = true;
				isAttackPlayer = false;
				isNearAttackPlayer = false;
				isFarAttackPlayer = false;
				isMiddleAttackPlayer = false;
				isLeft = false;
				isRight = false;
				isFar = false;
			}
			else if (isRight && rightHand.GetIsAttacking() == false)
			{
				if (rightHand.GetSprite().getGlobalBounds().intersects(player.GetHitBox().getGlobalBounds()))
				{
					player.OnHitted(atk, timeHit);
				}
				attackHitDelay = 0.f;
				isIdle = true;
				isAttackPlayer = false;
				isNearAttackPlayer = false;
				isFarAttackPlayer = false;
				isMiddleAttackPlayer = false;
				isLeft = false;
				isRight = false;
				isFar = false;
			}
			else if (isFar && rightHand.GetIsAttacking() == false)
			{
				if (leftHand.GetSprite().getGlobalBounds().intersects(player.GetHitBox().getGlobalBounds()) || rightHand.GetSprite().getGlobalBounds().intersects(player.GetHitBox().getGlobalBounds()))
				{
					player.OnHitted(atk, timeHit);
				}
				attackHitDelay = 0.f;
				isIdle = true;
				isAttackPlayer = false;
				isNearAttackPlayer = false;
				isFarAttackPlayer = false;
				isMiddleAttackPlayer = false;
				isLeft = false;
				isRight = false;
				isFar = false;
			}
		}
	}


}

void LamiPhaseTwo::Update(Player& player, float dt, std::vector<TestBlock*> blocks, Time playTime)
{
	if (health > START_HEALTH * 0.5f)
	{
		health -= 1;
	}
	std::cout << health << std::endl;
	Walk(dt, player);
	/*Attack(dt, atk, player, playTime);*/
	Dive(dt, player);
	if (health > 0)
	{
		if (!isDiving && !isReappearing)
		{
			leftHand.Update(dt, Vector2f(sprite.getGlobalBounds().left + 35, sprite.getGlobalBounds().top + 17));
			rightHand.Update(dt, Vector2f(sprite.getGlobalBounds().left + 89, sprite.getGlobalBounds().top + 17));
		}
		else if (isDiving && !isReappearing)
		{
			leftHand.Update(dt, Vector2f(sprite.getGlobalBounds().left + 20, sprite.getGlobalBounds().top + 26));
			rightHand.Update(dt, Vector2f(sprite.getGlobalBounds().left + 76, sprite.getGlobalBounds().top + 26));
		}
		else if (!isDiving && isReappearing)
		{

			leftHand.Update(dt, Vector2f(sprite.getGlobalBounds().left + 29, sprite.getGlobalBounds().top + 19));
			rightHand.Update(dt, Vector2f(sprite.getGlobalBounds().left + 85, sprite.getGlobalBounds().top + 19));
		}

		leftEye.Update(sprite, player, dt, hitBox);
		rightEye.Update(sprite, player, dt, hitBox);
	}
	AnimationUpdate();
	
	animation.Update(dt);
}

void LamiPhaseTwo::Dive(float dt, Player& player)
{
	if (health < START_HEALTH * 0.7f && diveCount == 0)
	{
		sprite.setOrigin((sprite.getTextureRect().width * 0.5f), sprite.getTextureRect().height * 0.5f);
		diveCount++;
		isDiving = true;

		attackDelay = 0.f;
		isIdle = false;
		isAttackPlayer = false;
		isNearAttackPlayer = false;
		isFarAttackPlayer = false;
		isMiddleAttackPlayer = false;
		isLeft = false;
		isRight = false;
		isFar = false;

		sprite.setPosition(position);
		findPlayerBox.setPosition(position);
		attackRangeBox.setPosition(position);
		attackRangeLeftBox.setPosition(position.x - attackRangeBox.getSize().x * 1.5f, position.y);
		attackRangeRightBox.setPosition(position.x + attackRangeBox.getSize().x * 1.5f, position.y);
		hitBox.setPosition(position);
	}

	if (isDiving && diveOn)
	{
		sprite.setOrigin((sprite.getTextureRect().width * 0.5f), sprite.getTextureRect().height * 0.5f);
		diveDelay += dt;
		float h = player.GetPosition().x - sprite.getPosition().x;
		float v = 3000.f - sprite.getPosition().y;
		Vector2f dir(h, v);
		position += Utils::Normalize(dir) * speed * 50.f * dt;
		sprite.setPosition(position);
		findPlayerBox.setPosition(position);
		attackRangeBox.setPosition(position);
		attackRangeLeftBox.setPosition(position.x - attackRangeBox.getSize().x * 1.5f, position.y);
		attackRangeRightBox.setPosition(position.x + attackRangeBox.getSize().x * 1.5f, position.y);
		hitBox.setPosition(position);

		if (diveDelay > 5.f)
		{
			diveOn = false;
			ReappearOn = true;
			diveDelay = 0.f;
		}
	}

	if (isDiving && ReappearOn)	//다이빙 후 원래 자리로 돌아가기
	{
		sprite.setOrigin((sprite.getTextureRect().width * 0.5f), sprite.getTextureRect().height * 0.5f);
		float h = 0.f;
		float v = originalPos.y - sprite.getPosition().y;
		Vector2f dir(h, v);
		position += Utils::Normalize(dir) * speed * 50.f * dt;

		sprite.setPosition(position);
		findPlayerBox.setPosition(position);
		attackRangeBox.setPosition(position);
		attackRangeLeftBox.setPosition(position.x - attackRangeBox.getSize().x * 1.5f, position.y);
		attackRangeRightBox.setPosition(position.x + attackRangeBox.getSize().x * 1.5f, position.y);
		hitBox.setPosition(position);


		if (sprite.getPosition().y < (originalPos.y))
		{
			sprite.setPosition(sprite.getPosition().x, originalPos.y);
			ReappearOn = false;
			isReappearing = true;
			isDiving = false;
			diveDelay = 0.f;
			
			position = sprite.getPosition();
			
		}
	}
}

void LamiPhaseTwo::Draw(RenderWindow* window)
{
	leftEye.Draw(window);
	rightEye.Draw(window);
	window->draw(sprite);

	window->draw(leftHand.GetSprite());
	window->draw(rightHand.GetSprite());

	window->draw(attackRangeBox);
	window->draw(attackRangeLeftBox);
	window->draw(attackRangeRightBox);
	window->draw(hitBox);
}

void LamiPhaseTwo::EyeUpdate(float dt, Player& player)
{
}

void LamiPhaseTwo::SetDive()
{
	if (diveOn)
	{
		diveOn = false;
	}
	else
	{
		diveOn = true;
	}
}

void LamiPhaseTwo::SetIdle()
{
	
	if (isIdle)
	{
		isIdle = false;
	}
	else
	{
		isIdle = true;
	}
	isReappearing = false;
	leftEye.SetStatus(Lami2Status::STATUS_REAPPEARINGTOIDLE, sprite);
	rightEye.SetStatus(Lami2Status::STATUS_REAPPEARINGTOIDLE, sprite);
}

void LamiPhaseTwo::EyeSetIdleStatus()
{
	leftEye.SetStatus(Lami2Status::STATUS_IDLE, sprite);
	rightEye.SetStatus(Lami2Status::STATUS_IDLE, sprite);
}

bool LamiPhaseTwo::OnHitted(int atk, float dt, Time timeHit)
{
	if (isAlive)
	{
		if (timeHit.asMilliseconds() - lastHit.asMilliseconds() > immuneMs)
		{
			lastHit = timeHit;
			if (health > 0)
			{
				health -= atk;
				return true;
			}
			else
			{
				isAlive = false;
			}
			return false;
		}
	}
	return false;
}

void LamiPhaseTwo::Gravity(float dt, std::vector<TestBlock*> blocks)
{
}

void LamiPhaseTwo::UpdateCollision(std::vector<TestBlock*> blocks)
{
}

void LamiPhaseTwo::UpdateCollisionAttackRangeBox(std::vector<TestBlock*> blocks)
{
}
