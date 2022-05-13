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

	Image Idle;
	Image Idle2;
	
	float eyeSpeed;

	float a = 1.f;
	float upY;
	float downY;
	float prevY;
	float updateY;

	Vector2f prevLeftEyePos;
public:
	LamiEye();
	void Init(Vector2f pos, int eyeSide, Sprite& sprite);
	void Update(Sprite& sprite, Player& player, float dt);
	void Draw(RenderWindow* window);
};

