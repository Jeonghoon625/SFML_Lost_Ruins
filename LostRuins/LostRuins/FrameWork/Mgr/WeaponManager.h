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
	const int MAX_TWO_HANDED_FPS = 16;

	WeaponType currentWeapon;
	int isFps;
	int maxFps;

	vector <TwohandWeapon*> twoHanded;

public:
	void Init();
	void SetSpritePosition(WeaponType weaponType, Sprite sprite, bool isDirection);
	void AttackWeapon(WeaponType weaponType);
	void Draw(RenderWindow* window, View* mainView);

	bool CheckFps();
	void NextFps();
	void ResetFps();
	void TwohandWeaponInit();
	~WeaponManager();
};

