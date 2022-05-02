#pragma once
#include <SFML/Graphics.hpp>

class SceneManager;

using namespace sf;

class Scene
{
protected:
	SceneManager* sceneMgr;

public:
	virtual void Init(SceneManager* sceneManager);
	virtual void Update(float dt, Time playTime, RenderWindow* window, View* mainView);
	virtual void Draw(RenderWindow* window, View* mainView);
	virtual ~Scene();
};

