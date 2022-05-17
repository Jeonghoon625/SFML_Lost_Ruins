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
	DefaultMapInit();

	VIEW_SPEED = mapWidth * 10.f;
	this->sceneMgr = sceneManager;

	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

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
			gridTileMap[i][j].setFillColor({255, 255, 255});
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

	currentMapIdText.setCharacterSize(30);
	currentMapIdText.setFillColor(Color::Red);
	currentMapIdText.setFont(font);
	currentMapIdText.setPosition(resolution.x * 0.393f, 7.f);
	currentMapIdText.setString("Map Id : Default");

	//test
	isDraw = true;
	isSelect = false;

	//Default Button Set
	CreateDefaultButtonSet();
}

void MapScene::DefaultMapInit()
{
	//Map Resource
	rapidcsv::Document resouceBackGrounds("data_tables/maps/Resource/Resource_BackGround.csv");
	std::vector<std::string> colResouceBackGroundsId = resouceBackGrounds.GetColumn<std::string>("resourceId");
	std::vector<std::string> colResouceBackGroundsPath = resouceBackGrounds.GetColumn<std::string>("resourcePath");
	int totalResouceBackGrounds = colResouceBackGroundsId.size();
	for (int i = 0; i < totalResouceBackGrounds; ++i)
	{
		backGroundResource.insert({ colResouceBackGroundsId[i], TextureHolder::GetTexture(colResouceBackGroundsPath[i]) });
	}

	rapidcsv::Document resouceObjects("data_tables/maps/Resource/Resource_Object.csv");
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

	rapidcsv::Document resouceTerrains("data_tables/maps/Resource/Resource_Terrain.csv");
	std::vector<std::string> colResouceTerrainsId = resouceTerrains.GetColumn<std::string>("resourceId");
	std::vector<std::string> colResouceTerrainsPath = resouceTerrains.GetColumn<std::string>("resourcePath");
	int totalResouceTerrains = colResouceTerrainsId.size();
	for (int i = 0; i < totalResouceTerrains; ++i)
	{
		TerrainResource terrain;
		terrain.tex = TextureHolder::GetTexture(colResouceTerrainsPath[i]);
		terrain.type = "T";
		terrainResource.insert({ colResouceTerrainsId[i], terrain });
	}

	//Map information
	rapidcsv::Document mapList("data_tables/maps/Map_List.csv");
	std::vector<std::string> colId = mapList.GetColumn<std::string>("mapId");
	std::vector<int> colWidth = mapList.GetColumn<int>("mapWidth");
	std::vector<int> colHeight = mapList.GetColumn<int>("mapHeight");
	std::vector<std::string> colspritePath = mapList.GetColumn<std::string>("spritePath");
	std::vector<std::string> colblockPath = mapList.GetColumn<std::string>("blockPath");
	int totalMaps = colId.size();

	currentMapId = colId[0];
	mapWidth = colWidth[0];
	mapHeight = colHeight[0];
	spritePath = colspritePath[0];
	blockPath = colblockPath[0];
}

Button MapScene::InitButton(float left, float top, float width, float height, string name, ButtonType type, ButtonCategory category, ButtonState state)
{
	RectangleShape buttonShape(Vector2f(width, height));
	buttonShape.setFillColor({ 15, 153, 153, 125 });
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

void MapScene::Update(float dt, Time playTime, RenderWindow* window, View* mainView, View* uiView)
{
	UpdateMousePos(window);
	MoveView(dt);

	if (!UpdateButton())
	{
		if (InputManager::GetMouseButtonDown(Mouse::Button::Left))
		{
			if (mousePosWorld.x < 0.f || mousePosWorld.y < 0.f || (mousePosWorld.x > mapWidth * gridSizeU) ||(mousePosWorld.y > mapHeight * gridSizeU))
			{
				currentInputState = ButtonState::NONE;
				selectButtons.clear();
				//currentInput.shape.setFillColor(Color::Transparent);
			}

			downGrid = mousePosGrid;
			//std::cout << "DGrid : " << downGrid.x << " " << downGrid.y << "\n";
			ingGrid.push_back(mousePosGrid);
			if (currentInputState == ButtonState::TERRAIN || currentInputState == ButtonState::OBJECT || currentInputState == ButtonState::BACKGROUND)
			{
				if(currentInput != nullptr)
				{
					CreateInputData(*currentInput);
				}
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

			if (currentInputState == ButtonState::TERRAIN && currentInput != nullptr)
			{
				CreateInputData(*currentInput);
			}
		}

		switch (currentInputState)
		{
		case::ButtonState::TERRAIN:
			if (InputManager::GetMouseButtonUp(Mouse::Button::Left))
			{
				upGrid = mousePosGrid;
				std::cout << "UGrid : " << upGrid.x << " " << upGrid.y << "\n";

				if (currentInput != nullptr)
				{
					CreateInputData(*currentInput);
				}

				ingGrid.clear();
			}
			break;

		case::ButtonState::BLOCK:
			if (InputManager::GetMouseButtonUp(Mouse::Button::Left) && currentDrag != nullptr)
			{
				CollisionBlock* block = new CollisionBlock(currentDrag->getGlobalBounds(), downGrid);
				blocks.push_back(block);

				delete currentDrag;
				currentDrag = nullptr;
				
				upGrid = mousePosGrid;
				std::cout << "UGrid : " << upGrid.x << " " << upGrid.y << "\n";

				ingGrid.clear();
			}
			break;

		default:
			ingGrid.clear();
			break;
		}

		if (InputManager::GetKeyDown(Keyboard::F8))
		{
			if (player != nullptr)
			{
				delete player;
			}
			player = new Player();
			player->Init(monsters);
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

				player->Update(dt, blocks, playTime, monsters);
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
		for (int i = 0; i < mapWidth; i++)
		{
			for (int j = 0; j < mapHeight; j++)
			{
				window->draw(gridTileMap[i][j]);
			}
		}
	}

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

	for (auto backGround : backGroundInput)
	{
		window->draw(backGround.shape);
	}

	for (auto terrain : terrainInput)
	{
		window->draw(terrain.shape);
	}

	for (auto object : objectInput)
	{
		window->draw(object.shape);
	}

	window->draw(tileSelector);

	if (player != nullptr)
	{
		player->Draw(window, mapView);
	}

	if (currentInputState != ButtonState::NONE && currentInput != nullptr)
	{
		window->draw(currentInput->shape);
	}
	
	//UI Render
	window->setView(*uiView);
	window->draw(mousePosText);
	window->draw(stateText);
	window->draw(currentMapIdText);

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
	Button buttonSave = InitButton(resolution.x * 0.75f - 105.f - 105.f - 105.f - 105.f - 105.f - 105.f - 105.f, resolution.y * 0.05f, 100.f, 50.f, "Save", ButtonType::DEFAULT, ButtonCategory::INPUT, ButtonState::NONE);
	buttons.push_back(buttonSave);

	Button buttonLoad = InitButton(resolution.x * 0.75f - 105.f - 105.f - 105.f - 105.f - 105.f - 105.f, resolution.y * 0.05f, 100.f, 50.f, "Load", ButtonType::DEFAULT, ButtonCategory::INPUT, ButtonState::NONE);
	buttons.push_back(buttonLoad);
	
	Button buttonClear = InitButton(resolution.x * 0.75f - 105.f - 105.f - 105.f - 105.f - 105.f, resolution.y * 0.05f, 100.f, 50.f, "All\nClear", ButtonType::DEFAULT, ButtonCategory::DELETE, ButtonState::NONE);
	buttons.push_back(buttonClear);

	Button buttonUndoBlock = InitButton(resolution.x * 0.75f, resolution.y * 0.05f + 55.f, 100.f, 50.f, "Undo\nBlock", ButtonType::DEFAULT, ButtonCategory::DELETE, ButtonState::OBJECT);
	buttons.push_back(buttonUndoBlock);

	Button buttonUndoTerrain = InitButton(resolution.x * 0.75f + 105.f, resolution.y * 0.05f + 55.f, 100.f, 50.f, "Undo\nTerrain", ButtonType::DEFAULT, ButtonCategory::DELETE, ButtonState::BLOCK);
	buttons.push_back(buttonUndoTerrain);

	Button buttonUndoObject = InitButton(resolution.x * 0.75f + 105.f + 105.f, resolution.y * 0.05f + 55.f, 100.f, 50.f, "Undo\nObject", ButtonType::DEFAULT, ButtonCategory::DELETE, ButtonState::TERRAIN);
	buttons.push_back(buttonUndoObject);

	Button buttonUndoBack = InitButton(resolution.x * 0.75f + 105.f + 105.f + 105.f, resolution.y * 0.05f + 55.f, 100.f, 50.f, "Undo\nBackGround", ButtonType::DEFAULT, ButtonCategory::DELETE, ButtonState::BACKGROUND);
	buttons.push_back(buttonUndoBack);


	Button buttonBlock = InitButton(resolution.x * 0.75f, resolution.y * 0.05f, 100.f, 50.f, "Collision\n  Block  ", ButtonType::DEFAULT, ButtonCategory::INPUT, ButtonState::BLOCK);
	buttons.push_back(buttonBlock);

	Button buttonTerrain = InitButton(resolution.x * 0.75f + 105.f, resolution.y * 0.05f, 100.f, 50.f, "Terrain", ButtonType::DEFAULT, ButtonCategory::INPUT, ButtonState::TERRAIN);
	buttons.push_back(buttonTerrain);

	Button buttonObject = InitButton(resolution.x * 0.75f + 105.f + 105.f, resolution.y * 0.05f, 100.f, 50.f, "Object", ButtonType::DEFAULT, ButtonCategory::INPUT, ButtonState::OBJECT);
	buttons.push_back(buttonObject);

	Button buttonBackGround = InitButton(resolution.x * 0.75f + (105.f * 3.f), resolution.y * 0.05f, 100.f, 50.f, "BackGround", ButtonType::DEFAULT, ButtonCategory::INPUT, ButtonState::BACKGROUND);
	buttons.push_back(buttonBackGround);
}

void MapScene::CreateSelectButtonSet(string buttonName)
{
	isSelect = true;
	float posX = resolution.x * 0.5f;
	float posY = resolution.y * 0.15f;
	int i = 0;

	Button buttonDelete;
	
	isSelect = true;

	selectButtons.clear();

	posX = resolution.x * 0.5f;
	posY = resolution.y * 0.15f;

	if (buttonName == "Object")
	{
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
	}

	if (buttonName == "Terrain")
	{
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
	}

	if (buttonName == "BackGround")
	{
		posX += 610.f;

		for (auto iter : backGroundResource)
		{
			posY += 55.f;
			i++;

			Button button;
			button = InitButton(posX, posY, 300.f, 50.f, iter.first, ButtonType::DEFAULT, ButtonCategory::SELECT, ButtonState::BACKGROUND);
			selectButtons.push_back(button);
		}
	}
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

					if (currentInput != nullptr)
					{
						delete currentInput;
					}

					currentInput = nullptr;

					if (button.buttonCategory == ButtonCategory::INPUT)
					{
						SetCurrentInputState(button.buttonState);
						CreateSelectButtonSet(button.buttonText.getString());
					}

					if (button.buttonCategory == ButtonCategory::DRAW)
					{
						SetCurrentDrawState(button.buttonState);
						CreateSelectButtonSet(button.buttonText.getString());
					}

					if (button.buttonCategory == ButtonCategory::DELETE)
					{
						string undo = button.buttonText.getString();

						if (undo == "Undo\nBlock")
						{
							if (!blocks.empty())
							{
								if (*(blocks.end() - 1) != nullptr)
								{
									delete* (blocks.end() - 1);
									*(blocks.end() - 1) = nullptr;
								}
								blocks.pop_back();
							}
						}

						if (undo == "Undo\nTerrain")
						{
							if (!terrainInput.empty())
							{
								terrainInput.pop_back();
							}
						}

						if (undo == "Undo\nBackGround")
						{
							if (!backGroundInput.empty())
							{
								backGroundInput.pop_back();
							}
						}

						if (undo == "Undo\nObject")
						{
							if (!objectInput.empty())
							{
								objectInput.pop_back();
							}
						}

						if (undo == "All\nClear")
						{
							terrainInput.clear();
							objectInput.clear();
							backGroundInput.clear();

							for (auto it : blocks)
							{
								if (it != nullptr)
								{
									delete it;
									it = nullptr;
								}
							}
						}
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
				currentInputState = (button.buttonState);

				if (currentInput != nullptr)
				{
					delete currentInput;
					currentInput = nullptr;
				}

				currentInput = new InputData();
				currentInput->resourceId = (string)button.buttonText.getString();
				currentInput->rotate = 0.f;

				if (button.buttonState == ButtonState::BACKGROUND)
				{
					currentTexture = backGroundResource.find((string)button.buttonText.getString())->second;
					
					currentInput->scaleX = 96.f;
					currentInput->scaleY = 96.f;
				}

				if (button.buttonState == ButtonState::OBJECT || button.buttonState == ButtonState::TERRAIN)
				{
					if (button.buttonState == ButtonState::OBJECT)
					{
						currentTexture = objectResource.find((string)button.buttonText.getString())->second.tex;
					}
					else
					{
						currentTexture = terrainResource.find((string)button.buttonText.getString())->second.tex;
					}
					
					currentInput->scaleX = currentTexture.getSize().x;
					currentInput->scaleY = currentTexture.getSize().y;
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

	case ButtonState::BACKGROUND:
		inputState = "BACKGROUND";
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

void MapScene::UpdateSelectTexture()
{
	if (currentInput != nullptr)
	{
		if (currentInputState == ButtonState::TERRAIN || currentInputState == ButtonState::BACKGROUND)
		{
			currentInput->posX = (mousePosGrid.x + (currentInput->shape.getLocalBounds().width * 0.5f)) * gridSizeU;
			currentInput->posY = (mousePosGrid.y + (currentInput->shape.getLocalBounds().height * 0.5f)) * gridSizeU;
		}
		else
		{
			currentInput->posX = mousePosWorld.x + (currentInput->shape.getLocalBounds().width * 0.5f);
			currentInput->posY = mousePosWorld.y + (currentInput->shape.getLocalBounds().height * 0.5f);
		}

		if (InputManager::GetKeyDown(Keyboard::U))
		{
			currentInput->scaleX *= -1.f;
		}

		if (InputManager::GetKeyDown(Keyboard::I))
		{
			currentInput->scaleY *= -1.f;
		}

		if (InputManager::GetKeyDown(Keyboard::O))
		{
			currentInput->rotate += 90.f;
		}

		if (InputManager::GetKeyDown(Keyboard::P))
		{
			currentInput->rotate -= 90.f;
		}

		currentInput->shape.setFillColor({ 255, 255, 255, 75 });
		currentInput->shape.setTexture(&currentTexture, true);
		currentInput->shape.setSize(Vector2f(1.f, 1.f));
		currentInput->shape.setScale(currentInput->scaleX, currentInput->scaleY);
		currentInput->shape.setPosition(currentInput->posX, currentInput->posY);
		currentInput->shape.setOrigin(currentInput->shape.getLocalBounds().width * 0.5f, currentInput->shape.getLocalBounds().height * 0.5f);
		currentInput->shape.setRotation(currentInput->rotate);
	}
}

void MapScene::CreateInputData(InputData currentInputData)
{
	InputData inputData;
	inputData = currentInputData;
	inputData.shape.setFillColor({ 255,255,255 });

	switch (currentInputState)
	{
	case ButtonState::BACKGROUND:
		inputData.shape.setTexture(&(backGroundResource.find(inputData.resourceId)->second));
		
		if (CompareInputData(inputData, backGroundInput) == false)
		{
			backGroundInput.push_back(inputData);
		}
		
		break;

	case ButtonState::TERRAIN:
		inputData.shape.setTexture(&(terrainResource.find(inputData.resourceId)->second.tex));

		if (CompareInputData(inputData, terrainInput) == false)
		{
			terrainInput.push_back(inputData);
		}
		break;

	case ButtonState::OBJECT:
		inputData.shape.setTexture(&(objectResource.find(inputData.resourceId)->second.tex));

		if (CompareInputData(inputData, objectInput) == false)
		{
			objectInput.push_back(inputData);
		}
		break;
	}
}

void MapScene::Save()
{
	csvfile csvSprite("Sprite_Default.csv");

	csvSprite << "resourceType" << "resourceId" << "rotate" << "scaleX" << "scaleY" << "posX" << "posY" << endrow;
	for (auto terrain : terrainInput)
	{
		csvSprite << "terrainInput" << terrain.resourceId << terrain.rotate << terrain.scaleX << terrain.scaleY << terrain.posX << terrain.posY << endrow;
	}
	
	for (auto object : objectInput)
	{
		csvSprite << "objectInput" << object.resourceId << object.rotate << object.scaleX << object.scaleY << object.posX << object.posY << endrow;
	}

	for (auto backGround : backGroundInput)
	{
		csvSprite << "backGroundInput" << backGround.resourceId << backGround.rotate << backGround.scaleX << backGround.scaleY << backGround.posX << backGround.posY << endrow;
	}

	csvfile csvBlock("Block_Default.csv");

	int i = 0;
	csvBlock << "index" << "x" << "y" << "width" << "height" << endrow;

	for (auto block : blocks)
	{
		csvBlock << i++ << block->GetBlockRect().left << block->GetBlockRect().top << block->GetBlockRect().width << block->GetBlockRect().height << endrow;
	}
}

void MapScene::Load(string mapName)
{
	string path = "data_tables/maps/" + mapName;
	rapidcsv::Document LoadSprites(path);
	std::vector<std::string> colSpritesType = LoadSprites.GetColumn<std::string>("resourceType");
	std::vector<std::string> colSpritesId = LoadSprites.GetColumn<std::string>("resourceId");
	std::vector<float> colSpritesRotate = LoadSprites.GetColumn<float>("rotate");
	std::vector<float> colSpritesScaleX = LoadSprites.GetColumn<float>("scaleX");
	std::vector<float> colSpritesScaleY = LoadSprites.GetColumn<float>("scaleY");
	std::vector<float> colSpritesPosX = LoadSprites.GetColumn<float>("posX");
	std::vector<float> colSpritesPosY = LoadSprites.GetColumn<float>("posY");

	int totalLoadSprites = colSpritesType.size();

	for (int i = 0; i < totalLoadSprites; ++i)
	{
		InputData inputData;
		inputData.resourceId = colSpritesId[i];
		inputData.rotate = colSpritesRotate[i];
		inputData.scaleX = colSpritesScaleX[i];
		inputData.scaleY = colSpritesScaleY[i];
		inputData.posX = colSpritesPosX[i];
		inputData.posY = colSpritesPosY[i];
		inputData.shape.setSize(Vector2f(1.f, 1.f));
		inputData.shape.setScale(inputData.scaleX, inputData.scaleY);
		inputData.shape.setPosition(inputData.posX, inputData.posY);
		inputData.shape.setOrigin(inputData.shape.getLocalBounds().width * 0.5f, inputData.shape.getLocalBounds().height * 0.5f);
		inputData.shape.setRotation(inputData.rotate);

		string spriteType = colSpritesType[i];
		if (spriteType == "terrainInput")
		{
			inputData.shape.setTexture(&(terrainResource.find((string)colSpritesId[i])->second.tex), true);
			terrainInput.insert(terrainInput.begin(), inputData);
		}

		if (spriteType == "objectInput")
		{
			inputData.shape.setTexture(&(objectResource.find((string)colSpritesId[i])->second.tex), true);
			objectInput.insert(objectInput.begin(), inputData);
		}

		if (spriteType == "backGroundInput")
		{
			inputData.shape.setTexture(&(backGroundResource.find((string)colSpritesId[i])->second), true);
			backGroundInput.insert(backGroundInput.begin(), inputData);
		}
	}
}

void MapScene::SetCurrentInputState(ButtonState state)
{
	currentInputState = state;
}

void MapScene::SetCurrentDrawState(ButtonState state)
{
	currentDrawState = state;
}

bool MapScene::CompareInputData(InputData inputData, vector<InputData> inputDatas)
{
	for (auto it : inputDatas)
	{
		if(
			it.resourceId == inputData.resourceId && 
			it.rotate == inputData.rotate &&
			it.scaleX == inputData.scaleX &&
			it.scaleY == inputData.scaleY &&
			it.posX == inputData.posX &&
			it.posY == inputData.posY
			)
		{
			return  true;
		}
	}

	return false;
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