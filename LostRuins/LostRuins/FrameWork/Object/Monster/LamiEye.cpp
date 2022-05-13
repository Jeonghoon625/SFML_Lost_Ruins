#include "LamiEye.h"

LamiEye::LamiEye()
{
}

void LamiEye::Init(Vector2f pos, int eyeSide, Sprite& sprite)
{
	this->eyeSide = eyeSide;
	Idle.loadFromFile("graphics/BossSewerPhase2Idle.png");
	Idle2.loadFromFile("graphics/Lami_Phase2.png");

	spriteEye.setTexture(TextureHolder::GetTexture("graphics/Eye.png"));
	spriteEye.setOrigin(spriteEye.getTextureRect().width * 0.5f, spriteEye.getTextureRect().height * 0.5f);

	spriteSclera.setTexture(TextureHolder::GetTexture("graphics/Sclera.png"));
	spriteSclera.setOrigin(spriteSclera.getTextureRect().width * 0.5f, spriteSclera.getTextureRect().height * 0.5f);


	if (eyeSide == 0)
	{
		spriteEye.setPosition(sprite.getGlobalBounds().left + (49.f), sprite.getGlobalBounds().top + (52.f));
		spriteSclera.setPosition(sprite.getGlobalBounds().left + (49.0f), sprite.getGlobalBounds().top + (52.f));
	}
	else
	{
		spriteEye.setPosition(sprite.getGlobalBounds().left + (74.f), sprite.getGlobalBounds().top + (52.f));
		spriteSclera.setPosition(sprite.getGlobalBounds().left + (74.f), sprite.getGlobalBounds().top + (52.f));
	}
	
	
	eyeSpeed = 50.f;
}

void LamiEye::Update(Sprite& sprite, Player& player, float dt)
{
	upY = sprite.getGlobalBounds().top + (52.f);
	downY = sprite.getGlobalBounds().top + (52.f) + 4;

	prevY = spriteSclera.getGlobalBounds().top + (spriteSclera.getGlobalBounds().height * 0.5f);

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

	spriteSclera.setPosition(sprite.getGlobalBounds().left + (49.0f), spriteSclera.getPosition().y + a * 0.4f);
	if (spriteSclera.getGlobalBounds().top + (spriteSclera.getGlobalBounds().height * 0.5f) < upY || spriteSclera.getGlobalBounds().top + (spriteSclera.getGlobalBounds().height * 0.5f) > downY)
	{
		spriteSclera.setPosition(spriteSclera.getPosition().x, prevY);
		std::cout << a << "dd" << std::endl;
	}

	prevLeftEyePos = Vector2f(spriteEye.getPosition().x, spriteEye.getPosition().y);

	float h = spriteSclera.getGlobalBounds().left + spriteSclera.getGlobalBounds().width;
	float v = spriteSclera.getGlobalBounds().top + (spriteSclera.getGlobalBounds().height * 0.5f);
	Vector2f dirRC(h, v);
	h = spriteSclera.getGlobalBounds().left + spriteSclera.getGlobalBounds().width;
	v = spriteSclera.getGlobalBounds().top + spriteSclera.getGlobalBounds().height * 0.9f;
	Vector2f dirRB(h, v);
	h = spriteSclera.getGlobalBounds().left + spriteSclera.getGlobalBounds().width * 0.5f;
	v = spriteSclera.getGlobalBounds().top + spriteSclera.getGlobalBounds().height * 0.9f;
	Vector2f dirCB(h, v);
	h = spriteSclera.getGlobalBounds().left + spriteSclera.getGlobalBounds().width * 0.1f;
	v = spriteSclera.getGlobalBounds().top + spriteSclera.getGlobalBounds().height * 0.9f;
	Vector2f dirLB(h, v);
	h = spriteSclera.getGlobalBounds().left + spriteSclera.getGlobalBounds().width * 0.1f;
	v = spriteSclera.getGlobalBounds().top + spriteSclera.getGlobalBounds().height * 0.5f;
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



	spriteEye.setPosition(spriteEye.getPosition() + Utils::Normalize(dir) * eyeSpeed * 2.f * dt);

	/*updateY = leftSclera.getGlobalBounds().top + (leftSclera.getGlobalBounds().height * 0.5f);*/
}


void LamiEye::Draw(RenderWindow* window)
{
	window->draw(spriteSclera);
	window->draw(spriteEye);
}
