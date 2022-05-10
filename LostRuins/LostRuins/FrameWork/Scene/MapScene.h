#pragma once

#include <SFML/Graphics.hpp>
#include <algorithm>
#include "Scene.h"
#include "../Mgr/TextureHolder.h"
#include "../Object/Player/Player.h"
#include "../Object/TestBlock/TestBlock.h"
#include "../Object/Monster/Monster.h"
#include "../Object/Monster/ZombieCrawler.h"
#include "../Object/Monster/ZombieWalker.h"
#include "TestSceneUI/TestSceneUi.h"

class MapScene : public Scene
{
	const float VIEW_SPEED = 200.f;
	float gridSizeF;
	unsigned gridSizeU;

	SceneManager* sceneMgr;
	Vector2i resolution;

	IntRect gameMap;

	Texture texBackground;
	VertexArray tileMap;
	View* mapView;
	View* uiView;
	RectangleShape shape;

	Vector2i mousePosScreen;
	Vector2i mousePosWindow;
	Vector2f mousePosView;
	Vector2u mousePosGrid;

	Text text;
	Font font;

public:
	MapScene();
	virtual void Init(SceneManager* sceneManager);
	virtual void Update(float dt, Time playTime, RenderWindow* window, View* mainView);
	virtual void Draw(RenderWindow* window, View* mainView);
	virtual ~MapScene();
};

