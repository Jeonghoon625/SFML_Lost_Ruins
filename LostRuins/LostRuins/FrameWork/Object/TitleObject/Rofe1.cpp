#include "Rofe1.h"
#include <iostream>

void Rofe1::Spawn(IntRect gameMap, Vector2i res, int tileSize)
{
	this->gameMapRofe1 = gameMap;
	resolustionRofe1 = res;
	this->tileSizeRofe1 = tileSize;
	positionRofe1.x = 750;
	positionRofe1.y = 910;
	spriteRofe1.setPosition(positionRofe1);
}

FloatRect Rofe1::GetGobalBound() const
{
	return spriteRofe1.getGlobalBounds();
}

Vector2f Rofe1::GetPosition() const
{
	return positionRofe1;
}

Sprite Rofe1::GetSprite() const
{
	return spriteRofe1;
}

void Rofe1::Init()
{
	textureRofe1 = TextureHolder::GetTexture("graphics/rofe1.png");

	spriteRofe1.setOrigin(12.5f, 54.0f);
	spriteRofe1.setScale(scale);
	AnimationInit();
	Spawn(gameMapRofe1, resolustionRofe1, tileSizeRofe1);
	animationRofe1.Play("TitleRF1");
}

void Rofe1::Update(float dt)
{
	animationRofe1.Update(dt);
}

void Rofe1::Draw(RenderWindow* window)
{
	window->draw(spriteRofe1);
}

void Rofe1::AnimationInit()
{
	animationRofe1.SetTarget(&spriteRofe1);

	rapidcsv::Document clips("data_tables/animations/title/Title_animation_clips1.csv");
	std::vector<std::string>colld = clips.GetColumn<std::string>("ID");
	std::vector<int> colFps = clips.GetColumn<int>("FPS");
	std::vector<int> colLoop = clips.GetColumn<int>("LOOP TYPE(0:Single, 1:Loop)");
	std::vector<std::string> colPath = clips.GetColumn<std::string>("CLIP PATH");

	int totalClips = colld.size();
	for (int i = 0; i < totalClips; ++i)
	{
		AnimationClip clip;
		clip.id = colld[i];
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
		animationRofe1.AddClip(clip);
	}
}
