#include "MapScene.h"
#include "../Mgr/InputManager.h"
#include <sstream>

MapScene::MapScene() : gridSizeF(32.f), gridSizeU(static_cast<unsigned>(gridSizeF)), shape(Vector2f(gridSizeF, gridSizeF)), tileSelector(Vector2f(gridSizeF, gridSizeF))
{
	tileSelector.setFillColor(Color::Transparent);
	tileSelector.setOutlineThickness(5.f);
	tileSelector.setOutlineColor(Color::Red);
	texBackground = TextureHolder::GetTexture("maps/Stage1/test.png");
	currentInputState = InputState::BLOCK;
}

void MapScene::Init(SceneManager* sceneManager)
{
	this->sceneMgr = sceneManager;

	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

mapView = new View(FloatRect(0, 0, resolution.x, resolution.y));
uiView = new View(FloatRect(0, 0, resolution.x, resolution.y));

tileMap.resize(mapWidth, vector<RectangleShape>());

for (int i = 0; i < mapWidth; i++)
{
	tileMap[i].resize(mapHeight, RectangleShape());
	for (int j = 0; j < mapHeight; j++)
	{
		tileMap[i][j].setSize(Vector2f(gridSizeF, gridSizeF));
		tileMap[i][j].setFillColor(Color::White);
		tileMap[i][j].setOutlineThickness(1.f);
		tileMap[i][j].setOutlineColor(Color::Black);
		tileMap[i][j].setPosition(i * gridSizeF, j * gridSizeF);
	}
}
font.loadFromFile("fonts/LiberationSans-Bold.ttf");
text.setCharacterSize(20);
text.setFillColor(Color::Blue);
text.setFont(font);
text.setPosition(0.f, 0.f);
text.setString("TEST");
}

void MapScene::Update(float dt, Time playTime, RenderWindow* window, View* mainView)
{
	mousePosScreen = Mouse::getPosition();
	mousePosWindow = Mouse::getPosition(*window);
	mousePosView = window->mapPixelToCoords(mousePosWindow);

	if (mousePosView.x >= 0.f && mousePosView.y >= 0.f && mousePosView.x <= mapWidth * gridSizeU && mousePosView.y <= mapHeight * gridSizeU)
	{
		mousePosGrid.x = mousePosView.x / gridSizeU;
		mousePosGrid.y = mousePosView.y / gridSizeU;
	}
	/*else
	{
		mousePosGrid.x = 0;
		mousePosGrid.y = 0;
	}*/

	tileSelector.setPosition(mousePosGrid.x * gridSizeF, mousePosGrid.y * gridSizeF);
	std::stringstream ss;
	ss << "Screen : " << mousePosScreen.x << " " << mousePosScreen.y << "\n"
		<< "Window : " << mousePosWindow.x << " " << mousePosWindow.y << "\n"
		<< "Map : " << mousePosView.x << " " << mousePosView.y << "\n"
		<< "Grid : " << mousePosGrid.x << " " << mousePosGrid.y << "\n";

	text.setString(ss.str());

	if (InputManager::GetKey(Keyboard::A))
	{
		mapView->move(-VIEW_SPEED * dt, 0.f);
	}

	if (InputManager::GetKey(Keyboard::D))
	{
		mapView->move(VIEW_SPEED * dt, 0.f);
	}

	if (InputManager::GetKey(Keyboard::W))
	{
		mapView->move(0, -VIEW_SPEED * dt);
	}

	if (InputManager::GetKey(Keyboard::S))
	{
		mapView->move(0, VIEW_SPEED * dt);
	}

	if (InputManager::GetKeyDown(Keyboard::Add))
	{
		mapView->zoom(0.5f);
	}

	if (InputManager::GetKeyDown(Keyboard::Subtract))
	{
		mapView->zoom(2.f);
	}

	if (InputManager::GetMouseButtonDown(Mouse::Button::Left))
	{
		finalGrid.clear();
		downGrid = mousePosGrid;
		std::cout << "DGrid : " << downGrid.x << " " << downGrid.y << "\n";

		if (currentInputState == InputState::BLOCK)
		{
			currentDrag = new RectangleShape(Vector2f(0.f, 0.f));
			currentDrag->setFillColor({ 100, 100, 200, 125 });
			currentDrag->setPosition(downGrid.x * gridSizeF, downGrid.y * gridSizeF);
		}
	}

	if (InputManager::GetMouseButton(Mouse::Button::Left) && currentInputState == InputState::BLOCK)
	{
		currentDrag->setSize(Vector2f(((int)mousePosGrid.x - (int)downGrid.x) * gridSizeF, ((int)mousePosGrid.y - (int)downGrid.y) * gridSizeF));

		if (((int)mousePosGrid.x - (int)downGrid.x) >= 0)
		{
			currentDrag->setSize(Vector2f(currentDrag->getSize().x + gridSizeF, currentDrag->getSize().y));
		}

		if (((int)mousePosGrid.y - (int)downGrid.y) >= 0)
		{
			currentDrag->setSize(Vector2f(currentDrag->getSize().x, currentDrag->getSize().y + gridSizeF));
		}
	}

	switch (currentInputState)
	{
	case::InputState::TERRAIN:
		if (InputManager::GetMouseButtonUp(Mouse::Button::Left))
		{
			upGrid = mousePosGrid;
			std::cout << "UGrid : " << upGrid.x << " " << upGrid.y << "\n";

			for (unsigned int i = downGrid.x; i <= upGrid.x; i++)
			{
				for (unsigned int j = downGrid.y; j <= upGrid.y; j++)
				{
					finalGrid.push_back(Vector2u(i, j));
				}
			}

			int i = 0;

			for (auto it : finalGrid)
			{
				CreateBackGround(it.x, it.y);
				std::cout << ++i << "Fgrid : " << it.x << " " << it.y << "\n";
			}
		}
		break;

	case::InputState::BLOCK:
		if (InputManager::GetMouseButtonUp(Mouse::Button::Left))
		{
			TestBlock* block = new TestBlock(currentDrag->getGlobalBounds(), downGrid);
			blocks.push_back(block);

			delete currentDrag;

			upGrid = mousePosGrid;
			std::cout << "UGrid : " << upGrid.x << " " << upGrid.y << "\n";

			CreateBlocks(downGrid.x, upGrid.x, downGrid.y, upGrid.y);
		}
		break;
	}

	text.setPosition(mousePosWindow.x + 10.f, mousePosWindow.y + 10.f);
}

void MapScene::Draw(RenderWindow* window, View* mainView)
{
	window->setView(*mapView);
	window->draw(shape);

	/*
	fromX = mousePosGrid.x;
	toX = mousePosGrid.x + 3;

	fromY = mousePosGrid.y;
	toY = mousePosGrid.y + 3;

	if (fromX < 0)
	{
		fromX = 0;
	}
	else if (fromX >= mapSize)
	{
		fromX = mapSize - 1;
	}

	if (toX < 0)
	{
		toX = 0;
	}
	else if (toX >= mapSize)
	{
		toX = mapSize - 1;
	}

	if (fromY < 0)
	{
		fromY = 0;
	}
	else if (fromY >= mapSize)
	{
		fromY = mapSize - 1;
	}

	if (toY < 0)
	{
		toY = 0;
	}
	else if (toY >= mapSize)
	{
		toY = mapSize - 1;
	}

	for (int i = fromX; i < toX; i++)
	{
		for (int j = fromY; j < toY; j++)
		{
			window->draw(tileMap[i][j]);
		}
	}
	*/
	
	for (int i = 0; i < mapWidth; i++)
	{
		for (int j = 0; j < mapHeight; j++)
		{
			window->draw(tileMap[i][j]);
		}
	}
	
	RectangleShape textureShape;

	fromX = mousePosGrid.x;
	fromY = mousePosGrid.y;
	textureShape.setFillColor({255, 255, 255, 125});
	textureShape.setTexture(&texBackground);
	textureShape.setPosition(fromX * gridSizeU, fromY * gridSizeU);
	textureShape.setSize(Vector2f(0.f, 0.f));
	textureShape.setScale(texBackground.getSize().x, texBackground.getSize().y);
	
	window->draw(vertexMap, &texBackground);
	window->draw(textureShape);

	if (InputManager::GetMouseButton(Mouse::Button::Left) && currentInputState == InputState::BLOCK)
	{
		window->draw(*currentDrag);
	}

	for (auto blockShape : blocks)
	{
		window->draw(blockShape->GetBlockShape());
	}

	window->draw(tileSelector);
	
	window->setView(*uiView);
	window->draw(text);


	window->setView(*mapView);
}

int MapScene::CreateBackGround(int r, int c)
{
	int TILE_SIZE = 32;
	int TILE_TYPES = 0;
	int VERTS_IN_QUAD = 4;

	int cols = mapHeight;
	int rows = mapWidth;

	vertexMap.setPrimitiveType(Quads);
	vertexMap.resize(cols * rows * VERTS_IN_QUAD);

	int index = r + c * cols;
	int vertexIndex = index * VERTS_IN_QUAD;

	float x = c * gridSizeF;
	float y = r * gridSizeF;
	 
	std::cout << vertexMap[vertexIndex + 0].position.y << std::endl;
	vertexMap[vertexIndex + 0].position = Vector2f(x, y);
	vertexMap[vertexIndex + 1].position = Vector2f(x + TILE_SIZE, y);
	vertexMap[vertexIndex + 2].position = Vector2f(x + TILE_SIZE, y + TILE_SIZE);
	vertexMap[vertexIndex + 3].position = Vector2f(x, y + TILE_SIZE);
	
	vertexMap[vertexIndex + 0].texCoords = Vector2f(0.f, 0.f);
	vertexMap[vertexIndex + 1].texCoords = Vector2f(TILE_SIZE, 0.f);
	vertexMap[vertexIndex + 2].texCoords = Vector2f(TILE_SIZE, TILE_SIZE);
	vertexMap[vertexIndex + 3].texCoords = Vector2f(0.f, TILE_SIZE);
	
	return cols * rows;
}


void MapScene::CreateBlocks(int fromX, int toX, int fromY, int toY)
{
}

MapScene::~MapScene()
{
	delete mapView;
	delete uiView;

	for (auto it : blocks)
	{
		delete it;
	}
	blocks.clear();
}

