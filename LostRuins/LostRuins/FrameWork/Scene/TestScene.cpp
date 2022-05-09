#include "TestScene.h"

void TestScene::Init(SceneManager* sceneManager)
{
	/*this->sceneMgr = sceneManager;

	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	player.Init(nullptr);
	gameMap = IntRect(0, 0, resolution.x, resolution.y);

	CreateBlock();
	CreateMonster();

	player.Spawn(gameMap, resolution, 0.5f);
	*/

	testSprite.setTexture(TextureHolder::GetTexture("graphics/Attack_Dagger_Standing.png"));
	testSprite.setTextureRect(IntRect(0 + (40 * 12), 0, 40, 50));
	testSprite.setScale(3.f, 3.f);
	testSprite.setPosition(Vector2f(800.f, resolution.y + 500.f));

	testWeapon.setTexture(TextureHolder::GetTexture("graphics/weapon.png"));
	testWeapon.setTextureRect(IntRect(3, 17, 4, 25));
	testWeapon.setOrigin(2.f, 25.f);
	testWeapon.setScale(3.f, 3.f);

	float wpXpos = 800.f;
	float wpYpos = resolution.y + 500;

	testWeapon.setPosition(Vector2f(wpXpos+105, wpYpos+83));
	testWeapon.setRotation(90.f);
}

void TestScene::Update(float dt, Time playTime, RenderWindow* window, View* mainView)
{
	/*for (auto zombieWalker : zombieWalkers)
	{
		zombieWalker->Update(dt, player.GetPosition(), blocks);
	}
	player.Update(dt, blocks);*/
}

void TestScene::Draw(RenderWindow* window, View* mainView)
{
	window->draw(testSprite);
	window->draw(testWeapon);
	///* View 설정*/
	//mainView->setCenter(player.GetPosition());

	////좌측 조정
	//if ((mainView->getCenter().x) - (mainView->getSize().x * 0.5f) < gameMap.left)
	//{
	//	mainView->move((mainView->getSize().x * 0.5f) - (mainView->getCenter().x), 0);
	//}

	////우측 조정
	//if ((mainView->getCenter().x) + (mainView->getSize().x * 0.5f) > gameMap.left + gameMap.width)
	//{
	//	mainView->move((gameMap.left + gameMap.width) - ((mainView->getCenter().x) + (mainView->getSize().x * 0.5f)), 0);
	//}

	////위측 조정
	//if ((mainView->getCenter().y) - (mainView->getSize().y * 0.5f) < gameMap.top)
	//{
	//	mainView->move(0, (mainView->getSize().y * 0.5f) - (mainView->getCenter().y));
	//}

	////아래측 조정
	//if ((mainView->getCenter().y) + (mainView->getSize().y * 0.5f) > gameMap.top + gameMap.height)
	//{
	//	mainView->move(0, (gameMap.top + gameMap.height) - ((mainView->getCenter().y) + (mainView->getSize().y * 0.5f)));
	//}

	//for (auto blockShape : blocks)
	//{
	//	window->draw(blockShape->GetBlockShape());
	//}
	//for (auto zombieWalker : zombieWalkers)
	//{
	//	zombieWalker->Draw(window);
	//}
	//player.Draw(window, mainView);
}

TestScene::~TestScene()
{
	/*for (auto blockShape : blocks)
	{
		delete blockShape;
	}
	blocks.clear();

	for (auto zombieWalker : zombieWalkers)
	{
		delete zombieWalker;
	}
	zombieWalkers.clear();*/
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