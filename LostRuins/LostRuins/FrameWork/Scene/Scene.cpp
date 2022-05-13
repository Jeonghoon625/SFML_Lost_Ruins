#include "Scene.h"

void Scene::Init(SceneManager* sceneManager)
{
	this->sceneMgr = sceneManager;
}

void Scene::Update(float dt, Time playTime, RenderWindow* window, View* mainView, View* uiView)
{
}

void Scene::Draw(RenderWindow* window, View* mainView, View* uiView)
{

}

Scene::~Scene()
{

}
