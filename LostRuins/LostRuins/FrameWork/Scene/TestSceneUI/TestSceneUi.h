#pragma once
#include <SFML/Graphics.hpp>
#include "../Scene.h"
#include "../../Mgr/TextureHolder.h"
#include "../../Mgr/UIManager.h"

using namespace sf;
class Player;

class TestUi
{
private:
	SceneManager* sceneMgr;

	Vector2i resolution;

	Texture textureUI;
	Texture textureIN;
	Texture textureSQ;

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

	Sprite Invenwindow;

	RectangleShape topBar;
	RectangleShape bottomBar;

	Sprite InvenWeapon;
	Sprite InvenOrder;
	Sprite InvenSupplies;
	Sprite InvenEquipment;
	Sprite InvenRelic;
	Sprite InvenRecord;
	Sprite InvenKey;
	Sprite InvenCS;
	Sprite Invenname;
	Sprite InvenMap;
	Sprite InvenBtQ;
	Sprite InvenBtW;

	std::map<std::string, Texture> texmap;

	////////////////////////////

	Font fontLostRuins;
	Vector2f healthBarsize;
	Text textHPbar;
	Text textMPbar;
	Text textInvenname; // TAB
	Text textInvenMap; // M
	Text textInvenBtQ;
	Text textInvenBtW;

	int HP;
	int MP;

public:

	virtual void Init(SceneManager* sceneManager);
	virtual void Update(float dt, Time playTime, RenderWindow* window, View* mainView);
	virtual void Draw(RenderWindow* window, View* mainView);
};