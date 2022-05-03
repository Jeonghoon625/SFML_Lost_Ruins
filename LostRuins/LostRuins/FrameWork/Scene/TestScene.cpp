#include "TestScene.h"

void TestScene::Init(SceneManager* sceneManager)
{
	this->sceneMgr = sceneManager;

	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	player.Init();
	gameMap = IntRect(0, 0, resolution.x, resolution.y);

	CreateBlock();

	player.Spawn(gameMap, resolution, 0.5f);
}

void TestScene::Update(float dt, Time playTime, RenderWindow* window, View* mainView)
{
	player.Update(dt, blocks);
}

void TestScene::Draw(RenderWindow* window, View* mainView)
{
	for (auto blockShape : blocks)
	{
		window->draw(blockShape->GetBlockShape());
	}
	player.Draw(window, mainView);
}

TestScene::~TestScene()
{

}

void TestScene::CreateBlock()
{
	for (auto bk : blocks)
	{
		delete bk;
	}

	blocks.clear();

	Vector2i res = resolution;

	TestBlock* block1 = new TestBlock(res.x * 0.5f - 100.f, res.y * 0.5f - 100.f, 200.f, 100.f);
	blocks.push_back(block1);
	TestBlock* block2 = new TestBlock(0.f, res.y - 100.f, res.x, 100.f);
	blocks.push_back(block2);
}