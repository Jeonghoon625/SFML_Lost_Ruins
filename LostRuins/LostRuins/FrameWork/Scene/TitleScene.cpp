#include "TitleScene.h"

void TitleScene::Init(SceneManager* sceneManager)
{
	this->sceneMgr = sceneManager;

	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

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
	title.setTextureRect(IntRect(41, 56, 1052, 77));
	title.setPosition(160, 220);

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
	AnimationInit(&heroine);
	animation.Play("heroine");
}

void TitleScene::Update(float dt, Time playTime, RenderWindow* window, View* mainView)
{
	animation.SetSpeed(3.5f);
	animation.Update(dt);
}

void TitleScene::Draw(RenderWindow* window, View* mainView)
{
	window->setView(*mainView);
	window->draw(sky);
	window->draw(backGround);
	window->draw(midGround);
	window->draw(title);
	window->draw(ForeGround);
	window->draw(heroine);
	window->draw(topBar);
	window->draw(bottomBar);
}

TitleScene::~TitleScene()
{

}

void TitleScene::AnimationInit(Sprite* sprite)
{
	animation.SetTarget(sprite);

	rapidcsv::Document clips("data_tables/animations/player/player_animation_clips.csv");
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
