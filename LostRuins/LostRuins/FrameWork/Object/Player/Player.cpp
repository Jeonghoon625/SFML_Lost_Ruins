#include "Player.h"
#include "../Monster/Monster.h"
#include "../Monster/ZombieWalker.h"
#include <iostream>

void Player::Init(ZombieWalker* zombie)
{
	health = START_HEALTH;
	maxHealth = START_HEALTH;
	mana = START_MANA;
	maxMana = START_MANA;

	speed = START_SPEED;
	JumpingSpeed = START_JUMP_SPEED;
	fallingSpeed = 0.f;
	rollSpeed = START_ROLL_SPEED;
	knockBackSpeed = START_KNOCK_BACK_SPEED;

	attackFps = 0.f;
	soundDelay = 0.f;
	rollTime = START_ROLL_TIME;
	immuneMs = START_IMMUNE_MS;
	deadTime = DEAD_TIME_COUNT;

	isFloor = false;
	isJump = false;
	isAttack = false;
	isSpell = false;
	isCrouch = false;
	isRoll = false;
	isDelay = false;
	isHit = false;
	isAlive = true;
	isPause = false;

	AnimationInit(&sprite);
	sprite.setOrigin(15.5f, 50.f);
	sprite.setScale(scale);
	currentStatus = Status::STATUS_IDLE;
	animation.Play("Idle");

	effectMgr.Init();
	attackMgr.Init(zombie, &effectMgr);
	SoundInit();

	this->zombie = zombie;

	for (int i = 0; i < MAX_TEXT_CACHE_SIZE; i++)
	{
		unuseDorR.push_back(new DamageAndRecovery());
	}
}

void Player::Update(float dt, std::vector <CollisionBlock*> blocks, Time playTime, std::vector<Monster*>& monsters)
{
	// 플레이어 행동
	PlayerAction(dt, playTime, monsters);

	// 충돌 처리
	UpdateCollision(blocks);

	// 애니메이션
	AnimationUpdate(dt);
	animation.Update(dt);

	attackMgr.Update(dt, blocks, playTime);
	effectMgr.Update(dt);

	auto DorR = useDorR.begin();
	while (DorR != useDorR.end())
	{
		DamageAndRecovery* isDorR = *DorR;
		isDorR->Update(dt);

		if (!isDorR->IsActive())
		{
			DorR = useDorR.erase(DorR);
		}
		else
		{
			++DorR;
		}
	}

	if (InputManager::GetKeyDown(Keyboard::Tab) && isPause == false)
	{
		isPause = true;
	}
	else if (InputManager::GetKeyDown(Keyboard::Escape) && isPause == false)
	{
		isPause = true;
	}
}

void Player::Draw(RenderWindow* window, View* mainView)
{
	window->setView(*mainView);
	window->draw(sprite);
	window->draw(hitBox);
	if (isAttack == true && isDelay == false)
	{
		attackMgr.WeaponDraw(window, mainView);
	}
	attackMgr.SpellDraw(window);
	effectMgr.Draw(window);

	for (auto DorR : useDorR)
	{
		window->draw(DorR->GetText());
	}
}

void Player::PlayerAction(float dt, Time playTime, std::vector<Monster*> monsters)
{
	float h = InputManager::GetAxisRaw(Axis::Horizontal);
	float v = InputManager::GetAxisRaw(Axis::Vertical);
	Vector2f dir(h, v);

	Utils::Normalize(dir);

	if (isAlive == true)
	{
		if (isFloor == true && isJump == false && isRoll == false && isHit == false)
		{
			if (isCrouch == false)
			{
				if (InputManager::GetKeyDown(Keyboard::C))
				{
					isFloor = false;
					isJump = true;
				}
				if (isAttack == false && isSpell == false)
				{
					if (InputManager::GetKeyDown(Keyboard::X))
					{
						attackMgr.SetAttackType(AttackType::DAGGER);
						attackFps = attackMgr.GetAttackFps();
						attackMgr.SetAttackPosition(sprite);
						isAttack = true;
					}
					else if (InputManager::GetKeyDown(Keyboard::Z))
					{
						attackMgr.SetAttackType(AttackType::TWO_HANDED);
						attackFps = attackMgr.GetAttackFps();
						attackMgr.SetAttackPosition(sprite);
						isAttack = true;
					}
					else if (InputManager::GetKeyDown(Keyboard::A))
					{
						attackMgr.SetAttackType(AttackType::FIRE_ARROW);
						attackFps = attackMgr.GetAttackFps();
						if (mana >= attackMgr.PaySpellCost())
						{
							mana -= attackMgr.PaySpellCost();
							isSpell = true;
						}
					}
					else if (InputManager::GetKeyDown(Keyboard::Space))
					{
						isRoll = true;
					}
					else if (InputManager::GetKey(Keyboard::Down))
					{
						hitBox.setSize(Vector2f(20.f, 23.f));
						hitBox.setOrigin(hitBoxCrouch);
						hitBox.setPosition(position);
						isCrouch = true;
					}
				}
			}

			if (InputManager::GetKeyUp(Keyboard::Down) && isCrouch == true)
			{
				hitBox.setSize(Vector2f(20.f, 48.f));
				hitBox.setOrigin(hitBoxStand);
				hitBox.setPosition(position);
				isCrouch = false;
			}
		}

		// 공격
		if (isAttack == true)
		{
			attackFps -= dt;
			if (attackFps < 0.f)
			{
				if (attackMgr.GetFps() == 5)
				{
					attackMgr.GetAttackSound();
				}

				if (isDelay == false)
				{
					attackMgr.NextFps();
					attackFps = attackMgr.GetAttackFps();
					if (attackMgr.CheckFps() == false)
					{
						attackMgr.ResetFps();
						isDelay = true;
					}
					else
					{
						if (attackMgr.GetFps() > attackMgr.GetHitFrame())
						{
							for (auto monster : monsters)
							{
								if (attackMgr.GetSprite().getGlobalBounds().intersects(monster->GetHitBox().getGlobalBounds()))
								{
									monster->OnHitted(attackMgr.GetAttackPoint(), dt, playTime);
								}
							}

							//if (attackMgr.GetSprite().getGlobalBounds().intersects(zombie->GetHitBox().getGlobalBounds()))
							//{
							//	//std::cout << "Hit" << zombie->GetHealth() << std::endl;
							//	/*zombie->OnHitted(attackMgr.GetAttackPoint(), dt, playTime);*/
							//	
							//}
						}
					}
				}
				else if (isDelay == true)
				{
					attackMgr.NextFps();
					attackFps = attackMgr.GetAttackFps();
					if (attackMgr.CheckDelay() == false)
					{
						attackMgr.ResetFps();
						isDelay = false;
						isAttack = false;
					}
				}
			}
		}
		// 주문
		else if (isSpell == true)
		{
			attackFps -= dt;
			if (attackFps < 0.2f && isDelay == false)
			{
				soundFireArrow.play();
				attackMgr.CastingSpell(sprite);
				isDelay = true;
			}
			else if (attackFps < 0.f && isDelay == true)
			{
				isDelay = false;
				isSpell = false;
			}
		}
		// 이동
		else
		{
			if (isHit == false)
			{
				if (isRoll == true)
				{
					rollTime -= dt;
					if (sprite.getScale().x > 0.f)
					{
						position.x += 1.f * rollSpeed * dt;
					}
					else if (sprite.getScale().x < 0.f)
					{
						position.x -= 1.f * rollSpeed * dt;
					}

					if (rollTime < 0.f)
					{
						rollTime = START_ROLL_TIME;
						isRoll = false;
					}
				}
				else if (isCrouch == false)
				{
					position.x += dir.x * speed * dt;
				}

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
			}
			else if (isHit == true)
			{
				if (sprite.getScale().x > 0.f)
				{
					position.x -= 1.f * knockBackSpeed * dt;
				}
				else if (sprite.getScale().x < 0.f)
				{
					position.x += 1.f * knockBackSpeed * dt;
				}
				knockBackSpeed -= GRAVITY_POWER * dt;
				position.y -= 1.f * knockBackSpeed * dt;
				if (knockBackSpeed < 0.f)
				{
					knockBackSpeed = START_KNOCK_BACK_SPEED;
					isHit = false;
				}
			}
		}
	}
	// 사망
	else if (isAlive == false)
	{
		if (isFloor == false)
		{
			if (sprite.getScale().x > 0.f)
			{
				position.x -= 1.f * knockBackSpeed * dt;
			}
			else if (sprite.getScale().x < 0.f)
			{
				position.x += 1.f * knockBackSpeed * dt;
			}
		}

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

		deadTime -= dt;
		if (deadTime < 0.f)
		{
			deadTime = DEAD_TIME_COUNT;
			isPause = true;
		}
	}

	sprite.setPosition(position);
	hitBox.setPosition(position);
}

void Player::Spawn(IntRect gameMap, Vector2i res, int tileSize)
{
	this->gameMap = gameMap;
	resolustion = res;
	this->tileSize = tileSize;

	position.x = this->gameMap.left + 200.f;
	position.y = this->gameMap.height * 0.5f;

	hitBox.setFillColor(Color(153, 153, 153, 0));
	hitBox.setSize(Vector2f(20.f, 48.f));
	hitBox.setOrigin(hitBoxStand);
	hitBox.setScale(scale);
	hitBox.setPosition(position);
}

bool Player::OnHitted(int damage, Time timeHit)
{
	if (isRoll == false && isAlive == true)
	{
		if (timeHit.asMilliseconds() - lastHit.asMilliseconds() > immuneMs)
		{
			lastHit = timeHit;
			health -= damage;

			effectMgr.HitActor(sprite);

			Vector2f spawnPos(position.x, sprite.getGlobalBounds().top);
			if (unuseDorR.empty())
			{
				for (int i = 0; i < MAX_TEXT_CACHE_SIZE; ++i)
				{
					unuseDorR.push_back(new DamageAndRecovery());
				}
			}
			DamageAndRecovery* DorR = unuseDorR.front();
			unuseDorR.pop_front();
			useDorR.push_back(DorR);
			DorR->HitPlayer(spawnPos, damage);

			if (health > 0)
			{
				isHit = true;
			}
			if (isAttack == true)
			{
				attackFps = attackMgr.GetAttackFps();
				attackMgr.ResetFps();
				isDelay = false;
				isAttack = false;
			}
			if (isJump == true)
			{
				isJump = false;
				JumpingSpeed = START_JUMP_SPEED;
			}
			if (isSpell == true)
			{
				isSpell = false;
			}

			if (health < 0)
			{
				health = 0;
				JumpingSpeed = DEAD_FALLING_SPEED;
				isAlive = false;
				isJump = true;
			}
			return true;
		}
	}
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

int Player::GetMaxHealth() const
{
	return maxHealth;
}

int Player::GetMana() const
{
	return mana;
}

int Player::GetMaxMana() const
{
	return maxMana;
}

RectangleShape Player::GetHitBox()
{
	return hitBox;
}

bool Player::GetAlive()
{
	return isAlive;
}

void Player::SetPause(bool isPause)
{
	this->isPause = isPause;
}

bool Player::GetPause()
{
	return isPause;
}

void Player::AnimationInit(Sprite* sprite)
{
	animation.SetTarget(sprite);

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

void Player::SoundInit()
{
	soundBackGround.setBuffer(SoundHolder::GetBuffer("sound/12058396_MotionElements_suspenseful-background.wav"));
	soundWalk.setBuffer(SoundHolder::GetBuffer("sound/FOOTSTEP_Trainers_Gravel_Compact_Run_RR2_mono.wav"));
	soundJump.setBuffer(SoundHolder::GetBuffer("sound/PlayerJumpRoll2.wav"));
	soundRoll.setBuffer(SoundHolder::GetBuffer("sound/PlayerJumpRoll1.wav"));
	soundDagger.setBuffer(SoundHolder::GetBuffer("sound/PlayerAttackShort0.wav"));
	soundTwoHanded.setBuffer(SoundHolder::GetBuffer("sound/PlayerAttackLong1.wav"));
	soundFireArrow.setBuffer(SoundHolder::GetBuffer("sound/FireArrow.wav"));
	soundDamage.setBuffer(SoundHolder::GetBuffer("sound/damage_a_03.wav"));
	soundDeath.setBuffer(SoundHolder::GetBuffer("sound/death_a_03.wav"));
	soundBackGround.play();
}

void Player::UpdateCollision(std::vector<CollisionBlock*> blocks)
{
	bool isCollided = false;
	for (auto bk : blocks)
	{
		if (hitBox.getGlobalBounds().intersects(bk->GetBlockRect()))
		{
			float blockUp = bk->GetBlockRect().top;
			float blockDown = bk->GetBlockRect().top + bk->GetBlockRect().height;
			float blockLeft = bk->GetBlockRect().left;
			float blockRight = bk->GetBlockRect().left + bk->GetBlockRect().width;

			float playerUp = hitBox.getGlobalBounds().top;
			float playerDown = hitBox.getGlobalBounds().top + hitBox.getGlobalBounds().height;
			float playerLeft = hitBox.getGlobalBounds().left;
			float playerRight = hitBox.getGlobalBounds().left + hitBox.getGlobalBounds().width;

			float playerXpos = hitBox.getGlobalBounds().left + hitBox.getGlobalBounds().width * 0.5f;
			float playerYpos = hitBox.getGlobalBounds().top + hitBox.getGlobalBounds().height * 0.5f;
			Vector2f pos = hitBox.getPosition();

			// 블럭 CT에 플레이어가 충돌
			if (blockUp > playerYpos && blockLeft < playerXpos && blockRight > playerXpos)
			{
				pos.y = blockUp + 1.f;
				isFloor = true;
				fallingSpeed = 0.f;
			}
			// 블럭 LT에 플레이어가 충돌
			else if (blockUp > playerYpos && blockLeft > playerXpos)
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
			else if (blockUp > playerYpos && blockRight < playerXpos)
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
					pos.x += abs(blockRight - playerLeft);
					pos.y -= abs(blockUp - playerDown);
					pos.y += 1.f;
				}
			}
			// 블럭 LC에 플레이어가 충돌
			else if (blockLeft > playerXpos && blockUp < playerYpos && blockDown > playerYpos)
			{
				pos.x = blockLeft - hitBox.getGlobalBounds().width * 0.5f;
			}
			// 블럭 RC에 플레이어가 충돌
			else if (blockRight < playerXpos && blockUp < playerYpos && blockDown > playerYpos)
			{
				pos.x = blockRight + hitBox.getGlobalBounds().width * 0.5f;
			}
			// 블럭 CB에 플레이어가 충돌
			else if (blockDown < playerYpos && blockLeft < playerXpos && blockRight > playerXpos)
			{
				pos.y = blockDown + hitBox.getGlobalBounds().height;
				isJump = false;
				JumpingSpeed = START_JUMP_SPEED;
			}
			// 블럭 LB에 플레이어가 충돌
			else if (blockDown < playerYpos && blockLeft > playerXpos)
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
					pos.y += abs(blockDown - playerUp);
				}
			}
			// 블럭 RB에 플레이어가 충돌
			else if (blockDown < playerYpos && blockRight < playerXpos)
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
					pos.y += abs(blockDown - playerUp);
				}
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

void Player::AnimationUpdate(float dt)
{
	// 스프라이트 반전
	if (isAttack == false && isRoll == false && isHit == false && isSpell == false && isAlive == true)
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
		if (isAlive == false)
		{
			SetStatus(Status::STATUS_DEAD);
		}
		else if (isHit == true)
		{
			SetStatus(Status::STATUS_HIT);
		}
		else if (InputManager::GetKeyDown(Keyboard::C))
		{
			SetStatus(Status::STATUS_JUMP);
		}
		else if (InputManager::GetKeyDown(Keyboard::X))
		{
			SetStatus(Status::STATUS_ATK_DAGGER);
		}
		else if (InputManager::GetKeyDown(Keyboard::Z))
		{
			SetStatus(Status::STATUS_ATK_TWO_STAND);
		}
		else if (InputManager::GetKeyDown(Keyboard::A))
		{
			SetStatus(Status::STATUS_SPELL);
		}
		else if (InputManager::GetKey(Keyboard::Down))
		{
			SetStatus(Status::STATUS_CROUCH);
		}
		else if (InputManager::GetKeyDown(Keyboard::Space))
		{
			SetStatus(Status::STATUS_ROLL);
		}
		else if (isFloor == false)
		{
			SetStatus(Status::STATUS_FALLING);
		}
		else if (InputManager::GetKey(Keyboard::Left) || InputManager::GetKey(Keyboard::Right))
		{
			SetStatus(Status::STATUS_RUN);
		}
		break;
	case Status::STATUS_RUN:
		if (isAlive == false)
		{
			SetStatus(Status::STATUS_DEAD);
		}
		else if (isHit == true)
		{
			SetStatus(Status::STATUS_HIT);
		}
		else if (InputManager::GetKeyDown(Keyboard::C))
		{
			SetStatus(Status::STATUS_JUMP);
		}
		else if (InputManager::GetKeyDown(Keyboard::X))
		{
			SetStatus(Status::STATUS_ATK_DAGGER);
		}
		else if (InputManager::GetKeyDown(Keyboard::Z))
		{
			SetStatus(Status::STATUS_ATK_TWO_STAND);
		}
		else if (InputManager::GetKeyDown(Keyboard::A))
		{
			SetStatus(Status::STATUS_SPELL);
		}
		else if (InputManager::GetKey(Keyboard::Down))
		{
			SetStatus(Status::STATUS_CROUCH);
		}
		else if (InputManager::GetKeyDown(Keyboard::Space))
		{
			SetStatus(Status::STATUS_ROLL);
		}
		else if (isFloor == false)
		{
			SetStatus(Status::STATUS_FALLING);
		}
		else if (InputManager::GetKeyUp(Keyboard::Left) || InputManager::GetKeyUp(Keyboard::Right))
		{
			SetStatus(Status::STATUS_IDLE);
		}
		break;
	case Status::STATUS_JUMP:
		if (isAlive == false)
		{
			SetStatus(Status::STATUS_DEAD);
		}
		else if (isHit == true)
		{
			SetStatus(Status::STATUS_HIT);
		}
		else if (isJump == false)
		{
			SetStatus(Status::STATUS_FALLING);
		}
		break;
	case Status::STATUS_FALLING:
		if (isAlive == false)
		{
			SetStatus(Status::STATUS_DEAD);
		}
		else if (isHit == true)
		{
			SetStatus(Status::STATUS_HIT);
		}
		else if (isFloor == true)
		{
			SetStatus(Status::STATUS_IDLE);
		}
		break;
	case Status::STATUS_CROUCH:
		if (isAlive == false)
		{
			SetStatus(Status::STATUS_DEAD);
		}
		else if (isHit == true)
		{
			SetStatus(Status::STATUS_HIT);
		}
		else if (InputManager::GetKeyUp(Keyboard::Down))
		{
			SetStatus(Status::STATUS_IDLE);
		}
		break;
	case Status::STATUS_ROLL:
		if (isRoll == false)
		{
			SetStatus(Status::STATUS_IDLE);
		}
		break;
	case Status::STATUS_ATK_TWO_STAND:
		if (isAlive == false)
		{
			SetStatus(Status::STATUS_DEAD);
		}
		else if (isHit == true)
		{
			SetStatus(Status::STATUS_HIT);
		}
		else if (isAttack == false)
		{
			SetStatus(Status::STATUS_IDLE);
		}
		break;
	case Status::STATUS_ATK_DAGGER:
		if (isAlive == false)
		{
			SetStatus(Status::STATUS_DEAD);
		}
		else if (isHit == true)
		{
			SetStatus(Status::STATUS_HIT);
		}
		else if (isAttack == false)
		{
			SetStatus(Status::STATUS_IDLE);
		}
		break;
	case Status::STATUS_SPELL:
		if (isAlive == false)
		{
			SetStatus(Status::STATUS_DEAD);
		}
		else if (isHit == true)
		{
			SetStatus(Status::STATUS_HIT);
		}
		else if (isSpell == false)
		{
			SetStatus(Status::STATUS_IDLE);
		}
		break;
	case Status::STATUS_HIT:
		if (isHit == false)
		{
			SetStatus(Status::STATUS_FALLING);
		}
	case Status::STATUS_DEAD:
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
		soundWalk.setLoop(false);
		if (prevStatus == Status::STATUS_RUN)
		{
			animation.Play("RuntoIdle");
			animation.PlayQueue("Idle");
		}
		else if (prevStatus == Status::STATUS_FALLING)
		{
			soundWalk.play();
			animation.Play("Landing");
			animation.PlayQueue("Idle");
		}
		else if (prevStatus == Status::STATUS_CROUCH)
		{
			animation.Play("CrouchingtoIdle");
			animation.PlayQueue("Idle");
		}
		else
		{
			animation.Play("Idle");
		}
		break;
	case Status::STATUS_RUN:
		soundWalk.setLoop(true);
		soundWalk.play();
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
		soundWalk.setLoop(false);
		soundJump.play();
		animation.Play("Jump");
		break;
	case Status::STATUS_FALLING:
		soundWalk.setLoop(false);
		animation.Play("Falling");
		break;
	case Status::STATUS_CROUCH:
		soundWalk.setLoop(false);
		animation.Play("Crouch");
		animation.PlayQueue("Crouching");
		break;
	case Status::STATUS_ROLL:
		soundWalk.setLoop(false);
		soundRoll.play();
		animation.Play("Roll");
		break;
	case Status::STATUS_ATK_TWO_STAND:
		soundWalk.setLoop(false);
		soundTwoHanded.play();
		animation.Play("Attack_Twohanded_Standing");
		break;
	case Status::STATUS_ATK_DAGGER:
		soundWalk.setLoop(false);
		soundDagger.play();
		animation.Play("Attack_Dagger_Standing");
		break;
	case Status::STATUS_SPELL:
		soundWalk.setLoop(false);
		animation.Play("CastingSpell1");
		animation.PlayQueue("CastingSpell3");
		break;
	case Status::STATUS_HIT:
		soundWalk.setLoop(false);
		soundDamage.play();
		animation.Play("DamageTaken");
		break;
	case Status::STATUS_DEAD:
		soundWalk.setLoop(false);
		soundDeath.play();
		animation.Play("Dead");
		break;
	}
}

void Player::Spawn(float x, float y)
{
	position.x = x;
	position.y = y;

	hitBox.setFillColor(Color(103, 103, 103, 0));
	hitBox.setSize(Vector2f(20.f, 48.f));
	hitBox.setOrigin(hitBoxStand);
	hitBox.setScale(scale);
	hitBox.setPosition(position);
}