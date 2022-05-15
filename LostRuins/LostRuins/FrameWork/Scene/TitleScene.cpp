#include "TitleScene.h"
#include "../Mgr/SceneManager.h"
#include "../Mgr/SoundHolder.h"

void TitleScene::Init(SceneManager* sceneManager)
{
	this->sceneMgr = sceneManager;
	menuPos = 1;
	loadPos = 1;

	resolution.x = 1920.f;
	resolution.y = 1080.f;

	SettingTextrue();
	SettingText();

	menuType = MenuType::MENU_SELECT;

	backGroundSound.setBuffer(SoundHolder::GetBuffer("sound/back_ground_sound.wav"));
	backGroundSound.play();
}

void TitleScene::Update(float dt, Time playTime, RenderWindow* window, View* mainView, View* uiView)
{
	aniHeroine.Update(dt);
	aniRope1.Update(dt);
	aniRope2.Update(dt);
	aniTree.Update(dt);
	aniDeadBush.Update(dt);

	switch (menuType)
	{
	case MenuType::MENU_SELECT:
		SelectingMenu(dt, window);
		break;
	case MenuType::MENU_LOAD:
		LoadingMenu(dt, window);
		break;
	case MenuType::MENU_OPTION:
		break;
	}
}

void TitleScene::Draw(RenderWindow* window, View* mainView, View* uiView)
{
	window->setView(*uiView);
	window->draw(sky);
	window->draw(backGround);
	window->draw(midGround);
	window->draw(title);
	window->draw(rope1);
	window->draw(rope2);
	window->draw(tree);
	window->draw(deadBush);
	window->draw(ForeGround);
	window->draw(heroine);

	if (menuType == MenuType::MENU_SELECT)
	{
		window->draw(topBar);
		window->draw(bottomBar);
	}

	window->draw(textGameStart);
	window->draw(textContinue);
	window->draw(textOption);
	window->draw(textMapEditor);
	window->draw(textExit);

	if (menuType == MenuType::MENU_LOAD)
	{
		window->draw(loadBack);
		window->draw(loadBar);
		window->draw(loadScreen);
		window->draw(loadSlot);
		for (int i = 0; i < MAX_SAVE_SLOT; i++)
		{
			window->draw(textLoadSlot[i]);
		}
	}
}

void TitleScene::SelectingMenu(float dt, RenderWindow* window)
{
	if (InputManager::GetKeyDown(Keyboard::Up) && menuPos > 1)
	{
		menuPos--;
	}
	else if (InputManager::GetKeyDown(Keyboard::Down) && menuPos < MAX_MENU_SLOT)
	{
		menuPos++;
	}

	switch (menuPos)
	{
	case GAME_START:
		textGameStart.setFillColor(Color::White);
		textContinue.setFillColor(Color(100, 100, 100));
		break;
	case CONTINUE:
		textContinue.setFillColor(Color::White);
		textGameStart.setFillColor(Color(100, 100, 100));
		textOption.setFillColor(Color(100, 100, 100));
		break;

	case OPTION:
		textOption.setFillColor(Color::White);
		textContinue.setFillColor(Color(100, 100, 100));
		textMapEditor.setFillColor(Color(100, 100, 100));
		break;

	case MAPEDIT:
		textMapEditor.setFillColor(Color::White);
		textOption.setFillColor(Color(100, 100, 100));
		textExit.setFillColor(Color(100, 100, 100));
		break;
		
	case EXIT:
		textExit.setFillColor(Color::White);
		textMapEditor.setFillColor(Color(100, 100, 100));
		break;
	}

	if (InputManager::GetKeyDown(Keyboard::Space))
	{
		GetSelect(window);
	}
}

void TitleScene::LoadingMenu(float dt, RenderWindow* window)
{
	if (InputManager::GetKeyDown(Keyboard::Up) && loadPos > 1)
	{
		loadPos--;
	}
	else if (InputManager::GetKeyDown(Keyboard::Down) && loadPos < MAX_SAVE_SLOT)
	{
		loadPos++;
	}

	window->draw(textGameStart);
	window->draw(textContinue);
	window->draw(textOption);
	window->draw(textMapEditor);
	window->draw(textExit);

	switch (loadPos)
	{
	case 1:
		loadSlot.setPosition(resolution.x * 0.5f, 500.f);
		break;
	case 2:
		loadSlot.setPosition(resolution.x * 0.5f, 500.f + 80.f);
		break;
	case 3:
		loadSlot.setPosition(resolution.x * 0.5f, 500.f + 160.f);
		break;
	}

	if (InputManager::GetKeyDown(Keyboard::Escape))
	{
		menuType = MenuType::MENU_SELECT;
	}
	else if (InputManager::GetKeyDown(Keyboard::Space))
	{

	}
}

void TitleScene::GetSelect(RenderWindow* window)
{
	switch (menuPos)
	{
	case GAME_START:
		sceneMgr->SceneSwitch(SceneType::GameScene);
		break;

	case CONTINUE:
		menuType = MenuType::MENU_LOAD;
		break;

	case OPTION:
		break;

	case MAPEDIT:
		sceneMgr->SceneSwitch(SceneType::MapScene);
		break;

	case EXIT:
		window->close();
		break;
	}
}

void TitleScene::SettingTextrue()
{
	textureTitle = TextureHolder::GetTexture("graphics/title.png");
	textureUi = TextureHolder::GetTexture("graphics/UI.png");

	sky.setTexture(textureTitle);
	sky.setTextureRect(IntRect(1, 1233, 640, 360));
	sky.setScale(Vector2f(3.f, 3.f));
	sky.setPosition(0, 0);

	backGround.setTexture(textureTitle);
	backGround.setTextureRect(IntRect(1, 1145, 480, 73));
	backGround.setOrigin(240, 73);
	backGround.setScale(Vector2f(4.f, 4.f));
	backGround.setPosition(resolution.x * 0.5f, resolution.y - 130);

	midGround.setTexture(textureTitle);
	midGround.setTextureRect(IntRect(1, 892, 410, 236));
	midGround.setOrigin(0, 236);
	midGround.setScale(Vector2f(4.f, 4.f));
	midGround.setPosition(-205, resolution.y + 140);

	title.setTexture(textureTitle);
	title.setTextureRect(IntRect(1, 1, 1162, 157));
	title.setPosition(120, 180);

	ForeGround.setTexture(textureTitle);
	ForeGround.setTextureRect(IntRect(1, 697, 640, 180));
	ForeGround.setOrigin(320, 180);
	ForeGround.setScale(Vector2f(4.f, 4.f));
	ForeGround.setPosition(resolution.x * 0.5f, resolution.y + 100);

	topBar.setSize(Vector2f(resolution.x, 80));
	topBar.setFillColor(Color::Black);
	topBar.setOrigin(0, 0);
	topBar.setPosition(0, 0);

	bottomBar.setSize(Vector2f(resolution.x, 80));
	bottomBar.setFillColor(Color::Black);
	bottomBar.setOrigin(0, 80);
	bottomBar.setPosition(0, resolution.y);

	heroine.setOrigin(0, 137);
	heroine.setPosition(resolution.x * 0.7f, resolution.y + 30);
	heroine.setScale(3.5f, 3.5f);
	AnimationInit(aniHeroine, &heroine);
	aniHeroine.Play("heroine");

	rope1.setOrigin(0.f, 60.f);
	rope1.setPosition(resolution.x * 0.5f - 230.f, resolution.y * 0.5f + 400.f);
	rope1.setScale(3.5f, 3.5f);
	AnimationInit(aniRope1, &rope1);
	aniRope1.Play("rope1");

	rope2.setOrigin(0.f, 80.f);
	rope2.setPosition(resolution.x * 0.5f + 130.f, resolution.y * 0.5f + 480.f);
	rope2.setScale(3.5f, 3.5f);
	AnimationInit(aniRope2, &rope2);
	aniRope2.Play("rope2");

	tree.setOrigin(103.f, 0.f);
	tree.setPosition(resolution.x, resolution.y*0.1f);
	tree.setScale(3.5f, 3.5f);
	AnimationInit(aniTree, &tree);
	aniTree.Play("tree");

	deadBush.setOrigin(25.f, 20.f);
	deadBush.setPosition(resolution.x * 0.37f, resolution.y - 200.f);
	deadBush.setScale(4.f, 4.f);
	AnimationInit(aniDeadBush, &deadBush);
	aniDeadBush.Play("deadBush");

	loadBack.setSize(Vector2f(820.f, resolution.y));
	loadBack.setFillColor(Color(0, 0, 0, 150));
	loadBack.setOrigin(820.f * 0.5f, 0);
	loadBack.setPosition(resolution.x * 0.5f, 0);

	loadScreen.setSize(Vector2f(520.f, 320.f));
	loadScreen.setFillColor(Color::White);
	loadScreen.setOrigin(520.f * 0.5f, 20);
	loadScreen.setPosition(resolution.x * 0.5f, 100.f);

	loadBar.setTexture(textureUi);
	loadBar.setTextureRect(IntRect(488, 1068, 223, 64));
	loadBar.setOrigin(111.5f, 0.f);
	loadBar.setScale(4.f, 18.f);
	loadBar.setPosition(resolution.x * 0.5f, 0.f);

	loadSlot.setSize(Vector2f(800.f, 40.f));
	loadSlot.setFillColor(Color(150, 150, 150, 80));
	loadSlot.setOrigin(800.f * 0.5f, 0.f);
	loadSlot.setPosition(resolution.x * 0.5f, 500.f);
}


void TitleScene::SettingText()
{
	fontLostRuins.loadFromFile("fonts/LiberationSans-Bold.ttf");

	textGameStart.setFont(fontLostRuins);
	textGameStart.setString("Game Start");
	textGameStart.setFillColor(Color::White);
	textGameStart.setCharacterSize(40);
	textGameStart.setPosition(resolution.x * 0.1f, resolution.y * 0.5f + 110.f);
	Utils::SetOrigin(textGameStart, Pivots::LC);

	textContinue.setFont(fontLostRuins);
	textContinue.setString("Continue");
	textContinue.setFillColor(Color(100, 100, 100));
	textContinue.setCharacterSize(40);
	textContinue.setPosition(resolution.x * 0.1f, resolution.y * 0.5f + 180.f);
	Utils::SetOrigin(textContinue, Pivots::LC);

	textOption.setFont(fontLostRuins);
	textOption.setString("Option");
	textOption.setFillColor(Color(100, 100, 100));
	textOption.setCharacterSize(40);
	textOption.setPosition(resolution.x * 0.1f, resolution.y * 0.5f + 250.f);
	Utils::SetOrigin(textOption, Pivots::LC);

	textMapEditor.setFont(fontLostRuins);
	textMapEditor.setString("Map Editor");
	textMapEditor.setFillColor(Color(100, 100, 100));
	textMapEditor.setCharacterSize(40);
	textMapEditor.setPosition(resolution.x * 0.1f, resolution.y * 0.5f + 320.f);
	Utils::SetOrigin(textMapEditor, Pivots::LC);

	textExit.setFont(fontLostRuins);
	textExit.setString("Exit");
	textExit.setFillColor(Color(100, 100, 100));
	textExit.setCharacterSize(40);
	textExit.setPosition(resolution.x * 0.1f, resolution.y * 0.5f + 390.f);
	Utils::SetOrigin(textExit, Pivots::LC);

	for (int i = 0; i < MAX_SAVE_SLOT; i++)
	{
		textLoadSlot[i].setFont(fontLostRuins);
		textLoadSlot[i].setString("---------");
		textLoadSlot[i].setFillColor(Color(200, 200, 200));
		textLoadSlot[i].setCharacterSize(30);
		textLoadSlot[i].setPosition(resolution.x * 0.5f, 500.f + (80.f * i));
		Utils::SetOrigin(textLoadSlot[i], Pivots::CC);
	}
}

void TitleScene::AnimationInit(AnimationController& animation, Sprite* sprite)
{
	animation.SetTarget(sprite);

	rapidcsv::Document clips("data_tables/animations/title/Title_animation_clips.csv");
	std::vector<std::string> colId = clips.GetColumn<std::string>("ID");
	std::vector<int> colFps = clips.GetColumn<int>("FPS");
	std::vector<int> colLoop = clips.GetColumn<int>("LOOP TYPE(0:Single, 1:Loop)");
	std::vector<std::string> colPath = clips.GetColumn<std::string>("CLIP PATH");

	int totalClips = colId.size();
	for (int i = 0; i < totalClips; ++i)
	{
		AnimationClip clip;
		clip.id = colId[i];
		clip.fps = colFps[i];
		clip.loopType = (AnimationLoopType)colLoop[i];

		rapidcsv::Document frames(colPath[i]);
		std::vector<std::string> colTexture = frames.GetColumn<std::string>("TEXTURE PATH");
		std::vector<int> colL = frames.GetColumn<int>("L");
		std::vector<int> colT = frames.GetColumn<int>("T");
		std::vector<int> colW = frames.GetColumn<int>("W");
		std::vector<int> colH = frames.GetColumn<int>("H");

		int totalFrames = colTexture.size();
		for (int j = 0; j < totalFrames; ++j)
		{
			if (texmap.find(colTexture[j]) == texmap.end())
			{
				auto& ref = texmap[colTexture[j]];
				ref.loadFromFile(colTexture[j]);
			}

			clip.frames.push_back(AnimationFrame(texmap[colTexture[j]],
				IntRect(colL[j], colT[j], colW[j], colH[j])));
		}
		animation.AddClip(clip);
	}
}

TitleScene::~TitleScene()
{
}