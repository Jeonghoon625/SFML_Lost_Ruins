#include "EffectManager.h"

void EffectManager::Init()
{
	isDirection = true;

	for (int i = 0; i < MAX_BLOOD_CACHE_SIZE; i++)
	{
		unuseBlood.push_back(new Blood());
	}
	for (int i = 0; i < MAX_EXPLOSION_CACHE_SIZE; i++)
	{
		unuseExplosion.push_back(new Explosion());
	}
}

void EffectManager::Update(float dt)
{
	auto blood = useBlood.begin();
	while (blood != useBlood.end())
	{
		Blood* isBlood = *blood;
		isBlood->Update(dt);

		if (!isBlood->IsActive())
		{
			blood = useBlood.erase(blood);
		}
		else
		{
			++blood;
		}
	}

	auto explosion = useExplosion.begin();
	while (explosion != useExplosion.end())
	{
		Explosion* isExplosion = *explosion;
		isExplosion->Update(dt);

		if (!isExplosion->IsActive())
		{
			explosion = useExplosion.erase(explosion);
		}
		else
		{
			++explosion;
		}
	}
}

void EffectManager::Draw(RenderWindow* window)
{
	for (auto blood : useBlood)
	{
		window->draw(blood->GetSprite());
	}

	for (auto explosion : useExplosion)
	{
		window->draw(explosion->GetSprite());
	}
}

void EffectManager::HitActor(Sprite sprite)
{
	float xpos = sprite.getPosition().x;
	float ypos = sprite.getGlobalBounds().top + sprite.getGlobalBounds().height * 0.5f;
	Vector2f spawnPos = (Vector2f(xpos, ypos));
	if (sprite.getScale().x > 0.f)
	{
		isDirection = true;
	}
	else if (sprite.getScale().x < 0.f)
	{
		isDirection = false;
	}

	if (unuseBlood.empty())
	{
		for (int i = 0; i < MAX_BLOOD_CACHE_SIZE; ++i)
		{
			unuseBlood.push_back(new Blood());
		}
	}
	Blood* blood = unuseBlood.front();
	unuseBlood.pop_front();
	useBlood.push_back(blood);
	blood->Bleeding(spawnPos, isDirection);
}

void EffectManager::HitExplosion(Vector2f pos)
{
	Vector2f spawnPos = pos;
	if (unuseExplosion.empty())
	{
		for (int i = 0; i < MAX_EXPLOSION_CACHE_SIZE; ++i)
		{
			unuseExplosion.push_back(new Explosion());
		}
	}
	Explosion* explosion = unuseExplosion.front();
	unuseExplosion.pop_front();
	useExplosion.push_back(explosion);
	explosion->Exploding(spawnPos);
}
