#pragma once
#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "../Mgr/TextureHolder.h"
#include "../Mgr/Utils.h"
#include "../Animation/AnimationController.h"
#include "../Animation/rapidcsv.h"
#include "TestSceneUI/TestSceneUi.h"
#include "../Object/Npc/Npc.h"
#include <map>

class TestSceneTT : public Scene
{
private:
	SceneManager* sceneMgr;
	Vector2i resolution;

	TestUi testUI;
	Npc testNpc;

	View* uiView;





public:
	virtual void Init(SceneManager* sceneManager);
	virtual void Update(float dt, Time playTime, RenderWindow* window, View* mainView, View* uiView);
	virtual void Draw(RenderWindow* window, View* mainView);
	virtual ~TestSceneTT();
};

