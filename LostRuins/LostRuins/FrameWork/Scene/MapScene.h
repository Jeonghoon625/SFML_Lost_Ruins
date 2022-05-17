#pragma once
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <vector>
#include <map>
#include "Scene.h"
#include "../Mgr/TextureHolder.h"
#include "../Object/Player/Player.h"
#include "../Object/Monster/Monster.h"
#include "../Object/Monster/GoblinAttacker.h"
#include "../Object/CollisionBlock/CollisionBlock.h"

enum class ButtonType
{
	DEFAULT,
	TOGGLE
};

enum class ButtonCategory
{
	INPUT,
	SELECT,
	DELETE,
	DRAW
};

enum class ButtonState
{
	BLOCK,
	OBJECT,
	TERRAIN,
	BACKGROUND,
	GATE,
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

struct TerrainResource
{
	Texture tex;
	string type;
};   

struct ObjectResource
{
	Texture tex;
	string type;
};

struct InputData
{
	RectangleShape shape;

	string resourceId;
	float rotate;
	float scaleX;
	float scaleY;
	float posX;
	float posY;
};

class MapScene : public Scene
{
	int mapWidth;
	int mapHeight;
	float VIEW_SPEED;

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
	vector<Vector2u> ingGrid;

	RectangleShape* currentDrag;

	Text mousePosText;
	Text stateText;
	Text currentMapIdText;
	Font font;

	ButtonState currentInputState;
	ButtonState currentDrawState;

	vector<Button> buttons;

	//test
	bool isDraw;
	Player* player;

	int fromX;
	int fromY;

	int toX;
	int toY;

	int rotation;
	
	map<string, TerrainResource> terrainResource;
	map<string, ObjectResource> objectResource;
	map<string, Texture> backGroundResource;

	bool isSelect;
	bool isDelete;
	bool isClicked;

	RectangleShape selectTable;
	vector<Button> selectButtons;
	vector <Monster*> monsters;

	InputData* currentInput;
	Texture currentTexture;

	vector <CollisionBlock*> blocks;
	vector<InputData> terrainInput;
	vector<InputData> objectInput;
	vector<InputData> backGroundInput;

	string spritePath;
	string blockPath;

	string currentMapId;

public:
	MapScene();

	virtual void Init(SceneManager* sceneManager);
	virtual void Update(float dt, Time playTime, RenderWindow* window, View* mainView, View* uiView);
	virtual void Draw(RenderWindow* window, View* mainView, View* uiView);

	void DefaultMapInit();

	void MoveView(float dt);
	void UpdateMousePos(RenderWindow* window);

	Button InitButton(float left, float top, float width, float height, string name, ButtonType type, ButtonCategory category, ButtonState state);

	void CreateDefaultButtonSet();
	void CreateSelectButtonSet(string buttonName);
	void CreateInputData(InputData currentInputData);

	bool UpdateButton();
	void UpdateSelectTexture();

	void SetCurrentInputState(ButtonState state);
	void SetCurrentDrawState(ButtonState state);

	bool CompareInputData(InputData inputData, vector<InputData> inputDatas);

	void Save();
	void Load(string mapName);

	virtual ~MapScene();
};