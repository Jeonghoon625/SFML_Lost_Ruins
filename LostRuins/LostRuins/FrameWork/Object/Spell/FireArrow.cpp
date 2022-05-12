#include "FireArrow.h"
#include "../../Object/Monster/ZombieWalker.h"

bool FireArrow::isLoading = false;
AnimationClip FireArrow::clip;

FireArrow::FireArrow(ZombieWalker* zombie, EffectManager* effectMgr)
	: damage(SPELL_DAMAGE), speed(DEFAULT_SPEED), isActive(false), isDirection(true)
{
	this->zombie = zombie;
	this->effectMgr = effectMgr;

	AnimationInit();
	sprite.setOrigin(16.f, 55.f);
	animation.Play("FireArrow");
}

void FireArrow::Spell(Vector2f pos, bool dir)
{
	SetActive(true);

	distance = 0.f;
	isDirection = dir;
	position = pos;
	if (isDirection == true)
	{
		sprite.setRotation(-90.f);
	}
	else if (isDirection == false)
	{
		sprite.setRotation(90.f);
	}

	sprite.setPosition(position);
}

void FireArrow::Update(float dt, std::vector <TestBlock*> blocks, Time playTime)
{
	if (isDirection == true)
	{
		position.x += 1.f * speed * dt;
	}
	else if (isDirection == false)
	{
		position.x -= 1.f * speed * dt;
	}
	sprite.setPosition(position);

	// 寒 面倒
	for (auto bk : blocks)
	{
		if (sprite.getGlobalBounds().intersects(bk->GetBlockRect()))
		{
			effectMgr->HitExplosion(position);
			Stop();
		}
	}

	// 利 面倒
	if (sprite.getGlobalBounds().intersects(zombie->GetHitBox().getGlobalBounds()))
	{
		effectMgr->HitExplosion(position);
		zombie->OnHitted(damage, dt, playTime);
		Stop();
	}

	// 芭府 力茄
	distance += speed * dt;
	if (distance > DEFAULT_DISTANCE)
	{
		Stop();
	}
	animation.Update(dt);
}

void FireArrow::SetActive(bool active)
{
	isActive = active;
}

void FireArrow::Stop()
{
	SetActive(false);
}

bool FireArrow::IsActive()
{
	return isActive;
}

Sprite FireArrow::GetSprite()
{
	return sprite;
}

void FireArrow::AnimationInit()
{
	animation.SetTarget(&sprite);
	if (!isLoading)
	{
		rapidcsv::Document clips("data_tables/animations/magic/magic_animation_clips.csv");
		std::vector<std::string> colId = clips.GetColumn<std::string>("ID");
		std::vector<int> colFps = clips.GetColumn<int>("FPS");
		std::vector<int> colLoop = clips.GetColumn<int>("LOOP TYPE(0:Single, 1:Loop)");
		std::vector<std::string> colPath = clips.GetColumn<std::string>("CLIP PATH");

		int totalClips = colId.size();
		for (int i = 0; i < totalClips; ++i)
		{
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
			isLoading = true;
		}
	}
	animation.AddClip(clip);
}