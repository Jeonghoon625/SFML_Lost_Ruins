#pragma once
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <map>
#include "Scene.h"
#include "../Mgr/TextureHolder.h"
#include "../Object/Player/Player.h"
#include "../Object/TestBlock/TestBlock.h"
#include "../Object/TestMonster/TestZombieWalker.h"

class TestScene : public Scene
{
	AnimationController animation;

	SceneManager* sceneMgr;

	Vector2i resolution;

	Player player;
	IntRect gameMap;

	Texture textureHeroine;

	Sprite heroineAction;

	vector <TestBlock*> blocks;
	vector <TestZombieWalker*> zombieWalkers;

	std::map<std::string, Texture> texmap;

	Sprite testSprite;
	Sprite testMagic;

public:
	virtual void Init(SceneManager* sceneManager);
	virtual void Update(float dt, Time playTime, RenderWindow* window, View* mainView);
	virtual void Draw(RenderWindow* window, View* mainView);
	virtual ~TestScene();

	void CreateBlock();
	void CreateMonster();
	void AnimationInit(Sprite* sprite);
	void AnimationInit1(Sprite* sprite);
};

