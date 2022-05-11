#pragma once
#include<SFML/Graphics.hpp>
#include <sstream>
#include "../../Mgr/Utils.h"

using namespace sf;

class DamageAndRecovery
{
private:
	Font fontLostRuins;
	const float MASSAGE_SPEED = 100.f;
	const float DEFAULT_DISTANCE = 70.f;

	bool isActive;

	Text textDorR;

	Vector2f postion;
	float speed;
	float distance;

public:
	DamageAndRecovery();

	void SetActive(bool active);
	bool IsActive();
	void HitPlayer(Vector2f pos, int damage);
	void Stop();

	void Update(float dt);
	Text GetText();
};