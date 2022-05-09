#include "Player.h"
#include "../Monster/ZombieWalker.h"
#include <iostream>

void Player::Init(ZombieWalker* zombie)
{
	health = START_HEALTH;
	maxHealth = START_HEALTH;
	speed = START_SPEED;
	immuneMs = START_IMMUNE_MS;
	fallingSpeed = 0.f;
	attackFps = 0.f;
	isFloor = false;
	isJump = false;

	texture = TextureHolder::GetTexture("graphics/heroin_sprite.png");

	sprite.setOrigin(15.5f, 50.f);
	sprite.setScale(scale);
	AnimationInit();
	animation.Play("Idle");

	weaponMgr.Init();

	this->zombie = zombie;
}

void Player::Spawn(IntRect gameMap, Vector2i res, int tileSize)
{
	this->gameMap = gameMap;
	resolustion = res;
	this->tileSize = tileSize;

	position.x = this->gameMap.left + 200.f;
	position.y = this->gameMap.top;

	hitBox.setFillColor(Color(153, 153, 153, 0));
	hitBox.setSize(Vector2f(20.f, 48.f));
	hitBox.setOrigin(hitBoxOrigin);
	hitBox.setScale(scale);
	hitBox.setPosition(position);
}

bool Player::OnHitted(int damage)
{
	std::cout << health << std::endl;
	health -= damage;
	if (health < 0)
	{
		health = 0;
	}
	return true;
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

RectangleShape Player::GetHitBox()
{
	return hitBox;
}

void Player::Update(float dt, std::vector <TestBlock*> blocks)
{
	float h = InputManager::GetAxisRaw(Axis::Horizontal);
	float v = InputManager::GetAxisRaw(Axis::Vertical);
	Vector2f dir(h, v);

	Utils::Normalize(dir);

	if (InputManager::GetKeyDown(Keyboard::C) && isFloor == true && isJump == false)
	{
		isFloor = false;
		isJump = true;
	}
	if (InputManager::GetKeyDown(Keyboard::X) && isFloor == true && isJump == false && isAttack == false)
	{
		weaponMgr.AttackWeapon(WeaponType::TWO_HANDED);
		attackFps = weaponMgr.GetAttackFps();
		weaponMgr.SetWeaponPosition(sprite);
		isAttack = true;
	}

	// 공격
	if (isAttack == true)
	{
		attackFps -= dt;
		if (attackFps < 0.f)
		{
			weaponMgr.NextFps();
			attackFps = weaponMgr.GetAttackFps();
			if (weaponMgr.CheckFps() == false)
			{
				weaponMgr.ResetFps();
				isAttack = false;
			}
			else
			{
				/*if (weaponMgr.GetSprite().getGlobalBounds().intersects(zombie->GetHitBox().getGlobalBounds()))
				{
					std::cout << "Hit" << zombie->GetHealth() << std::endl;
					zombie->OnHitted(10, dt);
				}*/
			}
		}
	}
	// 이동
	else
	{
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

		sprite.setPosition(position);
		hitBox.setPosition(position);
	}

	// 충돌 처리
	UpdateCollision(blocks);

	/* 충돌 처리 테스트용
	std::cout << isDirection << std::endl;
	if (isFloor == false)
	{
		std::cout << "떨어짐" << "  " << fallingSpeed << std::endl;
	}
	else
	{
		std::cout << "지면" << "  " << fallingSpeed << std::endl;
	}
	*/

	AnimationUpdate();
	animation.Update(dt);
}

void Player::Draw(RenderWindow* window, View* mainView)
{
	window->setView(*mainView);
	window->draw(sprite);
	window->draw(hitBox);
	if (isAttack == true)
	{
		weaponMgr.Draw(window, mainView);
	}
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
	bool isCollided = false;
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
				pos.y = blockUp + 1.f;
				isFloor = true;
				fallingSpeed = 0.f;
			}
			// 블럭 LT에 플레이어가 충돌
			if (blockUp > playerYpos && blockLeft > playerXpos && blockUp > playerYpos)
			{
				if (abs(blockLeft - playerRight) > abs(blockUp - playerDown))
				{
					pos.y = blockUp + 1.f;
					isFloor = true;
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
					pos.y += 1.f;
				}
			}
			// 블럭 RT에 플레이어가 충돌
			if (blockUp > playerYpos && blockRight < playerXpos && blockUp > playerYpos)
			{
				if (abs(blockRight - playerLeft) > abs(blockUp - playerDown))
				{
					pos.y = blockUp + 1.f;
					isFloor = true;
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
					pos.y += 1.f;
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

			isCollided = true;
			hitBox.setPosition(pos);
			position = pos;
		}
	}
	if (isCollided == false)
	{
		isFloor = false;
	}
}

void Player::AnimationUpdate()
{
	// 스프라이트 반전
	if (isAttack == false)
	{
		if (InputManager::GetKey(Keyboard::Left))
		{
			sprite.setScale(scaleFlipX);
		}
		else if (InputManager::GetKey(Keyboard::Right))
		{
			sprite.setScale(scale);
		}
	}

	// 유한 상태 기계(FSM)
	switch (currentStatus)
	{
	case Status::STATUS_IDLE:
		if (InputManager::GetKey(Keyboard::Left) || InputManager::GetKey(Keyboard::Right))
		{
			SetStatus(Status::STATUS_RUN);
		}
		else if (InputManager::GetKeyDown(Keyboard::C))
		{
			SetStatus(Status::STATUS_JUMP);
		}
		else if (InputManager::GetKeyDown(Keyboard::X))
		{
			SetStatus(Status::STATUS_ATK_TWO_STAND);
		}
		else if (isFloor == false)
		{
			SetStatus(Status::STATUS_FALLING);
		}
		break;
	case Status::STATUS_RUN:
		if (InputManager::GetKeyUp(Keyboard::Left) || InputManager::GetKeyUp(Keyboard::Right))
		{
			SetStatus(Status::STATUS_IDLE);
		}
		else if (InputManager::GetKeyDown(Keyboard::C))
		{
			SetStatus(Status::STATUS_JUMP);
		}
		else if (InputManager::GetKeyDown(Keyboard::X))
		{
			SetStatus(Status::STATUS_ATK_TWO_STAND);
		}
		else if (isFloor == false)
		{
			SetStatus(Status::STATUS_FALLING);
		}
		break;
	case Status::STATUS_JUMP:
		if (isJump == false)
		{
			SetStatus(Status::STATUS_FALLING);
		}
		break;
	case Status::STATUS_FALLING:
		if (isFloor == true)
		{
			SetStatus(Status::STATUS_IDLE);
		}
		break;
	case Status::STATUS_ATK_TWO_STAND:
		if (isAttack == false)
		{
			SetStatus(Status::STATUS_IDLE);
		}
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
	case Status::STATUS_IDLE:
		if (prevStatus == Status::STATUS_RUN)
		{
			animation.Play("RuntoIdle");
			animation.PlayQueue("Idle");
		}
		else if (prevStatus == Status::STATUS_FALLING)
		{
			animation.Play("Landing");
			animation.PlayQueue("Idle");
		}
		else
		{
			animation.Play("Idle");
		}
		break;
	case Status::STATUS_RUN:
		if (prevStatus == Status::STATUS_IDLE)
		{
			animation.Play("IdletoRun");
			animation.PlayQueue("Run");
		}
		else
		{
			animation.Play("Run");
		}
		break;
	case Status::STATUS_JUMP:
		animation.Play("Jump");
		break;
	case Status::STATUS_FALLING:
		animation.Play("Falling");
		break;
	case Status::STATUS_ATK_TWO_STAND:
		animation.Play("Attack_Twohanded_Standing");
		break;
	}
}