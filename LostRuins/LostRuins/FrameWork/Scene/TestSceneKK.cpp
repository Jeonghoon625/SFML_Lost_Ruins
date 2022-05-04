#include "TestSceneKK.h"

void TestSceneKK::Init(SceneManager* sceneManager)
{
	std::cout << "123";
	this->sceneMgr = sceneManager;
	Goblin.MonsterInit();
}

void TestSceneKK::Update(float dt, Time playTime, RenderWindow* window, View* mainView)
{
	Goblin.Update(dt);
	Goblin.Walk(dt);
	
}

void TestSceneKK::Draw(RenderWindow* window, View* mainView)
{
	Goblin.Draw(window);
}

TestSceneKK::~TestSceneKK()
{

}

