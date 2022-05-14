#include "LamiEye.h"
#include "../../Mgr/TextureHolder.h"


LamiEye::LamiEye()
{
}

void LamiEye::Init(int eyeSide, Sprite& sprite)
{
	currentStatus = Lami2Status::STATUS_IDLE;
	this->eyeSide = eyeSide;
	Idle.loadFromFile("graphics/BossSewerPhase2Idle.png");
	Idle2.loadFromFile("graphics/Lami_Phase2.png");

	spriteEye.setTexture(TextureHolder::GetTexture("graphics/Eye.png"));
	spriteEye.setOrigin(spriteEye.getTextureRect().width * 0.5f, spriteEye.getTextureRect().height * 0.5f);

	spriteSclera.setTexture(TextureHolder::GetTexture("graphics/Sclera.png"));
	spriteSclera.setOrigin(spriteSclera.getTextureRect().width * 0.5f, spriteSclera.getTextureRect().height * 0.5f);


	if (eyeSide == 0)		//left eye
	{
		spriteEye.setPosition(sprite.getGlobalBounds().left + (49.f), sprite.getGlobalBounds().top + (52.f));
		spriteSclera.setPosition(sprite.getGlobalBounds().left + (49.0f), sprite.getGlobalBounds().top + (52.f));
	}
	else              //right eye
	{
		spriteEye.setPosition(sprite.getGlobalBounds().left + (74.f), sprite.getGlobalBounds().top + (52.f));
		spriteSclera.setPosition(sprite.getGlobalBounds().left + (74.f), sprite.getGlobalBounds().top + (52.f));
	}

	a = 1.f;
	eyeSpeed = 50.f;
	updateY = spriteSclera.getGlobalBounds().top + (spriteSclera.getGlobalBounds().height * 0.5f);
}

void LamiEye::Update(Sprite& sprite, Player& player, float dt, RectangleShape& hitBox)
{
	float lengthRC;
	float lengthRB;
	float lengthCB;
	float lengthLB;
	float lengthLC;
	float h;
	float v;


	float length;
	Vector2f dir;

	Vector2f dirRC;

	Vector2f dirRB;

	Vector2f dirCB;
	
	Vector2f dirLB;
	
	Vector2f dirLC;
	if (eyeSide == 0)
	{
		switch (currentStatus)
		{
		case Lami2Status::STATUS_IDLE:
		
			upY = sprite.getGlobalBounds().top + (53.f) - 2.f;
			downY = sprite.getGlobalBounds().top + (53.f) + 3.f;

			prevY = spriteSclera.getGlobalBounds().top + (spriteSclera.getGlobalBounds().height * 0.5f);

			/*spriteSclera.setPosition(sprite.getGlobalBounds().left + 49.f, updateY);*/


			if ((Idle2.getPixel(sprite.getTextureRect().left + 49, sprite.getTextureRect().top + 50) == Idle.getPixel(48, 46)) && a == 1)
			{
				a *= -1;
			}
			else if ((Idle2.getPixel(sprite.getTextureRect().left + 49, sprite.getTextureRect().top + 43) == Idle.getPixel(48, 46)) && a == -1)
			{
				a *= -1;
			}

			spriteSclera.setPosition(sprite.getGlobalBounds().left + (49.0f), spriteSclera.getPosition().y + a * 0.15f);

			if (spriteSclera.getGlobalBounds().top + (spriteSclera.getGlobalBounds().height * 0.5f) < upY || spriteSclera.getGlobalBounds().top + (spriteSclera.getGlobalBounds().height * 0.5f) > downY)
			{
				if (a == 1)
				{
					spriteSclera.setPosition(spriteSclera.getPosition().x, downY);
				}
				else if (a == -1)
				{
					spriteSclera.setPosition(spriteSclera.getPosition().x, upY);
				}

				std::cout << a << "dd" << std::endl;
			}

			prevLeftEyePos = Vector2f(spriteEye.getPosition().x, spriteEye.getPosition().y);

			h = spriteSclera.getGlobalBounds().left + spriteSclera.getGlobalBounds().width;
			v = spriteSclera.getGlobalBounds().top + (spriteSclera.getGlobalBounds().height * 0.5f);
			 dirRC = Vector2f(h, v);
			h = spriteSclera.getGlobalBounds().left + spriteSclera.getGlobalBounds().width;
			v = spriteSclera.getGlobalBounds().top + spriteSclera.getGlobalBounds().height * 0.9f;
			 dirRB = Vector2f(h, v);
			h = spriteSclera.getGlobalBounds().left + spriteSclera.getGlobalBounds().width * 0.6f;
			v = spriteSclera.getGlobalBounds().top + spriteSclera.getGlobalBounds().height;
			 dirCB = Vector2f(h, v);
			h = spriteSclera.getGlobalBounds().left + spriteSclera.getGlobalBounds().width * 0.1f;
			v = spriteSclera.getGlobalBounds().top + spriteSclera.getGlobalBounds().height * 0.9f;
			 dirLB = Vector2f(h, v);
			h = spriteSclera.getGlobalBounds().left + spriteSclera.getGlobalBounds().width * 0.1f;
			v = spriteSclera.getGlobalBounds().top + spriteSclera.getGlobalBounds().height * 0.5f;
			dirLC = Vector2f(h, v);

			lengthRC = Utils::GetLength(dirRC - Vector2f(player.GetHitBox().getGlobalBounds().left + player.GetHitBox().getGlobalBounds().width * 0.5f, player.GetHitBox().getGlobalBounds().top + player.GetHitBox().getGlobalBounds().height * 0.5f));
			lengthRB = Utils::GetLength(dirRB - Vector2f(player.GetHitBox().getGlobalBounds().left + player.GetHitBox().getGlobalBounds().width * 0.5f, player.GetHitBox().getGlobalBounds().top + player.GetHitBox().getGlobalBounds().height * 0.5f));
			lengthCB = Utils::GetLength(dirCB - Vector2f(player.GetHitBox().getGlobalBounds().left + player.GetHitBox().getGlobalBounds().width * 0.5f, player.GetHitBox().getGlobalBounds().top + player.GetHitBox().getGlobalBounds().height * 0.5f));
			lengthLB = Utils::GetLength(dirLB - Vector2f(player.GetHitBox().getGlobalBounds().left + player.GetHitBox().getGlobalBounds().width * 0.5f, player.GetHitBox().getGlobalBounds().top + player.GetHitBox().getGlobalBounds().height * 0.5f));
			lengthLC = Utils::GetLength(dirLC - Vector2f(player.GetHitBox().getGlobalBounds().left + player.GetHitBox().getGlobalBounds().width * 0.5f, player.GetHitBox().getGlobalBounds().top + player.GetHitBox().getGlobalBounds().height * 0.5f));

			length;
			dir;

			if (lengthRC > lengthRB)
			{
				dir = dirRB - Vector2f(spriteEye.getGlobalBounds().left + spriteEye.getGlobalBounds().width, spriteEye.getGlobalBounds().top + spriteEye.getGlobalBounds().height);
				length = lengthRB;
			}
			else
			{
				dir = dirRC - Vector2f(spriteEye.getGlobalBounds().left + spriteEye.getGlobalBounds().width, spriteEye.getGlobalBounds().top + spriteEye.getGlobalBounds().height * 0.5f);
				length = lengthRC;
			}

			if (length > lengthCB)
			{
				dir = dirCB - Vector2f(spriteEye.getGlobalBounds().left + spriteEye.getGlobalBounds().width * 0.5f, spriteEye.getGlobalBounds().top + spriteEye.getGlobalBounds().height);
				length = lengthCB;
			}

			if (length > lengthLB)
			{
				dir = dirLB - Vector2f(spriteEye.getGlobalBounds().left, spriteEye.getGlobalBounds().top + spriteEye.getGlobalBounds().height);
				length = lengthLB;
			}

			if (length > lengthLC)
			{
				dir = dirLC - Vector2f(spriteEye.getGlobalBounds().left, spriteEye.getGlobalBounds().top + spriteEye.getGlobalBounds().height * 0.5f);
				length = lengthLC;
			}

			if (hitBox.getGlobalBounds().intersects(player.GetHitBox().getGlobalBounds()))
			{
				dir = dirCB - Vector2f(spriteEye.getGlobalBounds().left + spriteEye.getGlobalBounds().width * 0.5f, spriteEye.getGlobalBounds().top + spriteEye.getGlobalBounds().height);
			}

			if (Utils::GetLength(dir) < eyeSpeed * dt * 0.5f)
			{
			}
			else
			{
				spriteEye.setPosition(spriteEye.getPosition() + Utils::Normalize(dir) * eyeSpeed * 1.1f * dt);
			}
			break;
		
	

		case Lami2Status::STATUS_DIVING:
			spriteEye.setPosition(sprite.getGlobalBounds().left + (37.5f), sprite.getGlobalBounds().top + (67.f));
			spriteSclera.setPosition(sprite.getGlobalBounds().left + (37.5f), sprite.getGlobalBounds().top + (62.f));
			break;

		case Lami2Status::STATUS_REAPPEARING:
			spriteEye.setPosition(sprite.getGlobalBounds().left + (45.f), sprite.getGlobalBounds().top + (58.f));
			spriteSclera.setPosition(sprite.getGlobalBounds().left + (45.0f), sprite.getGlobalBounds().top + (56.f));
			break;
		case Lami2Status::STATUS_REAPPEARINGTOIDLE:
			spriteEye.setPosition(sprite.getGlobalBounds().left + (45.f), sprite.getGlobalBounds().top + (58.f));
			spriteSclera.setPosition(sprite.getGlobalBounds().left + (45.0f), sprite.getGlobalBounds().top + (55.f));
			break;
		default:

			break;
		}

	}

	else
	{
		switch (currentStatus)
		{
		case Lami2Status::STATUS_IDLE:
		{
			upY = sprite.getGlobalBounds().top + (53.f) - 2.f;
			downY = sprite.getGlobalBounds().top + (53.f) + 3.f;

			prevY = spriteSclera.getGlobalBounds().top + (spriteSclera.getGlobalBounds().height * 0.5f);

			/*spriteSclera.setPosition(sprite.getGlobalBounds().left + 49.f, updateY);*/


			if ((Idle2.getPixel(sprite.getTextureRect().left + 49, sprite.getTextureRect().top + 50) == Idle.getPixel(48, 46)) && a == 1)
			{
				a *= -1;
			}
			else if ((Idle2.getPixel(sprite.getTextureRect().left + 49, sprite.getTextureRect().top + 43) == Idle.getPixel(48, 46)) && a == -1)
			{
				a *= -1;
			}

			spriteSclera.setPosition(sprite.getGlobalBounds().left + (75.5f), spriteSclera.getPosition().y + a * 0.15f);

			if (spriteSclera.getGlobalBounds().top + (spriteSclera.getGlobalBounds().height * 0.5f) < upY || spriteSclera.getGlobalBounds().top + (spriteSclera.getGlobalBounds().height * 0.5f) > downY)
			{
				if (a == 1)
				{
					spriteSclera.setPosition(spriteSclera.getPosition().x, downY);
				}
				else if (a == -1)
				{
					spriteSclera.setPosition(spriteSclera.getPosition().x, upY);
				}

				std::cout << a << "dd" << std::endl;
			}

			prevLeftEyePos = Vector2f(spriteEye.getPosition().x, spriteEye.getPosition().y);

			h = spriteSclera.getGlobalBounds().left + spriteSclera.getGlobalBounds().width * 0.9f;
			v = spriteSclera.getGlobalBounds().top + (spriteSclera.getGlobalBounds().height * 0.5f);
			dirRC = Vector2f(h, v);
			h = spriteSclera.getGlobalBounds().left + spriteSclera.getGlobalBounds().width * 0.9f;
			v = spriteSclera.getGlobalBounds().top + spriteSclera.getGlobalBounds().height * 0.9f;
			 dirRB = Vector2f(h, v);
			h = spriteSclera.getGlobalBounds().left + spriteSclera.getGlobalBounds().width * 0.4f;
			v = spriteSclera.getGlobalBounds().top + spriteSclera.getGlobalBounds().height;
			 dirCB = Vector2f(h, v);
			h = spriteSclera.getGlobalBounds().left + spriteSclera.getGlobalBounds().width * 0.f;
			v = spriteSclera.getGlobalBounds().top + spriteSclera.getGlobalBounds().height * 0.9f;
			 dirLB = Vector2f(h, v);
			h = spriteSclera.getGlobalBounds().left + spriteSclera.getGlobalBounds().width * 0.f;
			v = spriteSclera.getGlobalBounds().top + spriteSclera.getGlobalBounds().height * 0.5f;
		dirLC = Vector2f(h, v);

			lengthRC = Utils::GetLength(dirRC - Vector2f(player.GetHitBox().getGlobalBounds().left + player.GetHitBox().getGlobalBounds().width * 0.5f, player.GetHitBox().getGlobalBounds().top + player.GetHitBox().getGlobalBounds().height * 0.5f));
			lengthRB = Utils::GetLength(dirRB - Vector2f(player.GetHitBox().getGlobalBounds().left + player.GetHitBox().getGlobalBounds().width * 0.5f, player.GetHitBox().getGlobalBounds().top + player.GetHitBox().getGlobalBounds().height * 0.5f));
			 lengthCB = Utils::GetLength(dirCB - Vector2f(player.GetHitBox().getGlobalBounds().left + player.GetHitBox().getGlobalBounds().width * 0.5f, player.GetHitBox().getGlobalBounds().top + player.GetHitBox().getGlobalBounds().height * 0.5f));
			 lengthLB = Utils::GetLength(dirLB - Vector2f(player.GetHitBox().getGlobalBounds().left + player.GetHitBox().getGlobalBounds().width * 0.5f, player.GetHitBox().getGlobalBounds().top + player.GetHitBox().getGlobalBounds().height * 0.5f));
			lengthLC = Utils::GetLength(dirLC - Vector2f(player.GetHitBox().getGlobalBounds().left + player.GetHitBox().getGlobalBounds().width * 0.5f, player.GetHitBox().getGlobalBounds().top + player.GetHitBox().getGlobalBounds().height * 0.5f));

			 length;
			 dir;

			if (lengthRC > lengthRB)
			{
				dir = dirRB - Vector2f(spriteEye.getGlobalBounds().left + spriteEye.getGlobalBounds().width, spriteEye.getGlobalBounds().top + spriteEye.getGlobalBounds().height);
				length = lengthRB;
			}
			else
			{
				dir = dirRC - Vector2f(spriteEye.getGlobalBounds().left + spriteEye.getGlobalBounds().width, spriteEye.getGlobalBounds().top + spriteEye.getGlobalBounds().height * 0.5f);
				length = lengthRC;
			}

			if (length > lengthCB)
			{
				dir = dirCB - Vector2f(spriteEye.getGlobalBounds().left + spriteEye.getGlobalBounds().width * 0.5f, spriteEye.getGlobalBounds().top + spriteEye.getGlobalBounds().height);
				length = lengthCB;
			}

			if (length > lengthLB)
			{
				dir = dirLB - Vector2f(spriteEye.getGlobalBounds().left, spriteEye.getGlobalBounds().top + spriteEye.getGlobalBounds().height);
				length = lengthLB;
			}

			if (length > lengthLC)
			{
				dir = dirLC - Vector2f(spriteEye.getGlobalBounds().left, spriteEye.getGlobalBounds().top + spriteEye.getGlobalBounds().height * 0.5f);
				length = lengthLC;
			}

			if (hitBox.getGlobalBounds().intersects(player.GetHitBox().getGlobalBounds()))
			{
				dir = dirCB - Vector2f(spriteEye.getGlobalBounds().left + spriteEye.getGlobalBounds().width * 0.5f, spriteEye.getGlobalBounds().top + spriteEye.getGlobalBounds().height);
			}

			if (Utils::GetLength(dir) < eyeSpeed * dt * 0.5f)
			{
			}
			else
			{
				spriteEye.setPosition(spriteEye.getPosition() + Utils::Normalize(dir) * eyeSpeed * 1.1f * dt);
			}
		}
		break;

		case Lami2Status::STATUS_DIVING:
			spriteEye.setPosition(sprite.getGlobalBounds().left + (62.5f), sprite.getGlobalBounds().top + (67.f));
			spriteSclera.setPosition(sprite.getGlobalBounds().left + (62.5f), sprite.getGlobalBounds().top + (62.f));
			break;

		case Lami2Status::STATUS_REAPPEARING:
			spriteEye.setPosition(sprite.getGlobalBounds().left + (70.f), sprite.getGlobalBounds().top + (58.f));
			spriteSclera.setPosition(sprite.getGlobalBounds().left + (70.f), sprite.getGlobalBounds().top + (56.f));
			break;
		case Lami2Status::STATUS_REAPPEARINGTOIDLE:
			spriteEye.setPosition(sprite.getGlobalBounds().left + (70.f), sprite.getGlobalBounds().top + (58.f));
			spriteSclera.setPosition(sprite.getGlobalBounds().left + (70.0f), sprite.getGlobalBounds().top + (55.f));
			break;
		default:
			break;
		}

	}
	/*updateY = spriteSclera.getGlobalBounds().top + (spriteSclera.getGlobalBounds().height * 0.5f);*/
}


void LamiEye::Draw(RenderWindow* window)
{
	window->draw(spriteSclera);
	window->draw(spriteEye);
}


void LamiEye::SetStatus(Lami2Status newStatus, Sprite& sprite)
{
	switch (newStatus)
	{
	case Lami2Status::STATUS_IDLE:
		currentStatus = Lami2Status::STATUS_IDLE;
		if (eyeSide == 0)		//left eye
		{

			spriteEye.setPosition(sprite.getGlobalBounds().left + (49.f), sprite.getGlobalBounds().top + (52.f));
			spriteSclera.setPosition(sprite.getGlobalBounds().left + (49.0f), sprite.getGlobalBounds().top + (52.f));
		}
		else              //right eye
		{
			spriteEye.setPosition(sprite.getGlobalBounds().left + (74.f), sprite.getGlobalBounds().top + (52.f));
			spriteSclera.setPosition(sprite.getGlobalBounds().left + (74.f), sprite.getGlobalBounds().top + (52.f));
		}
		break;
	case Lami2Status::STATUS_DIVING:
		currentStatus = Lami2Status::STATUS_DIVING;
		if (eyeSide == 0)		//left eye
		{
			spriteEye.setPosition(sprite.getGlobalBounds().left + (37.5f), sprite.getGlobalBounds().top + (67.f));
			spriteSclera.setPosition(sprite.getGlobalBounds().left + (37.5f), sprite.getGlobalBounds().top + (67.f));
		}
		else              //right eye
		{
			spriteEye.setPosition(sprite.getGlobalBounds().left + (62.5f), sprite.getGlobalBounds().top + (67.f));
			spriteSclera.setPosition(sprite.getGlobalBounds().left + (62.5f), sprite.getGlobalBounds().top + (67.f));
		}
		break;
	case Lami2Status::STATUS_REAPPEARING:
		currentStatus = Lami2Status::STATUS_REAPPEARING;
		if (eyeSide == 0)		//left eye
		{
			spriteEye.setPosition(sprite.getGlobalBounds().left + (45.f), sprite.getGlobalBounds().top + (54.f));
			spriteSclera.setPosition(sprite.getGlobalBounds().left + (45.0f), sprite.getGlobalBounds().top + (54.f));
		}
		else              //right eye
		{
			spriteEye.setPosition(sprite.getGlobalBounds().left + (70.f), sprite.getGlobalBounds().top + (54.f));
			spriteSclera.setPosition(sprite.getGlobalBounds().left + (70.f), sprite.getGlobalBounds().top + (54.f));
		}
		break;
	case Lami2Status::STATUS_REAPPEARINGTOIDLE:
		currentStatus = Lami2Status::STATUS_REAPPEARINGTOIDLE;
		break;
	default:
		break;
	}
}

