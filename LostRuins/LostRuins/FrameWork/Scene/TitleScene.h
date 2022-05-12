#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include "Scene.h"
#include "../Mgr/TextureHolder.h"
#include "../Mgr/SoundHolder.h"
#include "../Mgr/Utils.h"
#include "../Animation/AnimationController.h"
#include "../Animation/rapidcsv.h"
#include "../Object/TitleObject/Rofe1.h"
#include "../Object/TitleObject/Rofe2.h"

class TitleScene : public Scene
{
private:
	SceneManager* sceneMgr;

	Vector2i resolution;

	AnimationController aniHeroine;
	AnimationController aniRope1;
	AnimationController aniRope2;

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

	SoundHolder soundHlr;
	Sound backGroundSound;

	std::map<std::string, Texture> texmap;

	View* uiView;

public:
	virtual void Init(SceneManager* sceneManager);
	virtual void Update(float dt, Time playTime, RenderWindow* window, View* mainView, View* uiView);
	virtual void Draw(RenderWindow* window, View* mainView);
	virtual ~TitleScene();

	void AnimationInit(AnimationController& animation, Sprite* sprite);

};

