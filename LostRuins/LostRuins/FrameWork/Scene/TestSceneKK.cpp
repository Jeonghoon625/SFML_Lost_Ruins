#include "TestSceneKK.h"

void TestSceneKK::Init(SceneManager* sceneManager)
{
	
	this->sceneMgr = sceneManager;


	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	player.Init();
	IntRect gameMap(resolution.x * 0.5, resolution.y * 0.5f, 500, 500);
	player.Spawn(gameMap, resolution, 0.5f);

	Goblin.MonsterInit(20, 3, 50.f);
	zombieCrawler.MonsterInit(10, 5, 20.f);
	zombieWalker.MonsterInit(10, 3, 35.f);

}

void TestSceneKK::Update(float dt, Time playTime, RenderWindow* window, View* mainView)
{
	player.Update(dt, blocks);
	Goblin.Update(dt);
	/*Goblin.Walk(dt);*/
	zombieCrawler.Update(dt);
	/*zombieCrawler.Walk(dt);*/
	zombieWalker.Update(dt);
	/*zombieWalker.Walk(dt);*/
}

void TestSceneKK::Draw(RenderWindow* window, View* mainView)
{

	Goblin.Draw(window);
	zombieCrawler.Draw(window);
	zombieWalker.Draw(window);
	player.Draw(window, mainView);

}

TestSceneKK::~TestSceneKK()
{

}

