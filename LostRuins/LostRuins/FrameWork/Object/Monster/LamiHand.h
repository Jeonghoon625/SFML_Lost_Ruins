#pragma once
#include <SFML/Graphics.hpp>
#include "../../Animation/AnimationController.h"
#include "../../Animation/rapidcsv.h"

using namespace sf;

enum class Lami2Status
{
	STATUS_IDLE,
	STATUS_ATTACK_NEAR,
	STATUS_ATTACK_MIDDLE,
	STATUS_ATTACK_FAR,
	STATUS_DIVING,
	STATUS_REAPPEARING,
	STATUS_DEAD,
};

class LamiHand
{
private:
	Sprite sprite;
	AnimationController animation;
	std::map<std::string, Texture> texmap;

	Lami2Status currentStatus;


	bool isAttacking;

	String strIdle;
	String strNearAttack;
	String strNearAttackToIdle;
	String strMiddleAttack;
	String strMiddleAttackToIdle;
	String strFarAttack;
	String strFarAttackToIdle;
	String strDiving;
	String strReappearing;
	String strReappearingToIdle;
public:
	LamiHand();
	void Init(Vector2f pos, int handSide);
	void Update(float dt, Vector2f pos);
	void Draw(RenderWindow* window);
	Sprite GetSprite();

	void AnimationPlay(Lami2Status newStatus);
	void AnimationUpdate();
	void SetStatus(Lami2Status newStatus);

	void IdlePlay();
	void IsAttackingFalse();
	void AnimationInit(Sprite* sprite);

	bool GetIsAttacking();
};

