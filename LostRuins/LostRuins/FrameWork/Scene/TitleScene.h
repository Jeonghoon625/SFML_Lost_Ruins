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

enum class MenuType
{
	MENU_SELECT,
	MENU_LOAD,
	MENU_OPTION,
};

class TitleScene : public Scene
{
private:
	const int MAX_MENU_SLOT = 5;
	const int MAX_SAVE_SLOT = 3;

	SceneManager* sceneMgr;

	Vector2i resolution;

	AnimationController aniHeroine;
	AnimationController aniRope1;
	AnimationController aniRope2;
	AnimationController aniTree;
	AnimationController aniDeadBush;

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
	Sprite tree;
	Sprite deadBush;
	Sprite loadBar;

	RectangleShape topBar;
	RectangleShape bottomBar;

	RectangleShape loadBack;
	RectangleShape loadScreen;
	RectangleShape loadSlot;

	Text textGameStart;
	Text textContinue;
	Text textOption;
	Text textMapEditor;
	Text textExit;

	Text textLoadSlot[3];

	Sound backGroundSound;

	int menuPos;
	int loadPos;
	MenuType menuType;

	std::map<std::string, Texture> texmap;

public:
	virtual void Init(SceneManager* sceneManager);
	virtual void Update(float dt, Time playTime, RenderWindow* window, View* mainView, View* uiView);
	virtual void Draw(RenderWindow* window, View* mainView, View* uiView);
	virtual ~TitleScene();

	void SelectingMenu(float dt, RenderWindow* window);
	void LoadingMenu(float dt, RenderWindow* window);

	void GetSelect(RenderWindow* window);
	void SettingTextrue();
	void SettingText();
	void AnimationInit(AnimationController& animation, Sprite* sprite);

};

