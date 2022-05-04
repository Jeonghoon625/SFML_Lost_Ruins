#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class TestBlock
{
private:
	Vector2f position;
	FloatRect blockRect;
	RectangleShape blockShape;

public:
	TestBlock(float left, float top, float width, float hight);
	const Vector2f GetPosition();
	const FloatRect GetBlockRect();
	const RectangleShape GetBlockShape();
};

