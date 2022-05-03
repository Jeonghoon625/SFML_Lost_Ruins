#pragma once

#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "../Mgr/TextureHolder.h"
#include "../Mgr/Utils.h"
#include "../Animation/AnimationController.h"
#include "../Animation/rapidcsv.h"
#include <map>
#include "../Object/Monster/Monster.h"

class TestSceneKK : public Scene
{
private:
	SceneManager* sceneMgr;

	Vector2i resolution;

	TextureHolder textureHlr;
	AnimationController animation;

	Monster Goblin;

public:
	virtual void Init(SceneManager* sceneManager);
	virtual void Update(float dt, Time playTime, RenderWindow* window, View* mainView);
	virtual void Draw(RenderWindow* window, View* mainView);
	virtual ~TestSceneKK();
};


