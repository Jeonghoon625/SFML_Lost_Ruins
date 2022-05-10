#include "MapScene.h"
#include "../Mgr/InputManager.h"
#include <sstream>

MapScene::MapScene() : gridSizeF(32.f), gridSizeU(static_cast<unsigned>(gridSizeF)), shape(Vector2f(gridSizeF, gridSizeF))
{
}

void MapScene::Init(SceneManager* sceneManager)
{
	this->sceneMgr = sceneManager;

	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	mapView = new View(FloatRect(0, 0, resolution.x, resolution.y));
	uiView = new View(FloatRect(0, 0, resolution.x, resolution.y));

	font.loadFromFile("fonts/LiberationSans-Bold.ttf");
	text.setCharacterSize(30);
	text.setFillColor(Color::Red);
	text.setFont(font);
	text.setPosition(0.f, 0.f);
	text.setString("TEST");
}

void MapScene::Update(float dt, Time playTime, RenderWindow* window, View* mainView)
{
	window->setView(*mapView);
	mousePosScreen = Mouse::getPosition();
	mousePosWindow = Mouse::getPosition(*window);
	mousePosView = window->mapPixelToCoords(mousePosWindow);

	if (mousePosView.x >= 0.f && mousePosView.y >= 0.f)
	{
		mousePosGrid.x = mousePosView.x / gridSizeU;
		mousePosGrid.y = mousePosView.y / gridSizeU;
	}
	else
	{
		mousePosGrid.x = 0;
		mousePosGrid.y = 0;
	}

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
}

void MapScene::Draw(RenderWindow* window, View* mainView)
{
	window->setView(*mapView);
	window->draw(shape);
	window->setView(*uiView);
	window->draw(text);
}

MapScene::~MapScene()
{
	delete mapView;
	delete uiView;
}
