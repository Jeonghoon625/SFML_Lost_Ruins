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
#include "../Object/TestBlock/TestBlock.h"
#include <vector>

enum class InputState
{
	BLOCK,
	OBJECT,
	TERRAIN,
	NONE
};

class MapScene : public Scene
{
	const int mapWidth = 50;
	const int mapHeight = 20;

	const float VIEW_SPEED = mapWidth * 10.f;
	float gridSizeF;
	unsigned gridSizeU;
	
	SceneManager* sceneMgr;
	Vector2i resolution;

	Texture texBackground;

	View* mapView;
	View* uiView;
	
	RectangleShape shape;
	RectangleShape tileSelector;
	vector<vector <RectangleShape>> tileMap;

	int fromX;
	int toX;
	int fromY;
	int toY;

	Vector2i mousePosScreen;
	Vector2i mousePosWindow;
	Vector2f mousePosView;
	Vector2u mousePosGrid;

	Text text;
	Font font;

	Vector2u downGrid;
	Vector2u upGrid;
	vector<Vector2u> finalGrid;
	
	VertexArray vertexMap;
	InputState currentInputState;

	RectangleShape* currentDrag;

	vector <TestBlock*> blocks;

public:
	MapScene();
	int CreateBackGround(int c, int r);

	void CreateBlocks(int fromX, int toX, int fromY, int toY);
	virtual void Init(SceneManager* sceneManager);
	virtual void Update(float dt, Time playTime, RenderWindow* window, View* mainView);
	virtual void Draw(RenderWindow* window, View* mainView);
	virtual ~MapScene();
};

