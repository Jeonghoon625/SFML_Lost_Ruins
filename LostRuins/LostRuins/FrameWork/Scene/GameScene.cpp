#include "GameScene.h"

void GameScene::Init(SceneManager* sceneManager)
{
	this->sceneMgr = sceneManager;

	resolution.x = 1920.f;
	resolution.y = 1080.f;

	zombieWalker = new ZombieWalker();

	player.Init(zombieWalker);
	gameMap = FloatRect(0, 0, 35.f * 32.f, 15.f * 32.f);

	CreateBlock();

	player.Spawn(90.f, 340.f);

	// test
	zombieWalker->MonsterInit();

	//Dummy Map
	CreateBackGround();
	texBackground = TextureHolder::GetTexture("maps/Another/SewerWall.png");

	testUI.Init(sceneManager);
}

void GameScene::Update(float dt, Time playTime, RenderWindow* window, View* objectView, View* uiView)
{
	if (player.GetPause() == false)
	{
		if (player.GetAlive() == false)
		{
			dt *= 0.25f;
		}
		
		zombieWalker->Update(player, dt, blocks, playTime);

		if (zombieWalker->GetHealth() == 0)
		{
			zombieWalker->SetPosition(9999.f, 9999.f);
		}

		player.Update(dt, blocks, playTime, monsters);
	}
	else
	{
		if (InputManager::GetKeyDown(Keyboard::Escape) && 
			player.GetPause() == true)
		{
			player.SetPause(false);
		}
	}

	testUI.Update(dt, playTime, window, uiView, player);
	/*testNpc.Update(dt);
	coin.Update(dt, blocks, &player);*/
}

void GameScene::Draw(RenderWindow* window, View* objectView, View* uiView)
{
	window->setView(*objectView);
	/* View 설정*/
	objectView->setCenter(player.GetPosition());

	//좌측 조정
	if ((objectView->getCenter().x) - (objectView->getSize().x * 0.5f) < gameMap.left)
	{
		objectView->move((objectView->getSize().x * 0.5f) - (objectView->getCenter().x), 0);
	}

	//우측 조정
	if ((objectView->getCenter().x) + (objectView->getSize().x * 0.5f) > gameMap.left + gameMap.width)
	{
		objectView->move((gameMap.left + gameMap.width) - ((objectView->getCenter().x) + (objectView->getSize().x * 0.5f)), 0);
	}

	//위측 조정
	if ((objectView->getCenter().y) - (objectView->getSize().y * 0.5f) < gameMap.top)
	{
		objectView->move(0, (objectView->getSize().y * 0.5f) - (objectView->getCenter().y));
	}

	//아래측 조정
	if ((objectView->getCenter().y) + (objectView->getSize().y * 0.5f) > gameMap.top + gameMap.height)
	{
		objectView->move(0, (gameMap.top + gameMap.height) - ((objectView->getCenter().y) + (objectView->getSize().y * 0.5f)));
	}

	window->draw(tileMap, &texBackground);

	for (auto blockShape : blocks)
	{
		window->draw(blockShape->GetBlockShape());
	}

	player.Draw(window, objectView);

	// test
	zombieWalker->Draw(window);

	//testNpc.Draw(window);
	//coin.Draw(window, objectView, uiView);

	window->setView(*uiView);
	testUI.Draw(window, uiView);
}

GameScene::~GameScene()
{
	for (auto blockShape : blocks)
	{
		delete blockShape;
	}

	blocks.clear();
}

void GameScene::CreateBlock()
{
	for (auto bk : blocks)
	{
		delete bk;
	}

	blocks.clear();

	CollisionBlock* block1 = new CollisionBlock(0, 0, 64, 416);
	blocks.push_back(block1);
	CollisionBlock* block2 = new CollisionBlock(1056, 0, 64, 416);
	blocks.push_back(block2);
	CollisionBlock* block3 = new CollisionBlock(0, 416, 1120, 64);
	blocks.push_back(block3);
	CollisionBlock* block4 = new CollisionBlock(128, 352, 256, 32);
	blocks.push_back(block4);
	CollisionBlock* block5 = new CollisionBlock(416, 288, 224, 32);
	blocks.push_back(block5);
	CollisionBlock* block13 = new CollisionBlock(600, 220, 32, 32);
	blocks.push_back(block13);
	CollisionBlock* block14 = new CollisionBlock(480, 220, 32, 32);
	blocks.push_back(block14);
	CollisionBlock* block6 = new CollisionBlock(672, 352, 192, 32);
	blocks.push_back(block6);
	CollisionBlock* block7 = new CollisionBlock(928, 384, 32, 32);
	blocks.push_back(block7);
	CollisionBlock* block8 = new CollisionBlock(992, 320, 32, 32);
	blocks.push_back(block8);
	CollisionBlock* block9 = new CollisionBlock(128, 192, 224, 64);
	blocks.push_back(block9);
	CollisionBlock* block10 = new CollisionBlock(672, 192, 224, 64);
	blocks.push_back(block10);
	CollisionBlock* block11 = new CollisionBlock(928, 300, 32, 32);
	blocks.push_back(block11);
	CollisionBlock* block12 = new CollisionBlock(1012, 230, 32, 32);
	blocks.push_back(block12);

}

int GameScene::CreateBackGround()
{
	const int TILE_SIZE = 128;
	const int TILE_TYPES = 0;
	const int VERTS_IN_QUAD = 4;

	int cols = gameMap.width / TILE_SIZE;
	int rows = gameMap.height / TILE_SIZE;

	tileMap.setPrimitiveType(Quads);
	tileMap.resize(cols * rows * VERTS_IN_QUAD);

	for (int r   = 0; r < rows; ++r)
	{
		for (int c = 0; c < cols; ++c)
		{
			int index = r * cols + c;

			float x = c * TILE_SIZE;
			float y = r * TILE_SIZE;
			//std::cout << x << y << std::endl;
			int vertexIndex = index * VERTS_IN_QUAD;

			tileMap[vertexIndex + 0].position = Vector2f(x, y);
			tileMap[vertexIndex + 1].position = Vector2f(x + TILE_SIZE * 2.f, y);
			tileMap[vertexIndex + 2].position = Vector2f(x + TILE_SIZE * 2.f, y + TILE_SIZE * 2.f);
			tileMap[vertexIndex + 3].position = Vector2f(x, y + TILE_SIZE * 2.f);

			int texIndex = 0;

			float offset = texIndex * TILE_SIZE;
			tileMap[vertexIndex + 0].texCoords = Vector2f(0.f, offset);
			tileMap[vertexIndex + 1].texCoords = Vector2f(TILE_SIZE, offset);
			tileMap[vertexIndex + 2].texCoords = Vector2f(TILE_SIZE, offset + TILE_SIZE);
			tileMap[vertexIndex + 3].texCoords = Vector2f(0.f, offset + TILE_SIZE);
		}
	}

	return cols * rows;
}