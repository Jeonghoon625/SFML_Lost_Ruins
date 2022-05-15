#include "Monster.h"
#include "../../FrameWork/Mgr/Utils.h"
#include "../../FrameWork/Mgr/TextureHolder.h"

Monster::Monster()
	:health(20), atk(3), speed(50.f), nextMove(0.f), checkTime(0.f), isFindPlayer(false), isAttackPlayer(false), attackHitDelay(0.f), isFalling(true), hitDelay(0.f), isAlive(true), immuneMs(START_IMMUNE_MS)
	, isCollideHitBox(false), isCollideAttackRangeBox(false), attackDelay(0.f), fallingSpeed(0.f)
{
	isAttackPlayer = false;
	isHit = false;
	isAlive = true;
	isFindPlayer = false;
	isIdle = true;
	isWalk = false;
	isRun = false;
	resolution.x = 1920.f;
	resolution.y = 1080.f;
}

FloatRect Monster::GetGlobalBound()
{
	return sprite.getGlobalBounds();
}

Sprite Monster::GetSprite()
{
	return sprite;
}

Vector2f Monster::GetPosition()
{
	return position;
}

int Monster::GetHealth()
{
	return health;
}

void Monster::SetHealth(int healthNum)
{
	health = healthNum;
}

void Monster::Spawn(Vector2f pos)
{
	position = pos;
	sprite.setPosition(position);
	std::cout << sprite.getPosition().x << " " << sprite.getPosition().y << std::endl;
	findPlayerBox.setSize(Vector2f(200.f, 40.f));
	findPlayerBox.setScale(scale);
	findPlayerBox.setFillColor(Color(255, 255, 255, 80));
	findPlayerBox.setOrigin(200, 40);
	findPlayerBox.setPosition(position);
	
	attackRangeBox.setSize(Vector2f(30.f, 30.f));
	attackRangeBox.setScale(scale);
	attackRangeBox.setFillColor(Color(153, 0, 0, 80));
	attackRangeBox.setOrigin(30, 30);
	attackRangeBox.setPosition(position);

	hitBox.setSize(Vector2f(43.f, 30.f));
	hitBox.setScale(scale);
	hitBox.setOrigin(hitBox.getSize().x * 0.5f, hitBox.getSize().y * 0.99f);
	hitBox.setFillColor(Color(50, 50, 25, 70));
	hitBox.setPosition(position);
}

int Monster::GetAtk()
{
	return atk;
}

void Monster::SetAtk(int atkNum)
{
	atk = atkNum;
}

float Monster::GetSpeed()
{
	return 0.0f;
}

void Monster::SetSpeed(float speedNum)
{
	speed = speedNum;
}

RectangleShape Monster::GetHitBox()
{
	return hitBox;
}

void Monster::MonsterInit()
{
	strWalk = ("GoblinAttackerWalk");
	strIdle = ("GoblinAttackerIdle");
	strRun = ("GoblinAttackerRun");
	strDead = ("GoblinAttackerDead");
	strAttack = ("GoblinAttackerAttack");
	strAttackBlocked = ("GoblinAttackerAttackBlocked");
	strDamageTaken = ("GoblinAttackerDamageTaken");
	AnimationInit(&sprite);

	animation.Play(strIdle);
	sprite.setOrigin((sprite.getTextureRect().width) * 0.5f, sprite.getTextureRect().height);

	/*sprite.setPosition(resolution.x * 0.3f, resolution.y * 0.5f);*/
	sprite.setScale(scale);
	/*position = sprite.getPosition();*/


	/*findPlayerBox.setSize(Vector2f(200.f, 40.f));
	findPlayerBox.setScale(scale);
	findPlayerBox.setFillColor(Color(255, 255, 255, 80));
	findPlayerBox.setOrigin(200, 40);
	findPlayerBox.setPosition(sprite.getOrigin());

	attackRangeBox.setSize(Vector2f(30.f, 30.f));
	attackRangeBox.setScale(scale);
	attackRangeBox.setFillColor(Color(153, 0, 0, 80));
	attackRangeBox.setOrigin(30, 30);
	attackRangeBox.setPosition(sprite.getOrigin());

	hitBox.setSize(Vector2f(43.f, 30.f));
	hitBox.setScale(scale);
	hitBox.setOrigin(hitBox.getSize().x * 0.5f, hitBox.getSize().y * 0.99f);
	hitBox.setFillColor(Color(50, 50, 25, 70));
	hitBox.setPosition(sprite.getOrigin());*/

	SoundInit();

	currentStatus = MonsterStatus::STATUS_IDLE;
}


void Monster::AnimationInit(Sprite* sprite)
{
	animation.SetTarget(sprite);

	rapidcsv::Document clips("data_tables/animations/monster/monster_animation_clips.csv");
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

void Monster::AnimationUpdate()
{
	switch (currentStatus)
	{
	case MonsterStatus::STATUS_IDLE:
		if (isAlive == false)
		{
			SetStatus(MonsterStatus::STATUS_DEAD);
		}
		else if (isHit == true)
		{
			SetStatus(MonsterStatus::STATUS_HIT);
		}
		else if (isAttackPlayer == true)
		{
			SetStatus(MonsterStatus::STATUS_ATTACK);
		}
		else if (isWalk == true)
		{
			SetStatus(MonsterStatus::STATUS_WALK);
		}
		else if (isFindPlayer == true)
		{
			SetStatus(MonsterStatus::STATUS_RUN);
		}
		break;
	case MonsterStatus::STATUS_WALK:
		if (isAlive == false)
		{
			SetStatus(MonsterStatus::STATUS_DEAD);
		}
		else if (isHit == true)
		{
			SetStatus(MonsterStatus::STATUS_HIT);
		}
		else if (isFindPlayer == true)
		{
			SetStatus(MonsterStatus::STATUS_RUN);
		}
		else if (isIdle == true)
		{
			SetStatus(MonsterStatus::STATUS_IDLE);
		}
	case MonsterStatus::STATUS_RUN:
		if (isAlive == false)
		{
			SetStatus(MonsterStatus::STATUS_DEAD);
		}
		else if (isHit == true)
		{
			SetStatus(MonsterStatus::STATUS_HIT);
		}
		else if (isAttackPlayer)
		{
			SetStatus(MonsterStatus::STATUS_ATTACK);
		}
		break;
	case MonsterStatus::STATUS_ATTACK:
		if (isAlive == false)
		{
			SetStatus(MonsterStatus::STATUS_DEAD);
		}
		else if (isHit == true)
		{
			SetStatus(MonsterStatus::STATUS_HIT);
		}
		else if (isAttackPlayer == false)
		{
			SetStatus(MonsterStatus::STATUS_RUN);
		}
		break;
	case MonsterStatus::STATUS_HIT:
		if (isHit == false)
		{
			SetStatus(MonsterStatus::STATUS_RUN);
		}
	case MonsterStatus::STATUS_DEAD:
		break;
	default:
		break;
	}
}

void Monster::SetStatus(MonsterStatus newStatus)
{
	MonsterStatus prevStatus = currentStatus;
	currentStatus = newStatus;

	switch (currentStatus)
	{
	case MonsterStatus::STATUS_IDLE:
		animation.Play(strIdle);
		break;
	case MonsterStatus::STATUS_WALK:
		animation.Play(strWalk);
		break;
	case MonsterStatus::STATUS_RUN:
		animation.Play(strRun);
		break;
	case MonsterStatus::STATUS_ATTACK:
		animation.Play(strAttack);
		break;
	case MonsterStatus::STATUS_HIT:
		soundHitted.play();
		animation.Play(strDamageTaken);
		break;
	case MonsterStatus::STATUS_DEAD:
		animation.Play(strDead);
		break;
	}
}

void Monster::Walk(float dt)
{
	sprite.setOrigin((sprite.getTextureRect().width) * 0.5f, sprite.getTextureRect().height);	//sprite의 origin 수정
	if (isAlive)
	{
		if (!isFindPlayer && !isHit && !isAttackPlayer)
		{
			checkTime += dt;
			if (checkTime > 3.f)
			{
				checkTime = 0;
				nextMove = Utils::RandomRange(-1, 2);	//-1이면 오른쪽 0이면 멈춤 1이면 왼쪽

				switch (nextMove)
				{
				case -1:
					sprite.setScale(1.f, 1.f);
					isIdle = false;
					isWalk = true;
					/*animation.Play(strWalk);*/
					findPlayerBox.setOrigin(200.f, 40.f);
					attackRangeBox.setOrigin(attackRangeBox.getSize().x, attackRangeBox.getSize().y * 0.99f);
					break;
				case 0:
					/*animation.Play(strIdle);*/
					isIdle = true;
					isWalk - false;
					break;
				case 1:
					sprite.setScale(-1.f, 1.f);
					isIdle = false;
					isWalk = true;
					/*	animation.Play(strWalk);*/
					findPlayerBox.setOrigin(0.f, 40.f);
					attackRangeBox.setOrigin(attackRangeBox.getSize().x * 0.f, attackRangeBox.getSize().y * 0.99f);
					break;
				default:
					break;
				}
			}

			if ((isCollideHitBox && !isCollideAttackRangeBox) == false)
			{
				float h = (float)nextMove;
				float v = 0.f;
				Vector2f dir(h, v);
				position += Utils::Normalize(dir) * speed * dt;

				sprite.setPosition(position);
				findPlayerBox.setPosition(position);
				attackRangeBox.setPosition(position);
				hitBox.setPosition(position);
			}
		}
	}
}



void Monster::FindPlayer(Player& player)
{
	if (isAlive)
	{
		if (!isFindPlayer && !isAttackPlayer && !isHit)
		{
			if (findPlayerBox.getGlobalBounds().intersects(player.GetHitBox().getGlobalBounds()))
			{
				isIdle = false;
				isWalk = false;
				isFindPlayer = true;
				soundFindPlayer.play();
				/*	animation.Play(strRun);*/
			}
		}
	}
}

void Monster::ChasePlayer(Player& player, float dt)
{
	if (isAlive)
	{
		/*animation.PlayQueue(strRun);*/
		if (isFindPlayer && !isAttackPlayer)
		{
			if (attackRangeBox.getGlobalBounds().intersects(player.GetHitBox().getGlobalBounds()) && (attackDelay > 1.5f))
			{
				attackDelay = 0.f;
				/*animation.Play(strAttack);*/
				isFindPlayer = false;
				isAttackPlayer = true;
			}

			if (!isAttackPlayer && !isHit)
			{
				float h = player.GetPosition().x - sprite.getPosition().x;
				float v = 0.f;
				Vector2f dir(h, v);

				if (h > 0)
				{
					sprite.setScale(-1.f, 1.f);	//플레이어가 몬스터 왼쪽에 있을때
					attackRangeBox.setOrigin(attackRangeBox.getSize().x * 0.f, attackRangeBox.getSize().y * 0.99f);
					findPlayerBox.setOrigin(0.f, 40.f);
				}
				else
				{
					sprite.setScale(1.f, 1.f);	//플레이어가 몬스터 오른쪽에 있을때
					attackRangeBox.setOrigin(attackRangeBox.getSize().x, attackRangeBox.getSize().y * 0.99f);
					findPlayerBox.setOrigin(200.f, 40.f);
				}

				if (h * h > 200.f * 200.f || (sprite.getPosition().y - player.GetPosition().y) > 85 || sprite.getPosition().y - player.GetPosition().y < -50)		//플레이어의 거리가 떨어지면 플레이어 추적하는거 취소
				{
					isFindPlayer = false;
					isIdle = true;
				}
				if ((isCollideHitBox && !isCollideAttackRangeBox) == false)
				{
					position += Utils::Normalize(dir) * speed * dt;
					sprite.setPosition(position);

					findPlayerBox.setPosition(position);
					attackRangeBox.setPosition(position);
					hitBox.setPosition(position);
				}
			}
		}
	}
}

void Monster::Run(float dt)
{
}


void Monster::Attack(float dt, int atk, Player& player, Time timeHit)
{
	if (isAlive)
	{
		if (isAttackPlayer)
		{
			attackHitDelay += dt;

			sprite.setPosition(position);
			findPlayerBox.setPosition(position);
			attackRangeBox.setPosition(position);
			hitBox.setPosition(position);

			if (attackHitDelay > 0.75f)
			{
				if (attackRangeBox.getGlobalBounds().intersects(player.GetHitBox().getGlobalBounds()))
				{
					if (sprite.getPosition().x > player.GetSprite().getPosition().x)
					{
						monsterSide = true;
					}
					else
					{
						monsterSide = false;
					}
					player.OnHitted(atk, timeHit);
					// 여기에 player.onhitted
				}
				attackDelay = 0.f;
				attackHitDelay = 0.f;
				isAttackPlayer = false;
				isFindPlayer = true;
				/*animation.Play(strRun);*/
			}
		}
	}
}

bool Monster::OnHitted(int atk, float dt, Time timeHit)
{
	if (isAlive)
	{
		if (timeHit.asMilliseconds() - lastHit.asMilliseconds() > immuneMs)
		{
			lastHit = timeHit;
			if (health > 0)
			{
				/*animation.Play(strDamageTaken);*/
				attackDelay = 0;
				isFindPlayer = false;
				isHit = true;
				attackHitDelay = 0.f;
				isAttackPlayer = false;	//맞으면 공격하려던거 취소
				health -= atk;
				std::cout << "HP : " << GetHealth() << std::endl;
				return true;
			}
			else
			{
				isAlive = false;
			}
			return false;
		}
	}
}

void Monster::Gravity(float dt, std::vector<CollisionBlock*> blocks)
{
	if (isFalling)
	{
		fallingSpeed += GRAVITY_POWER * dt;
		if (fallingSpeed > 3000.f)
		{
			fallingSpeed = 3000.f;
		}
		position.y += fallingSpeed * dt;
	}

	
}

void Monster::UpdateCollision(std::vector<CollisionBlock*> blocks)
{
	isFalling = true;
	isCollideHitBox = false;
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

			isCollideHitBox = true;

			// 블럭 CT에 플레이어가 충돌
			if (blockUp > playerYpos && blockLeft < playerXpos && blockRight > playerXpos)
			{
				pos.y = blockUp + 1.f;
				isFalling = false;
				fallingSpeed = 0.f;
			}
			// 블럭 LT에 플레이어가 충돌
			else if (blockUp > playerYpos && blockLeft > playerXpos)
			{
				if (abs(blockLeft - playerRight) > abs(blockUp - playerDown))
				{
					pos.y = blockUp + 1.f;
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
					pos.y += 1.f;
				}
			}
			// 블럭 RT에 플레이어가 충돌
			else if (blockUp > playerYpos && blockRight < playerXpos)
			{
				if (abs(blockRight - playerLeft) > abs(blockUp - playerDown))
				{
					pos.y = blockUp + 1.f;
					isFalling = false;
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
				
			}
			// 블럭 LB에 플레이어가 충돌
			else if (blockDown < playerYpos && blockLeft > playerXpos)
			{
				if (abs(blockLeft - playerRight) > abs(blockDown - playerUp))
				{
					pos.y = blockDown + hitBox.getGlobalBounds().height;
					
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
			hitBox.setPosition(pos);
			position = pos;
			sprite.setPosition(pos);
		}
	}

}

void Monster::UpdateCollisionAttackRangeBox(std::vector<CollisionBlock*> blocks)
{
	isCollideAttackRangeBox = false;
	for (auto bk : blocks)
	{
		if (attackRangeBox.getGlobalBounds().intersects(bk->GetBlockRect()))
		{
			isCollideAttackRangeBox = true;
		}
	}
}

void Monster::Update(Player& player, float dt, std::vector<CollisionBlock*> blocks, Time playTime)
{
	animation.Update(dt);

	Gravity(dt, blocks);
	UpdateCollision(blocks);
	Walk(dt);
	FindPlayer(player);
	ChasePlayer(player, dt);
	Attack(dt, atk, player, playTime);
	AnimationUpdate();
	UpdateDelayAndStatus(dt);
	UpdateCollisionAttackRangeBox(blocks);
}

void Monster::UpdateDelayAndStatus(float dt)
{
	if (isHit)
	{
		hitDelay += dt;
		if (hitDelay > 0.9f)
		{
			hitDelay = 0.f;
			isHit = false;
			isFindPlayer = true;
		}
	}

	if (GetHealth() < 0)
	{
		isAlive = false;
	}

	attackDelay += dt;
}

void Monster::SoundInit()
{
	soundFindPlayer.setBuffer(SoundHolder::GetBuffer("sound/monster/Slime0.wav"));
	soundHitted.setBuffer(SoundHolder::GetBuffer("sound/monster/SlimeHitVoice0.wav"));
	soundDeath.setBuffer(SoundHolder::GetBuffer("sound/monster/SlimeDie0.wav"));
}




void Monster::Draw(RenderWindow* window)
{
	window->draw(findPlayerBox);
	window->draw(attackRangeBox);
	window->draw(hitBox);
	window->draw(sprite);
}

