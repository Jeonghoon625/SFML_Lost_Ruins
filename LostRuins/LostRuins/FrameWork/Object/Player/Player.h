#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include "../../Mgr/TextureHolder.h"
#include "../../Animation/AnimationController.h"
#include "../../Animation/rapidcsv.h"
#include "../../Mgr/Utils.h"
#include "../../Mgr/InputManager.h"
#include "../TestBlock/TestBlock.h"

using namespace sf;

enum class KeyInput
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
};

class Player
{
private:
	const Vector2f scale = Vector2f(3.f, 3.f);
	const Vector2f scaleFlipX = Vector2f(-3.f, 3.f);

	const Vector2f idleUpHitBox = Vector2f(10.f, 48.f);
	const Vector2f rightRunUpHitBox = Vector2f(5.f, 48.f);
	const Vector2f leftRunUpHitBox = Vector2f(15.f, 48.f);

	const Vector2f idleDownHitBox = Vector2f(10.f, 5.f);
	const Vector2f rightRunDownHitBox = Vector2f(5.f, 5.f);
	const Vector2f leftRunDownHitBox = Vector2f(15.f, 5.f);

	const float START_SPEED = 600;
	const float START_HEALTH = 20;
	const float START_MANA = 20;
	const float START_IMMUNE_MS = 200;
	const float GRAVITY_POWER = 2000.f;
	const float START_FALLING_SPEED = 200.f;
 
	TextureHolder textureHlr;
	AnimationController animation;

	Vector2f position;

	Vector2f lastDir;

	Texture texture;
	Sprite sprite;
	
	Vector2i resolustion;
	IntRect gameMap;

	int tileSize;
	int health;
	int maxHealth;

	float speed;
	float vel;

	float immuneMs;
	bool immune;

	bool isFalling;
	bool isJump;

	Time lastHit;

	std::map<std::string, Texture> texmap;

	RectangleShape upHitBox;
	RectangleShape downHitBox;

public:
	void Spawn(IntRect gameMap, Vector2i res, int tileSize);

	bool OnHitted(Time timeHit);

	Time GetLastTime() const;
	FloatRect GetGobalBound() const;
	Vector2f GetPosition() const;
	Sprite GetSprite() const;
	int GetHealth() const;

	void SetIsJump(bool jump);
	bool GetIsJump();

	void Init();
	void Update(float dt, std::vector <TestBlock*> blocks);
	void Draw(RenderWindow* window, View* mainView);

	void AnimationInit();

};

