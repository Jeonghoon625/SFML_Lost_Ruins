#include "Player.h"
#include <iostream>

void Player::Init()
{
	speed = START_SPEED;
	health = START_HEALTH;
	maxHealth = START_HEALTH;
	immuneMs = START_IMMUNE_MS;
	vel = START_FALLING_SPEED;
	isFalling = false;

	texture = TextureHolder::GetTexture("graphics/heroin_sprite.png");

	sprite.setOrigin(15.5f, 50.f);
	sprite.setScale(scale);
	AnimationInit();
	animation.Play("Idle");
}

void Player::Spawn(IntRect gameMap, Vector2i res, int tileSize)
{
	this->gameMap = gameMap;
	resolustion = res;
	this->tileSize = tileSize;

	position.x = this->gameMap.width * 0.5f;
	position.y = 0;

	upHitBox.setFillColor(Color(153, 153, 153, 80));
	upHitBox.setSize(Vector2f(20.f, 48.f));
	upHitBox.setOrigin(idleUpHitBox);
	upHitBox.setScale(scale);
	upHitBox.setPosition(position);

	downHitBox.setFillColor(Color(153, 0, 0, 80));
	downHitBox.setSize(Vector2f(20.f, 5.f));
	downHitBox.setOrigin(idleDownHitBox);
	downHitBox.setScale(scale);
	downHitBox.setPosition(position);
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
	return position;
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

void Player::Update(float dt, std::vector <TestBlock*> blocks)
{
	float h = InputManager::GetAxisRaw(Axis::Horizontal);
	float v = InputManager::GetAxisRaw(Axis::Vertical);
	Vector2f dir(h, v);

	Utils::Normalize(dir);

	// 이동
	if (dir.x == 0 && lastDir != dir)
	{
		animation.Play("Idle");
		upHitBox.setOrigin(idleUpHitBox);
		downHitBox.setOrigin(idleDownHitBox);
	}
	if (dir.x > 0.f && lastDir != dir)
	{
		animation.Play("Run");
		sprite.setScale(scale);
		upHitBox.setOrigin(rightRunUpHitBox);
		downHitBox.setOrigin(rightRunDownHitBox);
	}
	if (dir.x < 0.f && lastDir != dir)
	{
		animation.Play("Run");
		sprite.setScale(scaleFlipX);
		upHitBox.setOrigin(leftRunUpHitBox);
		downHitBox.setOrigin(leftRunDownHitBox);
	}

	// 점프
	if (InputManager::GetKey(Keyboard::Space) && GetIsJump() == false)
	{
		SetIsJump(true);
	}

	if (GetIsJump() == true)
	{

		SetIsJump(false);
	}

	position.x += dir.x * speed * dt;
	if (isFalling == true)
	{
		vel += GRAVITY_POWER * dt;
		if (vel > 10000.f)
		{
			vel = 10000.f;
		}
		position.y += vel * dt;
	}
	lastDir = dir;

	sprite.setPosition(position);
	upHitBox.setPosition(position);
	downHitBox.setPosition(position);

	// 충돌 처리
	if (isFalling == true)
	{
		for (auto bk : blocks)
		{
			if (downHitBox.getGlobalBounds().intersects(bk->GetBlockRect()))
			{
				if (downHitBox.getGlobalBounds().top < bk->GetBlockRect().top)
				{
					isFalling = false;
					vel = START_FALLING_SPEED;
					position.y = bk->GetBlockRect().top + 1;
					upHitBox.setPosition(position);
					downHitBox.setPosition(position);
					break;
				}
				else
				{
				
				}
			}
		}
	}

	else if (isFalling == false)
	{
		for (auto bk : blocks)
		{

			if (downHitBox.getGlobalBounds().intersects(bk->GetBlockRect()))
			{
				isFalling = false;
				break;
			}
			isFalling = true;
		}
	}

	animation.Update(dt);
}

void Player::Draw(RenderWindow* window, View* mainView)
{
	window->setView(*mainView);
	window->draw(sprite);
	window->draw(upHitBox);
	window->draw(downHitBox);
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
