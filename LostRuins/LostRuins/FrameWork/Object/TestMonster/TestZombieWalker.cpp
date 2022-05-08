#include "TestZombieWalker.h"

TestZombieWalker::TestZombieWalker(float xpos, float ypos)
{
	health = START_HEALTH;
	speed = START_SPEED;
	position = Vector2f(xpos, ypos);

	texture = TextureHolder::GetTexture("graphics/TestZombieWalker.png");

	sprite.setOrigin(21.5f, 50.f);
	sprite.setScale(scale);
	AnimationInit();
	animation.Play("Zw_Idle");
	sprite.setPosition(position);

	hitBox.setFillColor(Color(153, 153, 153, 80));
	hitBox.setSize(Vector2f(43.f, 50.f));
	hitBox.setOrigin(hitBoxOrigin);
	hitBox.setScale(scale);
	hitBox.setPosition(position);
}

void TestZombieWalker::Update(float dt, Vector2f playerPos, std::vector <TestBlock*> blocks)
{
	if (sprite.getScale().x > 0.f)
	{
		position.x += 1.f * speed * dt;
	}
	else
	{
		position.x += -1.f * speed * dt;
	}
	sprite.setPosition(position);
	hitBox.setPosition(position);

	UpdateCollision(blocks);
	animation.Play("Zw_Idle");
}

bool TestZombieWalker::OnHitted()
{
	return false;
}

bool TestZombieWalker::GetAlive()
{
	return false;
}

Sprite TestZombieWalker::GetSprite()
{
	return sprite;
}

RectangleShape TestZombieWalker::GetHitBox()
{
	return hitBox;
}

void TestZombieWalker::AnimationInit()
{
	animation.SetTarget(&sprite);

	rapidcsv::Document clips("data_tables/animations/testMonster/monster_animation_clips.csv");
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

void TestZombieWalker::UpdateCollision(std::vector<TestBlock*> blocks)
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

			float monsterUp = hitBox.getPosition().y - hitBox.getGlobalBounds().height;
			float monsterDown = hitBox.getPosition().y;
			float monsterLeft = hitBox.getGlobalBounds().left;
			float monsterRight = hitBox.getPosition().x + hitBox.getGlobalBounds().width * 0.5f;

			float monsterXpos = hitBox.getPosition().x;
			float monsterYpos = hitBox.getPosition().y - hitBox.getGlobalBounds().height * 0.5f;
			Vector2f pos = hitBox.getPosition();

			// 블럭 CB에 몬스터가 충돌
			if (blockDown < monsterYpos && blockLeft < monsterXpos && blockRight > monsterXpos)
			{
				pos.y = blockDown + hitBox.getGlobalBounds().height;
			}
			// 블럭 LB에 몬스터가 충돌
			if (blockDown < monsterYpos && blockLeft > monsterXpos && blockDown < monsterYpos)
			{
				if (abs(blockLeft - monsterRight) > abs(blockDown - monsterUp))
				{
					pos.y = blockDown + hitBox.getGlobalBounds().height;
				}
				else if (abs(blockLeft - monsterRight) < abs(blockDown - monsterUp))
				{
					pos.x = blockLeft - hitBox.getGlobalBounds().width * 0.5f;
				}
				else
				{
					pos.x -= abs(blockLeft - monsterRight);
					pos.y -= abs(blockDown - monsterUp);
				}
			}
			// 블럭 RB에 몬스터가 충돌
			if (blockDown < monsterYpos && blockRight < monsterXpos && blockDown < monsterYpos)
			{
				if (abs(blockRight - monsterLeft) > abs(blockDown - monsterUp))
				{
					pos.y = blockDown + hitBox.getGlobalBounds().height;
				}
				else if (abs(blockRight - monsterLeft) < abs(blockDown - monsterUp))
				{
					pos.x = blockRight + hitBox.getGlobalBounds().width * 0.5f;
				}
				else
				{
					pos.x += abs(blockRight - monsterLeft);
					pos.y -= abs(blockDown - monsterUp);
				}
			}
			// 블럭 CT에 몬스터가 충돌
			if (blockUp > monsterYpos && blockLeft < monsterXpos && blockRight > monsterXpos)
			{
				pos.y = blockUp + 1.f;
			}
			// 블럭 LT에 플레이어가 충돌
			if (blockUp > monsterYpos && blockLeft > monsterXpos && blockUp > monsterYpos)
			{
				if (abs(blockLeft - monsterRight) > abs(blockUp - monsterDown))
				{
					pos.y = blockUp + 1.f;
				}
				else if (abs(blockLeft - monsterRight) < abs(blockUp - monsterDown))
				{
					pos.x = blockLeft - hitBox.getGlobalBounds().width * 0.5f;
				}
				else
				{
					pos.x -= abs(blockLeft - monsterRight);
					pos.y -= abs(blockUp - monsterDown);
					pos.y += 1.f;
				}
			}
			// 블럭 RT에 플레이어가 충돌
			if (blockUp > monsterYpos && blockRight < monsterXpos && blockUp > monsterYpos)
			{
				if (abs(blockRight - monsterLeft) > abs(blockUp - monsterDown))
				{
					pos.y = blockUp + 1.f;
				}
				else if (abs(blockRight - monsterLeft) < abs(blockUp - monsterDown))
				{
					pos.x = blockRight + hitBox.getGlobalBounds().width * 0.5f;
				}
				else
				{
					pos.x -= abs(blockRight - monsterLeft);
					pos.y -= abs(blockUp - monsterDown);
					pos.y += 1.f;
				}
			}
			// 블럭 LC에 플레이어가 충돌
			if (blockLeft > monsterXpos && blockUp < monsterYpos && blockDown > monsterYpos)
			{
				pos.x = blockLeft - hitBox.getGlobalBounds().width * 0.5f;
			}
			// 블럭 RC에 플레이어가 충돌
			if (blockRight < monsterXpos && blockUp < monsterYpos && blockDown > monsterYpos)
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
		float revers = sprite.getScale().x * -1.f;
		if (sprite.getScale().x > 0.f)
		{
			sprite.setPosition(position.x + 3.f, position.y);
		}
		else if (sprite.getScale().x < 0.f)
		{
			sprite.setPosition(position.x - 3.f, position.y);
		}
		sprite.setScale(Vector2f(revers, sprite.getScale().y));
	}
}