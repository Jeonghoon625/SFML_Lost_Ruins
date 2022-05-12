#include "LamiHand.h"

LamiHand::LamiHand()
{
	AnimationInit(&sprite);
	animation.Play(strIdle);
}

void LamiHand::Init(Vector2f pos, int handSide)
{
	strIdle = "Lami2HandIdle";
	strNearAttack = "Lami2HandAttackNear";
	strNearAttackToIdle = "Lami2HandAttackNearToIdle";
	strMiddleAttack = "Lami2HandAttackMiddle";
	strMiddleAttackToIdle = "Lami2HandAttackMiddleToIdle";
	strFarAttack = "Lami2HandAttackFar";
	strFarAttackToIdle = "Lami2HandAttackFarToIdle";
	strDiving = "Lami2HandDiving";
	strReappearing = "Lami2HandReappearing";
	strReappearingToIdle = "Lami2HandReappearingToIdle";

	sprite.setOrigin(80.f,31.f);
	sprite.setPosition(pos);
	
	if (handSide == 0)
	{
		sprite.setScale(3.f, 3.f);
	}
	else
	{
		sprite.setScale(-3.f, 3.f);
	}
	
}

void LamiHand::Update(float dt, Vector2f pos)
{
	sprite.setPosition(pos);
	animation.Update(dt);
}

void LamiHand::Draw(RenderWindow* window)
{
	window->draw(sprite);
}

void LamiHand::AnimationInit(Sprite* sprite)
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
