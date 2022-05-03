#include "Monster.h"
#include "../../FrameWork/Mgr/Utils.h"
#include "../../FrameWork/Mgr/TextureHolder.h"

Monster::Monster()
	:health(20), atk(3), speed(50.f), nextMove(0.f), checkTime(0.f)
{
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;
	sprite.setOrigin(16.25f, 47);
	sprite.setTextureRect(IntRect(0, 0, 40, 40));
	sprite.setPosition(resolution.x*0.5f, resolution.y*0.5f);
	position = sprite.getPosition();
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

void Monster::SetHealth(int damage)
{
	health -= damage;
}

void Monster::MonsterInit()
{
	AnimationInit(&sprite);
	// 이동
	
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
	animation.Play("GoblinAttackerIdle");
}

void Monster::Walk(float dt)
{
	checkTime += dt;
	if (checkTime > 3.f)
	{
		nextMove = Utils::RandomRange(-1, 2);	//-1이면 오른쪽 0이면 멈춤 1이면 왼쪽
		switch (nextMove)
		{
		case -1:
			sprite.setScale(1.f, 1.f);
			animation.Play("GoblinAttackerWalk");
			break;
		case 0:
			animation.Play("GoblinAttackerIdle");
			break;
		case 1:
			sprite.setScale(-1.f, 1.f);
			animation.Play("GoblinAttackerWalk");
			break;
		default:
			break;
		}
		checkTime = 0;
	
	}
	float h = (float)nextMove;
	float v = 0.f;
	Vector2f dir(h, v);

	position += Utils::Normalize(dir) * speed * dt;

	sprite.setPosition(position);

	// 회전
	
}

void Monster::Run(float dt)
{

}

void Monster::Attack(float dt, int atk)
{
}

void Monster::Update(float dt)
{
	animation.Update(dt);
}

void Monster::Draw(RenderWindow* window)
{
	window->draw(sprite);
}

