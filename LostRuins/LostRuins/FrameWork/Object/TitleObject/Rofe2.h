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

class Rofe2
{
private:
	const Vector2f scale = Vector2f(3.f, 3.f);

	AnimationController animationRofe2;

	Vector2f positionRofe2;

	Vector2f lastDirRofe2;

	Texture textureRofe2;
	Sprite spriteRofe2;

	Vector2i resolustionRofe2;
	IntRect gameMapRofe2;

	std::map<std::string, Texture> texmap;

	int tileSizeRofe2;

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