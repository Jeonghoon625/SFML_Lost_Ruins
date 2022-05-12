#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "../Object/Effect/Blood.h"

using namespace sf;

enum class effectType
{
	BLOOD,
	EXPLOSION,
};

class EffectManager
{
private:
	const int MAX_BLOOD_CACHE_SIZE = 50;

	bool isDirection;

	std::list<Blood*> unuseblood;
	std::list<Blood*> useblood;

public:
	void Init();
	void Update(float dt);
	void Draw(RenderWindow* window);

	void HitActor(Sprite sprite);

};

