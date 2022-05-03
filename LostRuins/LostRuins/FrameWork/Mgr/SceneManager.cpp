#include "SceneManager.h"

void SceneManager::Init()
{
	SceneSwitch(SceneType::TEST);
}

void SceneManager::Update(float dt, Time playTime, RenderWindow* window, View* mainView)
{
	currentScene->Update(dt, playTime, window, mainView);
}

void SceneManager::Draw(RenderWindow* window, View* mainView)
{
	currentScene->Draw(window, mainView);
}

void SceneManager::SceneSwitch(SceneType sceneType)
{
	sceneRelease();
	switch (sceneType)
	{
	case SceneType::TITLE:
		/*currentScene = new TitleScene();*/
		currentScene = new TestSceneKK();
		break;
	case SceneType::TEST:
		currentScene = new TestSceneKK();
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
