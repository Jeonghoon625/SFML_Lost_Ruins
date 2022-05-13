#pragma once
#include <SFML/Graphics.hpp>
#include "Monster.h"
#include "../../Mgr/TextureHolder.h"
#include "LamiHand.h"
#include "LamiPhaseTwo.h"

using namespace sf;

class LamiPhaseTwo : public Monster
{
private:
	const int START_HEALTH = 50;

	RectangleShape attackRangeLeftBox;
	RectangleShape attackRangeRightBox;

	Lami2Status currentStatus;

	Sprite leftSclera;
	Sprite rightSclera;

	Sprite leftEye;
	Sprite RightEye;

	LamiHand leftHand;
	LamiHand rightHand;

	String strDiving;
	String strReappearing;
	String strReappearingToIdle;

	Image Idle;
	Image Idle2;

	Vector2f prevLeftEyePos;
	float a = 1.f;

	bool isNearAttackPlayer;
	bool isMiddleAttackPlayer;
	bool isFarAttackPlayer;
	bool isAlive;
	bool isIdle;
	bool isHit;
	bool isLeft;
	bool isRight;
	bool isFar;
	bool isDiving;
	bool isReappearing;
	bool diveOn;
	bool ReappearOn;


	float upY;
	float downY;
	float prevY;
	float updateY;
	float diveDelay;
	int punchCount;
	int diveCount;
	
public:
	LamiPhaseTwo();
	virtual void MonsterInit();

	virtual void Walk(float dt,Player& player);

	virtual void AnimationUpdate();
	virtual void SetStatus(Lami2Status newStatus);

	virtual void Attack(float dt, int atk, Player& player, Time timeHit);
	virtual void Update(Player& player, float dt, std::vector<TestBlock*> blocks, Time playtime);
	void Dive(float dt, Player& player);

	void Draw(RenderWindow* window);

	void EyeUpdate(float dt, Player& player);
	void SetDive();
	void SetIdle();

	virtual bool OnHitted(int atk, float dt, Time timeHit);
	virtual void Gravity(float dt, std::vector<TestBlock*> blocks);
	virtual void UpdateCollision(std::vector <TestBlock*> blocks);
	virtual void UpdateCollisionAttackRangeBox(std::vector <TestBlock*> blocks);
};

