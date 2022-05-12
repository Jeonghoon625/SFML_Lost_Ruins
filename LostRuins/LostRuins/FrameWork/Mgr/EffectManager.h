#pragma once
#include <SFML/Graphics.hpp>
#include <list>

using namespace sf;

enum class effectType
{
	BLOOD,
	EXPLOSION,
};

class EffectManager
{
private:
	const int MAX_BLOOD_CACHE_SIZE = 100;

	std::list<Blood*> unuseblood;
	std::list<Blood*> useblood;

public:
	void Init();
	void Update();
	void Draw(RenderWindow* window);

};

