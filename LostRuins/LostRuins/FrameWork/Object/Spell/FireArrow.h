#pragma once
#include <SFML/Graphics.hpp>
#include "../../Animation/AnimationController.h"
#include "../../Animation/rapidcsv.h"
#include "../../Object/TestBlock/TestBlock.h"
#include "../../Mgr/EffectManager.h"

using namespace sf;

class ZombieWalker;

class FireArrow
{
private:
	const int SPELL_DAMAGE = 10;
	const float DEFAULT_SPEED = 700.f;
	const float DEFAULT_DISTANCE = 800.f;

	AnimationController animation;

	Sprite sprite;

	bool isActive;
	bool isDirection;
	
	Vector2f position;
	int damage;
	float speed;
	float distance;

	std::map<std::string, Texture> texmap;
	static bool isLoading;
	static AnimationClip clip;

	ZombieWalker* zombie;
	EffectManager* effectMgr;

public:
	FireArrow(ZombieWalker* zombie, EffectManager* effectMgr);
	void Spell(Vector2f pos, bool dir);
	void Update(float dt, std::vector <TestBlock*> blocks, Time playTime);
	void SetActive(bool active);

	void Stop();
	bool IsActive();
	Sprite GetSprite();

	void AnimationInit();

};

