#pragma once
#include "SFML/Graphics.hpp"
#include "../Scene/Scene.h"
#include "../Scene/TitleScene.h"
#include "../Scene/TestSceneTT.h"
#include "../Scene/TestScene.h"
#include "../Scene/TestSceneKK.h"
#include "../Scene/GameScene.h"
#include "../Scene/MapScene.h"

using namespace sf;

enum class SceneType
{
	TITLE,
	TEST_LMH,
	TEST_KK,
	TEST_LJW,
	GameScene,
	MapScene
};

class SceneManager
{
private:
	Scene* currentScene;

public:
	void Init();
	void Update(float dt, Time playTime, RenderWindow* window, View* mainView, View* uiView);
	void Draw(RenderWindow* window, View* mainView);

	void SceneSwitch(SceneType sceneType);
	void sceneRelease();
	void sceneInit();
};

