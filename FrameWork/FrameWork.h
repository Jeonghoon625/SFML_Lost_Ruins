#pragma once
#include <SFML/Graphics.hpp>
#include "Mgr/InputManager.h"
#include "Mgr/SceneManager.h"

using namespace sf;

class FrameWork
{
private:
	RenderWindow* window;
	View* mainView;

	Vector2i resolution;

	SceneManager sceneMgr;

	Clock clock;
	Time playTime;
	Time dt;

public:
	bool Initialize();
	void Update();
	void Draw();
	int Run();

	~FrameWork();

};

