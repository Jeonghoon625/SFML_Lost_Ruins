#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include "Scene.h"
#include "../Mgr/TextureHolder.h"
#include "../Mgr/Utils.h"
#include "../Mgr/InputManager.h"
#include "../Animation/AnimationController.h"
#include "../Animation/rapidcsv.h"

enum GameMenu
{
	GAME_START = 1,
	CONTINUE,
	OPTION,
	MAPEDIT,
	EXIT,
};

class TitleScene : public Scene
{
private:
	SceneManager* sceneMgr;

	Vector2i resolution;

	AnimationController aniHeroine;
	AnimationController aniRope1;
	AnimationController aniRope2;

	Font fontLostRuins;
	Texture textureTitle;

	Sprite sky;
	Sprite backGround;
	Sprite midGround;
	Sprite title;
	Sprite ForeGround;
	Sprite heroine;
	Sprite rope1;
	Sprite rope2;

	RectangleShape topBar;
	RectangleShape bottomBar;

	Text textGameStart;
	Text textContinue;
	Text textOption;
	Text textMapEditor;
	Text textExit;

	Sound backGroundSound;

	int isPosition;

	std::map<std::string, Texture> texmap;

public:
	virtual void Init(SceneManager* sceneManager);
	virtual void Update(float dt, Time playTime, RenderWindow* window, View* mainView, View* uiView);
	virtual void Draw(RenderWindow* window, View* mainView, View* uiView);
	virtual ~TitleScene();

	void GetSelect(RenderWindow* window);
	void SettingTextrue();
	void SettingText();
	void AnimationInit(AnimationController& animation, Sprite* sprite);

};

