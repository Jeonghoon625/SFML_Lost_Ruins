#include "SceneManager.h"
#include "InputManager.h"

void SceneManager::Init()
{
	SceneSwitch(SceneType::TEST_KK);
}

void SceneManager::Update(float dt, Time playTime, RenderWindow* window, View* mainView, View* uiView)
{
	currentScene->Update(dt, playTime, window, mainView, uiView);

	if (InputManager::GetKeyDown(Keyboard::BackSpace))
	{
		SceneSwitch(SceneType::TITLE);
	}

	if (InputManager::GetKeyDown(Keyboard::F10))
	{
		SceneSwitch(SceneType::TEST_KK);
	}
}

void SceneManager::Draw(RenderWindow* window, View* mainView, View* uiView)
{
	currentScene->Draw(window, mainView, uiView);
}

void SceneManager::SceneSwitch(SceneType sceneType)
{
	sceneRelease();
	switch (sceneType)
	{
	case SceneType::TITLE:
		currentScene = new TitleScene();
		break;

	case SceneType::TEST_KK:
		currentScene = new TestSceneKK();
		break;

	case SceneType::TEST_LJW:
		currentScene = new TestSceneTT();
		break;

	case SceneType::TEST_LMH:
		currentScene = new GameScene();
		break;

	case SceneType::GameScene:
		currentScene = new GameScene();
		break;

	case SceneType::MapScene:
		currentScene = new MapScene();
		break;
	}
	sceneInit();
}

void SceneManager::sceneRelease()
{
	if (currentScene != nullptr)
	{
		delete currentScene;
	}
}

void SceneManager::sceneInit()
{
	currentScene->Init(this);
}
