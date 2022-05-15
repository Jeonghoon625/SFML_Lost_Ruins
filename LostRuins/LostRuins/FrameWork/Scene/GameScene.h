#pragma once
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <map>
#include "Scene.h"
#include "../Mgr/TextureHolder.h"
#include "../Object/Player/Player.h"
#include "../Object/CollisionBlock/CollisionBlock.h"
#include "../Object/Monster/Monster.h"
#include "../Object/Monster/ZombieCrawler.h"
#include "../Object/Monster/ZombieWalker.h"
#include "../Object/Npc/Npc.h"
#include "../Object/Coin/Coin.h"
#include "TestSceneUI/TestSceneUi.h"
#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "../Object/CollisionBlock/CollisionBlock.h"
#include "../Mgr/TextureHolder.h"
#include "../Object/Player/Player.h"
#include "../Mgr/Utils.h"
#include "../Animation/AnimationController.h"
#include "../Animation/rapidcsv.h"
#include <map>
#include "../Object/Monster/Monster.h"
#include "../Object/Monster/GoblinAttacker.h"
#include "../Object/Monster/ZombieCrawler.h"
#include "../Object/Monster/ZombieWalker.h"
#include "../Object/Monster/LamiPhaseTwo.h"
#include "../Object/Monster/SlimeGreen.h"
#include "../Object/Monster/LamiPhaseOne.h"

class MonsterSet
{
public:
	Monster* monster;
};

class GameScene : public Scene
{
	SceneManager* sceneMgr;
	Vector2i resolution;

	FloatRect gameMap;
	Player player;

	TestUi testUI;
	Npc testNpc;
	Coin coin;

	Texture textureHeroine;

	vector <CollisionBlock*> blocks;

	// test
	vector <Monster*> monsters;

	GoblinAttacker Goblin;
	ZombieCrawler zombieCrawler;
	ZombieWalker zombieWalker;
	SlimeGreen slimeGreen;
	LamiPhaseTwo Lami2;

	//Dummy Map
	Texture texBackground;
	VertexArray tileMap;

public:
	virtual void Init(SceneManager* sceneManager);
	virtual void Update(float dt, Time playTime, RenderWindow* window, View* mainView, View* uiView);
	virtual void Draw(RenderWindow* window, View* mainView, View* uiView);
	virtual ~GameScene();

	void CreateBlock(); 
	int CreateBackGround();
	void CreateMonsters();
};

