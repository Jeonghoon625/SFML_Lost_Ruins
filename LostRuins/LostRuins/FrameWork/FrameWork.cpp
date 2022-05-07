#include "FrameWork.h"

bool FrameWork::Initialize()
{
	
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;
	
	//resolution.x = 1600.f;
	//resolution.y = 900.f;
	window = new RenderWindow(VideoMode(1600.f, 900.f), "Lost Ruins", Style::Default);
	objectView = new View(FloatRect(0, 0, resolution.x, resolution.y));

	frameLimit = INIT_FRAME; //ÃÊ±â 60.f
	frameTimer = 0.f;

	InputManager::Init();
	sceneMgr.Init();

	return true;
}

void FrameWork::Update()
{
	InputManager::ClearInput();

	Event event;
	while (window->pollEvent(event))
	{
		switch (event.type)
		{
		case Event::Closed:
			window->close();
			break;

		//ESC close
		/*case Event::KeyPressed:
			if (event.key.code == Keyboard::Escape)
			{
				window->close();
			}
			break;
		*/

		default:
			break;
		}

		InputManager::ProcessInput(event);
	}

	InputManager::Update(frameTimer, *window, *objectView);
	sceneMgr.Update(frameTimer, playTime, window, objectView);
}

void FrameWork::Draw()
{
	window->clear();
	sceneMgr.Draw(window, objectView);
	window->display();
}

int FrameWork::Run()
{
	while (window->isOpen())
	{
		dt = clock.restart();

		playTime += dt;
		
		frameTimer += dt.asSeconds();
		float maxFPS = 1.f / frameLimit;
		float minFPS = 2.f / frameLimit;

		if (maxFPS <= frameTimer && frameTimer <= minFPS)
		{
			// std::cout << 1.f / frameTimer << std::endl; //Output FPS
			Update();
			Draw();

			frameTimer = 0.f;
		}	
		else if (frameTimer >= 2.f / frameLimit)
		{
			frameTimer = 0.f;
		}
	}

	return 0;
}

FrameWork::~FrameWork()
{
	delete window;
	delete objectView;
}
