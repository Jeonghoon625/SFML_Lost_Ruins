#pragma once
#include <SFML/Graphics.hpp>
#include "../Scene.h"
#include "../../Mgr/TextureHolder.h"
#include "../../Mgr/UIManager.h"
#include "../../Object/Player/Player.h"

using namespace sf;

class Npc;

class TestUi
{
private:
	SceneManager* sceneMgr;

	Vector2i resolution;

	Texture textureUI;
	Texture textureIN;
	Texture textureMAP;
	Texture textureSQ;
	Texture Blur1;

	//UI 이미지
	Texture scrollpng;
	Texture weaponpng;

	//UI 장비
	Sprite scr1;
	Sprite scr2;
	Sprite wea;
	Sprite shi;
	Sprite amr1;
	Sprite amr2;

	////////////


	Sprite Blur;

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
	Sprite InventoryMAP;

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
	Vector2f mpBarsize;
	Text textHPbar;
	Text textMPbar;
	Text textButtonTab; // TAB
	Text textButtonM; // M
	Text textInvenBtQ;
	Text textInvenBtW;
	Text textInven;
	Text textMap;
	Text textButtonX;
	Text textButtonZ;
	Text textButtonS;
	Text textButtonA;

	int menuNum;
	int escNum;
	int settingNum;

	int masterNum;
	int uiNum;
	int sfxNum;
	int musicNum;

	bool inventory;
	bool MAP;
	bool Escmenu;

	Texture textureback; //테스트배경
	Sprite spriteback; //테스트배경

	//Esc 텍스트
	Texture Escback1;
	Sprite Escback;
	Sprite EscCS;
	Text Continue;
	Text Setting;
	Text End;

	//setting
	Font settingLan;
	Texture texturesetting;
	Texture setBlur1;

	Sprite spriteset1;
	Sprite spriteset2;
	Sprite SettingBtQ;
	Sprite SettingBtW;
	Sprite SettingSet;
	Sprite SettingKey;
	Sprite SettingLeft;
	Sprite SettingRight;
	Sprite SettingESC;
	Sprite setBlur;
	Sprite LanCSL;
	Sprite LanCSR;
	Sprite ResCSL;
	Sprite ResCSR;
	Sprite FullCS;
	Sprite VsyCS;
	Sprite RenCSL;
	Sprite RenCSR;
	Sprite BattleCS;
	Sprite MasterBar;
	Sprite MasterCS;
	Sprite UIBar;
	Sprite UICS;
	Sprite SFXBar;
	Sprite SFXCS;
	Sprite MusicBar;
	Sprite MusicCS;
	Sprite ToggleLeft;
	Sprite ToggleRight;
	Sprite ESCBack;
	Sprite settingCS;



	Text SetBack;
	Text SetESC;
	Text Setname;
	Text Keyname;
	Text English;
	Text screensize;
	Text ModeFull;
	Text Back;
	Text Toggle;
	Text TogLeft;
	Text TogRight;
	Text textLanguage;
	Text textResolution;
	Text textFullScreen;
	Text textVsync;
	Text textRenderMode;
	Text textBattleLog;
	Text textMasterVolume;
	Text textUIVolume;
	Text textSFXVolume;
	Text textMusicVolume;
	Text SetBtQ;
	Text SetBtW;


	/// ////////////////////////////////
	Text KeyboardLeft;
	Sprite KeyboardLeftBox;
	Text KeyboardLeftDire;

	Text KeyboardRight;
	Sprite KeyboardRightBox;
	Text KeyboardRightDire;

	Text KeyboardUP;
	Sprite KeyboardUPBox;
	Text KeyboardUPDire;

	Text KeyboardDown;
	Sprite KeyboardDownBox;
	Text KeyboardDownDire;

	Text KeyboardSpace;
	Sprite KeyboardSpaceBox;
	Text KeyboardSpaceDire;

	Text KeyboardC;
	Sprite KeyboardCBox;
	Text KeyboardCDire;

	Text KeyboardZ;
	Sprite KeyboardZBox;
	Text KeyboardZDire;

	Text KeyboardX;
	Sprite KeyboardXBox;
	Text KeyboardXDire;

	Text KeyboardA;
	Sprite KeyboardABox;
	Text KeyboardADire;

	Text KeyboardS;
	Sprite KeyboardSBox;
	Text KeyboardSDire;

	Text KeyboardTab;
	Sprite KeyboardTabBox;
	Text KeyboardTabDire;

	Text KeyboardM;
	Sprite KeyboardMBox;
	Text KeyboardMDire;

	Text KeyboardV;
	Sprite KeyboardVBox;
	Text KeyboardVDire;

	Text KeyboardF;
	Sprite KeyboardFBox;
	Text KeyboardFDire;

	Text KeyboardQ;
	Sprite KeyboardQBox;
	Text KeyboardQDire;

	Text KeyboardW;
	Sprite KeyboardWBox;
	Text KeyboardWDire;

	bool Escset;
	bool Esckey;

public:

	virtual void Init(SceneManager* sceneManager);
	virtual void Update(float dt, Time playTime, RenderWindow* window, View* mainView, Player& player);
	virtual void Draw(RenderWindow* window, View* mainView);
	void SeeInven();
	void SeeMap();
	void EscSetting();
	void EscKeyboard();
};