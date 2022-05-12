#pragma once
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <vector>
#include "Scene.h"
#include "../Mgr/TextureHolder.h"
#include "../Object/Player/Player.h"
#include "../Object/Monster/Monster.h"
#include "../Object/Monster/ZombieCrawler.h"
#include "../Object/Monster/ZombieWalker.h"
#include "../Object/CollisionBlock/CollisionBlock.h"
#include "TestSceneUI/TestSceneUi.h"

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

	View* mapView;
	View* uiView;
	
	RectangleShape shape;
	RectangleShape tileSelector;
	vector<vector <RectangleShape>> gridTileMap;
	

	Vector2i mousePosScreen;
	Vector2i mousePosWindow;
	Vector2f mousePosWorld;
	Vector2u mousePosGrid;

	Vector2u downGrid;
	Vector2u upGrid;
	vector<Vector2u> finalGrid;
	RectangleShape* currentDrag;

	Text text;
	Font font;

	vector <CollisionBlock*> blocks;

	Texture selectTexture;
	VertexArray vertexMap;

	InputState currentInputState;

	//test
	bool isDraw;
	Player* player;

	int fromX;
	int toX;
	int fromY;
	int toY;

public:
	MapScene();

	virtual void Init(SceneManager* sceneManager);
	virtual void Update(float dt, Time playTime, RenderWindow* window, View* mainView, View* uiView);
	virtual void Draw(RenderWindow* window, View* mainView);

	void MoveView(float dt);
	void UpdateMousePos(RenderWindow* window);

	int CreateBackGround(int c, int r);
	void CreateBlocks(int fromX, int toX, int fromY, int toY);

	virtual ~MapScene();
};

