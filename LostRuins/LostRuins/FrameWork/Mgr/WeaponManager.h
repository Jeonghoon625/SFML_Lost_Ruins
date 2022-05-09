#pragma once
#include <SFML/Graphics.hpp>
#include <algorithm>
#include "../Object/Weapon/TwohandWeapon.h"

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
	const int MAX_TWO_HANDED_FPS = 17;
	const int TWO_HANDED_DELAY = 3;

	const float TWO_HANDED_ATTACK_FPS = 0.05f;

	WeaponType currentWeapon;
	Sprite sprite;

	int isFps;
	int maxFps;
	int delay;

	vector <TwohandWeapon*> twoHanded;

public:
	void Init();
	void AttackWeapon(WeaponType weaponType);
	void SetWeaponPosition(Sprite sprite);
	void Draw(RenderWindow* window, View* mainView);

	int GetAttackPoint();
	float GetAttackFps();
	bool CheckFps();
	bool CheckDelay();
	void NextFps();
	void ResetFps();
	Sprite GetSprite();

	~WeaponManager();
	void TwohandWeaponInit();
};

