#include "FrameWork.h"

bool FrameWork::Initialize()
{
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;
	//window = new RenderWindow(VideoMode(resolution.x, resolution.y), "Lost Ruins", Style::Default);
	window = new RenderWindow(VideoMode(1600.f, 900.f), "Lost Ruins", Style::Default);
	mainView = new View(FloatRect(0, 0, resolution.x, resolution.y));

	InputManager::Init();

	sceneMgr.Init();

	return true;
}

void FrameWork::Update()
{
	InputManager::ClearInput();

	Event event;
	while (window->pollEvent(event));
	{
		switch (event.type)
		{
		case Event::Closed:
			window->close();
			break;
		default:
			break;
		}
		InputManager::ProcessInput(event);
	}
	InputManager::Update(dt.asSeconds(), *window, *mainView);
	sceneMgr.Update(dt.asSeconds(), playTime, window, mainView);
}

void FrameWork::Draw()
{
	window->clear();
	sceneMgr.Draw(window, mainView);
	window->display();
}

int FrameWork::Run()
{
	while (window->isOpen())
	{
		dt = clock.restart();
		playTime += dt;

		Update();
		Draw();
	}

	return 0;
}

FrameWork::~FrameWork()
{
	delete window;
	delete mainView;
}
