#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include "../../Mgr/TextureHolder.h"
#include "../../Animation/AnimationController.h"
#include "../../Animation/rapidcsv.h"
#include "../../Mgr/Utils.h"
#include "../../Mgr/InputManager.h"

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
	const float START_SPEED = 450;
	const float START_HEALTH = 20;
	const float START_MANA = 20;
	const float START_IMMUNE_MS = 200;

	TextureHolder textureHlr;
	AnimationController animation;

	Vector2f postion;

	Texture texture;
	Sprite sprite;
	
	Vector2f dir;

	Vector2i resolustion;
	IntRect gameMap;

	int tileSize;
	int health;
	int maxHealth;

	float speed;

	float immuneMs;
	bool immune;

	Time lastHit;

	std::map<std::string, Texture> texmap;

public:
	void Spawn(IntRect gameMap, Vector2i res, int tileSize);

	bool OnHitted(Time timeHit);

	Time GetLastTime() const;
	FloatRect GetGobalBound() const;
	Vector2f GetPosition() const;
	Sprite GetSprite() const;
	int GetHealth() const;

	void Init();
	void Update(float dt);
	void Draw(RenderWindow* window, View* mainView);

	void AnimationInit();

};

