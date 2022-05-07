#pragma once
#include <SFML/Graphics.hpp>
#include "Mgr/InputManager.h"
#include "Mgr/SceneManager.h"
#include "Mgr/TextureHolder.h"

using namespace sf;

class FrameWork
{
private:
	const float INIT_FRAME = 60.f;

	RenderWindow* window;
	Vector2i resolution;
	View* objectView;

	SceneManager sceneMgr;
	TextureHolder textureHolder;

	Clock clock;
	Time playTime;
	Time dt;

	float frameLimit;
	float frameTimer;
	
public:
	bool Initialize();
	void Update();
	void Draw();
	int Run();

	~FrameWork();

};

