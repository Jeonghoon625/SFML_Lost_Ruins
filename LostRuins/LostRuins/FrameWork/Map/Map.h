#pragma once

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <string>
#include <vector>
#include "../Scene/Scene.h"
#include "../Mgr/TextureHolder.h"
#include "../Object/Player/Player.h"
#include "../Object/Monster/Monster.h"
#include "../Object/Monster/ZombieCrawler.h"
#include "../Object/Monster/ZombieWalker.h"
#include "../Object/CollisionBlock/CollisionBlock.h"

using namespace sf;

//enum class AnimationLoopType
//{
//	Single,
//	Loop,
//};

//struct AnimationFrame
//{
//	Texture* texture;
//	IntRect texCoord;
//
//	AnimationFrame(Texture& tex, const IntRect& coord);
//};

struct Map
{
	std::string mapId;
	int mapWidth;
	int mapHeight;
};

