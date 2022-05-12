#pragma once
#include <SFML/Graphics.hpp>
#include "Monster.h"
#include "../../Mgr/TextureHolder.h"

using namespace sf;

class LamiPhaseTwo : public Monster
{
private:
	RectangleShape attackRangeLeftBox;
	RectangleShape attackRangeRightBox;

	Sprite leftSclera;
	Sprite rightSclera;

	Sprite leftEye;
	Sprite RightEye;

	String strDiving;
	String strReappearing;
	String strReappearingToIdle;

	Image Idle;
	Image Idle2;
	int a = 1;

	float upY;
	float downY;
	float prevY;
public:
	LamiPhaseTwo();
	virtual void MonsterInit();

	virtual void Walk(float dt,Player& player);

	virtual void Attack(float dt, int atk, Player& player, Time timeHit);
	virtual void Update(Player& player, float dt, std::vector<TestBlock*> blocks, Time playtime);
	void Draw(RenderWindow* window);

	void EyeUpdate(float dt, Player& player);

	virtual bool OnHitted(int atk, float dt, Time timeHit);
};

