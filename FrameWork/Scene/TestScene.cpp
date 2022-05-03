#include "TestScene.h"

void TestScene::Init(SceneManager* sceneManager)
{
	this->sceneMgr = sceneManager;

	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	player.Init();
	IntRect gameMap(resolution.x * 0.5, resolution.y * 0.5f, 500, 500);
	player.Spawn(gameMap, resolution, 0.5f);
}

void TestScene::Update(float dt, Time playTime, RenderWindow* window, View* mainView)
{
	player.Update(dt);
}

void TestScene::Draw(RenderWindow* window, View* mainView)
{
	player.Draw(window, mainView);
}

TestScene::~TestScene()
{

}