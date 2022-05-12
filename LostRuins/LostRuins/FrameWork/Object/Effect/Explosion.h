#pragma once
#include <SFML/Graphics.hpp>
#include "../../Animation/AnimationController.h"
#include "../../Animation/rapidcsv.h"

using namespace sf;

class Explosion
{
private:
	const float DEFAULT_TIME = 0.5f;

	AnimationController animation;

	Sprite sprite;

	bool isActive;

	Vector2f position;
	float time;

	std::map<std::string, Texture> texmap;
	static bool isLoading;
	static AnimationClip clip;

public:
	Explosion();
	void Exploding(Vector2f pos);
	void Update(float dt);
	void SetActive(bool active);

	void Stop();
	bool IsActive();
	Sprite GetSprite();

	void AnimationInit();

};

