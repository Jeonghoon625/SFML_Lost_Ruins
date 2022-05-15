#include "MapScene.h"
#include <sstream>
#include <iostream>
#include "../Map/csvfile.h"
#include "../Mgr/InputManager.h"
#include "../Mgr/Utils.h"

MapScene::MapScene() : gridSizeF(32.f), gridSizeU(static_cast<unsigned>(gridSizeF)), shape(Vector2f(gridSizeF, gridSizeF)), tileSelector(Vector2f(gridSizeF, gridSizeF))
{
}

void MapScene::Init(SceneManager* sceneManager)
{
	MapDataInit();

	VIEW_SPEED = mapWidth * 10.f;
	this->sceneMgr = sceneManager;

	resolution.x = 1920.f; // VideoMode::getDesktopMode().width;
	resolution.y = 1080.f; // VideoMode::getDesktopMode().height;

	mapView = new View(FloatRect(0, 0, resolution.x, resolution.y));
	uiView = new View(FloatRect(0, 0, resolution.x, resolution.y));

	//State
	currentInputState = ButtonState::NONE;
	currentDrawState = ButtonState::NONE;

	//격자무늬
	gridTileMap.resize(mapWidth, vector<RectangleShape>());

	for (int i = 0; i < mapWidth; i++)
	{
		gridTileMap[i].resize(mapHeight, RectangleShape());
		for (int j = 0; j < mapHeight; j++)
		{
			gridTileMap[i][j].setSize(Vector2f(gridSizeF, gridSizeF));
			gridTileMap[i][j].setFillColor(Color::White);
			gridTileMap[i][j].setOutlineThickness(1.f);
			gridTileMap[i][j].setOutlineColor(Color::Black);
			gridTileMap[i][j].setPosition(i * gridSizeF, j * gridSizeF);
		}
	}

	//타일맵 선택 영역 하이라이트
	tileSelector.setFillColor(Color::Transparent);
	tileSelector.setOutlineThickness(5.f);
	tileSelector.setOutlineColor(Color::Red);

	//UI Text
	font.loadFromFile("fonts/LiberationSans-Bold.ttf");
	mousePosText.setCharacterSize(20);
	mousePosText.setFillColor(Color::Magenta);
	mousePosText.setFont(font);
	mousePosText.setPosition(0.f, 0.f);
	mousePosText.setString("TEST");

	stateText.setCharacterSize(30);
	stateText.setFillColor(Color::Red);
	stateText.setFont(font);
	stateText.setPosition(0.f, 0.f);
	stateText.setString("TEST");

	//test
	//selectTexture = terrainResource.find("SewerBossOneWayCorner")->second.tex;
	isDraw = true;
	isSelect = false;

	//Default Button Set
	CreateDefaultButtonSet();
}

void MapScene::Update(float dt, Time playTime, RenderWindow* window, View* mainView, View* uiView)
{
	UpdateMousePos(window);
	MoveView(dt);

	if (!UpdateButton())
	{
		if (InputManager::GetMouseButtonDown(Mouse::Button::Left))
		{
			if (mousePosWorld.x >= 0.f && mousePosWorld.y >= 0.f && mousePosWorld.x <= mapWidth * gridSizeU && mousePosWorld.y <= mapHeight * gridSizeU)
			{
				currentInputState = ButtonState::NONE;
			}

			downGrid = mousePosGrid;
			std::cout << "DGrid : " << downGrid.x << " " << downGrid.y << "\n";
			ingGrid.push_back(mousePosGrid);
			if (currentInputState == ButtonState::TERRAIN)
			{
				//CreateBackGround(downGrid.x, downGrid.y);
			}

			if (currentInputState == ButtonState::BLOCK)
			{
				currentDrag = new RectangleShape(Vector2f(0.f, 0.f));
				currentDrag->setFillColor({ 100, 100, 200, 125 });
				currentDrag->setPosition(downGrid.x * gridSizeF, downGrid.y * gridSizeF);
			}
		}

		if (InputManager::GetMouseButton(Mouse::Button::Left))
		{
			if (currentInputState == ButtonState::BLOCK && currentDrag != nullptr)
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

			if (currentInputState == ButtonState::TERRAIN)
			{
				auto it = find(ingGrid.begin(), ingGrid.end(), mousePosGrid);
				if (it == ingGrid.end())
				{
					//CreateBackGround(mousePosGrid.x, mousePosGrid.y);
				}

				ingGrid.push_back(mousePosGrid);
			}
		}

		switch (currentInputState)
		{
		case::ButtonState::TERRAIN:
			if (InputManager::GetMouseButtonUp(Mouse::Button::Left))
			{
				upGrid = mousePosGrid;
				std::cout << "UGrid : " << upGrid.x << " " << upGrid.y << "\n";
				ingGrid.clear();
			}
			break;

		case::ButtonState::BLOCK:
			if (InputManager::GetMouseButtonUp(Mouse::Button::Left))
			{
				CollisionBlock* block = new CollisionBlock(currentDrag->getGlobalBounds(), downGrid);
				blocks.push_back(block);

				delete currentDrag;
				currentDrag = nullptr;
				
				upGrid = mousePosGrid;
				std::cout << "UGrid : " << upGrid.x << " " << upGrid.y << "\n";
			}
			break;

		default:
			break;
		}

		if (InputManager::GetKeyDown(Keyboard::F8))
		{
			if (player != nullptr)
			{
				delete player;
			}
			player = new Player();
			player->Init(nullptr);
			player->Spawn(mousePosWorld.x, mousePosWorld.y);
		}

		if (player != nullptr)
		{
			if (player->GetPause() == false)
			{
				if (player->GetAlive() == false)
				{
					dt *= 0.25f;
				}

				/*player->Update(dt, blocks, playTime);*/
			}

			if (InputManager::GetKeyDown(Keyboard::F9))
			{
				delete player;
				player = nullptr;
			}
		}
		if (InputManager::GetKeyDown(Keyboard::Num1))
		{
			isDraw = !isDraw;
		}
	}
	
	UpdateSelectTexture();
}

void MapScene::Draw(RenderWindow* window, View* mainView, View* uiView)
{
	//Object Render
	window->setView(*mapView);

	if (isDraw)
	{
		window->draw(shape);

		for (int i = 0; i < mapWidth; i++)
		{
			for (int j = 0; j < mapHeight; j++)
			{
				window->draw(gridTileMap[i][j]);
			}
		}
	}


	window->draw(vertexMap, &selectTexture);

	if (InputManager::GetMouseButton(Mouse::Button::Left) && currentInputState == ButtonState::BLOCK && currentDrag != nullptr)
	{
		window->draw(*currentDrag);
	}

	if (isDraw)
	{
		for (auto blockShape : blocks)
		{
			window->draw(blockShape->GetBlockShape());
		}
	}
	
	window->draw(tileSelector);

	if (player != nullptr)
	{
		player->Draw(window, mapView);
	}

	window->draw(currentTextureShape);

	//UI Render
	window->setView(*uiView);
	window->draw(mousePosText);
	window->draw(stateText);
	for (auto button : buttons)
	{
		window->draw(button.buttonShape);
		window->draw(button.buttonText);
	}

	if (isSelect)
	{
		for (auto button : selectButtons)
		{
			window->draw(button.buttonShape);
			window->draw(button.buttonText);
		}
	}

	window->setView(*mapView);
	
}

void MapScene::MoveView(float dt)
{
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
}

void MapScene::UpdateMousePos(RenderWindow* window)
{
	mousePosScreen = Mouse::getPosition();
	mousePosWindow = Mouse::getPosition(*window);
	mousePosWorld = window->mapPixelToCoords(mousePosWindow);

	if (mousePosWorld.x >= 0.f && mousePosWorld.y >= 0.f && mousePosWorld.x <= mapWidth * gridSizeU && mousePosWorld.y <= mapHeight * gridSizeU)
	{
		mousePosGrid.x = mousePosWorld.x / gridSizeU;
		mousePosGrid.y = mousePosWorld.y / gridSizeU;
	}

	tileSelector.setPosition(mousePosGrid.x * gridSizeF, mousePosGrid.y * gridSizeF);
	std::stringstream ss;
	ss << "Screen : " << mousePosScreen.x << " " << mousePosScreen.y << "\n"
		<< "Window : " << mousePosWindow.x << " " << mousePosWindow.y << "\n"
		<< "World : " << mousePosWorld.x << " " << mousePosWorld.y << "\n"
		<< "Grid : " << mousePosGrid.x << " " << mousePosGrid.y << "\n";
	mousePosText.setString(ss.str());
	mousePosText.setPosition(mousePosWindow.x + 10.f, mousePosWindow.y + 10.f);
}

void MapScene::CreateDefaultButtonSet()
{
	Button buttonBlock = InitButton(resolution.x * 0.75f - 105.f, resolution.y * 0.05f, 100.f, 50.f, "Collision\n  Block  ", ButtonType::DEFAULT, ButtonCategory::INPUT, ButtonState::BLOCK);
	buttons.push_back(buttonBlock);

	Button buttonGate = InitButton(resolution.x * 0.75f, resolution.y * 0.05f, 100.f, 50.f, "Gate", ButtonType::DEFAULT, ButtonCategory::INPUT, ButtonState::GATE);
	buttons.push_back(buttonGate);

	Button buttonTerrain = InitButton(resolution.x * 0.75f + 105.f, resolution.y * 0.05f, 100.f, 50.f, "Terrain", ButtonType::DEFAULT, ButtonCategory::INPUT, ButtonState::TERRAIN);
	buttons.push_back(buttonTerrain);

	Button buttonObject = InitButton(resolution.x * 0.75f + 105.f + 105.f, resolution.y * 0.05f, 100.f, 50.f, "Object", ButtonType::DEFAULT, ButtonCategory::INPUT, ButtonState::OBJECT);
	buttons.push_back(buttonObject);

	Button buttonBackGround = InitButton(resolution.x * 0.75f + (105.f * 3.f), resolution.y * 0.05f, 100.f, 50.f, "BackGround", ButtonType::DEFAULT, ButtonCategory::INPUT, ButtonState::BACKGROUND);
	buttons.push_back(buttonBackGround);
}

void MapScene::CreateSelectButtonSet(ButtonState state)
{
	isSelect = true;
	float posX = resolution.x * 0.5f;
	float posY = resolution.y * 0.15f;
	int i = 0;

	switch (state)
	{
	case ButtonState::BLOCK:
		
		isSelect = false;

		selectButtons.clear();

		break;

	case ButtonState::GATE:

		isSelect = false;

		selectButtons.clear();

		break;

	case ButtonState::OBJECT:
		
		isSelect = true;

		selectButtons.clear();

		posX = resolution.x * 0.5f;
		posY = resolution.y * 0.15f;

		i = 0;

		for (auto iter : objectResource)
		{
			if (i % 12 == 0)
			{
				posX += 305.f;
				posY = resolution.y * 0.15f;
			}

			posY += 55.f;
			i++;

			Button button;
			button = InitButton(posX, posY, 300.f, 50.f, iter.first, ButtonType::DEFAULT, ButtonCategory::SELECT, ButtonState::OBJECT);
			selectButtons.push_back(button);
		}
		break;

	case ButtonState::TERRAIN:

		isSelect = true;

		selectButtons.clear();

		posX = resolution.x * 0.5f;
		posY = resolution.y * 0.15f;

		i = 0;

		for (auto iter : terrainResource)
		{
			if (i % 12 == 0)
			{
				posX += 305.f;
				posY = resolution.y * 0.15f;
			}

			posY += 55.f;
			i++;

			Button button;
			button = InitButton(posX, posY, 300.f, 50.f, iter.first, ButtonType::DEFAULT, ButtonCategory::SELECT, ButtonState::TERRAIN);
			selectButtons.push_back(button);
		}
		break;

	case ButtonState::BACKGROUND:

		isSelect = true;

		selectButtons.clear();

		posX = resolution.x * 0.5f;
		posY = resolution.y * 0.15f;

		i = 0;

		for (auto iter : backGroundResource)
		{
			if (i % 12 == 0)
			{
				posX += 305.f;
				posY = resolution.y * 0.15f;
			}

			posY += 55.f;
			i++;

			Button button;
			button = InitButton(posX, posY, 300.f, 50.f, iter.first, ButtonType::DEFAULT, ButtonCategory::SELECT, ButtonState::BACKGROUND);
			selectButtons.push_back(button);
		}
		break;


	}
}

Button MapScene::InitButton(float left, float top, float width, float height, string name, ButtonType type, ButtonCategory category, ButtonState state)
{
	RectangleShape buttonShape(Vector2f(width, height));
	buttonShape.setFillColor({15, 153, 153, 125});
	buttonShape.setPosition(left, top);

	FloatRect buttonRect(left, top, width, height);

	Text buttonText;
	buttonText.setFont(font);
	buttonText.setCharacterSize(15);
	buttonText.setFillColor(Color::Black);
	buttonText.setString(name);
	buttonText.setOrigin(buttonText.getLocalBounds().left + buttonText.getLocalBounds().width * 0.5, buttonText.getLocalBounds().top + buttonText.getLocalBounds().height * 0.5);
	buttonText.setPosition(left + width * 0.5, top + height * 0.5);

	Button button;
	button.buttonRect = buttonRect;
	button.buttonShape = buttonShape;
	button.buttonText = buttonText;
	button.buttonType = type;
	button.buttonCategory = category;
	button.buttonState = state;
	button.isButtonToggle = false;
	button.isButtonClick = false;

	return button;
}

bool MapScene::UpdateButton()
{
	bool isButtonUpdate = false;

	for (Button& button : buttons)
	{
		if (button.buttonRect.contains(mousePosWindow.x, mousePosWindow.y)) //Hover
		{	
			button.buttonShape.setFillColor(Color(255, 0, 0, 125)); //Red

			if (InputManager::GetMouseButtonDown(Mouse::Button::Left))
			{
				button.isButtonClick = true;
				std::cout << "ButtonDown" << std::endl;
			}

			if (InputManager::GetMouseButton(Mouse::Button::Left) && button.isButtonClick)	
			{
				button.buttonShape.setFillColor(Color::Blue); //Blue
				std::cout << "Button" << std::endl;
			}

			if (InputManager::GetMouseButtonUp(Mouse::Button::Left))
			{
				switch (button.buttonType)
				{
				case ButtonType::DEFAULT:
					if (button.buttonCategory == ButtonCategory::INPUT)
					{
						SetCurrentInputState(button.buttonState);
						CreateSelectButtonSet(button.buttonState);
					}

					if (button.buttonCategory == ButtonCategory::DRAW)
					{
						SetCurrentDrawState(button.buttonState);
						CreateSelectButtonSet(button.buttonState);
					}
					break;
				
				case ButtonType::TOGGLE:
					break;

				default:
					break;
				}

				button.buttonShape.setFillColor(Color(255, 0, 0, 125)); //Red
				button.isButtonClick = false;
				std::cout << "ButtonUp" << std::endl;
			}

			isButtonUpdate = true;
		}
		else
		{
			button.buttonShape.setFillColor(Color(153, 153, 153, 125)); //Gray
		}
	}

	for (Button& button : selectButtons)
	{
		if (button.buttonRect.contains(mousePosWindow.x, mousePosWindow.y)) //Hover
		{
			button.buttonShape.setFillColor(Color(255, 0, 0, 125)); //Red

			if (InputManager::GetMouseButtonDown(Mouse::Button::Left))
			{
				button.isButtonClick = true;
			}

			if (InputManager::GetMouseButton(Mouse::Button::Left) && button.isButtonClick)
			{
				button.buttonShape.setFillColor(Color::Blue); //Blue
			}

			if (InputManager::GetMouseButtonUp(Mouse::Button::Left))
			{
				if (button.buttonState == ButtonState::BACKGROUND)
				{
					cout << (string)button.buttonText.getString() << endl;
					selectTexture = backGroundResource.find((string)button.buttonText.getString())->second;
				}

				if (button.buttonState == ButtonState::OBJECT)
				{
					cout << (string)button.buttonText.getString() << endl;
					selectTexture = objectResource.find((string)button.buttonText.getString())->second.tex;
				}

				if (button.buttonState == ButtonState::TERRAIN)
				{
					cout << (string)button.buttonText.getString() << endl;
					selectTexture = terrainResource.find((string)button.buttonText.getString())->second.tex;
				}

				button.buttonShape.setFillColor(Color(255, 0, 0, 125)); //Red
				button.isButtonClick = false;
			}

			isButtonUpdate = true;
		}
		else
		{
			button.buttonShape.setFillColor(Color(15, 153, 153, 125)); //Gray
		}
	}
	std::stringstream ss;
	string inputState;
	switch (currentInputState)
	{
	case ButtonState::BLOCK:
		inputState = "BLOCK";
		break;
	case ButtonState::NONE:
		inputState = "NONE";
		break;
	case ButtonState::OBJECT:
		inputState = "OBJECT";
		break;
	case ButtonState::TERRAIN:
		inputState = "TERRAIN";
		break;
	}
	string drawState;
	switch (currentDrawState)
	{
	case ButtonState::BLOCK:
		drawState = "BLOCK";
		break;
	case ButtonState::NONE:
		drawState = "NONE";
		break;
	case ButtonState::OBJECT:
		drawState = "OBJECT";
		break;
	case ButtonState::TERRAIN:
		drawState = "TERRAIN";
		break;
	}
	ss << "InputState : " << inputState << '\n'
		<< "DrawState : " << drawState << std::endl;

	stateText.setString(ss.str());

	return isButtonUpdate;
}

void MapScene::SetCurrentInputState(ButtonState state)
{
	currentInputState = state;
}

void MapScene::SetCurrentDrawState(ButtonState state)
{
	currentDrawState = state;
}

void MapScene::MapDataInit()
{
	//Map Resource
	rapidcsv::Document resouceBackGrounds("data_tables/maps/Resource_BackGround.csv");
	std::vector<std::string> colResouceBackGroundsId = resouceBackGrounds.GetColumn<std::string>("resourceId");
	std::vector<std::string> colResouceBackGroundsPath = resouceBackGrounds.GetColumn<std::string>("resourcePath");
	int totalResouceBackGrounds = colResouceBackGroundsId.size();
	for (int i = 0; i < totalResouceBackGrounds; ++i)
	{
		backGroundResource.insert({ colResouceBackGroundsId[i], TextureHolder::GetTexture(colResouceBackGroundsPath[i])});
	}

	rapidcsv::Document resouceObjects("data_tables/maps/Resource_Object.csv");
	std::vector<std::string> colResouceObjectsId = resouceObjects.GetColumn<std::string>("resourceId");
	std::vector<std::string> colResouceObjectsPath = resouceObjects.GetColumn<std::string>("resourcePath");
	std::vector<std::string> colResouceObjectsType = resouceObjects.GetColumn<std::string>("resourceType");
	int totalResouceObjects = colResouceObjectsId.size();
	for (int i = 0; i < totalResouceObjects; ++i)
	{
		ObjectResource object;
		object.tex = TextureHolder::GetTexture(colResouceObjectsPath[i]);
		object.type = colResouceObjectsType[i];
		objectResource.insert({ colResouceObjectsId[i], object });
	}

	rapidcsv::Document resouceTerrains("data_tables/maps/Resource_Terrain.csv");
	std::vector<std::string> colResouceTerrainsId = resouceTerrains.GetColumn<std::string>("resourceId");
	std::vector<std::string> colResouceTerrainsPath = resouceTerrains.GetColumn<std::string>("resourcePath");
	int totalResouceTerrains = colResouceTerrainsId.size();
	for (int i = 0; i < totalResouceTerrains; ++i)
	{
		TerrainResource terrain;
		terrain.tex = TextureHolder::GetTexture(colResouceTerrainsPath[i]);
		terrain.angle = 0.f;
		terrain.flip = Flip::NONE;
		terrainResource.insert({ colResouceTerrainsId[i], terrain });
	}

	//Map information
	rapidcsv::Document clips("data_tables/maps/Map_Clips.csv");
	std::vector<std::string> colId = clips.GetColumn<std::string>("mapId");
	std::vector<int> colWidth = clips.GetColumn<int>("mapWidth");
	std::vector<int> colHeight = clips.GetColumn<int>("mapHeight");
	std::vector<std::string> colPath = clips.GetColumn<std::string>("mapDataPath");

	int totalMaps = colId.size();

	mapWidth = colWidth[0];
	mapHeight = colHeight[0];
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

void MapScene::UpdateSelectTexture()
{
	fromX = mousePosGrid.x;
	fromY = mousePosGrid.y;

	currentTextureShape.setFillColor({255, 255, 255, 75});
	currentTextureShape.setTexture(&selectTexture, true);
	currentTextureShape.setSize(Vector2f(1.f, 1.f));
	currentTextureShape.setScale(selectTexture.getSize().x, selectTexture.getSize().y);
	currentTextureShape.setPosition((fromX + (currentTextureShape.getLocalBounds().width * 0.5f)) * gridSizeU, (fromY + (currentTextureShape.getLocalBounds().height * 0.5f)) * gridSizeU);
	currentTextureShape.setOrigin(currentTextureShape.getLocalBounds().width * 0.5f, currentTextureShape.getLocalBounds().height * 0.5f);
	//currentTextureShape.setRotation(180.f);
}

//Map 순회
/*for (auto iter : backGroundResource)
	{
		cout << iter.first << " " << iter.second.getSize().x << endl;
	}*/

//Vertex
/*int MapScene::CreateBackGround(int c, int r)
{
	int TILE_WIDTH = 32;
	int TILE_HEIGHT = 32;
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

	vertexMap[vertexIndex + 0].position = Vector2f(x, y);
	vertexMap[vertexIndex + 1].position = Vector2f(x + TILE_WIDTH, y);
	vertexMap[vertexIndex + 2].position = Vector2f(x + TILE_WIDTH, y + TILE_HEIGHT);
	vertexMap[vertexIndex + 3].position = Vector2f(x, y + TILE_HEIGHT);
	
	vertexMap[vertexIndex + 0].texCoords = Vector2f(0.f, 0.f);
	vertexMap[vertexIndex + 1].texCoords = Vector2f(TILE_WIDTH, 0.f);
	vertexMap[vertexIndex + 2].texCoords = Vector2f(TILE_WIDTH, TILE_HEIGHT);
	vertexMap[vertexIndex + 3].texCoords = Vector2f(0.f, TILE_HEIGHT);
	
	return cols * rows;
}*/

//csv 파일쓰기
/*

csvfile csv("Test.csv");
csv << "X" << "VALUE" << endrow;
// Data
int i = 1;
csv << i++ << 123 << endrow;

*/

//미리보기
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