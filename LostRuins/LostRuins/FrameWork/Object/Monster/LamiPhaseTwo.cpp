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
	attackHitDelay = 0.f;
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

	sprite.setOrigin((sprite.getTextureRect().width) * 0.5f, sprite.getTextureRect().height);
	sprite.setPosition(resolution.x * 0.3f, resolution.y * 1.1f);
	/*sprite.setPosition(500 * 0.3f, 500 * 1.2f);*/


	sprite.setScale(scale);

	leftSclera.setTexture(TextureHolder::GetTexture("graphics/Sclera.png"));

	leftSclera.setOrigin(leftSclera.getTextureRect().width * 0.5f, leftSclera.getTextureRect().height * 0.5f);
	leftSclera.setPosition(sprite.getGlobalBounds().left + (49.0f * 3.f), sprite.getGlobalBounds().top + (52. * 3.f));
	leftSclera.setScale(3.f, 3.f);

	leftEye.setTexture(TextureHolder::GetTexture("graphics/Eye.png"));
	leftEye.setScale(scale);
	leftEye.setOrigin(leftEye.getTextureRect().width * 0.5f, leftEye.getTextureRect().height * 0.5f);
	leftEye.setPosition(500, 500);

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


	hitBox.setSize(Vector2f(43.f, 30.f));
	hitBox.setScale(scale);
	hitBox.setOrigin(hitBox.getSize().x * 0.5f, hitBox.getSize().y * 0.99f);
	hitBox.setFillColor(Color(50, 50, 25, 70));
	hitBox.setPosition(sprite.getOrigin());

	animation.Play(strIdle);

	leftHand.Init(Vector2f(sprite.getGlobalBounds().left + 35 * 3, sprite.getGlobalBounds().top + 17 * 3), 0);
	rightHand.Init(Vector2f(sprite.getGlobalBounds().left + 89 * 3, sprite.getGlobalBounds().top + 17 * 3), 1);
	a = 1.f;
	updateY = leftSclera.getGlobalBounds().top + (leftSclera.getGlobalBounds().height * 0.5f);
}

void LamiPhaseTwo::Walk(float dt, Player& player)
{
	sprite.setOrigin((sprite.getTextureRect().width * 0.5f), sprite.getTextureRect().height);

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
		else if (isFarAttackPlayer == true)
		{
			SetStatus(Lami2Status::STATUS_ATTACK_FAR);
			leftHand.SetStatus(Lami2Status::STATUS_ATTACK_FAR);
		}
		else if (isMiddleAttackPlayer == true)
		{
			SetStatus(Lami2Status::STATUS_ATTACK_MIDDLE);
			leftHand.SetStatus(Lami2Status::STATUS_ATTACK_MIDDLE);
		}
		else if (isNearAttackPlayer == true)
		{
			SetStatus(Lami2Status::STATUS_ATTACK_NEAR);
			leftHand.SetStatus(Lami2Status::STATUS_ATTACK_NEAR);
		}
		break;
	case Lami2Status::STATUS_ATTACK_NEAR:
		if (isNearAttackPlayer == false)
		{
			SetStatus(Lami2Status::STATUS_IDLE);
		}
		/*leftHand.SetStatus(Lami2Status::STATUS_ATTACK_NEAR);*/
		break;
	case Lami2Status::STATUS_ATTACK_MIDDLE:
		if (isMiddleAttackPlayer == false)
		{
			SetStatus(Lami2Status::STATUS_IDLE);
		}
		/*leftHand.SetStatus(Lami2Status::STATUS_ATTACK_MIDDLE);*/
		break;
	case Lami2Status::STATUS_ATTACK_FAR:
		if (isFarAttackPlayer == false)
		{
			SetStatus(Lami2Status::STATUS_IDLE);
		}
	/*	leftHand.SetStatus(Lami2Status::STATUS_ATTACK_FAR);*/
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
				isIdle = false;
				isNearAttackPlayer = true;
				attackDelay = 0.f;
				isFindPlayer = false;
				isAttackPlayer = true;
			}
			else if (attackRangeLeftBox.getGlobalBounds().intersects(player.GetHitBox().getGlobalBounds()) && attackDelay > 0.5f)
			{
				isIdle = false;
				isFarAttackPlayer = true;
				attackDelay = 0.f;
				isFindPlayer = false;
				isAttackPlayer = true;
			}
			else if (attackRangeRightBox.getGlobalBounds().intersects(player.GetHitBox().getGlobalBounds()) && attackDelay > 0.5f)
			{
				isIdle = false;
				isFarAttackPlayer = true;
				attackDelay = 0.f;
				isFindPlayer = false;
				isAttackPlayer = true;
			}
		}
		else if (isAttackPlayer)
		{
			attackHitDelay += dt;
			if (attackHitDelay > 1.f)
			{
				if (attackRangeBox.getGlobalBounds().intersects(player.GetHitBox().getGlobalBounds()))
				{
					/*if (sprite.getPosition().x > player.GetSprite().getPosition().x)
					{
						monsterSide = true;
					}
					else
					{
						monsterSide = false;
					}
					player.OnHitted(atk, timeHit);*/
				}

				attackHitDelay = 0.f;
				isIdle = true;
				isAttackPlayer = false;
				isNearAttackPlayer = false;
				isFarAttackPlayer = false;
				isMiddleAttackPlayer = false;
			}
		}
	}
}

void LamiPhaseTwo::Update(Player& player, float dt, std::vector<TestBlock*> blocks, Time playTime)
{
	animation.Update(dt);
	Walk(dt, player);
	Attack(dt, 1, player, playTime);
	EyeUpdate(dt, player);
	leftHand.Update(dt, Vector2f(sprite.getGlobalBounds().left + 35 * 3, sprite.getGlobalBounds().top + 17 * 3));
	rightHand.Update(dt, Vector2f(sprite.getGlobalBounds().left + 89 * 3, sprite.getGlobalBounds().top + 17 * 3));
	AnimationUpdate();
}

void LamiPhaseTwo::Draw(RenderWindow* window)
{
	window->draw(leftSclera);
	window->draw(sprite);
	window->draw(leftEye);
	window->draw(leftHand.GetSprite());
	window->draw(rightHand.GetSprite());
	window->draw(attackRangeBox);
	window->draw(attackRangeLeftBox);
	window->draw(attackRangeRightBox);
}

void LamiPhaseTwo::EyeUpdate(float dt, Player& player)
{
	upY = sprite.getGlobalBounds().top + (52 * 3.f) - 3;
	downY = sprite.getGlobalBounds().top + (52 * 3.f) + 12;

	prevY = leftSclera.getGlobalBounds().top + (leftSclera.getGlobalBounds().height * 0.5f);
	if (leftSclera.getGlobalBounds().top + (leftSclera.getGlobalBounds().height * 0.5f) > 1000.f)
	{
		leftSclera.setPosition(sprite.getGlobalBounds().left + (49.0f * 3.f), sprite.getGlobalBounds().top + (52.f * 3.f));
	}
	else
	{
		leftSclera.setPosition(sprite.getGlobalBounds().left + (49.0f * 3.f), updateY);
	}
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
	std::cout << a << std::endl;



	leftSclera.getGlobalBounds().top; /*getGlobalBounds().top*/
	float h = player.GetPosition().x - leftEye.getPosition().x;
	float v = player.GetPosition().y - leftEye.getPosition().y;
	Vector2f dir(h, v);
	leftEye.setPosition(leftEye.getPosition() + Utils::Normalize(dir) * speed * dt*3.f);
	leftSclera.setPosition(leftSclera.getPosition().x, leftSclera.getPosition().y + a*0.4);

	if (leftSclera.getGlobalBounds().top + (leftSclera.getGlobalBounds().height * 0.5f) < upY || leftSclera.getGlobalBounds().top + (leftSclera.getGlobalBounds().height * 0.5f) > downY)
	{
		leftSclera.setPosition(leftSclera.getPosition().x, prevY);
		std::cout << a << "dd" << std::endl;
	}
	updateY = leftSclera.getGlobalBounds().top + (leftSclera.getGlobalBounds().height * 0.5f);

}

bool LamiPhaseTwo::OnHitted(int atk, float dt, Time timeHit)
{
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
