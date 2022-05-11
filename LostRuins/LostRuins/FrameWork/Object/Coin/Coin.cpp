#include "Coin.h"
#include<iostream>

void Coin::Init()
{
	textureCoin = TextureHolder::GetTexture("graphics/goldcoin.png");

	spriteCoin.setOrigin(12.5f, 54.0f);
	spriteCoin.setScale(1.5f, 1.5f);
	AnimationInit();
	Spawn(gameMapCoin, resolustionCoin, tileSizeCoin);
	animationCoin.Play("Gold");
}

void Coin::Update(float dt, std::vector<TestBlock*> blocks)
{
	animationCoin.Update(dt);
	animationCoin.PlayQueue("Gold");
	spriteCoin.setPosition(spriteCoin.getPosition().x, positionCoin.y);
	Gravity(dt, blocks);
}

void Coin::Draw(RenderWindow* window)
{
	window->draw(spriteCoin);
}

void Coin::Gravity(float dt, std::vector<TestBlock*> blocks)
{
	if (isFalling)
	{
		fallingSpeed += GRAVITY_POWER * dt;
		if (fallingSpeed > 3000.f)
		{
			fallingSpeed = 3000.f;
		}
		positionCoin.y += fallingSpeed * dt;
	}

	UpdateCollision(blocks);
}

void Coin::UpdateCollision(std::vector<TestBlock*> blocks)
{
	isFalling = true;
	isCollideCoin = false;
	for (auto bk : blocks)
	{
		if (spriteCoin.getGlobalBounds().intersects(bk->GetBlockRect()))
		{
			float blockUp = bk->GetBlockRect().top;
			float blockLeft = bk->GetBlockRect().left;
			float blockRight = bk->GetPosition().x + bk->GetBlockRect().width * 0.5f;
			float coinDown = spriteCoin.getPosition().y;

			float coinXpos = spriteCoin.getPosition().x;
			float coinYpos = spriteCoin.getPosition().y - spriteCoin.getGlobalBounds().height * 0.5f;

			Vector2f pos = spriteCoin.getPosition();

			isCollideCoin = true;

			// 블럭 CT에 플레이어가 충돌
			if (blockUp > coinXpos && blockLeft < coinXpos && blockRight > coinXpos)
			{
				pos.y = blockUp;
				isFalling = false;
				fallingSpeed = 0.f;
			}

			spriteCoin.setPosition(pos);
			positionCoin = pos;
			spriteCoin.setPosition(pos);
		}
	}
}

void Coin::Spawn(IntRect gameMap, Vector2i res, int tileSize)
{
	this->gameMapCoin = gameMap;
	resolustionCoin = res;
	this->tileSizeCoin = tileSize;
	positionCoin.x = 1000.f;
	positionCoin.y = 736.f;
	spriteCoin.setPosition(positionCoin);
}

FloatRect Coin::GetGobalBound() const
{
	return spriteCoin.getGlobalBounds();
}

Vector2f Coin::GetPosition() const
{
	return positionCoin;
}

Sprite Coin::GetSprite() const
{
	return spriteCoin;
}


void Coin::AnimationInit()
{
	animationCoin.SetTarget(&spriteCoin);

	rapidcsv::Document clips("data_tables/animations/coin/COIN_animation_clips.csv");
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
		animationCoin.AddClip(clip);
	}
}