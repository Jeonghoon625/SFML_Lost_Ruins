#include "Player.h"

void Player::Init()
{
	speed = START_SPEED;
	health = START_HEALTH;
	maxHealth = START_HEALTH;
	immuneMs = START_IMMUNE_MS;
	vel = 0.f;

	texture = TextureHolder::GetTexture("graphics/heroin_sprite.png");

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
	postion.y = 0;
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

void Player::SetIsJump(bool isJump)
{
	this->isJump = isJump;
}

bool Player::GetIsJump()
{
	return isJump;
}

void Player::Update(float dt)
{
	float h = InputManager::GetAxisRaw(Axis::Horizontal);
	float v = InputManager::GetAxisRaw(Axis::Vertical);
	Vector2f dir(h, v);

	Utils::Normalize(dir);

	// �̵�
	if (dir.x == 0 && lastDir != dir)
	{
		animation.Play("Idle");
	}
	if (dir.x > 0.f && lastDir != dir)
	{
		animation.Play("Run");
		sprite.setScale(scale);
	}
	if (dir.x < 0.f && lastDir != dir)
	{
		animation.Play("Run");
		sprite.setScale(scaleFlipX);
	}

	// ����
	if (InputManager::GetKey(Keyboard::Space) && GetIsJump() == false)
	{
		SetIsJump(true);
	}

	if (GetIsJump() == true)
	{

		SetIsJump(false);
	}

	postion.x += dir.x * speed * dt;

	vel += GRAVITY_POWER * dt;
	postion.y += vel * dt;

	lastDir = dir;

	sprite.setPosition(postion);
	animation.Update(dt);
}

void Player::Draw(RenderWindow* window, View* mainView)
{
	window->setView(*mainView);
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
