#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include <cstdlib>
#include "../../Animation/AnimationController.h"
#include "../../Mgr/TextureHolder.h"
#include "../../Mgr/Utils.h"
#include "../../Animation/rapidcsv.h"
#include "../TitleObject/Rofe2.h"

using namespace sf;

class Rofe1
{
private:
	const Vector2f scale = Vector2f(3.f, 3.f);

	AnimationController animationRofe1;

	Vector2f positionRofe1;

	Vector2f lastDirRofe1;

	Texture textureRofe1;
	Sprite spriteRofe1;

	Vector2i resolustionRofe1;
	IntRect gameMapRofe1;

	std::map<std::string, Texture> texmap;

	int tileSizeRofe1;

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

