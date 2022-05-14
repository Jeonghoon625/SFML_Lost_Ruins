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

enum class ButtonType
{
	DEFAULT,
	TOGGLE
};

enum class ButtonCategory
{
	DRAW,
	INPUT
};

enum class ButtonState
{
	BLOCK,
	OBJECT,
	TERRAIN,
	NONE
};

struct Button
{
	RectangleShape buttonShape;
	FloatRect buttonRect;
	Text buttonText;

	ButtonType buttonType;
	ButtonCategory buttonCategory;
	ButtonState buttonState;

	bool isButtonClick;
	bool isButtonToggle;
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

	Text mousePosText;
	Text stateText;
	Font font;

	vector <CollisionBlock*> blocks;

	Texture selectTexture;
	VertexArray vertexMap;

	ButtonState currentInputState;
	ButtonState currentDrawState;

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
	Button InitButton(float left, float top, float width, float height, string name, ButtonType type, ButtonCategory category, ButtonState state);
	bool UpdateButton();
	void SetCurrentInputState(ButtonState state);
	void SetCurrentDrawState(ButtonState state);
	virtual ~MapScene();
};

