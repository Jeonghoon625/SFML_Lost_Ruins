#pragma once
#include <SFML/Graphics.hpp>
#include <algorithm>
#include "Scene.h"
#include "../Mgr/TextureHolder.h"
#include "../Object/Player/Player.h"
#include "../Object/TestBlock/TestBlock.h"

// test
#include "../Object/Monster/Monster.h"

class TestScene : public Scene
{
	SceneManager* sceneMgr;

	Vector2i resolution;

	Player player;
	IntRect gameMap;

	Texture textureHeroine;

	Sprite heroineAction;

	vector <TestBlock*> blocks;

	Sprite testSprite;
	Sprite testWeapon;

	// test
	Monster Goblin;

public:
	virtual void Init(SceneManager* sceneManager);
	virtual void Update(float dt, Time playTime, RenderWindow* window, View* mainView);
	virtual void Draw(RenderWindow* window, View* mainView);
	virtual ~TestScene();

	void CreateBlock();
};

