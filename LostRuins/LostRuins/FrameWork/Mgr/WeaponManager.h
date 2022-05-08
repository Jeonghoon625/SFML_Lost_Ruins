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
	Sprite sprite;

	int isFps;
	int maxFps;

	vector <TwohandWeapon*> twoHanded;

public:
	void Init();
	void SetSpritePosition(WeaponType weaponType, Sprite sprite);
	void AttackWeapon(WeaponType weaponType);
	void Draw(RenderWindow* window, View* mainView);

	bool CheckFps();
	void NextFps();
	void ResetFps();
	Sprite GetSprite();

	void TwohandWeaponInit();
	~WeaponManager();
};

