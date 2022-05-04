#pragma once
#include <SFML/Graphics.hpp>
#include "../../Animation/AnimationController.h"
#include "../../Animation/rapidcsv.h"

using namespace sf;

class Monster
{
protected:
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

	int GetAtk();
	void SetAtk(int atk);

	float GetSpeed();
	void SetSpeed(float speed);

	virtual void MonsterInit(int health, int atk, float speed);

	void AnimationInit(Sprite* sprite);

	virtual void Walk(float dt);
	virtual void Run(float dt);
	virtual void Attack(float dt, int atk);

	void Update(float dt);

	void Draw(RenderWindow* window);
};

