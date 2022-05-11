#pragma once
#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "../Mgr/TextureHolder.h"
#include "../Mgr/Utils.h"
#include "../Animation/AnimationController.h"
#include "../Animation/rapidcsv.h"
#include "TestSceneUI/TestSceneUi.h"
#include "../Object/Npc/Npc.h"
#include "../Object/Player/Player.h"
#include "../Object/TestBlock/TestBlock.h"
#include "../Object/Monster/Monster.h"
#include "../Object/Monster/ZombieCrawler.h"
#include "../Object/Monster/ZombieWalker.h"
#include "TestSceneUI/TestSceneUi.h"
#include <map>
#include <algorithm>

class TestSceneTT : public Scene
{
private:
	SceneManager* sceneMgr;
	Vector2i resolution;

	TestUi testUI;
	Npc testNpc;

	View* uiView;

	Player player;
	IntRect gameMap;

	Texture textureHeroine;
	Sprite heroineAction;

	vector <TestBlock*> blocks;

	Sprite testSprite;
	Sprite testWeapon;

	// test
	ZombieWalker* zombieWalker;

	//Dummy Map
	Texture texBackground;
	VertexArray tileMap;

public:
	virtual void Init(SceneManager* sceneManager);
	virtual void Update(float dt, Time playTime, RenderWindow* window, View* mainView, View* uiView);
	virtual void Draw(RenderWindow* window, View* mainView);
	virtual ~TestSceneTT();

	void CreateBlock();
	int CreateBackGround();
};

