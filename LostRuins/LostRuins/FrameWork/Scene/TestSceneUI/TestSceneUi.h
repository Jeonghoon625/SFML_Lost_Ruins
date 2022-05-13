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
	std::map<std::string, Texture> texmap;
	Vector2f healthBarsize; // HP바 사이즈
	Vector2f mpBarsize;		// MP바 사이즈

	// 테스트 배경	
	Texture textureback; //테스트배경
	Sprite spriteback; //테스트배경

	// UI 텍스처
	Texture textureUI;
	Texture textureIN;
	Texture textureMAP;
	Texture textureSQ;
	Texture Blur1;

	//UI 스크롤 이미지
	Texture scrollpng;
	Sprite scr1;
	Sprite scr2;

	//UI 무기 이미지 (한손검) (단검)
	Texture weaponpng;
	Sprite wea; // Z무기
	Sprite shi; // X무기

	//UI 장비 이미지
	Sprite amr1;
	Sprite amr2;

	// UI 이미지 (ex 체력칸, 마나칸, 무기칸 등등..)
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
	Sprite Invenwindow; // 인벤토리 창
	Sprite InventoryMAP;// 맵창
	Sprite InvenallCS;	// 인벤토리 내 카테고리 커서
	
	////////////////////////////////////////////
	//                                        //
	//  인벤토리 무기칸 스프라이트 / 텍스트   //
	//                                        //
	////////////////////////////////////////////
	
	// 장검 무기 페이지
	Sprite InvenLongWeapon;
	Sprite InvenWeaponZblock1; // Z무기 블럭
	Sprite InvenWeaponXblock2; // X무기 블럭
	Sprite InvenWeaponblock3;
	Sprite InvenWeaponblock4;
	Sprite InvenWeaponblock5;
	Sprite InvenWeaponZblock6; // Z무기 블럭 색깔
	Sprite InvenWeaponXblock7; // X무기 블럭 색깔
	
	Text textInvenweapon1;
	Text textInvenweapon2;
	Text textInvenweapon3;
	Text textInvenweapon4;
	Text textInvenweapon5;
	Text textInvenweapon6;
	Text textInvenweapon7;
	Text textInvenweapon8;
	Text textInvenweapon9;

	// 단검 무기 페이지
	Sprite InvenWeaponZblock21; // Z무기 블럭
	Sprite InvenWeaponXblock22; // X무기 블럭
	Sprite InvenWeaponblock23;
	Sprite InvenWeaponblock24;
	Sprite InvenWeaponblock25;
	Sprite InvenWeaponZblock26; // Z무기블럭 색깔
	Sprite InvenWeaponXblock27; // X 무기블럭 색깔

	Text textInvenweapon21; 
	Text textInvenweapon22; 
	Text textInvenweapon23;
	Text textInvenweapon24;
	Text textInvenweapon25;
	Text textInvenweapon26;
	Text textInvenweapon27;
	Text textInvenweapon28;
	Text textInvenweapon29;

	////////////////////////////////////////////
	//                                        //
	//  인벤토리 주문칸 스프라이트 / 텍스트   //
	//                                        //
	////////////////////////////////////////////

	Sprite InvenOrder; // 주문
	Sprite Orderblankrhombus1; //  1. 마름모 빈칸
	Sprite Orderblankrhombus2; // 2. 마름모 빈칸
	Sprite orderitemphotoframe1; // 1. 우측 아이템 네모칸
	Sprite orderitemphotoframe2; // 2. 우측 아이템 네모칸
	Sprite OdescriptionImage1; // 1. 우측 아이템 이미지
	Sprite OdescriptionImage2; // 2. 우측 아이템 이미지
	Sprite Oitembackground1; // 1. 우측 아이템 이미지 뒷배경
	Sprite Oitembackground2; // 2. 우측 아이템 이미지 뒷배경
	Sprite Orderfullrhombus1; // 1. 채원진 마름모
	Sprite Orderfullrhombus2; // 2. 채원진 마름모

	Text Otextscrollname1; // 1. 리스트 내 아이템 이름
	Text Otextscrollname2; // 2. 리스트 내 아이템 이름
	Text OtextItemnamefield1; // 1. 우측 아이템 이름
	Text OtextItemnamefield2; // 2. 우측 아이템 이름
	Text Omagictype1; // 1. 마법타입
	Text Omagictype2; // 2. 마법타입
	Text Oattackspeed1; // 1. 공격속도
	Text Oattackspeed2; // 2. 공격속도
	Text ODamage1; // 1. 데미지
	Text ODamage2; // 2. 데미지
	Text OItemDescription1; // 1. 아이템설명 텍스트
	Text OItemDescription2; // 1. 아이템설명 텍스트
	Text OItemDescription3; // 1. 아이템설명 텍스트
	Text OItemDescription01; // 2. 아이템설명 텍스트
	Text OItemDescription02; // 2. 아이템설명 텍스트
	Text OItemDescription03; // 2. 아이템설명 텍스트
	Text OItemDescription04; // 2. 아이템설명 텍스트

	////////////////////////////////////////////
	//                                        //
	// 인벤토리 소모품칸 스프라이트 / 텍스트  //
	//                                        //
	////////////////////////////////////////////

	Sprite InvenSupplies; // 소모품
	Sprite InvenSuppliesblock1;
	Sprite InvenSuppliesblock2;
	Sprite InvenSuppliesblock3;
	Text textInvenSupplies1;
	Text textInvenSupplies2;
	Text textInvenSupplies3;

	////////////////////////////////////////////
	//                                        //
	//  인벤토리 장비칸 스프라이트 / 텍스트   //
	//                                        //
	////////////////////////////////////////////

	Sprite InvenEquipment; // 장비
	Sprite InvenEquipmentblock1;
	Sprite InvenEquipmentblock2;
	Sprite InvenEquipmentblock3;
	Text textInvenEquipment1;
	Text textInvenEquipment2;
	Text textInvenEquipment3;

	////////////////////////////////////////////
	//                                        //
	//  인벤토리 유물칸 스프라이트 / 텍스트   //
	//                                        //
	////////////////////////////////////////////

	Sprite InvenRelic; // 유물
	Sprite InvenRelicblock;

	////////////////////////////////////////////
	//                                        //
	//  인벤토리 기록칸 스프라이트 / 텍스트   //
	//                                        //
	////////////////////////////////////////////

	Sprite InvenRecord; // 기록(핸드폰)
	Sprite InvenRecordblock;

	////////////////////////////////////////////
	//                                        //
	//  인벤토리 열쇠칸 스프라이트 / 텍스트   //
	//                                        //
	////////////////////////////////////////////

	Sprite InvenKey; // 열쇠
	Sprite InvenKeyblock;


	// 인벤토리 스프라이트
	Sprite InvenCS;
	Sprite Invenname;
	Sprite InvenMap;
	Sprite InvenBtQ;
	Sprite InvenBtW;


	// UI 배경 폰트 / 텍스트

	Font fontLostRuins;	
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


	//Esc 텍스트 / 배경 / 스프라이트
	Texture Escback1;
	Sprite Escback;
	Sprite EscCS;
	Text Continue;
	Text Setting;
	Text End;

	// ESC -> Setting
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
	Sprite FullCS2;
	Sprite VsyCS;
	Sprite VsyCS2;
	Sprite RenCSL;
	Sprite RenCSR;
	Sprite BattleCS;
	Sprite BattleCS2;
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


	// ESC -> Keyboard
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


	int menuNum;
	int escNum;
	int settingNum;
	int masterNum;
	int uiNum;
	int sfxNum;
	int musicNum;
	int weaponNum;
	int orderNum;
	int SuppliesNum;
	int EquipmentNum;

	bool inventory;
	bool MAP;
	bool Escmenu;

	bool Zweapon;
	bool Zweaponview;
	bool Xweapon;
	bool Xweaponview;

	bool Zscroll;
	bool Zscrollview;
	bool Xscroll;
	bool Xscrollview;

	bool Escset;
	bool FullCSsetview;
	bool VsyCSSetview;
	bool BattleCSSetview;
	bool Esckey;

public:

	virtual void Init(SceneManager* sceneManager);
	virtual void Update(float dt, Time playTime, RenderWindow* window, View* mainView, Player& player);
	virtual void Draw(RenderWindow* window, View* mainView);
	void Initstartimg();
	void SeeInven();
	void SeeMap();
	void Escapemenu();
	void EscSetting();
	void ESCsettag();
	void EscKeyboard();
	void weaponlist1();
	void weaponlist2();
	void scrollList1();
	void scrollList2();
};