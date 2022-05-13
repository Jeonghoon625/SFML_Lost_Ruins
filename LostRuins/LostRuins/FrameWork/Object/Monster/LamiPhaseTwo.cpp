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
	Idle.loadFromFile("graphics/BossSewerPhase2Idle.png");
	Idle2.loadFromFile("graphics/Lami_Phase2.png");
	strIdle = ("Lami2Idle");
	strDiving = "Lami2Diving";
	strReappearing = "Lami2Reappearing";
	strReappearingToIdle = "Lami2Reappearing";

	animation.Play(strIdle);

	sprite.setOrigin((sprite.getTextureRect().width) * 0.5f, sprite.getTextureRect().height * 0.5f);
	sprite.setPosition(200.f, resolution.y * 0.7f);

	sprite.setScale(scale);

	leftSclera.setTexture(TextureHolder::GetTexture("graphics/Sclera.png"));

	leftSclera.setOrigin(leftSclera.getTextureRect().width * 0.5f, leftSclera.getTextureRect().height * 0.5f);
	leftSclera.setPosition(sprite.getGlobalBounds().left + (49.0f), sprite.getGlobalBounds().top + (52.f));
	leftSclera.setScale(1.f, 1.f);

	leftEye.setTexture(TextureHolder::GetTexture("graphics/Eye.png"));
	leftEye.setScale(scale);
	leftEye.setOrigin(leftEye.getTextureRect().width * 0.5f, leftEye.getTextureRect().height * 0.5f);
	leftEye.setPosition(sprite.getGlobalBounds().left + (49.f), sprite.getGlobalBounds().top + (52.f));

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

	attackRangeLeftBox.setSize(Vector2f(60.f, 150.f));
	attackRangeLeftBox.setScale(scale);
	attackRangeLeftBox.setFillColor(Color(153, 0, 0, 80));
	attackRangeLeftBox.setOrigin(attackRangeBox.getGlobalBounds().width, attackRangeBox.getSize().y);
	attackRangeLeftBox.setPosition(sprite.getOrigin().x, sprite.getOrigin().y);

	attackRangeRightBox.setSize(Vector2f(60.f, 150.f));
	attackRangeRightBox.setScale(scale);
	attackRangeRightBox.setFillColor(Color(153, 0, 0, 80));
	attackRangeRightBox.setOrigin(attackRangeBox.getSize().x, attackRangeBox.getSize().y);
	attackRangeRightBox.setPosition(sprite.getOrigin().x, sprite.getOrigin().y);


	hitBox.setSize(Vector2f(60.f, 100.f));
	hitBox.setScale(scale);
	hitBox.setOrigin(hitBox.getSize().x * 0.5f, hitBox.getSize().y * 0.99f);
	hitBox.setFillColor(Color(0, 0, 200, 70));
	hitBox.setPosition(sprite.getOrigin());



	leftHand.Init(Vector2f(sprite.getGlobalBounds().left + 35, sprite.getGlobalBounds().top + 17), 0);
	rightHand.Init(Vector2f(sprite.getGlobalBounds().left + 89, sprite.getGlobalBounds().top + 17), 1);
	a = 1.f;
	updateY = leftSclera.getGlobalBounds().top + (leftSclera.getGlobalBounds().height * 0.5f);
}

void LamiPhaseTwo::Walk(float dt, Player& player)
{

	if (!isAttackPlayer && !isDiving && !isReappearing)
	{
		sprite.setOrigin((sprite.getTextureRect().width * 0.5f), sprite.getTextureRect().height * 0.5f);
		float h = player.GetPosition().x - sprite.getPosition().x;
		float v = 0.f;
		Vector2f dir(h, v);
		position += Utils::Normalize(dir) * speed * dt;

		sprite.setPosition(position);
		findPlayerBox.setPosition(position);
		attackRangeBox.setPosition(position);
		attackRangeLeftBox.setPosition(position.x - attackRangeBox.getSize().x * 5, position.y);
		attackRangeRightBox.setPosition(position.x + attackRangeBox.getSize().x * 5, position.y);
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
		}
		break;
	case Lami2Status::STATUS_REAPPEARING:
		if (isReappearing == false)
		{
			SetStatus(Lami2Status::STATUS_IDLE);
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
			animation.Play(strReappearingToIdle);
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
		animation.Play(strReappearingToIdle, std::bind(&LamiPhaseTwo::SetIdle, this));
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
	Attack(dt, atk, player, playTime);
	Dive(dt, player);
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

	AnimationUpdate();
	EyeUpdate(dt, player);
	animation.Update(dt);
}

void LamiPhaseTwo::Dive(float dt, Player& player)
{
	if (health < START_HEALTH * 0.7f && diveCount == 0)
	{
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
		attackRangeLeftBox.setPosition(position.x - attackRangeBox.getSize().x * 5, position.y);
		attackRangeRightBox.setPosition(position.x + attackRangeBox.getSize().x * 5, position.y);
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
		attackRangeLeftBox.setPosition(position.x - attackRangeBox.getSize().x * 5, position.y);
		attackRangeRightBox.setPosition(position.x + attackRangeBox.getSize().x * 5, position.y);
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
		float v = resolution.y * 0.7f - sprite.getPosition().y;
		Vector2f dir(h, v);
		position += Utils::Normalize(dir) * speed * 50.f * dt;

		sprite.setPosition(position);
		findPlayerBox.setPosition(position);
		attackRangeBox.setPosition(position);
		attackRangeLeftBox.setPosition(position.x - attackRangeBox.getSize().x * 5, position.y);
		attackRangeRightBox.setPosition(position.x + attackRangeBox.getSize().x * 5, position.y);
		hitBox.setPosition(position);


		if (sprite.getPosition().y < (resolution.y * 0.7f))
		{
			sprite.setPosition(sprite.getPosition().x, resolution.y * 0.7f);
			ReappearOn = false;
			isReappearing = true;
			isDiving = false;
			diveDelay = 0.f;
		}
	}
	std::cout << sprite.getPosition().y << std::endl;
}

void LamiPhaseTwo::Draw(RenderWindow* window)
{
	window->draw(leftSclera);
	window->draw(leftEye);
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
	if (!isDiving && !isReappearing)
	{
		upY = sprite.getGlobalBounds().top + (52.f);
		downY = sprite.getGlobalBounds().top + (52.f) + 4;

		prevY = leftSclera.getGlobalBounds().top + (leftSclera.getGlobalBounds().height * 0.5f);

		/*leftSclera.setPosition(sprite.getGlobalBounds().left + (49.0f * 3.f), updateY);*/

		std::cout << prevY << std::endl;
		std::cout << upY << std::endl;
		std::cout << downY << std::endl;
		if ((Idle2.getPixel(sprite.getTextureRect().left + 49, sprite.getTextureRect().top + 50) == Idle.getPixel(48, 46)) && a == 1)
		{
			a *= -1;
		}
		else if ((Idle2.getPixel(sprite.getTextureRect().left + 49, sprite.getTextureRect().top + 43) == Idle.getPixel(48, 46)) && a == -1)
		{
			a *= -1;
		}

		leftSclera.setPosition(sprite.getGlobalBounds().left + (49.0f), leftSclera.getPosition().y + a * 0.4f);
		if (leftSclera.getGlobalBounds().top + (leftSclera.getGlobalBounds().height * 0.5f) < upY || leftSclera.getGlobalBounds().top + (leftSclera.getGlobalBounds().height * 0.5f) > downY)
		{
			leftSclera.setPosition(leftSclera.getPosition().x, prevY);
			std::cout << a << "dd" << std::endl;
		}

		prevLeftEyePos = Vector2f(leftEye.getPosition().x, leftEye.getPosition().y);

		float h = leftSclera.getGlobalBounds().left + leftSclera.getGlobalBounds().width;
		float v = leftSclera.getGlobalBounds().top + (leftSclera.getGlobalBounds().height * 0.5f);
		Vector2f dirRC(h, v);
		h = leftSclera.getGlobalBounds().left + leftSclera.getGlobalBounds().width;
		v = leftSclera.getGlobalBounds().top + leftSclera.getGlobalBounds().height * 0.9f;
		Vector2f dirRB(h, v);
		h = leftSclera.getGlobalBounds().left + leftSclera.getGlobalBounds().width * 0.5f;
		v = leftSclera.getGlobalBounds().top + leftSclera.getGlobalBounds().height * 0.9f;
		Vector2f dirCB(h, v);
		h = leftSclera.getGlobalBounds().left + leftSclera.getGlobalBounds().width * 0.1f;
		v = leftSclera.getGlobalBounds().top + leftSclera.getGlobalBounds().height * 0.9f;
		Vector2f dirLB(h, v);
		h = leftSclera.getGlobalBounds().left + leftSclera.getGlobalBounds().width * 0.1f;
		v = leftSclera.getGlobalBounds().top + leftSclera.getGlobalBounds().height * 0.5f;
		Vector2f dirLC(h, v);

		float lengthRC = Utils::GetLength(dirRC - Vector2f(player.GetHitBox().getGlobalBounds().left + player.GetHitBox().getGlobalBounds().width * 0.5f, player.GetHitBox().getGlobalBounds().top + player.GetHitBox().getGlobalBounds().height * 0.5f));
		float lengthRB = Utils::GetLength(dirRB - Vector2f(player.GetHitBox().getGlobalBounds().left + player.GetHitBox().getGlobalBounds().width * 0.5f, player.GetHitBox().getGlobalBounds().top + player.GetHitBox().getGlobalBounds().height * 0.5f));
		float lengthCB = Utils::GetLength(dirCB - Vector2f(player.GetHitBox().getGlobalBounds().left + player.GetHitBox().getGlobalBounds().width * 0.5f, player.GetHitBox().getGlobalBounds().top + player.GetHitBox().getGlobalBounds().height * 0.5f));
		float lengthLB = Utils::GetLength(dirLB - Vector2f(player.GetHitBox().getGlobalBounds().left + player.GetHitBox().getGlobalBounds().width * 0.5f, player.GetHitBox().getGlobalBounds().top + player.GetHitBox().getGlobalBounds().height * 0.5f));
		float lengthLC = Utils::GetLength(dirLC - Vector2f(player.GetHitBox().getGlobalBounds().left + player.GetHitBox().getGlobalBounds().width * 0.5f, player.GetHitBox().getGlobalBounds().top + player.GetHitBox().getGlobalBounds().height * 0.5f));

		float length;
		Vector2f dir;

		if (lengthRC > lengthRB)
		{
			dir = dirRB - Vector2f(leftEye.getGlobalBounds().left + leftEye.getGlobalBounds().width, leftEye.getGlobalBounds().top + leftEye.getGlobalBounds().height);
			length = lengthRB;
		}
		else
		{
			dir = dirRC - Vector2f(leftEye.getGlobalBounds().left + leftEye.getGlobalBounds().width, leftEye.getGlobalBounds().top + leftEye.getGlobalBounds().height * 0.5f);
			length = lengthRC;
		}

		if (length > lengthCB)
		{
			dir = dirCB - Vector2f(leftEye.getGlobalBounds().left + leftEye.getGlobalBounds().width * 0.5f, leftEye.getGlobalBounds().top + leftEye.getGlobalBounds().height);
			length = lengthCB;
		}

		if (length > lengthLB)
		{
			dir = dirLB - Vector2f(leftEye.getGlobalBounds().left, leftEye.getGlobalBounds().top + leftEye.getGlobalBounds().height);
			length = lengthLB;
		}

		if (length > lengthLC)
		{
			dir = dirLC - Vector2f(leftEye.getGlobalBounds().left, leftEye.getGlobalBounds().top + leftEye.getGlobalBounds().height * 0.5f);
			length = lengthLC;
		}



		leftEye.setPosition(leftEye.getPosition() + Utils::Normalize(dir) * speed * 2.f * dt);

		/*updateY = leftSclera.getGlobalBounds().top + (leftSclera.getGlobalBounds().height * 0.5f);*/
	}
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
