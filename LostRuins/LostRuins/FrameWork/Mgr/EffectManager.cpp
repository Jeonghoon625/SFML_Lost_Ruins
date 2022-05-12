#include "EffectManager.h"

void EffectManager::Init()
{
	isDirection = true;

	for (int i = 0; i < MAX_BLOOD_CACHE_SIZE; i++)
	{
		unuseblood.push_back(new Blood());
	}
}

void EffectManager::Update(float dt)
{
	auto blood = useblood.begin();
	while (blood != useblood.end())
	{
		Blood* isBlood = *blood;
		isBlood->Update(dt);

		if (!isBlood->IsActive())
		{
			blood = useblood.erase(blood);
		}
		else
		{
			++blood;
		}
	}
}

void EffectManager::Draw(RenderWindow* window)
{
	for (auto blood : useblood)
	{
		window->draw(blood->GetSprite());
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

	if (unuseblood.empty())
	{
		for (int i = 0; i < MAX_BLOOD_CACHE_SIZE; ++i)
		{
			unuseblood.push_back(new Blood());
		}
	}
	Blood* blood = unuseblood.front();
	unuseblood.pop_front();
	useblood.push_back(blood);
	blood->Bleeding(spawnPos, isDirection);
}
