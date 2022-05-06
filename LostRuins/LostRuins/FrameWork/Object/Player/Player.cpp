#include "Player.h"
#include <iostream>

void Player::Init()
{
	speed = START_SPEED;
	health = START_HEALTH;
	maxHealth = START_HEALTH;
	immuneMs = START_IMMUNE_MS;
	fallingSpeed = 0.f;
	isFalling = true;
	isJump = false;
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

	hitBox.setFillColor(Color(0, 0, 255, 192));
	hitBox.setSize(Vector2f(20.f, 48.f));
	hitBox.setOrigin(hitBoxMiddle);
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

	// 애니메이션
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

	if (skipDt == true)
	{
		dt = 0.f;
		skipDt = false;
	}

	if (InputManager::GetKeyDown(Keyboard::Up) && isFalling == false && isJump == false)
	{
		isJump = true;
	}

	// 이동
	position.x += dir.x * speed * dt;
	if (isJump == false)
	{
		fallingSpeed += GRAVITY_POWER * dt;
		if (fallingSpeed > 3000.f)
		{
			fallingSpeed = 3000.f;
		}
	}

	else if (isJump == true)
	{
		JumpingSpeed -= GRAVITY_POWER * dt;
		position.y -= JumpingSpeed * dt;
		if (JumpingSpeed < 0.f)
		{
			isJump = false;
			JumpingSpeed = START_JUMP_SPEED;
		}
	}
	position.y += fallingSpeed * dt;

	lastDir = dir;

	sprite.setPosition(position);
	hitBox.setPosition(position);

	// 충돌 처리
	UpdateCollision(blocks);

	if (isFalling == true)
	{
		std::cout << "떨어짐" << "  " << fallingSpeed << std::endl;
	}
	else
	{
		std::cout << "지면" << "  " << fallingSpeed << std::endl;
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

void Player::UpdateCollision(std::vector<TestBlock*> blocks)
{
	isFalling = true;
	for (auto bk : blocks)
	{
		if (hitBox.getGlobalBounds().intersects(bk->GetBlockRect()))
		{
			float blockUp = bk->GetBlockRect().top;
			float blockDown = bk->GetPosition().y + bk->GetBlockRect().height * 0.5f;
			float blockLeft = bk->GetBlockRect().left;
			float blockRight = bk->GetPosition().x + bk->GetBlockRect().width * 0.5f;

			float playerUp = hitBox.getPosition().y - hitBox.getGlobalBounds().height;
			float playerDown = hitBox.getPosition().y;
			float playerLeft = hitBox.getGlobalBounds().left;
			float playerRight = hitBox.getPosition().x + hitBox.getGlobalBounds().width * 0.5f;

			float playerXpos = hitBox.getPosition().x;
			float playerYpos = hitBox.getPosition().y - hitBox.getGlobalBounds().height * 0.5f;

			Vector2f pos = hitBox.getPosition();

			if (blockDown < playerYpos && playerUp > blockDown - 10.f)
			{
				//std::cout << "블럭 아래에 플레이어가 충돌" << std::endl;
				pos.y = blockDown + hitBox.getGlobalBounds().height;
				isJump = false;
				JumpingSpeed = START_JUMP_SPEED;
			}
			if (blockUp > playerYpos && playerDown < blockUp + 10.f)
			{
				//std::cout << "블럭 위에 플레이어가 충돌" << std::endl;
				pos.y = blockUp;
				isFalling = false;
				fallingSpeed = 0.f;
			}
			if (blockLeft > playerXpos && playerRight < blockLeft + 10.f)
			{
				//std::cout << "블럭 왼쪽에 플레이어가 충돌" << std::endl;
				pos.x = blockLeft - hitBox.getGlobalBounds().width * 0.5f - 1.f;
			}
			if (blockRight < playerXpos && playerLeft > blockRight - 10.f)
			{
				//std::cout << "블럭 오른쪽에 플레이어가 충돌" << std::endl;
				pos.x = blockRight + hitBox.getGlobalBounds().width * 0.5f + 1.f;
			}
			hitBox.setPosition(pos);
			position = pos;
		}
	}
}

RectangleShape Player::GetHitBox()
{
	return hitBox;
}
