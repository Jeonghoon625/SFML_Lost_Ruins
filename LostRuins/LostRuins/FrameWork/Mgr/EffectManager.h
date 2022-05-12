#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "../Object/Effect/Blood.h"
#include "../Object/Effect/Explosion.h"

using namespace sf;

class EffectManager
{
private:
	const int MAX_BLOOD_CACHE_SIZE = 50;
	const int MAX_EXPLOSION_CACHE_SIZE = 50;

	bool isDirection;

	std::list<Blood*> unuseBlood;
	std::list<Blood*> useBlood;
	std::list<Explosion*> unuseExplosion;
	std::list<Explosion*> useExplosion;

public:
	void Init();
	void Update(float dt);
	void Draw(RenderWindow* window);

	void HitActor(Sprite sprite);
	void HitExplosion(Vector2f pos);

};

