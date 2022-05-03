#pragma once
#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "../Mgr/TextureHolder.h"
#include "../Mgr/Utils.h"
#include "../Animation/AnimationController.h"
#include "../Animation/rapidcsv.h"
#include <map>

class TitleScene : public Scene
{
private:
	SceneManager* sceneMgr;

	Vector2i resolution;

	TextureHolder textureHlr;
	AnimationController animation;

	Texture textureTitle;

	Sprite sky;
	Sprite backGround;
	Sprite midGround;
	Sprite title;
	Sprite ForeGround;
	Sprite heroine;

	RectangleShape topBar;
	RectangleShape bottomBar;

	std::map<std::string, Texture> texmap;

public:
	virtual void Init(SceneManager* sceneManager);
	virtual void Update(float dt, Time playTime, RenderWindow* window, View* mainView);
	virtual void Draw(RenderWindow* window, View* mainView);
	virtual ~TitleScene();

	void AnimationInit(Sprite* sprite);
};

