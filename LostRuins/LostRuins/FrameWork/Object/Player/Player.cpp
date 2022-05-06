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

	texture = TextureHolder::GetTexture("graphics/heroin_sprite.png");

	sprite.setOrigin(15.5f, 50.f);
	sprite.setScale(scale);
	AnimationInit();
	animation.Play("Idle");
}

RectangleShape Player::GetHitBox()
{
	return hitBox;
}

void Player::Spawn(IntRect gameMap, Vector2i res, int tileSize)
{
	this->gameMap = gameMap;
	resolustion = res;
	this->tileSize = tileSize;

	position.x = this->gameMap.width * 0.5f;
	position.y = resolustion.y * 0.5f - 1.f;

	hitBox.setFillColor(Color(153, 153, 153, 0));
	hitBox.setSize(Vector2f(20.f, 48.f));
	hitBox.setOrigin(hitBoxOrigin);
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
	/*{
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
	}*/

	if (InputManager::GetKeyDown(Keyboard::C) && isFalling == false && isJump == false)
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
	lastYpos = position.y;
	lastDir = dir;

	sprite.setPosition(position);
	hitBox.setPosition(position);

	// 충돌 처리
	UpdateCollision(blocks);

	// 테스트용
	std::cout << isFalling << std::endl;
	/*if (isFalling == true)
	{
		std::cout << "떨어짐" << "  " << fallingSpeed << std::endl;
	}
	else
	{
		std::cout << "지면" << "  " << fallingSpeed << std::endl;
	}*/

	AnimationUpdate();
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

			// 블럭 CB에 플레이어가 충돌
			if (blockDown < playerYpos && blockLeft < playerXpos && blockRight > playerXpos)
			{
				pos.y = blockDown + hitBox.getGlobalBounds().height;
				isJump = false;
				JumpingSpeed = START_JUMP_SPEED;
			}
			// 블럭 LB에 플레이어가 충돌
			if (blockDown < playerYpos && blockLeft > playerXpos && blockDown < playerYpos)
			{
				if (abs(blockLeft - playerRight) > abs(blockDown - playerUp))
				{
					pos.y = blockDown + hitBox.getGlobalBounds().height;
					isJump = false;
					JumpingSpeed = START_JUMP_SPEED;
				}
				else if (abs(blockLeft - playerRight) < abs(blockDown - playerUp))
				{
					pos.x = blockLeft - hitBox.getGlobalBounds().width * 0.5f;
				}
				else
				{
					pos.x -= abs(blockLeft - playerRight);
					pos.y -= abs(blockDown - playerUp);
				}
			}
			// 블럭 RB에 플레이어가 충돌
			if (blockDown < playerYpos && blockRight < playerXpos && blockDown < playerYpos)
			{
				if (abs(blockRight - playerLeft) > abs(blockDown - playerUp))
				{
					pos.y = blockDown + hitBox.getGlobalBounds().height;
					isJump = false;
					JumpingSpeed = START_JUMP_SPEED;
				}
				else if (abs(blockRight - playerLeft) < abs(blockDown - playerUp))
				{
					pos.x = blockRight + hitBox.getGlobalBounds().width * 0.5f;
				}
				else
				{
					pos.x += abs(blockRight - playerLeft);
					pos.y -= abs(blockDown - playerUp);
				}
			}
			// 블럭 CT에 플레이어가 충돌
			if (blockUp > playerYpos && blockLeft < playerXpos && blockRight > playerXpos)
			{
				pos.y = blockUp;
				isFalling = false;
				fallingSpeed = 0.f;
			}
			// 블럭 LT에 플레이어가 충돌
			if (blockUp > playerYpos && blockLeft > playerXpos && blockUp > playerYpos)
			{
				if (abs(blockLeft - playerRight) > abs(blockUp - playerDown))
				{
					pos.y = blockUp;
					isFalling = false;
					fallingSpeed = 0.f;
				}
				else if (abs(blockLeft - playerRight) < abs(blockUp - playerDown))
				{
					pos.x = blockLeft - hitBox.getGlobalBounds().width * 0.5f;
				}
				else
				{
					pos.x -= abs(blockLeft - playerRight);
					pos.y -= abs(blockUp - playerDown);
				}
			}
			// 블럭 RT에 플레이어가 충돌
			if (blockUp > playerYpos && blockRight < playerXpos && blockUp > playerYpos)
			{
				if (abs(blockRight - playerLeft) > abs(blockUp - playerDown))
				{
					pos.y = blockUp;
					isFalling = false;
					fallingSpeed = 0.f;
				}
				else if (abs(blockRight - playerLeft) < abs(blockUp - playerDown))
				{
					pos.x = blockRight + hitBox.getGlobalBounds().width * 0.5f;
				}
				else
				{
					pos.x -= abs(blockRight - playerLeft);
					pos.y -= abs(blockUp - playerDown);
				}
			}
			// 블럭 LC에 플레이어가 충돌
			if (blockLeft > playerXpos && blockUp < playerYpos && blockDown > playerYpos)
			{
				pos.x = blockLeft - hitBox.getGlobalBounds().width * 0.5f;
			}
			// 블럭 RC에 플레이어가 충돌
			if (blockRight < playerXpos && blockUp < playerYpos && blockDown > playerYpos)
			{
				pos.x = blockRight + hitBox.getGlobalBounds().width * 0.5f;
			}
			hitBox.setPosition(pos);
			position = pos;
		}
	}
}

void Player::AnimationUpdate()
{
	switch (currentStatus)
	{
	case Status::STATUS_IDLE:
		if (InputManager::GetKeyDown(Keyboard::Left))
		{
			sprite.setScale(scaleFlipX);
			SetStatus(STATUS_RUN);
		}
		else if (InputManager::GetKeyDown(Keyboard::Right))
		{
			sprite.setScale(scale);
			SetStatus(STATUS_RUN);
		}
		else if (InputManager::GetKeyDown(Keyboard::C))
		{
			SetStatus(STATUS_JUMP);
		}
		break;
	case Status::STATUS_RUN:
		if (InputManager::GetKeyUp(Keyboard::Left) || InputManager::GetKeyUp(Keyboard::Right))
		{
			SetStatus(STATUS_IDLE);
		}
		else if (InputManager::GetKeyDown(Keyboard::C))
		{
			SetStatus(STATUS_JUMP);
		}
		break;
	case Status::STATUS_JUMP:
		if (isFalling == false)
		{
			SetStatus(STATUS_IDLE);
		}
		if (InputManager::GetKeyDown(Keyboard::Left))
		{
			sprite.setScale(scaleFlipX);
		}
		else if (InputManager::GetKeyDown(Keyboard::Right))
		{
			sprite.setScale(scale);
		}
		break;
	case Status::STATUS_FALLING:
		break;
	default:
		break;
	}
}

void Player::SetStatus(Status newStatus)
{
	Status prevStatus = currentStatus;
	currentStatus = newStatus;

	switch (currentStatus)
	{
	case STATUS_IDLE:
		animation.Play("Idle");
		break;
	case STATUS_RUN:
		animation.Play("Run");
		break;
	case STATUS_JUMP:
		animation.Play("Jump");
		break;
	case STATUS_FALLING:
		animation.Play("Falling");
		break;
	}
}
