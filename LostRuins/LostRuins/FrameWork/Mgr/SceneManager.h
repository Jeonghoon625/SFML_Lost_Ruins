#pragma once
#include "SFML/Graphics.hpp"
#include "../Scene/Scene.h"
#include "../Scene/TitleScene.h"
#include "../Scene/TestSceneTT.h"
#include "../Scene/TestSceneKK.h"
#include "../Scene/GameScene.h"
#include "../Scene/MapScene.h"
#include "../Scene/EndingScene.h"

using namespace sf;

enum class SceneType
{
	TITLE,
	TEST_LMH,
	TEST_KK,
	TEST_LJW,
	GameScene,
	MapScene,
	EndingScene,
};

class SceneManager
{
private:
	Scene* currentScene;

public:
	void Init();
	void Update(float dt, Time playTime, RenderWindow* window, View* mainView, View* uiView);
	void Draw(RenderWindow* window, View* mainView, View* uiView);

	void SceneSwitch(SceneType sceneType);
	void sceneRelease();
	void sceneInit();
};

