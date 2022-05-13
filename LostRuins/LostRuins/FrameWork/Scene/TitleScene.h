#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include "Scene.h"
#include "../Mgr/TextureHolder.h"
#include "../Mgr/SoundHolder.h"
#include "../Mgr/Utils.h"
#include "../Mgr/InputManager.h"
#include "../Animation/AnimationController.h"
#include "../Animation/rapidcsv.h"

enum GameMenu
{
	GAME_START = 1,
	CONTINUE,
	OPTION,
	EXIT,
};

enum class MenuType
{
	MENU_SELECT,
	MENU_LOAD,
	MENU_OPTION,
};

class TitleScene : public Scene
{
private:
	const int MAX_MENU_SLOT = 4;
	const int MAX_SAVE_SLOT = 3;

	SceneManager* sceneMgr;
	SoundHolder soundHlr;

	Vector2i resolution;

	AnimationController aniHeroine;
	AnimationController aniRope1;
	AnimationController aniRope2;

	Font fontLostRuins;
	Texture textureTitle;
	Texture textureUi;

	Sprite sky;
	Sprite backGround;
	Sprite midGround;
	Sprite title;
	Sprite ForeGround;
	Sprite heroine;
	Sprite rope1;
	Sprite rope2;

	Sprite loadBar;

	RectangleShape topBar;
	RectangleShape bottomBar;

	RectangleShape loadBack;
	RectangleShape loadScreen;
	RectangleShape loadSlot;

	Text textGameStart;
	Text textContinue;
	Text textOption;
	Text textExit;

	Text textLoadSlot[3];

	Sound backGroundSound;

	int menuPos;
	int loadPos;
	MenuType menuType;

	std::map<std::string, Texture> texmap;

	View* uiView;

public:
	virtual void Init(SceneManager* sceneManager);
	virtual void Update(float dt, Time playTime, RenderWindow* window, View* mainView, View* uiView);
	virtual void Draw(RenderWindow* window, View* mainView);
	virtual ~TitleScene();

	void SelectingMenu(float dt, RenderWindow* window);
	void LoadingMenu(float dt);

	void GetSelect(RenderWindow* window);
	void SettingTextrue();
	void SettingText();
	void AnimationInit(AnimationController& animation, Sprite* sprite);

};

