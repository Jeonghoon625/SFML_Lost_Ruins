#include "TestSceneTT.h"

void TestSceneTT::Init(SceneManager* sceneManager)
{
	this->sceneMgr = sceneManager;

	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	testUI.Init(this->sceneMgr);
}

void TestSceneTT::Update(float dt, Time playTime, RenderWindow* window, View* mainView)
{
	testUI.Update(dt, playTime, window, mainView);
}

void TestSceneTT::Draw(RenderWindow* window, View* mainView)
{
	window->setView(*mainView);
	testUI.Draw(window, mainView);
}

TestSceneTT::~TestSceneTT()
{

}
