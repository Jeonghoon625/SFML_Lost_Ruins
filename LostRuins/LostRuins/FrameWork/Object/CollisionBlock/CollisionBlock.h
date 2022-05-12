#pragma once
#include <SFML/Graphics.hpp>
#include "../../Mgr/TextureHolder.h"

using namespace sf;

class CollisionBlock
{
private:
	Vector2f position;
	FloatRect blockRect;
	RectangleShape blockShape;
	Texture texture;
public:
	CollisionBlock(float centerX, float centerY, float width, float height);
	CollisionBlock(FloatRect getGlobalBounds, Vector2u mousePosGrid);

	const Vector2f GetPosition();
	const FloatRect GetBlockRect();
	const RectangleShape GetBlockShape();
};

