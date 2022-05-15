#include "Npc.h"
#include <iostream>

void Npc::Init()
{
	textureNpc = TextureHolder::GetTexture("graphics/npc1.png");

	spriteNpc.setOrigin(12.5f, 54.0f);
	spriteNpc.setScale(scale);	
	AnimationInit();
	Spawn(gameMapNpc, resolustionNpc, tileSizeNpc);
	animationNpc.Play("Idle");
	positionNpc.x = 1680.f;
	positionNpc.y = 736.f;
	spriteNpc.setPosition(positionNpc);
}

void Npc::Spawn(IntRect gameMap, Vector2i res, int tileSize)
{
	this->gameMapNpc = gameMap;
	resolustionNpc = res;
	this->tileSizeNpc = tileSize;
	positionNpc.x = 1680.f;
	positionNpc.y = 736.f;
	spriteNpc.setPosition(positionNpc);
}

FloatRect Npc::GetGobalBound() const
{
	return spriteNpc.getGlobalBounds();
}

Vector2f Npc::GetPosition() const
{
	return positionNpc;
}

Sprite Npc::GetSprite() const
{
	return spriteNpc;
}

void Npc::Update(float dt)
{
	animationNpc.Update(dt);
	animationNpc.PlayQueue("Idle");
}

void Npc::Draw(RenderWindow* window)
{
	window->draw(spriteNpc);
}

void Npc::AnimationInit()
{
	animationNpc.SetTarget(&spriteNpc);

	rapidcsv::Document clips("data_tables/animations/npc/NPC_animation_clips2.csv");
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
		animationNpc.AddClip(clip);
	}	
}