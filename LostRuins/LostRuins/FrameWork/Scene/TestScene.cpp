#include "TestScene.h"

void TestScene::Init(SceneManager* sceneManager)
{
	this->sceneMgr = sceneManager;

	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	player.Init(nullptr);
	gameMap = IntRect(0, 0, resolution.x, resolution.y);

	CreateBlock();
	CreateMonster();

	player.Spawn(gameMap, resolution, 0.5f);

	float wpXpos = 500.f;
	float wpYpos = resolution.y * 0.5f;

}


void TestScene::Update(float dt, Time playTime, RenderWindow* window, View* mainView)
{
	player.Update(dt, blocks);
	for (auto zombieWalker : zombieWalkers)
	{
		zombieWalker->Update(dt, player.GetPosition(), blocks);
	}
}

void TestScene::Draw(RenderWindow* window, View* mainView)
{
	for (auto blockShape : blocks)
	{
		window->draw(blockShape->GetBlockShape());
	}
	for (auto zombieWalker : zombieWalkers)
	{
		zombieWalker->Draw(window);
	}
	player.Draw(window, mainView);
}

TestScene::~TestScene()
{
	for (auto blockShape : blocks)
	{
		delete blockShape;
	}
	blocks.clear();

	for (auto zombieWalker : zombieWalkers)
	{
		delete zombieWalker;
	}
	zombieWalkers.clear();
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
	TestBlock* block2 = new TestBlock(res.x * 0.5f, res.y - 50.f, 3000.f, 100.f);
	blocks.push_back(block2);
	TestBlock* block3 = new TestBlock(440.f, res.y * 0.75f - 50.f, 600.f, 50.f);
	blocks.push_back(block3);
	TestBlock* block4 = new TestBlock(1480.f, res.y * 0.75f - 50.f, 600.f, 50.f);
	blocks.push_back(block4);
	TestBlock* block5 = new TestBlock(res.x * 0.5f - 1550.f, res.y - 200.f, 100.f, 400.f);
	blocks.push_back(block5);
	TestBlock* block6 = new TestBlock(res.x * 0.5f + 1550.f, res.y - 200.f, 100.f, 400.f);
	blocks.push_back(block6);
}

void TestScene::CreateMonster()
{
	for (auto zw : zombieWalkers)
	{
		delete zw;
	}
	zombieWalkers.clear();

	Vector2i res = resolution;

	TestZombieWalker* zombieWalker1 = new TestZombieWalker(res.x * 0.5f, res.y * 0.5f);
	zombieWalkers.push_back(zombieWalker1);
}