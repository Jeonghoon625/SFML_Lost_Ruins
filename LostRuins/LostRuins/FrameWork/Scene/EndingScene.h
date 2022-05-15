#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Scene.h"
#include "../Mgr/TextureHolder.h"
#include "../Mgr/SoundHolder.h"
#include "../Mgr/Utils.h"

using namespace sf;

class EndingScene : public Scene
{
private:
	const float ENDING_ROLL_TIME = 93.f;
	const float ENDING_ROLL_SPEED = 100.f;

	SceneManager* sceneMgr;
	Vector2i resolution;
	Vector2f position;

	Sprite spriteIllust;
	Sound soundEnding;

	Font fontLostRuins;
	Text endingStr1;
	Text advisor;
	Text endingStr2;
	Text member1;
	Text member2;
	Text member3;
	Text member4;
	Text endingStr3;
	Text skipEnding;

	float endingRoll;
	float speed;

	bool stop;

public:
	virtual void Init(SceneManager* sceneManager);
	virtual void Update(float dt, Time playTime, RenderWindow* window, View* mainView, View* uiView);
	virtual void Draw(RenderWindow* window, View* mainView, View* uiView);
	virtual ~EndingScene();

};

