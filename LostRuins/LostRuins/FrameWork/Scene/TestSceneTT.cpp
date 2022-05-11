#include "TestSceneTT.h"

void TestSceneTT::Init(SceneManager* sceneManager)
{
	this->sceneMgr = sceneManager;

	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	testUI.Init(this->sceneMgr);
	testNpc.Init();
}

void TestSceneTT::Update(float dt, Time playTime, RenderWindow* window, View* mainView, View* uiView)
{
	this->uiView = uiView;
	testUI.Update(dt, playTime, window, uiView);
	testNpc.Update(dt);
}

void TestSceneTT::Draw(RenderWindow* window, View* mainView)
{
	window->setView(*uiView);
	testUI.Draw(window, uiView);
	testNpc.Draw(window);
}

TestSceneTT::~TestSceneTT()
{

}
