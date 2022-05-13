#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include <cstdlib>
#include "../../Animation/AnimationController.h"
#include "../../Mgr/TextureHolder.h"
#include "../../Mgr/Utils.h"
#include "../../Animation/rapidcsv.h"
#include "../Player/Player.h"

using namespace sf;

class Coin
{
private:

	//////////////////////////////////////

	bool isFalling;
	float fallingSpeed;
	const float GRAVITY_POWER = 2000.f;

	Font fontGold;
	Text textGold;
	
	//////////////////////////////////////v

	const Vector2f scale = Vector2f(3.f, 3.f);

	AnimationController animationCoin;

	Vector2f positionCoin;

	Vector2f lastDirCoin;

	Texture textureCoin;
	Sprite spriteCoin;

	Vector2i resolustionCoin;
	IntRect gameMapCoin;

	std::map<std::string, Texture> texmap;

	bool isCollideCoin;
	int tileSizeCoin;

	float coinTimer;
	

public:
	void Spawn(IntRect gameMap, Vector2i res, int tileSize);

	FloatRect GetGobalBound() const;
	Vector2f GetPosition() const;
	Sprite GetSprite() const;

	void Init();
	void Update(float dt, std::vector<TestBlock*> blocks, Player &player);
	void Draw(RenderWindow* window, View* mainView, View* uiView);

	
	//////////////////////////////
		
	void Gravity(float dt, std::vector<TestBlock*> blocks);
	void UpdateCollision(std::vector <TestBlock*> blocks);
	bool Coindelete = false;

	/////////////////////////////

	void AnimationInit();
};

