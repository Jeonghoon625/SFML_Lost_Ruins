#pragma once
#include <SFML/Graphics.hpp>
#include "../Player/Player.h"
#include "LamiHand.h"

using namespace sf;

class LamiEye
{
private:
	Sprite spriteEye;
	Sprite spriteSclera;
	int eyeSide;

	Image Idle;
	Image Idle2;

	Lami2Status currentStatus;
	
	float eyeSpeed;

	float a;
	float upY;
	float downY;
	float prevY;
	float updateY;

	Vector2f prevLeftEyePos;
public:
	LamiEye();
	void Init(int eyeSide, Sprite& sprite);
	void Update(Sprite& sprite, Player& player, float dt, RectangleShape& hitBox);
	void Draw(RenderWindow* window);

	void SetStatus(Lami2Status newStatus, Sprite& sprite);
};

