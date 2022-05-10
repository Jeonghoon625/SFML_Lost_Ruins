#include "Rofe2.h"
#include <iostream>

void Rofe2::Spawn(IntRect gameMap, Vector2i res, int tileSize)
{
	this->gameMapRofe2 = gameMap;
	resolustionRofe2 = res;
	this->tileSizeRofe2 = tileSize;
	positionRofe2.x = 1200;
	positionRofe2.y = 910;
	spriteRofe2.setPosition(positionRofe2);
}

FloatRect Rofe2::GetGobalBound() const
{
	return spriteRofe2.getGlobalBounds();
}

Vector2f Rofe2::GetPosition() const
{
	return positionRofe2;
}

Sprite Rofe2::GetSprite() const
{
	return spriteRofe2;
}

void Rofe2::Init()
{
	textureRofe2 = TextureHolder::GetTexture("graphics/rofe2.png");

	spriteRofe2.setOrigin(12.5f, 54.0f);
	spriteRofe2.setScale(scale);
	AnimationInit();
	Spawn(gameMapRofe2, resolustionRofe2, tileSizeRofe2);
	animationRofe2.Play("TitleRF2");
}

void Rofe2::Update(float dt)
{
	animationRofe2.Update(dt);
}

void Rofe2::Draw(RenderWindow* window)
{
	window->draw(spriteRofe2);
}

void Rofe2::AnimationInit()
{
	animationRofe2.SetTarget(&spriteRofe2);

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
		animationRofe2.AddClip(clip);
	}
}
