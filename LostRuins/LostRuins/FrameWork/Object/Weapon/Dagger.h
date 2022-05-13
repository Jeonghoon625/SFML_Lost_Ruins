#pragma once
#include <SFML/Graphics.hpp>
#include "../../Mgr/TextureHolder.h"

using namespace sf;

class Dagger
{
private:
	const Vector2f scale = Vector2f(1.f, 1.f);
	const Vector2f scaleFlipX = Vector2f(-1.f, 1.f);

	Sprite spriteWeapon;
	Vector2f position;
	float rotation;

public:
	Dagger(float xpos, float ypos, float angle);
	void SetPosition(Sprite sprite);
	const Sprite GetSprite();
	const Vector2f GetPosition();
	const float GetRotation();
};

