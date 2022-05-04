#include "Player.h"
#include <iostream>

void Player::Init()
{
	speed = START_SPEED;
	health = START_HEALTH;
	maxHealth = START_HEALTH;
	immuneMs = START_IMMUNE_MS;
	fallingSpeed = 0.f;
	isFalling = false;
	skipDt = true;

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
	position.y = 200.f;

	hitBox.setFillColor(Color(153, 153, 153, 80));
	hitBox.setSize(Vector2f(20.f, 48.f));
	hitBox.setOrigin(idleUpHitBox);
	hitBox.setScale(scale);
	hitBox.setPosition(position);
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
		hitBox.setOrigin(idleUpHitBox);
	}
	if (dir.x > 0.f && lastDir != dir)
	{
		animation.Play("Run");
		sprite.setScale(scale);
		hitBox.setOrigin(rightRunUpHitBox);
	}
	if (dir.x < 0.f && lastDir != dir)
	{
		animation.Play("Run");
		sprite.setScale(scaleFlipX);
		hitBox.setOrigin(leftRunUpHitBox);
	}

	// 점프
	if (InputManager::GetKeyDown(Keyboard::Space) && isJump == false && isFalling == false)
	{
		std::cout << "Jump" << std::endl;
		isJump = true;
	}

	if (isJump == true)
	{
		isFalling == true;
	}

	if (skipDt == true)
	{
		dt = 0.f;
		skipDt = false;
	}

	// 이동
	position.x += dir.x * speed * dt;
	if (isFalling == true)
	{
		fallingSpeed += GRAVITY_POWER * dt;
		if (fallingSpeed > 10000.f)
		{
			fallingSpeed = 10000.f;
		}
		if (isJump == true)
		{
			fallingSpeed * -1.f;
		}
		position.y += fallingSpeed * dt;
	}
	lastDir = dir;

	sprite.setPosition(position);
	hitBox.setPosition(position);

	// 충돌 처리
	for (auto bk : blocks)
	{
		Vector2f pos = hitBox.getPosition();
		if (hitBox.getGlobalBounds().intersects(bk->GetBlockRect()))
		{
			if (bk->GetBlockRect().top > hitBox.getPosition().y - hitBox.getGlobalBounds().height * 0.5f &&
				hitBox.getPosition().y < bk->GetBlockRect().top + 5.f)
			{
				pos.y = bk->GetBlockRect().top;
				fallingSpeed = 0.f;
				if (isJump == false)
				{
					isFalling = false;
				}
			}
			else if (bk->GetPosition().y + bk->GetBlockRect().height * 0.5f < hitBox.getPosition().y - hitBox.getGlobalBounds().height * 0.5f
				&& abs(hitBox.getPosition().y - hitBox.getGlobalBounds().height) > bk->GetPosition().y + bk->GetBlockRect().height * 0.5f - 5.f)
			{
				pos.y = bk->GetPosition().y + bk->GetBlockRect().height * 0.5f + hitBox.getGlobalBounds().height;
			}
			else if (bk->GetBlockRect().left > hitBox.getPosition().x)
			{
				pos.x = abs(hitBox.getGlobalBounds().width * 0.5f - bk->GetBlockRect().left);
			}
			else if (bk->GetPosition().x + bk->GetBlockRect().width * 0.5f < hitBox.getPosition().x)
			{
				pos.x = hitBox.getGlobalBounds().width * 0.5f + bk->GetPosition().x + bk->GetBlockRect().width * 0.5f;
			}
			hitBox.setPosition(pos);
			position = pos;
			break;
		}
		else if (isJump == false)
		{
			isFalling = true;
		}
	}

	animation.Update(dt);
}

void Player::Draw(RenderWindow* window, View* mainView)
{
	window->setView(*mainView);
	window->draw(sprite);
	window->draw(hitBox);
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
