#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include "../../Mgr/TextureHolder.h"
#include "../../Animation/AnimationController.h"
#include "../../Animation/rapidcsv.h"
#include "../../Mgr/Utils.h"
#include "../TestBlock/TestBlock.h"

using namespace sf;

class TestZombieWalker
{
private:
	const Vector2f scale = Vector2f(3.f, 3.f);
	const Vector2f scaleFlipX = Vector2f(-3.f, 3.f);
	const Vector2f hitBoxOrigin = Vector2f(21.5f, 50.f);

	const int START_HEALTH = 20;
	const float START_SPEED = 40.f;

	AnimationController animation;

	Vector2f position;
	Texture texture;
	Sprite sprite;

	Vector2i resolustion;
	IntRect gameMap;

	int tileSize;
	int health;
	float speed;

	bool isAlive;

	std::map<std::string, Texture> texmap;

	RectangleShape hitBox;

public:
	TestZombieWalker(float xpos, float ypos);
	void Update(float dt, Vector2f playerPos, std::vector <TestBlock*> blocks);
	void Draw(RenderWindow* window);

	bool OnHitted();
	bool GetAlive();

	Sprite GetSprite();
	RectangleShape GetHitBox();

	void AnimationInit();
	void UpdateCollision(std::vector<TestBlock*> blocks);
};

