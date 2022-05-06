#include "Monster.h"
#include "../../FrameWork/Mgr/Utils.h"
#include "../../FrameWork/Mgr/TextureHolder.h"

Monster::Monster()
	:health(20), atk(3), speed(50.f), nextMove(0.f), checkTime(0.f),isFindPlayer(false),isAttackPlayer(false),attackDelay(0.f),isFalling(true)
	,strWalk("GoblinAttackerWalk"),strIdle("GoblinAttackerIdle"),strRun("GoblinAttackerRun"),strDead("GoblinAttackerDead"), strAttack("GoblinAttackerAttack")
	,strAttackBlocked("GoblinAttackerAttackBlocked"),strDemageTaken("GoblinAttackerDemageTaken")
{

	
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;
	
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

void Monster::SetHealth(int health)
{
	this->health;
}

int Monster::GetAtk()
{
	return atk;
}

void Monster::SetAtk(int atk)
{
	this->atk;
}

float Monster::GetSpeed()
{
	return 0.0f;
}

void Monster::SetSpeed(float speed)
{
	this->speed;
}

RectangleShape Monster::GetHitBox()
{
	return hitBox;
}

void Monster::MonsterInit()
{
	AnimationInit(&sprite);

	sprite.setOrigin(23.f,30);		//고블린 발 끝 좌표 23,30
	sprite.setPosition(resolution.x * 0.3f, resolution.y * 0.5f);
	sprite.setScale(scale);
	position = sprite.getPosition();

	
	findPlayerBox.setSize(Vector2f(200.f,40.f));
	findPlayerBox.setScale(scale);
	findPlayerBox.setFillColor(Color(255, 255, 255, 80));
	findPlayerBox.setOrigin(200,40);
	findPlayerBox.setPosition(sprite.getOrigin());
	
	attackRangeBox.setSize(Vector2f(30.f, 30.f));
	attackRangeBox.setScale(scale);
	attackRangeBox.setFillColor(Color(153,0,0,80));
	attackRangeBox.setOrigin(30, 30);
	attackRangeBox.setPosition(sprite.getOrigin());

	hitBox.setSize(Vector2f(43.f, 30.f));
	hitBox.setScale(scale);
	hitBox.setOrigin(21.5f, 30.f);
	hitBox.setFillColor(Color(50, 50, 25, 70));
	hitBox.setPosition(sprite.getOrigin());
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

void Monster::Walk(float dt)
{
	if (!isFindPlayer)
	{
		checkTime += dt;
		if (checkTime > 3.f)
		{
			checkTime = 0;
			nextMove = Utils::RandomRange(-1, 2);	//-1이면 오른쪽 0이면 멈춤 1이면 왼쪽
			switch (nextMove)
			{
			case -1:
				sprite.setScale(3.f, 3.f);
				animation.Play("GoblinAttackerWalk");
				sprite.setOrigin(23.f, 30);
				findPlayerBox.setOrigin(200.f, 40.f);
				attackRangeBox.setOrigin(30, 30);
				break;
			case 0:
				animation.Play("GoblinAttackerIdle");
				sprite.setOrigin(23.f, 30);
				break;
			case 1:
				sprite.setScale(-3.f, 3.f);
				animation.Play("GoblinAttackerWalk");
				sprite.setOrigin(23.f, 30);
				findPlayerBox.setOrigin(0.f, 40.f);
				attackRangeBox.setOrigin(0, 30);
				break;
			default:
				break;
			}
		}

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



void Monster::FindPlayer(Player& player)
{
	if (!isFindPlayer)
	{
		if (findPlayerBox.getGlobalBounds().intersects(player.GetHitBox().getGlobalBounds()))
		{
			isFindPlayer = true;
			
			sprite.setOrigin(23.f, 47);		//고블린 뛸때 발 좌표가 23.f, 47임
			animation.Play("GoblinAttackerRun");
		}
	}
}

void Monster::ChasePlayer(Player&player, float dt)
{
	if (isFindPlayer&& !isAttackPlayer)
	{
		if (attackRangeBox.getGlobalBounds().intersects(player.GetHitBox().getGlobalBounds()))
		{
			sprite.setOrigin(20.f, 38);		//공격할때 고블린 발 끝 좌표 20,38
			animation.Play("GoblinAttackerAttack");
			isAttackPlayer = true;
		}

		if (!isAttackPlayer)
		{
			
			float h = player.GetPosition().x - sprite.getPosition().x;
			float v = 0.f;
			Vector2f dir(h, v);

			position += (Utils::Normalize(dir) * speed) * 2.f * dt;
			sprite.setPosition(position);

			findPlayerBox.setPosition(position);
			attackRangeBox.setPosition(position);
			hitBox.setPosition(position);

			if (h > 0)
			{
				sprite.setScale(-3.f, 3.f);	//플레이어가 몬스터 왼쪽에 있을때
				attackRangeBox.setOrigin(0, 30);
				findPlayerBox.setOrigin(0.f, 40.f);
			}
			else
			{
				sprite.setScale(3.f, 3.f);	//플레이어가 몬스터 오른쪽에 있을때
				attackRangeBox.setOrigin(30, 30);
				findPlayerBox.setOrigin(200.f, 40.f);
			}

			if (h * h > 500.f * 500.f)		//플레이어의 거리가 떨어지면 플레이어 추적하는거 취소
			{
				isFindPlayer = false;
			}
		}
	}
}

void Monster::Run(float dt)
{
}


void Monster::Attack(float dt, int atk, Player&player)
{
	if (isAttackPlayer)
	{
		attackDelay += dt;
		if (attackDelay > 1.5f)
		{
			//if(attackRangeBox.getGlobalBounds().intersects(player.GetHitBox().getGlobalBounds()));
			//{
			//	/*player.OnHitted();*/
			//}
			//여기에 함수 추가해서 플레이어 Onhitted 나 set 함수 써서 hp 깎이면 됨 ㅇ.
			attackDelay = 0.f;
			isAttackPlayer = false;
			sprite.setOrigin(23.f, 47);	//뛸 때 고블린 발 끝 좌표 20,38
			animation.Play("GoblinAttackerRun");
		}
	}
}

bool Monster::OnHitted(int atk)
{
	if(health > 0)
	{
		animation.Play(strDemageTaken);
		health -= atk;
		return true;
	}
}

void Monster::Gravity(float dt, std::vector<TestBlock*> blocks)
{
	
		fallingSpeed += GRAVITY_POWER * dt;
		if (fallingSpeed > 3000.f)
		{
			fallingSpeed = 3000.f;
		}
		position.y += fallingSpeed * dt;
		std::cout << position.y << std::endl;
		UpdateCollision(blocks);
	
}

void Monster::UpdateCollision(std::vector<TestBlock*> blocks)
{
	for (auto bk : blocks)
	{
		if (hitBox.getGlobalBounds().intersects(bk->GetBlockRect()))
		{
			isFalling = false;
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
				/*JumpingSpeed = START_JUMP_SPEED;*/
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
			sprite.setPosition(pos);
			hitBox.setPosition(pos);
			position = pos;
		}
		/*else
		{
			isFalling = true;
		}*/
	}
}

void Monster::Update(Player& player,float dt, std::vector<TestBlock*> blocks)
{
	animation.Update(dt);
	Walk(dt);
	FindPlayer(player);
	ChasePlayer(player,dt);
	Attack(dt, atk, player);
	Gravity(dt, blocks);
}


void Monster::Draw(RenderWindow* window)
{
	window->draw(findPlayerBox);
	window->draw(attackRangeBox);
	window->draw(hitBox);
	window->draw(sprite);
	
}

