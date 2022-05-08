#pragma once
#include <SFML/Graphics.hpp>
#include "../../Animation/AnimationController.h"
#include "../../Animation/rapidcsv.h"
#include "../Player/Player.h"
using namespace sf;

class Monster
{
protected:
	const Vector2f scale = Vector2f(3.f, 3.f);
	const float GRAVITY_POWER = 2000.f;
	float fallingSpeed;
	bool isFalling;

	Vector2i resolution;

	int health;
	int atk;
	float speed;

	string strIdle;
	string strWalk;
	string strRun;
	string strDead;
	string strAttack;
	string strAttackBlocked;
	string strDemageTaken;


	int nextMove;
	float checkTime;

	bool isFindPlayer;
	bool isAttackPlayer;
	bool alive;

	float attackDelay;
	float hitDelay;

	Sprite sprite;
	Vector2f position;

	RectangleShape findPlayerBox;		// Find Player
	RectangleShape attackRangeBox;
	RectangleShape hitBox;

	AnimationController animation;
	std::map<std::string, Texture> texmap;
public:
	Monster();
	FloatRect GetGlobalBound();
	virtual Sprite GetSprite();
	Vector2f GetPosition();
	int GetHealth();
	void SetHealth(int damage);

	int GetAtk();
	void SetAtk(int atk);

	float GetSpeed();
	void SetSpeed(float speed);

	RectangleShape GetHitBox();

	virtual void MonsterInit();

	void AnimationInit(Sprite* sprite);

	virtual void Walk(float dt);

	virtual void FindPlayer(Player& player);
	virtual void ChasePlayer(Player& player, float dt);
	virtual void Run(float dt);
	virtual void Attack(float dt, int atk, Player& player);

	virtual bool OnHitted(int atk, float dt);

	void Gravity(float dt, std::vector<TestBlock*> blocks);
	void UpdateCollision(std::vector <TestBlock*> blocks);

	void Update(Player& player, float dt, std::vector<TestBlock*> blocks);

	void Draw(RenderWindow* window);
};

