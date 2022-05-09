#include "MapScene.h"
#include "../Mgr/InputManager.h"
#include <sstream>

MapScene::MapScene() : gridSizeF(300.f), gridSizeU(static_cast<unsigned>(gridSizeF)), shape(Vector2f(gridSizeF, gridSizeF))
{
	
}

void MapScene::Init(SceneManager* sceneManager)
{
	this->sceneMgr = sceneManager;

	resolution.x = 1920.f;
	resolution.y = 1080.f;

	font.loadFromFile("fonts/LiberationSans-Regular.ttf");
	text.setCharacterSize(10);
	text.setFillColor(Color::Blue);
	text.setFont(font);
	text.setPosition(500.f, 100.f);
	text.setString("TEST");
}

void MapScene::Update(float dt, Time playTime, RenderWindow* window, View* mainView)
{
	mousePosScreen = Mouse::getPosition();
	mousePosWindow = Mouse::getPosition(*window);
	mousePosView = window->mapPixelToCoords(mousePosWindow);
	if (mousePosView.x >= 0.f)
	{
		mousePosGrid.x = mousePosView.x / gridSizeU;
	}
	if (mousePosView.y >= 0.f)
	{
		mousePosGrid.y = mousePosView.y / gridSizeU;
	}

	std::stringstream ss;
	ss << "Screen : " << mousePosScreen.x << " " << mousePosScreen.y << "\n"
		<< "Window : " << mousePosWindow.x << " " << mousePosWindow.y << "\n"
		<< "View : " << mousePosView.x << " " << mousePosView.y << "\n"
		<< "Grid : " << mousePosGrid.x << " " << mousePosGrid.y << "\n";

	text.setString(ss.str());

	if (InputManager::GetKey(Keyboard::A))
	{
		mainView->move(-VIEW_SPEED * dt, 0.f);

	}

	if (InputManager::GetKey(Keyboard::D))
	{
		mainView->move(VIEW_SPEED * dt, 0.f);

	}

	if (InputManager::GetKey(Keyboard::W))
	{
		mainView->move(0, -VIEW_SPEED * dt);
	}

	if (InputManager::GetKey(Keyboard::S))
	{
		mainView->move(0, VIEW_SPEED * dt);

	}
}

void MapScene::Draw(RenderWindow* window, View* mainView)
{
	window->setView(*mainView);
	window->draw(shape);
	window->draw(text);
}

MapScene::~MapScene()
{
}
