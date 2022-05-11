#include "TestSceneTT.h"

void TestSceneTT::Init(SceneManager* sceneManager)
{
	this->sceneMgr = sceneManager;

	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	testUI.Init(this->sceneMgr);
	testNpc.Init();
}

void TestSceneTT::Update(float dt, Time playTime, RenderWindow* window, View* mainView)
{
	testUI.Update(dt, playTime, window, mainView);
	testNpc.Update(dt);
}

void TestSceneTT::Draw(RenderWindow* window, View* mainView)
{
	window->setView(*mainView);
	testUI.Draw(window, mainView);
	testNpc.Draw(window);
}

TestSceneTT::~TestSceneTT()
{

}
