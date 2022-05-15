#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <algorithm>
#include <list>
#include "../Mgr/SoundHolder.h"
#include "../Object/CollisionBlock/CollisionBlock.h"
#include "../Object/Weapon/TwohandWeapon.h"
#include "../Object/Weapon/Dagger.h"
#include "../Object/Spell/FireArrow.h"
#include "../Mgr/EffectManager.h"

using namespace sf;
using namespace std;

class CollisionBlock;
class ZombieWalker;

enum class AttackType
{
	DAGGER,
	TWO_HANDED,
	FIRE_ARROW,
};

class AttackManager
{
private:
	const int MAX_DAGGER_FPS = 12;
	const int DAGGER_DELAY = 3;
	const int MAX_TWO_HANDED_FPS = 17;
	const int TWO_HANDED_DELAY = 3;

	const int DAGGER_HIT_FRAME = 9;
	const int TWO_HANDED_HIT_FRAME = 10;
	const float DAGGER_ATTACK_FPS = 0.03f;
	const float TWO_HANDED_ATTACK_FPS = 0.04f;

	const int SPELL_COST_FIRE_ARROW = 4;

	const int MAX_SPELL_CACHE_SIZE = 50;
	const float FIRE_ARROW_CAST_TIME = 0.8f;

	AttackType currentAtkType;
	Sprite sprite;

	SoundBuffer soundDagger;
	SoundBuffer soundTwoHanded;

	Sound soundWeapon;

	int isFps;
	int maxFps;
	int cost;
	int delay;

	bool isDirection;

	vector <TwohandWeapon*> twoHanded;
	vector <Dagger*> daggers;

	std::list<FireArrow*> unuseSpell;
	std::list<FireArrow*> useSpell;

	ZombieWalker* zombie;
	EffectManager* effectMgr;

public:
	void Init(ZombieWalker* zombie, EffectManager* effectMgr);
	void Update(float dt, std::vector <CollisionBlock*> blocks, Time playTime);
	void WeaponDraw(RenderWindow* window, View* mainView);
	void SpellDraw(RenderWindow* window);

	void SetAttackType(AttackType attackType);
	void SetAttackPosition(Sprite sprite);
	void CastingSpell(Sprite sprite);
	void GetAttackSound();

	int GetAttackPoint();
	int GetHitFrame();
	float GetAttackFps();
	bool CheckFps();
	bool CheckDelay();
	int GetFps();
	void NextFps();
	void ResetFps();
	Sprite GetSprite();

	int PaySpellCost();

	~AttackManager();
	void TwohandWeaponInit();
	void DaggerWeaponInit();

};

