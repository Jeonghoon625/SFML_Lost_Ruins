#include "TestScene.h"

void TestScene::Init(SceneManager* sceneManager)
{
	this->sceneMgr = sceneManager;

	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	player.Init();
	IntRect gameMap(0, 0, resolution.x, resolution.y);
	player.Spawn(gameMap, resolution, 0.5f);

	testGround.setSize(Vector2f(resolution.x, 80));
	testGround.setFillColor(Color(153,153,153));
	testGround.setOrigin(0, 80);
	testGround.setPosition(0, resolution.y);
}

void TestScene::Update(float dt, Time playTime, RenderWindow* window, View* mainView)
{
	player.Update(dt);
}

void TestScene::Draw(RenderWindow* window, View* mainView)
{
	player.Draw(window, mainView);
	window->draw(testGround);
}

TestScene::~TestScene()
{

}