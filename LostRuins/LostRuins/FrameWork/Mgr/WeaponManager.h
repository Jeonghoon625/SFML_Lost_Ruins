#pragma once
#include <SFML/Graphics.hpp>
#include <algorithm>
#include "../Object/Weapon/TwohandWeapon.h"
#include "../Object/Weapon/Dagger.h"

using namespace sf;
using namespace std;

enum class WeaponType
{
	DAGGER,
	ONE_HANDED,
	TWO_HANDED,
};

class WeaponManager
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

	WeaponType currentWeapon;
	Sprite sprite;

	int isFps;
	int maxFps;
	int delay;

	vector <TwohandWeapon*> twoHanded;
	vector <Dagger*> daggers;

public:
	void Init();
	void AttackWeapon(WeaponType weaponType);
	void SetWeaponPosition(Sprite sprite);
	void Draw(RenderWindow* window, View* mainView);

	int GetAttackPoint();
	int GetHitFrame();
	float GetAttackFps();
	bool CheckFps();
	bool CheckDelay();
	int GetFps();
	void NextFps();
	void ResetFps();
	Sprite GetSprite();

	~WeaponManager();
	void TwohandWeaponInit();
	void DaggerWeaponInit();
};

