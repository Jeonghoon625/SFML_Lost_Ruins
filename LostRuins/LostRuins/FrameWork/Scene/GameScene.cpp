#include "GameScene.h"

void GameScene::Init(SceneManager* sceneManager)
{
	this->sceneMgr = sceneManager;

	resolution.x = 1920.f;
	resolution.y = 1080.f;

	player.Init();
	gameMap = IntRect(0, 0, resolution.x, resolution.y);

	CreateBlock();

	player.Spawn(gameMap, resolution, 0.5f);

	float wpXpos = 500.f;
	float wpYpos = resolution.y * 0.5f;

	// test
	zombieWalker.MonsterInit();

	//Dummy Map
	CreateBackGround();
	texBackground = TextureHolder::GetTexture("maps/ShedWallMossLightMap.png");
}

void GameScene::Update(float dt, Time playTime, RenderWindow* window, View* mainView)
{
	player.Update(dt, blocks);
	
	
	// test
	zombieWalker.Update(player, dt, blocks);

	/*
	ViewRect = player.GetHitBox();
	ViewRect.setSize(Vector2f(200.f, 200.f));
	ViewRect.setFillColor(Color(153, 13, 203, 80));
	ViewRect.move((ViewRect.getGlobalBounds().width * - 0.5f) + 
	(player.GetGobalBound().width * 0.25f), ViewRect.getGlobalBounds().height * -0.25f);*/
}

void GameScene::Draw(RenderWindow* window, View* mainView)
{
	window->draw(tileMap, &texBackground);
	window->draw(ViewRect);
	for (auto blockShape : blocks)
	{
		window->draw(blockShape->GetBlockShape());
	}

	player.Draw(window, mainView);

	// test
	zombieWalker.Draw(window);
	
	//testUI.Draw(window, mainView);
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

	Vector2i res = resolution;

	TestBlock* block1 = new TestBlock(res.x * 0.5f, res.y * 0.5f, 800.f, 50.f);
	blocks.push_back(block1);
	TestBlock* block2 = new TestBlock(res.x * 0.5f, res.y - 50.f, res.x, 100.f);
	blocks.push_back(block2);
	TestBlock* block3 = new TestBlock(440.f, res.y * 0.75f - 50.f, 600.f, 50.f);
	blocks.push_back(block3);
	TestBlock* block4 = new TestBlock(1480.f, res.y * 0.75f - 50.f, 600.f, 50.f);
	blocks.push_back(block4);
	TestBlock* block7 = new TestBlock(res.x * 0.5f, res.y - 150.f, 100.f, 100.f);
	blocks.push_back(block7);
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

	for (int r = 0; r < rows; ++r)
	{
		for (int c = 0; c < cols; ++c)
		{
			int index = r * cols + c;

			float x = c * TILE_SIZE;
			float y = r * TILE_SIZE;
			std::cout << x << y << std::endl;
			int vertexIndex = index * VERTS_IN_QUAD;

			tileMap[vertexIndex + 0].position = Vector2f(x, y);
			tileMap[vertexIndex + 1].position = Vector2f(x + TILE_SIZE, y);
			tileMap[vertexIndex + 2].position = Vector2f(x + TILE_SIZE, y + TILE_SIZE);
			tileMap[vertexIndex + 3].position = Vector2f(x, y + TILE_SIZE);

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