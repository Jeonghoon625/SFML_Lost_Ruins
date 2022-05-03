#include "Player.h"

void Player::Init()
{
	speed = START_SPEED;
	health = START_HEALTH;
	maxHealth = START_HEALTH;
	immuneMs = START_IMMUNE_MS;

	texture = TextureHolder::GetTexture("graphics/heroin_sprite.png");

	Utils::SetOrigin(sprite, Pivots::CC);

	sprite.setOrigin(15.5f, 50.f);
	sprite.setScale(3.f, 3.f);
	AnimationInit();
	animation.Play("Idle");
}

void Player::Spawn(IntRect gameMap, Vector2i res, int tileSize)
{
	this->gameMap = gameMap;
	resolustion = res;
	this->tileSize = tileSize;

	postion.x = this->gameMap.width * 0.5f;
	postion.y = this->gameMap.height * 0.5f;
}

bool Player::OnHitted(Time timeHit)
{
	return false;
}

Time Player::GetLastTime() const
{
	return lastHit;
}

FloatRect Player::GetGobalBound() const
{
	return sprite.getGlobalBounds();
}

Vector2f Player::GetPosition() const
{
	return postion;
}

Sprite Player::GetSprite() const
{
	return sprite;
}

int Player::GetHealth() const
{
	return health;
}

void Player::Update(float dt)
{
	float h = InputManager::GetAxis(Axis::Horizontal);
	float v = InputManager::GetAxis(Axis::Vertical);
	Vector2f dir(h, v);

	float length = sqrt(dir.x * dir.x + dir.y * dir.y);
	if (length > 1)
	{
		dir /= length;
	}

	/*if(InputManager::GetKey(Keyboard::Right))
	{
		dir = Vector2f(1.f, 0.f);
	}
	else
	{
		dir = Vector2f(0.f, 0.f);
	}*/

	if (InputManager::GetKeyDown(Keyboard::Right))
	{
		sprite.setScale(3.f, 3.f);
		animation.Play("Run");

	}
	else if (InputManager::GetKeyUp(Keyboard::Right))
	{
		sprite.setScale(3.f, 3.f);
		animation.Play("Idle");
	}

	if (InputManager::GetKeyDown(Keyboard::Left))
	{
		sprite.setScale(-3.f, 3.f);
		animation.Play("Run");

	}
	else if (InputManager::GetKeyUp(Keyboard::Left))
	{
		sprite.setScale(-3.f, 3.f);
		animation.Play("Idle");
	}

	postion += dir * speed * dt;
	postion.y = resolustion.y * 0.5f;

	sprite.setPosition(postion);
	animation.Update(dt);
}

void Player::Draw(RenderWindow* window, View* mainView)
{
	window->draw(sprite);
}

void Player::AnimationInit()
{
	animation.SetTarget(&sprite);

	rapidcsv::Document clips("data_tables/animations/player/player_animation_clips2.csv");
	std::vector<std::string> colId = clips.GetColumn<std::string>("ID");
	std::vector<int> colFps = clips.GetColumn<int>("FPS");
	std::vector<int> colLoop = clips.GetColumn<int>("LOOP TYPE(0:Single, 1:Loop)");
	std::vector<std::string> colPath = clips.GetColumn<std::string>("CLIP PATH");

	int totalClips = colId.size();
	for (int i = 0; i < totalClips; ++i)
	{
		AnimationClip clip;
		clip.id = colId[i];
		clip.fps = colFps[i];
		clip.loopType = (AnimationLoopType)colLoop[i];

		rapidcsv::Document frames(colPath[i]);
		std::vector<std::string> colTexture = frames.GetColumn<std::string>("TEXTURE PATH");
		std::vector<int> colL = frames.GetColumn<int>("L");
		std::vector<int> colT = frames.GetColumn<int>("T");
		std::vector<int> colW = frames.GetColumn<int>("W");
		std::vector<int> colH = frames.GetColumn<int>("H");

		int totalFrames = colTexture.size();
		for (int j = 0; j < totalFrames; ++j)
		{
			if (texmap.find(colTexture[j]) == texmap.end())
			{
				auto& ref = texmap[colTexture[j]];
				ref.loadFromFile(colTexture[j]);
			}

			clip.frames.push_back(AnimationFrame(texmap[colTexture[j]],
				IntRect(colL[j], colT[j], colW[j], colH[j])));
		}
		animation.AddClip(clip);
	}
}
