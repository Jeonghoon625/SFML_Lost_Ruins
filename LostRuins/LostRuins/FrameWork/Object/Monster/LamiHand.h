#pragma once
#include <SFML/Graphics.hpp>
#include "../../Animation/AnimationController.h"
#include "../../Animation/rapidcsv.h"

using namespace sf;

class LamiHand
{
private:
	Sprite sprite;
	AnimationController animation;
	std::map<std::string, Texture> texmap;

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

	void AnimationInit(Sprite* sprite);
};

