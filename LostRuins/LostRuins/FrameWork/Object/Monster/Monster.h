#pragma once
#include <SFML/Graphics.hpp>
#include "../../Animation/AnimationController.h"
#include "../../Animation/rapidcsv.h"

using namespace sf;

class Monster
{
private:
	Vector2i resolution;

	int health;
	int atk;
	float speed;

	int nextMove;
	float checkTime;

	Sprite sprite;
	Vector2f position;

	AnimationController animation;
	std::map<std::string, Texture> texmap;
public:
	Monster();
	FloatRect GetGlobalBound();
	Sprite GetSprite();
	Vector2f GetPosition();
	int GetHealth();
	void SetHealth(int damage);

	void MonsterInit();

	void AnimationInit(Sprite* sprite);

	void Walk(float dt);
	void Run(float dt);
	void Attack(float dt, int atk);

	void Update(float dt);

	void Draw(RenderWindow* window);
};

