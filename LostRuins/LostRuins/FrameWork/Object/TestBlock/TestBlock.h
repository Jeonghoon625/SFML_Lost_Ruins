#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class TestBlock
{
private:
	FloatRect blockRect;
	RectangleShape blockShape;

public:
	TestBlock(float left, float top, float width, float hight);
	const FloatRect GetBlockRect();
	const RectangleShape GetBlockShape();
};

