#pragma once
#include <SFML/Graphics.hpp>
#include "../../Mgr/TextureHolder.h"

using namespace sf;

class TestBlock
{
private:
	Vector2f position;
	FloatRect blockRect;
	RectangleShape blockShape;
	Texture texture;
public:
	TestBlock(float left, float top, float width, float hight);
	TestBlock(FloatRect getGlobalBounds, Vector2u mousePosGrid);
	const Vector2f GetPosition();
	const FloatRect GetBlockRect();
	const RectangleShape GetBlockShape();
};

