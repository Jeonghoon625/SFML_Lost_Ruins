#pragma once
#include <SFML/Graphics.hpp>
#include "LamiPhaseTwo.h"

using namespace sf;

class LamiEye
{
private:
	Sprite spriteEye;
	Sprite spriteSclera;
	int eyeSide;
public:
	LamiEye();
	void Init(Vector2f pos, int eyeSide, Sprite& sprite);
	void Update();
	void Draw();
};

