#include "FireArrow.h"

FireArrow::FireArrow()
	: speed(DEFAULT_SPEED), isActive(false), isDirection(true)
{
	texture = TextureHolder::GetTexture("graphics/fire.png");
	sprite.setTexture(texture);
	AnimationInit();
	sprite.setOrigin(16.f, 0.f);
	animation.Play("FireArrow");
}

void FireArrow::Spell(Vector2f pos, Sprite sprite)
{
	SetActive(true);

	distance = 0.f;
	float xpos = 0.f;
	float ypos = sprite.getGlobalBounds().top + sprite.getGlobalBounds().height * 0.5f;
	if (sprite.getScale().x > 0.f)
	{
		this->sprite.setRotation(-90.f);
		xpos = sprite.getGlobalBounds().left + sprite.getGlobalBounds().width;
		isDirection = true;
	}
	else if (sprite.getScale().x < 0.f)
	{
		this->sprite.setRotation(90.f);
		xpos = sprite.getGlobalBounds().left;
		isDirection = false;
	}

	this->sprite.setPosition(Vector2f(xpos, ypos));
}

void FireArrow::Update(float dt)
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

	distance += speed * dt;
	if (distance > DEFAULT_DISTANCE)
	{
		Stop();
	}
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
