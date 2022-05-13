#include "TitleScene.h"
#include "../Mgr/SceneManager.h"

void TitleScene::Init(SceneManager* sceneManager)
{
	this->sceneMgr = sceneManager;
	isPosition = 1;

	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	SettingTextrue();
	SettingText();

	backGroundSound.setBuffer(SoundHolder::GetBuffer("sound/back_ground_sound.wav"));
	backGroundSound.play();
}

void TitleScene::Update(float dt, Time playTime, RenderWindow* window, View* mainView, View* uiView)
{
	if (InputManager::GetKeyDown(Keyboard::Up) && isPosition > 1)
	{
		isPosition--;
	}
	else if (InputManager::GetKeyDown(Keyboard::Down) && isPosition < 4)
	{
		isPosition++;
	}

	switch (isPosition)
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
		textExit.setFillColor(Color(100, 100, 100));
		break;
	case EXIT:
		textExit.setFillColor(Color::White);
		textOption.setFillColor(Color(100, 100, 100));
		break;
	}

	aniHeroine.Update(dt);
	aniRope1.Update(dt);
	aniRope2.Update(dt);
	this->uiView = uiView;

	if (InputManager::GetKeyDown(Keyboard::Space))
	{
		GetSelect(window);
	}
}

void TitleScene::Draw(RenderWindow* window, View* mainView)
{
	window->setView(*uiView);
	window->draw(sky);
	window->draw(backGround);
	window->draw(midGround);
	window->draw(title);
	window->draw(rope1);
	window->draw(rope2);
	window->draw(ForeGround);
	window->draw(heroine);
	window->draw(topBar);
	window->draw(bottomBar);

	window->draw(textGameStart);
	window->draw(textContinue);
	window->draw(textOption);
	window->draw(textExit);
}

TitleScene::~TitleScene()
{

}

void TitleScene::GetSelect(RenderWindow* window)
{
	switch (isPosition)
	{
	case GAME_START:
		sceneMgr->SceneSwitch(SceneType::GameScene);
		break;
	case CONTINUE:
		break;
	case OPTION:
		break;
	case EXIT:
		window->close();
		break;
	}
}

void TitleScene::SettingTextrue()
{
	textureTitle = TextureHolder::GetTexture("graphics/title.png");

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
}

void TitleScene::SettingText()
{
	fontLostRuins.loadFromFile("fonts/LiberationSans-Bold.ttf");

	textGameStart.setFont(fontLostRuins);
	textGameStart.setString("Game Start");
	textGameStart.setFillColor(Color::White);
	textGameStart.setCharacterSize(40);
	textGameStart.setPosition(resolution.x * 0.1f, resolution.y * 0.5f + 180.f);
	Utils::SetOrigin(textGameStart, Pivots::LC);

	textContinue.setFont(fontLostRuins);
	textContinue.setString("Continue");
	textContinue.setFillColor(Color(100, 100, 100));
	textContinue.setCharacterSize(40);
	textContinue.setPosition(resolution.x * 0.1f, resolution.y * 0.5f + 250.f);
	Utils::SetOrigin(textContinue, Pivots::LC);

	textOption.setFont(fontLostRuins);
	textOption.setString("Option");
	textOption.setFillColor(Color(100, 100, 100));
	textOption.setCharacterSize(40);
	textOption.setPosition(resolution.x * 0.1f, resolution.y * 0.5f + 320.f);
	Utils::SetOrigin(textOption, Pivots::LC);

	textExit.setFont(fontLostRuins);
	textExit.setString("Exit");
	textExit.setFillColor(Color(100, 100, 100));
	textExit.setCharacterSize(40);
	textExit.setPosition(resolution.x * 0.1f, resolution.y * 0.5f + 390.f);
	Utils::SetOrigin(textExit, Pivots::LC);
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