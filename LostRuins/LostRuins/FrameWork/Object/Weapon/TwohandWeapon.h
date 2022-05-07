#pragma once
#include <SFML/Graphics.hpp>
#include "../../Mgr/TextureHolder.h"

using namespace sf;

class TwohandWeapon
{
private:
	Sprite spriteWeapon;
	Vector2f position;
	float rotation;

public:
	TwohandWeapon(float xpos, float ypos, float angle);
	void SetPosition(Sprite sprite);
	const Sprite GetSprite();
	const Vector2f GetPosition();
	const float GetRotation();
};

