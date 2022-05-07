#include "WeaponManager.h"

void WeaponManager::Init()
{
	isFps = 0;
	maxFps = 0;

	TwohandWeaponInit();
}

void WeaponManager::SetSpritePosition(WeaponType weaponType, Sprite sprite)
{
	switch (weaponType)
	{
	case WeaponType::DAGGER:
		break;
	case WeaponType::ONE_HANDED:
		break;
	case WeaponType::TWO_HANDED:
		maxFps = MAX_TWO_HANDED_FPS;
		for (auto spriteWeapon : twoHanded)
		{
			spriteWeapon->SetPosition(sprite);
		}
		break;
	}
}

void WeaponManager::AttackWeapon(WeaponType weaponType)
{
	switch (weaponType)
	{
	case WeaponType::DAGGER:
		currentWeapon = WeaponType::DAGGER;
		break;
	case WeaponType::ONE_HANDED:
		currentWeapon = WeaponType::ONE_HANDED;
		break;
	case WeaponType::TWO_HANDED:
		currentWeapon = WeaponType::TWO_HANDED;
		break;
	}
}

void WeaponManager::Draw(RenderWindow* window, View* mainView)
{
	window->setView(*mainView);

	switch (currentWeapon)
	{
	case WeaponType::DAGGER:
		break;
	case WeaponType::ONE_HANDED:
		break;
	case WeaponType::TWO_HANDED:
		this->sprite = twoHanded.at(isFps)->GetSprite();
		window->draw(sprite);
		break;
	}
}

bool WeaponManager::CheckFps()
{
	return isFps < maxFps ? true : false;
}

void WeaponManager::NextFps()
{
	isFps++;
}

void WeaponManager::ResetFps()
{
	isFps = 0;
}

void WeaponManager::TwohandWeaponInit()
{
	for (auto wp : twoHanded)
	{
		delete wp;
	}
	twoHanded.clear();

	TwohandWeapon* twoHanded_1fps = new TwohandWeapon(75.f, 80.f, -80.f);
	twoHanded.push_back(twoHanded_1fps);
	TwohandWeapon* twoHanded_2fps = new TwohandWeapon(75.f, 65.f, -85.f);
	twoHanded.push_back(twoHanded_2fps);
	TwohandWeapon* twoHanded_3fps = new TwohandWeapon(60.f, 60.f, -100.f);
	twoHanded.push_back(twoHanded_3fps);
	TwohandWeapon* twoHanded_4fps = new TwohandWeapon(55.f, 40.f, -110.f);
	twoHanded.push_back(twoHanded_4fps);
	TwohandWeapon* twoHanded_5fps = new TwohandWeapon(50.f, 30.f, -125.f);
	twoHanded.push_back(twoHanded_5fps);
	TwohandWeapon* twoHanded_6fps = new TwohandWeapon(50.f, 30.f, -125.f);
	twoHanded.push_back(twoHanded_6fps);
	TwohandWeapon* twoHanded_7fps = new TwohandWeapon(55.f, 30.f, -115.f);
	twoHanded.push_back(twoHanded_7fps);
	TwohandWeapon* twoHanded_8fps = new TwohandWeapon(70.f, 30.f, -100.f);
	twoHanded.push_back(twoHanded_8fps);
	TwohandWeapon* twoHanded_9fps = new TwohandWeapon(85.f, 30.f, -80.f);
	twoHanded.push_back(twoHanded_9fps);
	TwohandWeapon* twoHanded_10fps = new TwohandWeapon(85.f, 50.f, -40.f);
	twoHanded.push_back(twoHanded_10fps);
	TwohandWeapon* twoHanded_11fps = new TwohandWeapon(90.f, 90.f, 20.f);
	twoHanded.push_back(twoHanded_11fps);
	TwohandWeapon* twoHanded_12fps = new TwohandWeapon(65.f, 80.f, 50.f);
	twoHanded.push_back(twoHanded_12fps);
	TwohandWeapon* twoHanded_13fps = new TwohandWeapon(65.f, 80.f, 80.f);
	twoHanded.push_back(twoHanded_13fps);
	TwohandWeapon* twoHanded_14fps = new TwohandWeapon(65.f, 80.f, 100.f);
	twoHanded.push_back(twoHanded_14fps);
	TwohandWeapon* twoHanded_15fps = new TwohandWeapon(65.f, 80.f, 120.f);
	twoHanded.push_back(twoHanded_15fps);
	TwohandWeapon* twoHanded_16fps = new TwohandWeapon(65.f, 80.f, 120.f);
	twoHanded.push_back(twoHanded_16fps);
}

WeaponManager::~WeaponManager()
{
	for (auto spriteWeapon : twoHanded)
	{
		delete spriteWeapon;
	}
	twoHanded.clear();
}