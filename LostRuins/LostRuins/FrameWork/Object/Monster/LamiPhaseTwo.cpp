#include "LamiPhaseTwo.h"

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
	atk = 3;
	attackHitDelay = 0.f;
	punchCount = 0;
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

	sprite.setOrigin((sprite.getTextureRect().width) * 0.5f, sprite.getTextureRect().height*0.5f);
	sprite.setPosition(resolution.x*0.5, resolution.y * 0.7f);
	/*sprite.setPosition(500 * 0.3f, 500 * 1.2f);*/

	sprite.setScale(scale);

	leftSclera.setTexture(TextureHolder::GetTexture("graphics/Sclera.png"));

	leftSclera.setOrigin(leftSclera.getTextureRect().width * 0.5f, leftSclera.getTextureRect().height * 0.5f);
	leftSclera.setPosition(sprite.getGlobalBounds().left + (49.0f * 3.f), sprite.getGlobalBounds().top + (52.f * 3.f));
	leftSclera.setScale(3.f, 3.f);

	leftEye.setTexture(TextureHolder::GetTexture("graphics/Eye.png"));
	leftEye.setScale(scale);
	leftEye.setOrigin(leftEye.getTextureRect().width * 0.5f, leftEye.getTextureRect().height * 0.5f);
	leftEye.setPosition(sprite.getGlobalBounds().left + (49.0f * 3.f), sprite.getGlobalBounds().top + (52.f * 3.f));

	/*Sprite leftSclera;
	Sprite rightSclera;

	Sprite leftEye;
	Sprite RightEye;*/

	SetHealth(20);
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
	attackRangeLeftBox.setOrigin(attackRangeBox.getSize().x * 0.5, attackRangeBox.getSize().y);
	attackRangeLeftBox.setPosition(sprite.getOrigin().x - 180.f, sprite.getOrigin().y);

	attackRangeRightBox.setSize(Vector2f(60.f, 150.f));
	attackRangeRightBox.setScale(scale);
	attackRangeRightBox.setFillColor(Color(153, 0, 0, 80));
	attackRangeRightBox.setOrigin(attackRangeBox.getSize().x * 0.5, attackRangeBox.getSize().y);
	attackRangeRightBox.setPosition(sprite.getOrigin().x + 180.f, sprite.getOrigin().y);


	hitBox.setSize(Vector2f(60.f, 100.f));
	hitBox.setScale(scale);
	hitBox.setOrigin(hitBox.getSize().x * 0.5f, hitBox.getSize().y * 0.99f);
	hitBox.setFillColor(Color(0, 0, 100, 70));
	hitBox.setPosition(sprite.getOrigin());

	

	leftHand.Init(Vector2f(sprite.getGlobalBounds().left + 35 * 3, sprite.getGlobalBounds().top + 17 * 3), 0);
	rightHand.Init(Vector2f(sprite.getGlobalBounds().left + 89 * 3, sprite.getGlobalBounds().top + 17 * 3), 1);
	a = 1.f;
	updateY = leftSclera.getGlobalBounds().top + (leftSclera.getGlobalBounds().height * 0.5f);
}

void LamiPhaseTwo::Walk(float dt, Player& player)
{
	if (!isAttackPlayer)
	{

		sprite.setOrigin((sprite.getTextureRect().width * 0.5f), sprite.getTextureRect().height*0.5f);
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
		SetStatus(Lami2Status::STATUS_DIVING);
		break;
	case Lami2Status::STATUS_REAPPEARING:
		if (isAlive == false)
		{
			SetStatus(Lami2Status::STATUS_DEAD);
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
		animation.PlayQueue(strIdle);
		break;
	case Lami2Status::STATUS_DIVING:
		animation.Play(strDiving);
		break;
	case Lami2Status::STATUS_REAPPEARING:
		animation.Play(strReappearing);
		break;
	default:
		break;
	}
}

void LamiPhaseTwo::Attack(float dt, int atk, Player& player, Time timeHit)
{
	if (isAlive)
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

	Walk(dt, player);
	
	Attack(dt, atk, player, playTime);

	leftHand.Update(dt, Vector2f(sprite.getGlobalBounds().left + 35 * 3, sprite.getGlobalBounds().top + 17 * 3));
	rightHand.Update(dt, Vector2f(sprite.getGlobalBounds().left + 89 * 3, sprite.getGlobalBounds().top + 17 * 3));
	AnimationUpdate();
	EyeUpdate(dt, player);
	animation.Update(dt);
}

void LamiPhaseTwo::Draw(RenderWindow* window)
{
	window->draw(leftSclera);
	window->draw(leftEye);
	window->draw(leftHand.GetSprite());
	window->draw(rightHand.GetSprite());
	window->draw(sprite);
	window->draw(attackRangeBox);
	window->draw(attackRangeLeftBox);
	window->draw(attackRangeRightBox);
	window->draw(hitBox);
}

void LamiPhaseTwo::EyeUpdate(float dt, Player& player)
{
	upY = sprite.getGlobalBounds().top + (52.f * 3.f) ;
	downY = sprite.getGlobalBounds().top + (52.f * 3.f) + 12;

	prevY = leftSclera.getGlobalBounds().top + (leftSclera.getGlobalBounds().height * 0.5f);

	leftSclera.setPosition(sprite.getGlobalBounds().left + (49.0f * 3.f), updateY);

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

	leftSclera.setPosition(leftSclera.getPosition().x, leftSclera.getPosition().y + a * 0.4f);
	if (leftSclera.getGlobalBounds().top + (leftSclera.getGlobalBounds().height * 0.5f) < upY || leftSclera.getGlobalBounds().top + (leftSclera.getGlobalBounds().height * 0.5f) > downY)
	{
		leftSclera.setPosition(leftSclera.getPosition().x, prevY);
		std::cout << a << "dd" << std::endl;
	}

	float h = player.GetPosition().x - leftEye.getPosition().x;
	float v = player.GetPosition().y - leftEye.getPosition().y;
	Vector2f dir(h, v);
	prevLeftEyePos = Vector2f(leftEye.getPosition().x, leftEye.getPosition().y);
	
	
	

	if (leftEye.getGlobalBounds().left + leftEye.getGlobalBounds().width < leftSclera.getGlobalBounds().left + leftSclera.getGlobalBounds().width
		&& leftEye.getGlobalBounds().left > leftSclera.getGlobalBounds().left
		&& leftEye.getGlobalBounds().top + leftEye.getGlobalBounds().height < leftSclera.getGlobalBounds().top + leftSclera.getGlobalBounds().height
		&& leftEye.getGlobalBounds().top > leftSclera.getGlobalBounds().top)
	{
		leftEye.setPosition(leftEye.getPosition() + Utils::Normalize(dir) * speed * dt * 4.f);
	}
	if (leftSclera.getGlobalBounds().left + (leftSclera.getGlobalBounds().width * 0.5f) + 12 < leftEye.getGlobalBounds().left + (leftEye.getGlobalBounds().width * 0.5f))
	{
		leftEye.setPosition(prevLeftEyePos.x, leftEye.getPosition().y);
	}
	if (leftSclera.getGlobalBounds().left + (leftSclera.getGlobalBounds().width * 0.5f) - 6 > leftEye.getGlobalBounds().left + (leftEye.getGlobalBounds().width * 0.5f))
	{
		leftEye.setPosition(prevLeftEyePos.x, leftEye.getPosition().y);
	}
	if (leftSclera.getGlobalBounds().top + (leftSclera.getGlobalBounds().height * 0.5f) + 6 < leftEye.getGlobalBounds().top + (leftEye.getGlobalBounds().height * 0.5f))
	{
		leftEye.setPosition(leftEye.getPosition().x, prevLeftEyePos.y);
	}
	if (leftSclera.getGlobalBounds().top + (leftSclera.getGlobalBounds().height * 0.5f) - 9 > leftEye.getGlobalBounds().top + (leftEye.getGlobalBounds().height * 0.5f))
	{
		leftEye.setPosition(leftEye.getPosition().x, prevLeftEyePos.y);
	}

	updateY = leftSclera.getGlobalBounds().top + (leftSclera.getGlobalBounds().height * 0.5f);
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
