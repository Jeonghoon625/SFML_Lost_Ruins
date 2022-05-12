#pragma once
#include <SFML/Graphics.hpp>
#include "../../Animation/AnimationController.h"
#include "../../Animation/rapidcsv.h"

using namespace sf;

class Blood
{
private:
	const float DEFAULT_TIME = 0.7f;

	AnimationController animation;

	Sprite sprite;

	bool isActive;
	bool isDirection;

	Vector2f position;
	float time;

	std::map<std::string, Texture> texmap;
	static bool isLoading;
	static AnimationClip clip;

public:
	Blood();
	void Bleeding(Vector2f pos, bool dir);
	void Update(float dt);
	void SetActive(bool active);

	void Stop();
	bool IsActive();
	Sprite GetSprite();

	void AnimationInit();

};

