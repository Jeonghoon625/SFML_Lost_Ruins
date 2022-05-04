#pragma once
#include <SFML/Graphics.hpp>
#include "../Scene.h"
#include "../../Mgr/TextureHolder.h"

class TestUi
{
private:
	SceneManager* sceneMgr;

	Vector2i resolution;

	Texture textureUI;

	Sprite HPbar;
	Sprite HPbarLine;

	Sprite MPbar;
	Sprite MPbarLine;

	Sprite BossHPbar;
	Sprite BossHPbarLine;

	Sprite Inventory;
	Sprite Mapicon;
	Sprite Wear1;
	Sprite Wear2;

	Sprite Weapon;
	Sprite Shield;

	Sprite ScrollA;
	Sprite ScrollS;

	Sprite ButtonTab;
	Sprite ButtonM;
	Sprite ButtonA;
	Sprite ButtonS;
	Sprite ButtonZ;
	Sprite ButtonX;

	RectangleShape topBar;
	RectangleShape bottomBar;

	std::map<std::string, Texture> texmap;
	

public:
	virtual void Init(SceneManager* sceneManager);
	virtual void Update(float dt, Time playTime, RenderWindow* window, View* mainView);
	virtual void Draw(RenderWindow* window, View* mainView);
};