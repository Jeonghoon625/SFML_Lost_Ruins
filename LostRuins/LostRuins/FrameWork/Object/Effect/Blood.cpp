#include "Blood.h"

bool Blood::isLoading = false;
AnimationClip Blood::clip;

Blood::Blood()
	: time(DEFAULT_TIME), isActive(false), isDirection(true)
{
	AnimationInit();
	sprite.setOrigin(0.f, 25.f);
	animation.Play("Blood");
}

void Blood::Bleeding(Vector2f pos, bool dir)
{
	SetActive(true);

	time = DEFAULT_TIME;
	isDirection = dir;
	//position = pos;
	if (isDirection == true)
	{
		position.x = pos.x - 15.f;
		sprite.setScale(4.f, 4.f);
	}
	else if (isDirection == false)
	{
		position.x = pos.x + 15.f;
		sprite.setScale(-4.f, 4.f);
	}
	position.y = pos.y;

	sprite.setPosition(position);
}

void Blood::Update(float dt)
{
	// 시간 제한
	time -= dt;
	if (time < 0.f)
	{
		Stop();
	}
	animation.Update(dt);
}

void Blood::SetActive(bool active)
{
	isActive = active;
}

void Blood::Stop()
{
	SetActive(false);
}

bool Blood::IsActive()
{
	return isActive;
}

Sprite Blood::GetSprite()
{
	return sprite;
}

void Blood::AnimationInit()
{
	animation.SetTarget(&sprite);
	if (!isLoading)
	{
		rapidcsv::Document clips("data_tables/animations/effect/effect_animation_clips.csv");
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
