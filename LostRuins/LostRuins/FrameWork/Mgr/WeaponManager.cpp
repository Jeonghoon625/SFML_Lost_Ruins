#include "WeaponManager.h"

void WeaponManager::Init()
{
	isFps = 0;
	maxFps = 0;

	TwohandWeaponInit();
	DaggerWeaponInit();
}

void WeaponManager::AttackWeapon(WeaponType weaponType)
{
	switch (weaponType)
	{
	case WeaponType::DAGGER:
		currentWeapon = WeaponType::DAGGER;
		maxFps = MAX_DAGGER_FPS;
		delay = DAGGER_DELAY;
		currentWeapon = WeaponType::DAGGER;
		break;
	case WeaponType::ONE_HANDED:
		currentWeapon = WeaponType::ONE_HANDED;
		break;
	case WeaponType::TWO_HANDED:
		maxFps = MAX_TWO_HANDED_FPS;
		delay = TWO_HANDED_DELAY;
		currentWeapon = WeaponType::TWO_HANDED;
		break;
	}
}

void WeaponManager::SetWeaponPosition(Sprite sprite)
{
	switch (currentWeapon)
	{
	case WeaponType::DAGGER:
		for (auto spriteWeapon : daggers)
		{
			spriteWeapon->SetPosition(sprite);
		}
		break;
	case WeaponType::ONE_HANDED:
		break;
	case WeaponType::TWO_HANDED:
		for (auto spriteWeapon : twoHanded)
		{
			spriteWeapon->SetPosition(sprite);
		}
		break;
	}
}

void WeaponManager::Draw(RenderWindow* window, View* mainView)
{
	window->setView(*mainView);

	switch (currentWeapon)
	{
	case WeaponType::DAGGER:
		this->sprite = daggers.at(isFps)->GetSprite();
		window->draw(sprite);
		break;
	case WeaponType::ONE_HANDED:
		break;
	case WeaponType::TWO_HANDED:
		this->sprite = twoHanded.at(isFps)->GetSprite();
		window->draw(sprite);
		break;
	}
}

int WeaponManager::GetAttackPoint()
{
	int damage = 0;
	switch (currentWeapon)
	{
	case WeaponType::DAGGER:
		damage = 5;
		break;
	case WeaponType::ONE_HANDED:
		break;
	case WeaponType::TWO_HANDED:
		damage = 10;
		break;
	default:
		break;
	}

	return damage;
}

int WeaponManager::GetHitFrame()
{
	int frame = 0;
	switch (currentWeapon)
	{
	case WeaponType::DAGGER:
		frame = DAGGER_HIT_FRAME;
		break;
	case WeaponType::ONE_HANDED:
		break;
	case WeaponType::TWO_HANDED:
		frame = TWO_HANDED_HIT_FRAME;
		break;
	}

	return frame;
}

float WeaponManager::GetAttackFps()
{
	float fps = 0.f;
	switch (currentWeapon)
	{
	case WeaponType::DAGGER:
		fps = DAGGER_ATTACK_FPS;
		break;
	case WeaponType::ONE_HANDED:
		break;
	case WeaponType::TWO_HANDED:
		fps = TWO_HANDED_ATTACK_FPS;
		break;
	}

	return fps;
}

bool WeaponManager::CheckFps()
{
	return isFps < maxFps ? true : false;
}

bool WeaponManager::CheckDelay()
{
	return isFps < delay ? true : false;
}

int WeaponManager::GetFps()
{
	return isFps;
}

void WeaponManager::NextFps()
{
	isFps++;
}

void WeaponManager::ResetFps()
{
	isFps = 0;
}

Sprite WeaponManager::GetSprite()
{
	return sprite;
}

WeaponManager::~WeaponManager()
{
	for (auto spriteWeapon : twoHanded)
	{
		delete spriteWeapon;
	}
	twoHanded.clear();
}

void WeaponManager::TwohandWeaponInit()
{
	for (auto spriteWeapon : twoHanded)
	{
		delete spriteWeapon;
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
	TwohandWeapon* twoHanded_12fps = new TwohandWeapon(65.f, 80.f, 60.f);
	twoHanded.push_back(twoHanded_12fps);
	TwohandWeapon* twoHanded_13fps = new TwohandWeapon(65.f, 80.f, 90.f);
	twoHanded.push_back(twoHanded_13fps);
	TwohandWeapon* twoHanded_14fps = new TwohandWeapon(65.f, 80.f, 110.f);
	twoHanded.push_back(twoHanded_14fps);
	TwohandWeapon* twoHanded_15fps = new TwohandWeapon(65.f, 80.f, 120.f);
	twoHanded.push_back(twoHanded_15fps);
	TwohandWeapon* twoHanded_16fps = new TwohandWeapon(65.f, 80.f, 120.f);
	twoHanded.push_back(twoHanded_16fps);
	TwohandWeapon* twoHanded_17fps = new TwohandWeapon(65.f, 80.f, 120.f);
	twoHanded.push_back(twoHanded_17fps);
}

void WeaponManager::DaggerWeaponInit()
{
	for (auto spriteWeapon : daggers)
	{
		delete spriteWeapon;
	}
	daggers.clear();

	Dagger* dagger_1fps = new Dagger(15.f, 88.f, 90.f);
	daggers.push_back(dagger_1fps);
	Dagger* dagger_2fps = new Dagger(10.f, 83.f, 90.f);
	daggers.push_back(dagger_2fps);
	Dagger* dagger_3fps = new Dagger(4.f, 70.f, 90.f);
	daggers.push_back(dagger_3fps);
	Dagger* dagger_4fps = new Dagger(4.f, 62.f, 90.f);
	daggers.push_back(dagger_4fps);
	Dagger* dagger_5fps = new Dagger(3.f, 52.f, 90.f);
	daggers.push_back(dagger_5fps);
	Dagger* dagger_6fps = new Dagger(15.f, 52.f, 90.f);
	daggers.push_back(dagger_6fps);
	Dagger* dagger_7fps = new Dagger(30.f, 65.f, 90.f);
	daggers.push_back(dagger_7fps);
	Dagger* dagger_8fps = new Dagger(57.f, 70.f, 90.f);
	daggers.push_back(dagger_8fps);
	Dagger* dagger_9fps = new Dagger(80.f, 77.f, 90.f);
	daggers.push_back(dagger_9fps);
	Dagger* dagger_10fps = new Dagger(105.f, 83.f, 90.f);
	daggers.push_back(dagger_10fps);
	Dagger* dagger_11fps = new Dagger(105.f, 83.f, 90.f);
	daggers.push_back(dagger_11fps);
	Dagger* dagger_12fps = new Dagger(105.f, 83.f, 90.f);
	daggers.push_back(dagger_12fps);
}
