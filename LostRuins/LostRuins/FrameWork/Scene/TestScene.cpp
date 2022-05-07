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

	float wpXpos = 500.f;
	float wpYpos = resolution.y * 0.5f;

	// test
	zombieWalker.MonsterInit();
}

void TestScene::Update(float dt, Time playTime, RenderWindow* window, View* mainView)
{
	player.Update(dt, blocks);

	// test
	zombieWalker.Update(player, dt, blocks);
}

void TestScene::Draw(RenderWindow* window, View* mainView)
{
	for (auto blockShape : blocks)
	{
		window->draw(blockShape->GetBlockShape());
	}
	player.Draw(window, mainView);

	// test
	zombieWalker.Draw(window);
}

TestScene::~TestScene()
{
	for (auto blockShape : blocks)
	{
		delete blockShape;
	}
	blocks.clear();
}

void TestScene::CreateBlock()
{
	for (auto bk : blocks)
	{
		delete bk;
	}

	blocks.clear();

	Vector2i res = resolution;

	TestBlock* block1 = new TestBlock(res.x * 0.5f, res.y * 0.5f, 800.f, 50.f);
	blocks.push_back(block1);
	TestBlock* block2 = new TestBlock(res.x * 0.5f, res.y - 50.f, res.x, 100.f);
	blocks.push_back(block2);
	TestBlock* block3 = new TestBlock(440.f, res.y * 0.75f - 50.f, 600.f, 50.f);
	blocks.push_back(block3);
	TestBlock* block4 = new TestBlock(1480.f, res.y * 0.75f - 50.f, 600.f, 50.f);
	blocks.push_back(block4);
	/*TestBlock* block5 = new TestBlock(240.f, res.y * 0.75f - 200.f, 200.f, 200.f);
	blocks.push_back(block5);
	TestBlock* block6 = new TestBlock(1680.f, res.y * 0.75f - 200.f, 200.f, 200.f);
	blocks.push_back(block6);*/
	TestBlock* block7 = new TestBlock(res.x * 0.5f, res.y - 150.f, 100.f, 100.f);
	blocks.push_back(block7);
}