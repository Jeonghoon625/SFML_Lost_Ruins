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

	testSprite.setTexture(TextureHolder::GetTexture("graphics/heroin_sprite.png"));
	AnimationInit1(&testSprite);
	testSprite.setOrigin(15.5f, 50.f);
	testSprite.setScale(3.f, 3.f);
	testSprite.setPosition(Vector2f(800.f, resolution.y + 500.f));

	testMagic.setTexture(TextureHolder::GetTexture("graphics/fire.png"));
	AnimationInit(&testMagic);
	testMagic.setOrigin(16.f, 0.f);
	testMagic.setRotation(-90.f);
	animation.Play("FireArrow");

	float xpos = testSprite.getGlobalBounds().left + testSprite.getGlobalBounds().width;
	float ypos = testSprite.getPosition().y - testSprite.getGlobalBounds().height * 0.5f;
	testMagic.setPosition(Vector2f(xpos, ypos));
}


void TestScene::Update(float dt, Time playTime, RenderWindow* window, View* mainView, View* uiView)
{
	animation.Update(dt);
	/*for (auto zombieWalker : zombieWalkers)
	{
		zombieWalker->Update(dt, player.GetPosition(), blocks);
	}
	player.Update(dt, blocks, playTime);*/
}

void TestScene::Draw(RenderWindow* window, View* mainView)
{
	window->draw(testSprite);
	window->draw(testMagic);
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

void TestScene::AnimationInit(Sprite* sprite)
{
	animation.SetTarget(sprite);

	rapidcsv::Document clips("data_tables/animations/magic/magic_animation_clips.csv");
	std::vector<std::string> colId = clips.GetColumn<std::string>("ID");
	std::vector<int> colFps = clips.GetColumn<int>("FPS");
	std::vector<int> colLoop = clips.GetColumn<int>("LOOP TYPE(0:Single, 1:Loop)");
	std::vector<std::string> colPath = clips.GetColumn<std::string>("CLIP PATH");

	int totalClips = colId.size();
	for (int i = 0; i < totalClips; ++i)
	{
		AnimationClip clip;
		clip.id = colId[i];
		clip.fps = colFps[i];
		clip.loopType = (AnimationLoopType)colLoop[i];

		rapidcsv::Document frames(colPath[i]);
		std::vector<std::string> colTexture = frames.GetColumn<std::string>("TEXTURE PATH");
		std::vector<int> colL = frames.GetColumn<int>("L");
		std::vector<int> colT = frames.GetColumn<int>("T");
		std::vector<int> colW = frames.GetColumn<int>("W");
		std::vector<int> colH = frames.GetColumn<int>("H");

		int totalFrames = colTexture.size();
		for (int j = 0; j < totalFrames; ++j)
		{
			if (texmap.find(colTexture[j]) == texmap.end())
			{
				auto& ref = texmap[colTexture[j]];
				ref.loadFromFile(colTexture[j]);
			}

			clip.frames.push_back(AnimationFrame(texmap[colTexture[j]],
				IntRect(colL[j], colT[j], colW[j], colH[j])));
		}
		animation.AddClip(clip);
	}
}

void TestScene::AnimationInit1(Sprite* sprite)
{
	animation.SetTarget(sprite);

	rapidcsv::Document clips("data_tables/animations/player/player_animation_clips2.csv");
	std::vector<std::string> colId = clips.GetColumn<std::string>("ID");
	std::vector<int> colFps = clips.GetColumn<int>("FPS");
	std::vector<int> colLoop = clips.GetColumn<int>("LOOP TYPE(0:Single, 1:Loop)");
	std::vector<std::string> colPath = clips.GetColumn<std::string>("CLIP PATH");

	int totalClips = colId.size();
	for (int i = 0; i < totalClips; ++i)
	{
		AnimationClip clip;
		clip.id = colId[i];
		clip.fps = colFps[i];
		clip.loopType = (AnimationLoopType)colLoop[i];

		rapidcsv::Document frames(colPath[i]);
		std::vector<std::string> colTexture = frames.GetColumn<std::string>("TEXTURE PATH");
		std::vector<int> colL = frames.GetColumn<int>("L");
		std::vector<int> colT = frames.GetColumn<int>("T");
		std::vector<int> colW = frames.GetColumn<int>("W");
		std::vector<int> colH = frames.GetColumn<int>("H");

		int totalFrames = colTexture.size();
		for (int j = 0; j < totalFrames; ++j)
		{
			if (texmap.find(colTexture[j]) == texmap.end())
			{
				auto& ref = texmap[colTexture[j]];
				ref.loadFromFile(colTexture[j]);
			}

			clip.frames.push_back(AnimationFrame(texmap[colTexture[j]],
				IntRect(colL[j], colT[j], colW[j], colH[j])));
		}
		animation.AddClip(clip);
	}
}