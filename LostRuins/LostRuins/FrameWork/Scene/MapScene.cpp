#include "MapScene.h"
#include "../Mgr/InputManager.h"
#include <sstream>

MapScene::MapScene() : gridSizeF(16.f), gridSizeU(static_cast<unsigned>(gridSizeF)), shape(Vector2f(gridSizeF, gridSizeF)), tileSelector(Vector2f(gridSizeF, gridSizeF))
{
	tileSelector.setFillColor(Color::Transparent);
	tileSelector.setOutlineThickness(5.f);
	tileSelector.setOutlineColor(Color::Red);
	texBackground = TextureHolder::GetTexture("maps/Stage1/SewerWall.png");
}

void MapScene::Init(SceneManager* sceneManager)
{
	this->sceneMgr = sceneManager;

	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	mapView = new View(FloatRect(0, 0, resolution.x, resolution.y));
	uiView = new View(FloatRect(0, 0, resolution.x, resolution.y));

	tileMap.resize(mapSize, vector<RectangleShape>());

	for (int i = 0; i < mapSize; i++)
	{
		tileMap[i].resize(mapSize, RectangleShape());
		for (int j = 0; j < mapSize; j++)
		{
			tileMap[i][j].setSize(Vector2f(gridSizeF, gridSizeF));
			tileMap[i][j].setFillColor(Color::White);
			tileMap[i][j].setOutlineThickness(1.f);
			tileMap[i][j].setOutlineColor(Color::Black);
			tileMap[i][j].setPosition(i * gridSizeF, j * gridSizeF);
		}
	}
	font.loadFromFile("fonts/LiberationSans-Bold.ttf");
	text.setCharacterSize(30);
	text.setFillColor(Color::Red);
	text.setFont(font);
	text.setPosition(0.f, 0.f);
	text.setString("TEST");
}

void MapScene::Update(float dt, Time playTime, RenderWindow* window, View* mainView)
{
	mousePosScreen = Mouse::getPosition();
	mousePosWindow = Mouse::getPosition(*window);
	mousePosView = window->mapPixelToCoords(mousePosWindow);

	if (mousePosView.x >= 0.f && mousePosView.y >= 0.f && mousePosView.x <= mapSize * gridSizeU && mousePosView.y <= mapSize * gridSizeU)
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
		<< "Grid : " << mousePosGrid.y << " " << mousePosGrid.x << "\n";

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
		std::cout << "DGrid : " << downGrid.y << " " << downGrid.x << "\n";
	}

	if (InputManager::GetMouseButtonUp(Mouse::Button::Left))
	{
		upGrid = mousePosGrid;
		std::cout << "UGrid : " << upGrid.y << " " << upGrid.x << "\n";
		
		for (unsigned int i = downGrid.y; i <= upGrid.y; i++)
		{
			for (unsigned int j = downGrid.x; j <= upGrid.x; j++)
			{
				finalGrid.push_back(Vector2u(i, j));
			}
		}

		int i = 0;
		for (auto it : finalGrid)
		{
			CreateBackGround(it.x, it.y);
			std::cout << ++i << "Fgrid : " << it.x << " " << it.y  << "\n";
		}
	}
}

void MapScene::Draw(RenderWindow* window, View* mainView)
{
	window->setView(*mapView);
	window->draw(shape);

	fromX = mousePosGrid.x;
	toX = mousePosGrid.x + 3;

	fromY = mousePosGrid.y;
	toY = mousePosGrid.y + 3;

	/*
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
	
	for (int i = 0; i < mapSize; i++)
	{
		for (int j = 0; j < mapSize; j++)
		{
			window->draw(tileMap[i][j]);
		}
	}
	
	window->draw(tileSelector);
	window->draw(vertexMap, &texBackground);
	window->setView(*uiView);
	window->draw(text);

	window->setView(*mapView);
}

int MapScene::CreateBackGround(int c, int r)
{
	const int TILE_SIZE = 128;
	const int TILE_TYPES = 0;
	const int VERTS_IN_QUAD = 4;

	int cols = mapSize * gridSizeU / TILE_SIZE;
	int rows = mapSize * gridSizeU / TILE_SIZE;

	vertexMap.setPrimitiveType(Quads);
	vertexMap.resize(cols * rows * VERTS_IN_QUAD);

	int index = r * cols + c;

	float x = c * TILE_SIZE;
	float y = r * TILE_SIZE;
	std::cout << x << y << std::endl;
	int vertexIndex = index * VERTS_IN_QUAD;

	vertexMap[vertexIndex + 0].position = Vector2f(x, y);
	vertexMap[vertexIndex + 1].position = Vector2f(x + TILE_SIZE / gridSizeU, y);
	vertexMap[vertexIndex + 2].position = Vector2f(x + TILE_SIZE / gridSizeU, y + TILE_SIZE / gridSizeU);
	vertexMap[vertexIndex + 3].position = Vector2f(x, y + TILE_SIZE / gridSizeU);

	int texIndex = 0;

	float offset = texIndex * TILE_SIZE;
	vertexMap[vertexIndex + 0].texCoords = Vector2f(0.f, offset);
	vertexMap[vertexIndex + 1].texCoords = Vector2f(TILE_SIZE, offset);
	vertexMap[vertexIndex + 2].texCoords = Vector2f(TILE_SIZE, offset + TILE_SIZE);
	vertexMap[vertexIndex + 3].texCoords = Vector2f(0.f, offset + TILE_SIZE);

	return cols * rows;
}

MapScene::~MapScene()
{
	delete mapView;
	delete uiView;
}

