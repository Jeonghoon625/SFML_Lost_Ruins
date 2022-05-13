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

enum class DrawState
{
	ALL,
	BLOCK,
	OBJECT,
	TERRAIN,
	NONE
};

enum class Category
{
	Draw,
	Input
};

struct Button
{
	RectangleShape buttonShape;
	FloatRect buttonRect;
	Text buttonText;
	Category buttonCategory;
	InputState buttonInputState;
	DrawState buttonDrawState;
	bool isToggle;
};

class MapScene : public Scene
{
	const int mapWidth = 35;
	const int mapHeight = 15;
	const float VIEW_SPEED = mapWidth * 10.f;

	float gridSizeF;
	unsigned gridSizeU;
	
	SceneManager* sceneMgr;
	Vector2i resolution;

	View* mapView;
	View* uiView;
	View* miniMapView;

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
	DrawState currentDrawState;

	vector <Button> buttons;
	
	string name;

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
	virtual void Draw(RenderWindow* window, View* mainView, View* uiView);

	void MoveView(float dt);
	void UpdateMousePos(RenderWindow* window);

	int CreateBackGround(int c, int r);

	void CreateButtonSet();
	Button CreateButton(float left, float top, float width, float height, string name, InputState buttonInputState, DrawState buttonDrawState);
	void UpdateButton();

	virtual ~MapScene();
};

