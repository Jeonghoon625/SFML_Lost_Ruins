#pragma once
#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "../Mgr/TextureHolder.h"
#include "../Object/Player/Player.h"

class TestScene : public Scene
{
	SceneManager* sceneMgr;

	Vector2i resolution;

	Player player;

	Texture textureHeroine;

	Sprite heroineAction;

public:
	virtual void Init(SceneManager* sceneManager);
	virtual void Update(float dt, Time playTime, RenderWindow* window, View* mainView);
	virtual void Draw(RenderWindow* window, View* mainView);
	virtual ~TestScene();

};

