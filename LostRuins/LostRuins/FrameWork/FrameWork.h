#pragma once
#include <SFML/Graphics.hpp>
#include "Mgr/InputManager.h"
#include "Mgr/SceneManager.h"
#include "Mgr/TextureHolder.h"
#include "Candle/Candle.hpp"
#include "Candle/RadialLight.hpp"

using namespace sf;

class FrameWork
{
private:
	const float INIT_FRAME = 60.f;

	RenderWindow* window;
	Vector2i resolution;
	View* objectView;
	View* uiView;

	SceneManager sceneMgr;
	TextureHolder textureHolder;

	Clock clock;
	Time playTime;
	Time dt;

	float frameLimit;
	float frameTimer;

	candle::RadialLight light;
	candle::EdgeVector edges;
	
public:
	bool Initialize();
	void Update();
	void Draw();
	int Run();

	~FrameWork();

};

