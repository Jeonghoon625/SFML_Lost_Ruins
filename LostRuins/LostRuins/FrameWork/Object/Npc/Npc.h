#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include <cstdlib>
#include "../../Animation/AnimationController.h"
#include "../../Mgr/TextureHolder.h"
#include "../../Mgr/Utils.h"
#include "../../Animation/rapidcsv.h"

using namespace sf;

class Npc
{
private:
	const Vector2f scale = Vector2f(1.f, 1.f);

	AnimationController animationNpc;

	Vector2f positionNpc;

	Vector2f lastDirNpc;

	Texture textureNpc;
	Sprite spriteNpc;
	
	Vector2i resolustionNpc;
	IntRect gameMapNpc;

	std::map<std::string, Texture> texmap;

	int tileSizeNpc;

public:
	void Spawn(IntRect gameMap, Vector2i res, int tileSize);

	FloatRect GetGobalBound() const;
	Vector2f GetPosition() const;
	Sprite GetSprite() const;	

	void Init();
	void Update(float dt);
	void Draw(RenderWindow* window);

	void AnimationInit();
};

