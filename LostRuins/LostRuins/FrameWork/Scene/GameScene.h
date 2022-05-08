#pragma once
#include <SFML/Graphics.hpp>
#include <algorithm>
#include "Scene.h"
#include "../Mgr/TextureHolder.h"
#include "../Object/Player/Player.h"
#include "../Object/TestBlock/TestBlock.h"
#include "../Object/Monster/Monster.h"
#include "../Object/Monster/ZombieCrawler.h"
#include "../Object/Monster/ZombieWalker.h"
#include "TestSceneUI/TestSceneUi.h"

class GameScene : public Scene
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
	ZombieWalker* zombieWalker;
	TestUi testUI;

	//Dummy Map
	Texture texBackground;
	VertexArray tileMap;

public:
	virtual void Init(SceneManager* sceneManager);
	virtual void Update(float dt, Time playTime, RenderWindow* window, View* mainView);
	virtual void Draw(RenderWindow* window, View* mainView);
	virtual ~GameScene();

	void CreateBlock(); 
	int CreateBackGround();
};

