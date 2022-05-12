#pragma once
#include <SFML/Graphics.hpp>
#include "../../Mgr/TextureHolder.h"
#include "../../Animation/AnimationController.h"
#include "../../Animation/rapidcsv.h"
#include "../TestBlock/TestBlock.h"

using namespace sf;

class FireArrow
{
private:
	const float DEFAULT_SPEED = 700.f;
	const float DEFAULT_DISTANCE = 1000.f;

	AnimationController animation;

	Texture texture;
	Sprite sprite;

	bool isActive;
	bool isDirection;
	
	Vector2f position;
	float speed;
	float distance;

	std::map<std::string, Texture> texmap;
	static bool isLoading;
	static AnimationClip clip;

public:
	FireArrow();
	void Spell(Vector2f pos, bool dir);
	void Update(float dt);
	void SetActive(bool active);

	void Stop();
	bool IsActive();
	Sprite GetSprite();

	void AnimationInit();

};

