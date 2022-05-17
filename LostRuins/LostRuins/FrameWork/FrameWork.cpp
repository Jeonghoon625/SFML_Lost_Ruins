#include "FrameWork.h"


bool FrameWork::Initialize()
{
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	window = new RenderWindow(VideoMode(resolution.x, resolution.y), "Lost Ruins", Style::Default); 

	objectView = new View(FloatRect(0, 0, resolution.x, resolution.y));
	objectView->setCenter(resolution.x * 0.5f, resolution.y * 0.5f);
	objectView->zoom(1.f/4.f);

	uiView = new View(FloatRect(0, 0, resolution.x, resolution.y));
	uiView->setCenter(resolution.x * 0.5f, resolution.y * 0.5f);

	frameLimit = INIT_FRAME; //ÃÊ±â 60.f
	frameTimer = 0.f;

	InputManager::Init();
	sceneMgr.Init();

	//light
	light.setRange(0);
	edges.emplace_back(sf::Vector2f(200.f, 100.f), sf::Vector2f(200.f, 300.f));
	
	isFulltScreen = false;

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
		case Event::KeyPressed:
		/*	if (event.key.code == Keyboard::Escape)
			{
				window->close();
			}*/

			if (event.key.code == Keyboard::F5)
			{
				isFulltScreen = !isFulltScreen;

				if (isFulltScreen)
				{
					window->create(VideoMode(resolution.x, resolution.y), "Lost Ruins", Style::Fullscreen);
				}
				else
				{
					window->create(VideoMode(resolution.x, resolution.y), "Lost Ruins", Style::Default);
				}
			}
			break;
		
		default:
			break;
		}

		InputManager::ProcessInput(event);
	}

	InputManager::Update(frameTimer, *window, *objectView);
	sceneMgr.Update(frameTimer, playTime, window, objectView, uiView);
}

void FrameWork::Draw()
{
	window->clear();
	sceneMgr.Draw(window, objectView, uiView);
	window->draw(light);
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
	delete uiView;
}
