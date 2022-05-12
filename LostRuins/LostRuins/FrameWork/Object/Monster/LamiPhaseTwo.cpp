#include "LamiPhaseTwo.h"

LamiPhaseTwo::LamiPhaseTwo()
	:Monster()
{

}

void LamiPhaseTwo::MonsterInit()
{
	Idle.loadFromFile("graphics/BossSewerPhase2Idle.png");
	Idle2.loadFromFile("graphics/Lami_Phase2.png");
	strIdle = ("Lami2Idle");
	strDiving = "Lami2Diving";	
	strReappearing = "Lami2Reappearing";
	strReappearingToIdle = "Lami2Reappearing";

	sprite.setPosition(resolution.x * 0.3f, resolution.y * 1.2f);
	sprite.setOrigin((sprite.getTextureRect().width) * 0.5f, sprite.getTextureRect().height);
	
	sprite.setScale(scale);

	leftSclera.setTexture(TextureHolder::GetTexture("graphics/Lami_Phase2.png"));
	leftSclera.setTextureRect(IntRect(3,17,15,15));
	leftSclera.setScale(3.1f,3.1f);
	leftSclera.setOrigin(leftSclera.getTextureRect().width * 0.5f, leftSclera.getTextureRect().height * 0.5f);
	leftSclera.setPosition(sprite.getGlobalBounds().left + (49.0f*3.f), sprite.getGlobalBounds().top + (52.*3.f));
	
	

	leftEye.setTexture(TextureHolder::GetTexture("graphics/Lami_Phase2.png"));
	leftEye.setTextureRect(IntRect(26,20,8,9));
	leftEye.setScale(scale);
	leftEye.setOrigin(leftEye.getTextureRect().width * 0.5f, leftEye.getTextureRect().height * 0.5f);
	leftEye.setPosition(500, 500);

	Sprite leftSclera;
	Sprite rightSclera;

	Sprite leftEye;
	Sprite RightEye;

	SetHealth(20);
	SetAtk(3);
	SetSpeed(50.f);


	position = sprite.getPosition();
	AnimationInit(&sprite);

	findPlayerBox.setSize(Vector2f(200.f, 40.f));
	findPlayerBox.setScale(scale);
	findPlayerBox.setFillColor(Color(255, 255, 255, 80));
	findPlayerBox.setOrigin(200, 40);
	findPlayerBox.setPosition(sprite.getOrigin());

	attackRangeBox.setSize(Vector2f(90.f, 150.f));
	attackRangeBox.setScale(scale);
	attackRangeBox.setFillColor(Color(153, 0, 0, 80));
	attackRangeBox.setOrigin(attackRangeBox.getSize().x*0.5, attackRangeBox.getSize().y);
	attackRangeBox.setPosition(sprite.getOrigin());

	attackRangeLeftBox.setSize(Vector2f(90.f, 150.f));
	attackRangeLeftBox.setScale(scale);
	attackRangeLeftBox.setFillColor(Color(153, 0, 0, 80));
	attackRangeLeftBox.setOrigin(attackRangeBox.getSize().x * 0.5, attackRangeBox.getSize().y);
	attackRangeLeftBox.setPosition(sprite.getOrigin().x - 180.f, sprite.getOrigin().y);

	attackRangeRightBox.setSize(Vector2f(90.f,150.f));
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
	
	a = 1;
}

void LamiPhaseTwo::Walk(float dt, Player& player)
{
	sprite.setOrigin((sprite.getTextureRect().width) * 0.5f, sprite.getTextureRect().height);

	float h = player.GetPosition().x - sprite.getPosition().x;
	float v = 0.f;
	Vector2f dir(h, v);
	position += Utils::Normalize(dir) * speed * dt;

	sprite.setPosition(position);
	findPlayerBox.setPosition(position);
	attackRangeBox.setPosition(position);
	attackRangeLeftBox.setPosition(position);
	attackRangeRightBox.setPosition(position);
	hitBox.setPosition(position);
}

void LamiPhaseTwo::Attack(float dt, int atk, Player& player, Time timeHit)
{
	if (isAlive)
	{
		if (attackRangeBox.getGlobalBounds().intersects(player.GetHitBox().getGlobalBounds()) && attackDelay > 0.5f)
		{
			attackDelay = 0.f;
			isFindPlayer = false;
			isAttackPlayer = true;
		}
		else if (attackRangeLeftBox.getGlobalBounds().intersects(player.GetHitBox().getGlobalBounds()) && attackDelay > 0.5f)
		{
			attackDelay = 0.f;
			isFindPlayer = false;
			isAttackPlayer = true;
		}
		else if (attackRangeRightBox.getGlobalBounds().intersects(player.GetHitBox().getGlobalBounds()) && attackDelay > 0.5f)
		{
			attackDelay = 0.f;
			isFindPlayer = false;
			isAttackPlayer = true;
		}


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
}

void LamiPhaseTwo::Update(Player& player, float dt, std::vector<TestBlock*> blocks, Time playtime)
{
	animation.Update(dt);
	Walk(dt, player);
	EyeUpdate(dt, player);
}

void LamiPhaseTwo::Draw(RenderWindow* window)
{
	
	window->draw(leftSclera);
	window->draw(sprite);
	window->draw(leftEye);
	
}

void LamiPhaseTwo::EyeUpdate(float dt, Player& player)
{
	upY = sprite.getGlobalBounds().top + (52. * 3.f) - 6;
	downY = sprite.getGlobalBounds().top + (52. * 3.f) + 12;
	prevY = leftSclera.getGlobalBounds().top + (leftSclera.getGlobalBounds().height * 0.5f);
	leftSclera.setPosition(sprite.getGlobalBounds().left + (49.0f * 3.f), sprite.getGlobalBounds().top + (52.f * 3.f));
	
	std::cout << prevY << std::endl;
	if((Idle2.getPixel(sprite.getTextureRect().left+49, sprite.getTextureRect().top+50) == Idle.getPixel(48, 46)) && a == 1)
	{
		a *= -1;
	}
	else if((Idle2.getPixel(sprite.getTextureRect().left + 49, sprite.getTextureRect().top + 43) == Idle.getPixel(48, 46)) && a ==-1)
	{
		a *= -1;
	}
	std::cout << a << std::endl;
	leftSclera.setPosition(leftSclera.getPosition().x, leftSclera.getPosition().y + a*1.7f);
	
	if (leftSclera.getGlobalBounds().top + (leftSclera.getGlobalBounds().height * 0.5f) < upY || leftSclera.getGlobalBounds().top + (leftSclera.getGlobalBounds().height * 0.5f) > downY)
	{
		leftSclera.setPosition(leftSclera.getPosition().x, prevY);
		std::cout << a << "dd" << std::endl;
	}
	

	leftSclera.getGlobalBounds().top; /*getGlobalBounds().top*/
	float h = player.GetPosition().x - leftEye.getPosition().x;
	float v = player.GetPosition().y - leftEye.getPosition().y;
	Vector2f dir(h, v);
	leftEye.setPosition(leftEye.getPosition() + Utils::Normalize(dir) * speed * dt);


}

bool LamiPhaseTwo::OnHitted(int atk, float dt, Time timeHit)
{
	return false;
}
