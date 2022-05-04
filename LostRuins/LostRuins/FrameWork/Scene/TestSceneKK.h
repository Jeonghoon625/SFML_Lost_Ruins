#pragma once

#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "../Mgr/TextureHolder.h"
#include "../Object/Player/Player.h"
#include "../Mgr/Utils.h"
#include "../Animation/AnimationController.h"
#include "../Animation/rapidcsv.h"
#include <map>
#include "../Object/Monster/Monster.h"
#include "../Object/Monster/ZombieCrawler.h"
#include "../Object/Monster/ZombieWalker.h"




class TestSceneKK : public Scene
{
private:
	SceneManager* sceneMgr;

	Vector2i resolution;

	AnimationController animation;

	Player player;
	Texture textureHeroine;
	Sprite heroineAction;
	

	Monster Goblin;
	ZombieCrawler zombieCrawler;
	ZombieWalker zombieWalker;

public:
	virtual void Init(SceneManager* sceneManager);
	virtual void Update(float dt, Time playTime, RenderWindow* window, View* mainView);
	virtual void Draw(RenderWindow* window, View* mainView);
	virtual ~TestSceneKK();
};

