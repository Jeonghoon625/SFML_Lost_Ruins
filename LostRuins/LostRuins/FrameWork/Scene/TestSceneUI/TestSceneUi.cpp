#include "TestSceneUi.h"
#include "../../FrameWork/Mgr/InputManager.h"

using namespace sf;
using namespace std;

void TestUi::Init(SceneManager* sceneManager)
{
	this->sceneMgr = sceneManager;

	resolution.x = 1920.f;
	resolution.y = 1080.f;

	Initstartimg();
}

void TestUi::Update(float dt, Time playTime, RenderWindow* window, View* mainView, Player& player)
{
	float HPbarwidth = 314;
	float HPbarHeight = 17;
	healthBarsize = Vector2f(HPbarwidth, HPbarHeight);
	HPbar.setScale(player.GetHealth() / 20.f, 1.f); //player.GetMaxHealth()

	/*float MPwidth = 314;
	float MPbarHeight = 17;
	mpBarsize = Vector2f(MPwidth, HPbarHeight);
	MPbar.setScale(player.get)*/

	ESCsettag();

	if (InputManager::GetKeyDown(Keyboard::Z) && inventory == true && weaponNum == 1 && menuNum == 1)
	{
		Zweaponview = !Zweaponview;
	}
	if (InputManager::GetKeyDown(Keyboard::X) && inventory == true && weaponNum == 2 && menuNum == 1)
	{
		Xweaponview = !Xweaponview;
	}



	if (InputManager::GetKeyDown(Keyboard::Z) && inventory == true && orderNum == 1 && menuNum == 2)
	{
		Zscrollview = !Zscrollview;
	}

	if (InputManager::GetKeyDown(Keyboard::X) && inventory == true && orderNum == 2 && menuNum == 2)
	{
		Xscrollview = !Xscrollview;
	}


	if (InputManager::GetKeyDown(Keyboard::Z) && inventory == true && SuppliesNum == 1 && menuNum == 3)
	{
		Zfoodview = !Zfoodview;
	}




	if (InputManager::GetKeyDown(Keyboard::Z) && inventory == true && EquipmentNum == 1 && menuNum == 4)
	{
		ZEquipview = !ZEquipview;
	}

	if (InputManager::GetKeyDown(Keyboard::X) && inventory == true && EquipmentNum == 2 && menuNum == 4)
	{
		XEquipview = !XEquipview;
	}



	if (InputManager::GetKeyDown(Keyboard::Z) && inventory == true && relicsNum == 1 && menuNum == 5)
	{
		Zrelicsview = !Zrelicsview;
	}




	if (InputManager::GetKeyDown(Keyboard::Key::Escape) && inventory == false && MAP == false)
	{
		Escapemenu();
	}

	if (InputManager::GetKeyDown(Keyboard::Tab) && Escmenu == false)
	{
		menuNum = 1;
		orderNum = 1;
		weaponNum = 1;
		SuppliesNum = 1;
		MAP = false;
		inventory = true;
		InvenallCS.setPosition(340, 394);
		SeeInven();
		weaponlist1();		
	}
	if (InputManager::GetKeyDown(Keyboard::Key::Down) && inventory == true && Zweapon == true && menuNum == 1 && Xweapon == true && weaponNum == 1)
	{
		weaponlist2();
	}


	
	
	if (InputManager::GetKeyDown(Keyboard::Escape) && inventory == true)
	{
		inventory = false;
		Escmenu = false;
	}

	if (InputManager::GetKeyDown(Keyboard::M))
	{
		inventory = false;
		MAP = true;
		SeeMap();
	}

	if (InputManager::GetKeyDown(Keyboard::Escape) && MAP == true)
	{
		MAP = false;
		Escmenu = false;
	}

	if (InputManager::GetKeyDown(Keyboard::Key::Left) && inventory == true && menuNum != 1)
	{
		orderNum = 1;
		weaponNum = 1;
		SuppliesNum = 1;
		EquipmentNum = 1;
		relicsNum = 1;
		--menuNum;
		InvenCS.setPosition(InvenCS.getPosition().x - 80, 328);
		InvenallCS.setPosition(340, 394);
	}

	if (InputManager::GetKeyDown(Keyboard::Key::Right) && inventory == true && menuNum != 7)
	{
		orderNum = 1;
		weaponNum = 1;
		SuppliesNum = 1;
		EquipmentNum = 1;
		relicsNum = 1;
		++menuNum;
		InvenCS.setPosition(InvenCS.getPosition().x + 80, 328);
		InvenallCS.setPosition(340, 394);
	}

	
	if (inventory == true && Zweapon == true && menuNum == 1 && Xweapon == true)
	{
		if (InputManager::GetKeyDown(Keyboard::Key::Up) && weaponNum != 1)
		{
			--weaponNum;
			InvenallCS.setPosition(340, InvenallCS.getPosition().y - 50);
		}
		if (InputManager::GetKeyDown(Keyboard::Key::Down) && weaponNum != 2)
		{
			++weaponNum;
			InvenallCS.setPosition(340, InvenallCS.getPosition().y + 50);
		}
	}

	if (inventory == true && Zscroll == true && menuNum == 2 && Xscroll == true)
	{
		if (InputManager::GetKeyDown(Keyboard::Key::Up) && orderNum != 1)
		{
			--orderNum;
			InvenallCS.setPosition(340, InvenallCS.getPosition().y - 50);
		}
		if (InputManager::GetKeyDown(Keyboard::Key::Down) && orderNum != 2)
		{
			++orderNum;
			InvenallCS.setPosition(340, InvenallCS.getPosition().y + 50);
		}
	}


	if (inventory == true && ZEquip == true && menuNum == 4 && XEquip == true)
	{
		if (InputManager::GetKeyDown(Keyboard::Key::Up) && EquipmentNum != 1)
		{
			--EquipmentNum;
			InvenallCS.setPosition(340, InvenallCS.getPosition().y - 50);
		}
		if (InputManager::GetKeyDown(Keyboard::Key::Down) && EquipmentNum != 2)
		{
			++EquipmentNum;
			InvenallCS.setPosition(340, InvenallCS.getPosition().y + 50);
		}
	}



	if (InputManager::GetKeyDown(Keyboard::Key::Right) && inventory == true && menuNum == 2 && orderNum == 1 && Zscroll == true && Xscroll == true)
	{
		scrollList1();
	}
	if (InputManager::GetKeyDown(Keyboard::Key::Down) && inventory == true && menuNum == 2 && orderNum == 2 && Zscroll == true && Xscroll == true)
	{
		scrollList2();
	}


	if (InputManager::GetKeyDown(Keyboard::Key::Right) && inventory == true && menuNum == 3 && SuppliesNum == 1 && Zfood == true)
	{
		Supplies();
	}


	if (InputManager::GetKeyDown(Keyboard::Key::Right) && inventory == true && menuNum == 4 && EquipmentNum == 1 && ZEquip == true && XEquip == true)
	{
		EquipList1();
	}
	if (InputManager::GetKeyDown(Keyboard::Key::Down) && inventory == true && menuNum == 4 && EquipmentNum == 2 && ZEquip == true && XEquip == true)
	{
		EquipList2();
	}

	if (InputManager::GetKeyDown(Keyboard::Key::Right) && inventory == true && menuNum == 5 && relicsNum == 1 && Zrelics == true)
	{
		relics();
	}

	
	if (InputManager::GetKeyDown(Keyboard::Key::Q) && MAP == false && Escset == false && Esckey == false)
	{
		inventory = false;
		MAP = true;
		SeeMap();
	}
	else if (InputManager::GetKeyDown(Keyboard::Key::Q) && inventory == false && Escset == false && Esckey == false)
	{
		menuNum = 1;
		MAP = false;
		inventory = true;
		SeeInven();
	}
	if (InputManager::GetKeyDown(Keyboard::Key::Q) && inventory == false && Escset == true && Esckey == false && MAP == false)
	{
		Escset = false;
		Esckey = true;
		EscKeyboard();
	}
	else if (InputManager::GetKeyDown(Keyboard::Key::Q) && inventory == false && Escset == false && Esckey == true && MAP == false)
	{
		settingNum = 1;
		Esckey = false;
		Escset = true;
		EscSetting();
	}


	if (InputManager::GetKeyDown(Keyboard::Key::W) && MAP == false && Escset == false && Esckey == false)
	{
		inventory = false;
		MAP = true;
		SeeMap();
	}
	else if (InputManager::GetKeyDown(Keyboard::Key::W) && inventory == false && Escset == false && Esckey == false)
	{
		menuNum = 1;
		MAP = false;
		inventory = true;
		SeeInven();
	}
	if (InputManager::GetKeyDown(Keyboard::Key::W) && inventory == false && Escset == true && Esckey == false && MAP == false)
	{
		Escset = false;
		Esckey = true;		
		EscKeyboard();
	}
	else if (InputManager::GetKeyDown(Keyboard::Key::W) && inventory == false && Escset == false && Esckey == true && MAP == false)
	{
		settingNum = 1;
		Esckey = false;
		Escset = true;
		EscSetting();
	}


	if (Escmenu == true)
	{
		if (InputManager::GetKeyDown(Keyboard::Key::Up) == true && escNum != 1)
		{
			--escNum;
			EscCS.setPosition(280, EscCS.getPosition().y - 80);
		}

		if (InputManager::GetKeyDown(Keyboard::Key::Down) == true && escNum != 3)
		{
			++escNum;
			EscCS.setPosition(280, EscCS.getPosition().y + 80);
		}
	}

	if (Escset == true)
	{
		if (InputManager::GetKeyDown(Keyboard::Key::Up) && settingNum != 1)
		{
			--settingNum;
			settingCS.setPosition(642, settingCS.getPosition().y - 80);
		}

		if (InputManager::GetKeyDown(Keyboard::Key::Down) && settingNum != 10)
		{
			++settingNum;
			settingCS.setPosition(642, settingCS.getPosition().y + 80);
		}

		if (InputManager::GetKeyDown(Keyboard::Key::Right) && settingNum == 3)
		{
			FullCSsetview = !FullCSsetview;
		}
		if (InputManager::GetKeyDown(Keyboard::Key::Left) && settingNum == 3)
		{
			FullCSsetview = !FullCSsetview;	
		}

		if (InputManager::GetKeyDown(Keyboard::Key::Right) && settingNum == 4)
		{
			VsyCSSetview = !VsyCSSetview;			
		}
		if (InputManager::GetKeyDown(Keyboard::Key::Left) && settingNum == 4)
		{
			VsyCSSetview = !VsyCSSetview;			
		}

		if (InputManager::GetKeyDown(Keyboard::Key::Right) && settingNum == 6)
		{
			BattleCSSetview = !BattleCSSetview;			
		}
		if (InputManager::GetKeyDown(Keyboard::Key::Left) && settingNum == 6)
		{
			BattleCSSetview = !BattleCSSetview;			
		}

		if (InputManager::GetKeyDown(Keyboard::Key::Left) && settingNum == 7 && masterNum != 1)
		{
			--masterNum;
			MasterCS.setPosition(MasterCS.getPosition().x - 67, 660);
		}
		if (InputManager::GetKeyDown(Keyboard::Key::Right) && settingNum == 7 && masterNum != 6)
		{
			++masterNum;
			MasterCS.setPosition(MasterCS.getPosition().x + 67, 660);
		}

		if (InputManager::GetKeyDown(Keyboard::Key::Left) && settingNum == 8 && uiNum != 1)
		{
			--uiNum;
			UICS.setPosition(UICS.getPosition().x - 67, 740);
		}
		if (InputManager::GetKeyDown(Keyboard::Key::Right) && settingNum == 8 && uiNum != 6)
		{
			++uiNum;
			UICS.setPosition(UICS.getPosition().x + 67, 740);
		}

		if (InputManager::GetKeyDown(Keyboard::Key::Left) && settingNum == 9 && sfxNum != 1)
		{
			--sfxNum;
			SFXCS.setPosition(SFXCS.getPosition().x - 67, 820);
		}
		if (InputManager::GetKeyDown(Keyboard::Key::Right) && settingNum == 9 && sfxNum != 6)
		{
			++sfxNum;
			SFXCS.setPosition(SFXCS.getPosition().x + 67, 820);
		}

		if (InputManager::GetKeyDown(Keyboard::Key::Left) && settingNum == 10 && musicNum != 1)
		{
			--musicNum;
			MusicCS.setPosition(MusicCS.getPosition().x - 67, 900);
		}
		if (InputManager::GetKeyDown(Keyboard::Key::Right) && settingNum == 10 && musicNum != 6)
		{
			++musicNum;
			MusicCS.setPosition(MusicCS.getPosition().x + 67, 900);
		}

	}

	if (InputManager::GetKeyDown(Keyboard::Key::Space) && Escmenu == true)
	{
		switch (escNum)
		{
		case 1:
			Escmenu = false;
			player.SetPause(false);
			break;

		case 2:
			Escmenu = false;
			Escset = true;
			if (Escset == true)
			{
				EscSetting();
			}
			break;

		case 3:
			exit(0);
		}
	}

	if (InputManager::GetKeyDown(Keyboard::Key::Escape) && Escset == true)
	{
		Escset = false;
	}
	if (InputManager::GetKeyDown(Keyboard::Key::Escape) && Esckey == true)
	{
		Esckey = false;
	}

}

void TestUi::Draw(RenderWindow* window, View* mainView)
{
	/*window->draw(amr1);
	window->draw(amr2);*/
	window->draw(HPbarLine);
	window->draw(HPbar);
	window->draw(MPbarLine);
	window->draw(MPbar);

	/*window->draw(BossHPbarLine);
	window->draw(BossHPbar);*/

	window->draw(Inventory);
	window->draw(Mapicon);
	window->draw(Wear1);
	window->draw(Wear2);
	window->draw(Shield);
	window->draw(Weapon);
	window->draw(ScrollA);
	window->draw(ScrollS);
	

	window->draw(ButtonTab);
	window->draw(ButtonM);
	window->draw(ButtonX);
	window->draw(ButtonZ);
	window->draw(ButtonS);
	window->draw(ButtonA);

	window->draw(textHPbar); // 체력숫자
	window->draw(textMPbar); // 마나숫자
	window->draw(textButtonTab); // TAB버튼
	window->draw(textButtonM); // M버튼
	window->draw(textButtonX); // 버튼X
	window->draw(textButtonZ); // 버튼Z
	window->draw(textButtonS); // 버튼S
	window->draw(textButtonA); // 버튼A

	if (inventory == true)
	{
		window->draw(Blur);
		window->draw(Invenwindow); // 인벤토리 창
		window->draw(InvenLongWeapon); // 인벤토리 무기
		window->draw(InvenOrder); // 인벤토리 주문
		window->draw(InvenSupplies); // 인벤토리 소모품
		window->draw(InvenEquipment); // 인벤토리 장비
		window->draw(InvenRelic); // 인벤토리 유물
		window->draw(InvenRecord); // 인벤토리 기록
		window->draw(InvenKey); // 인벤토리 열쇠
		window->draw(InvenCS); // 인벤토리 커서
		window->draw(Invenname); // 인벤토리 이름
		window->draw(InvenMap); // 인벤토리 맵
		window->draw(InvenBtQ); // 인벤토리Q버튼
		window->draw(InvenBtW); // 인벤토리W버튼

		window->draw(textInvenBtQ); // 인벤토리 내 Q버튼
		window->draw(textInvenBtW); // 인벤토리 내 W버튼
		window->draw(textInven); // (인벤토리) 텍스트
		window->draw(textMap); // (맵) 텍스트
	}

	if (MAP == true)
	{
		window->draw(Blur);
		window->draw(InventoryMAP); // 인벤토리 맵
		window->draw(Invenname); // 인벤토리 이름
		window->draw(InvenMap); // 인벤토리 맵
		window->draw(InvenBtQ); // 인벤토리Q버튼
		window->draw(InvenBtW); // 인벤토리W버튼

		window->draw(textInvenBtQ); // 인벤토리 내 Q버튼
		window->draw(textInvenBtW); // 인벤토리 내 W버튼
		window->draw(textInven); // (인벤토리) 텍스트
		window->draw(textMap); // (맵) 텍스트
	}

	if (Escmenu == true)
	{
		window->draw(Escback);
		window->draw(EscCS);
		window->draw(Continue);
		window->draw(Setting);
		window->draw(End);
	}

	if (Escset == true)
	{
		window->draw(setBlur);
		window->draw(spriteset1);
		window->draw(spriteset2);
		window->draw(SettingSet);
		window->draw(SettingKey);
		window->draw(SettingBtQ);
		window->draw(SettingBtW);
		window->draw(SetBtQ);
		window->draw(SetBtW);
		window->draw(Setname);
		window->draw(Keyname);
		window->draw(textLanguage);
		window->draw(LanCSL);
		window->draw(English);
		window->draw(LanCSR);
		window->draw(textResolution);
		window->draw(ResCSL);
		window->draw(screensize);
		window->draw(ResCSR);
		window->draw(textFullScreen);
		if (FullCSsetview)
		{
			window->draw(FullCS);
		}
		else
		{
			window->draw(FullCS2);
		}
		window->draw(textVsync);
		if (VsyCSSetview)
		{
			window->draw(VsyCS);
		}
		else
		{
			window->draw(VsyCS2);
		}
		window->draw(textRenderMode);
		window->draw(RenCSL);
		window->draw(ModeFull);
		window->draw(RenCSR);
		window->draw(textBattleLog);
		if (BattleCSSetview)
		{
			window->draw(BattleCS);
		}
		else
		{
			window->draw(BattleCS2);
		}		
		window->draw(textMasterVolume);
		window->draw(MasterBar);
		window->draw(MasterCS);
		window->draw(textUIVolume);
		window->draw(UIBar);
		window->draw(UICS);
		window->draw(textSFXVolume);
		window->draw(SFXBar);
		window->draw(SFXCS);
		window->draw(textMusicVolume);
		window->draw(MusicBar);
		window->draw(MusicCS);
		window->draw(Toggle);
		window->draw(ToggleLeft);
		window->draw(ToggleRight);
		window->draw(TogLeft);
		window->draw(TogRight);
		window->draw(SetBack);
		window->draw(ESCBack);
		window->draw(SetESC);
		window->draw(settingCS);
	}

	if (Esckey == true)
	{
		window->draw(setBlur);
		window->draw(spriteset1);
		window->draw(spriteset2);
		window->draw(SettingSet);
		window->draw(SettingKey);
		window->draw(SettingBtQ);
		window->draw(SettingBtW);
		window->draw(SetBtQ);
		window->draw(SetBtW);
		window->draw(Setname);
		window->draw(Keyname);
		window->draw(KeyboardLeft);
		window->draw(KeyboardLeftBox);
		window->draw(KeyboardLeftDire);
		window->draw(KeyboardRight);
		window->draw(KeyboardRightBox);
		window->draw(KeyboardRightDire);
		window->draw(KeyboardUP);
		window->draw(KeyboardUPBox);
		window->draw(KeyboardUPDire);
		window->draw(KeyboardDown);
		window->draw(KeyboardDownBox);
		window->draw(KeyboardDownDire);
		window->draw(KeyboardSpace);
		window->draw(KeyboardSpaceBox);
		window->draw(KeyboardC);
		window->draw(KeyboardCBox);
		window->draw(KeyboardSpaceDire);
		window->draw(KeyboardCDire);
		window->draw(KeyboardZ);
		window->draw(KeyboardZBox);
		window->draw(KeyboardZDire);
		window->draw(KeyboardX);
		window->draw(KeyboardXBox);
		window->draw(KeyboardXDire);
		window->draw(KeyboardA);
		window->draw(KeyboardABox);
		window->draw(KeyboardADire);
		window->draw(KeyboardS);
		window->draw(KeyboardSBox);
		window->draw(KeyboardSDire);
		window->draw(KeyboardTab);
		window->draw(KeyboardTabBox);
		window->draw(KeyboardTabDire);
		window->draw(KeyboardM);
		window->draw(KeyboardMBox);
		window->draw(KeyboardMDire);
		window->draw(KeyboardV);
		window->draw(KeyboardVBox);
		window->draw(KeyboardVDire);
		window->draw(KeyboardF);
		window->draw(KeyboardFBox);
		window->draw(KeyboardFDire);
		window->draw(KeyboardQ);
		window->draw(KeyboardQBox);
		window->draw(KeyboardQDire);
		window->draw(KeyboardW);
		window->draw(KeyboardWBox);
		window->draw(KeyboardWDire);
		window->draw(SetBack);
		window->draw(ESCBack);
		window->draw(SetESC);
	}

	if (Zweapon == true && menuNum == 1 && Xweapon == true && weaponNum == 1)
	{
		if (inventory == true)
		{
			window->draw(InvenWeaponblock5);
			window->draw(InvenallCS);
			window->draw(InvenWeaponZblock1);
			window->draw(textInvenweapon1);
			window->draw(InvenWeaponXblock2);
			window->draw(textInvenweapon2);
			window->draw(InvenWeaponblock3);
			window->draw(textInvenweapon3);
			window->draw(InvenWeaponblock4);
			window->draw(textInvenweapon4);
			window->draw(textInvenweapon5);
			window->draw(textInvenweapon6);
			window->draw(textInvenweapon7);
			window->draw(textInvenweapon8);
			window->draw(textInvenweapon9);
		}

		if (Zweaponview)
		{
			if (inventory == true)
			{
				window->draw(InvenWeaponZblock6);
				window->draw(InvenWeaponZblock26);
			}
		}
		if (Xweaponview)
		{
			if (inventory == true)
			{
				window->draw(InvenWeaponXblock7);
				window->draw(InvenWeaponXblock27);
			}
		}
	}


	if (Zweapon == true && menuNum == 1 && Xweapon == true && weaponNum == 2)
	{
		if (inventory == true)
		{
			window->draw(InvenWeaponblock25);
			window->draw(InvenallCS);
			window->draw(InvenWeaponZblock21);
			window->draw(textInvenweapon21);
			window->draw(InvenWeaponXblock22);
			window->draw(textInvenweapon22);
			window->draw(InvenWeaponblock23);
			window->draw(textInvenweapon23);
			window->draw(InvenWeaponblock24);
			window->draw(textInvenweapon24);
			window->draw(textInvenweapon25);
			window->draw(textInvenweapon26);
			window->draw(textInvenweapon27);
			window->draw(textInvenweapon28);
			window->draw(textInvenweapon29);
		}
		if (Zweaponview)
		{
			if (inventory == true)
			{
				window->draw(InvenWeaponZblock6);
				window->draw(InvenWeaponZblock26);
			}
		}
		if (Xweaponview)
		{
			if (inventory == true)
			{
				window->draw(InvenWeaponXblock7);
				window->draw(InvenWeaponXblock27);
			}
		}
	}

	if (Zweaponview)
	{
		window->draw(wea);
	}

	if (Xweaponview)
	{
		window->draw(shi);
	}
	////////////////////////////////////////////////////////////////////
	
	if (Zscroll == true && menuNum == 2 && Xscroll == true && orderNum == 1)
	{
		if (inventory == true)
		{
			window->draw(Oitembackground1);
			window->draw(InvenallCS);
			window->draw(Orderblankrhombus1);
			window->draw(Otextscrollname1);
			window->draw(Orderblankrhombus2);
			window->draw(Otextscrollname2);
			window->draw(orderitemphotoframe1);
			window->draw(OtextItemnamefield1);
			window->draw(OdescriptionImage1);
			window->draw(Omagictype1);
			window->draw(Oattackspeed1);
			window->draw(ODamage1);
			window->draw(OItemDescription1);
			window->draw(OItemDescription2);
			window->draw(OItemDescription3);
		}
		if (Zscrollview)
		{
			if (inventory == true)
			{
				window->draw(Orderfullrhombus1);
				window->draw(Orderfullrhombus3);
			}			
		}


		if (Xscrollview)
		{
			if (inventory == true)
			{
				window->draw(Orderfullrhombus2);
				window->draw(Orderfullrhombus4);
			}			
		}		
	}
	
	

	if (Zscroll == true && menuNum == 2 && Xscroll == true && orderNum == 2)
	{
		if (inventory == true)
		{
			window->draw(Oitembackground2);
			window->draw(InvenallCS);
			window->draw(Orderblankrhombus1);
			window->draw(Otextscrollname1);
			window->draw(Orderblankrhombus2);
			window->draw(Otextscrollname2);
			window->draw(orderitemphotoframe2);
			window->draw(OtextItemnamefield2);
			window->draw(OdescriptionImage2);
			window->draw(Omagictype2);
			window->draw(Oattackspeed2);
			window->draw(ODamage2);
			window->draw(OItemDescription01);
			window->draw(OItemDescription02);
			window->draw(OItemDescription03);
			window->draw(OItemDescription04);
		}

		if (Zscrollview)
		{
			if (inventory == true)
			{
				window->draw(Orderfullrhombus1);
				window->draw(Orderfullrhombus3);
			}						
		}


		if (Xscrollview)
		{
			if (inventory == true)
			{
				window->draw(Orderfullrhombus2);
				window->draw(Orderfullrhombus4);
			}					
		}
	}
	if (Zscrollview)
	{
		window->draw(scr1);
	}
	if (Xscrollview)
	{
		window->draw(scr2);
	}



	if (Zfood == true && menuNum == 3 && SuppliesNum == 1)
	{
		if (inventory == true)
		{
			window->draw(Suppliesitembackground1);
			window->draw(InvenallCS);
			window->draw(Suppliesblankrhombus1);
			window->draw(Suppliestextscrollname1);
			window->draw(Suppliesitemphotoframe1);
			window->draw(SuppliestextItemnamefield1);
			window->draw(SuppliesdescriptionImage1);
			window->draw(Suppliesmagictype1);
			window->draw(Suppliesattackspeed1);
			window->draw(SuppliesDamage1);
			window->draw(SuppliesItemDescription1);
			window->draw(SuppliesItemDescription2);
			window->draw(SuppliesItemDescription3);
		}
		if (Zfoodview)
		{
			if (inventory == true)
			{
				window->draw(Suppliesrderfullrhombus1);
			}
		}
	}



	if (ZEquip == true && menuNum == 4 && XEquip == true && EquipmentNum == 1)
	{
		if (inventory == true)
		{
			window->draw(Equipitembackground1);
			window->draw(InvenallCS);
			window->draw(Equipblankrhombus1);
			window->draw(Equiptextscrollname1);
			window->draw(Equipblankrhombus2);
			window->draw(Equiptextscrollname2);
			window->draw(Equipitemphotoframe1);
			window->draw(EquiptextItemnamefield1);
			window->draw(EquipdescriptionImage1);
			window->draw(Equipmagictype1);
			window->draw(Equipattackspeed1);
			window->draw(EquipDamage1);
			window->draw(EquipItemDescription1);
			window->draw(EquipItemDescription2);
			window->draw(EquipItemDescription3);
		}
		if (ZEquipview)
		{
			if (inventory == true)
			{
				window->draw(Equiprderfullrhombus1);
				window->draw(Equiprderfullrhombus3);
			}
		}


		if (XEquipview)
		{
			if (inventory == true)
			{
				window->draw(Equiprderfullrhombus2);
				window->draw(Equiprderfullrhombus4);
			}
		}
	}



	if (ZEquip == true && menuNum == 4 && XEquip == true && EquipmentNum == 2)
	{
		if (inventory == true)
		{
			window->draw(Equipitembackground2);
			window->draw(InvenallCS);
			window->draw(Equipblankrhombus1);
			window->draw(Equiptextscrollname1);
			window->draw(Equipblankrhombus2);
			window->draw(Equiptextscrollname2);
			window->draw(Equipitemphotoframe2);
			window->draw(EquiptextItemnamefield2);
			window->draw(EquipdescriptionImage2);
			window->draw(Equipmagictype2);
			window->draw(Equipattackspeed2);
			window->draw(EquipDamage2);
			window->draw(EquipItemDescription01);
			window->draw(EquipItemDescription02);
			window->draw(EquipItemDescription03);
			window->draw(EquipItemDescription04);
		}

		if (ZEquipview)
		{
			if (inventory == true)
			{
				window->draw(Equiprderfullrhombus1);
				window->draw(Equiprderfullrhombus3);
			}
		}


		if (XEquipview)
		{
			if (inventory == true)
			{
				window->draw(Equiprderfullrhombus2);
				window->draw(Equiprderfullrhombus4);
			}
		}
	}
	if (ZEquipview)
	{
		window->draw(amr1);
	}
	if (XEquipview)
	{
		window->draw(amr2);
	}

	if (Zrelics == true && menuNum == 5 && relicsNum == 1)
	{
		if (inventory == true)
		{
			window->draw(Relicitembackground1);
			window->draw(InvenallCS);
			window->draw(Relicblankrhombus1);
			window->draw(Relictextscrollname1);
			window->draw(Relicitemphotoframe1);
			window->draw(RelictextItemnamefield1);
			window->draw(RelicdescriptionImage1);
			window->draw(Relicmagictype1);
			window->draw(Relicattackspeed1);
			window->draw(RelicDamage1);
			window->draw(RelicItemDescription1);
			window->draw(RelicItemDescription2);
			window->draw(RelicItemDescription3);
		}
		if (Zrelicsview)
		{
			if (inventory == true)
			{
				window->draw(Relicrderfullrhombus1);
			}
		}
	}
}

void TestUi::Initstartimg()
{
	// 테스트 배경
	textureback = TextureHolder::GetTexture("graphics/background.png");

	spriteback.setTexture(textureback);
	spriteback.setPosition(0, 0);


	//인벤토리 내 카테고리 커서
	InvenallCS.setTexture(textureUI); // 인벤토리 커서
	InvenallCS.setTextureRect(IntRect(351, 1347, 1209, 90));
	InvenallCS.setScale(Vector2f(0.2f, 0.5f));
	InvenallCS.setPosition(340, 394);


	// UI 스크롤 이미지
	scrollpng = TextureHolder::GetTexture("graphics/Scroll.png");

	scr1.setTexture(scrollpng);
	scr1.setTextureRect(IntRect(3, 131, 20, 22));
	scr1.setScale(Vector2f(1.7f, 1.7f));
	scr1.setPosition(1570, 34);

	scr2.setTexture(scrollpng);
	scr2.setTextureRect(IntRect(103, 131, 20, 22));
	scr2.setScale(Vector2f(1.7f, 1.7f));
	scr2.setPosition(1662, 34);


	// UI 무기 이미지 (한손검)(단검)
	weaponpng = TextureHolder::GetTexture("graphics/Weapon.png");

	wea.setTexture(weaponpng);
	wea.setTextureRect(IntRect(13, 148, 14, 53));
	wea.setScale(Vector2f(1.1f, 1.1f));
	wea.setPosition(1767, 27);

	shi.setTexture(weaponpng);
	shi.setTextureRect(IntRect(3, 17, 4, 25));
	shi.setScale(Vector2f(1.9f, 1.9f));
	shi.setPosition(1863, 33);


	// UI 장비 이미지
	amr1.setTexture(scrollpng);
	amr1.setTextureRect(IntRect(3, 226, 12, 15));
	amr1.setScale(Vector2f(2.5f, 2.5f));
	amr1.setPosition(547, 35);

	amr2.setTexture(scrollpng);
	amr2.setTextureRect(IntRect(20, 226, 11, 14));
	amr2.setScale(Vector2f(2.5f, 2.5f));
	amr2.setPosition(629, 35);


	// UI 이미지 (ex 체력칸, 마나칸, 무기칸 등등..)
	textureUI = TextureHolder::GetTexture("graphics/UI.png");

	HPbarLine.setTexture(textureUI);
	HPbarLine.setTextureRect(IntRect(355, 822, 353, 33));
	HPbarLine.setPosition(0, 10);

	HPbar.setTexture(textureUI);
	HPbar.setTextureRect(IntRect(20, 830, 314, 17));
	HPbar.setPosition(18, 18);

	MPbarLine.setTexture(textureUI);
	MPbarLine.setTextureRect(IntRect(350, 876, 348, 33));
	MPbarLine.setPosition(0, 50);

	MPbar.setTexture(textureUI);
	MPbar.setTextureRect(IntRect(18, 884, 314, 17));
	MPbar.setPosition(17, 58);

	BossHPbarLine.setTexture(textureUI);
	BossHPbarLine.setTextureRect(IntRect(3, 1507, 718, 17));
	BossHPbarLine.setPosition(610, 1000);

	BossHPbar.setTexture(textureUI);
	BossHPbar.setTextureRect(IntRect(11, 1489, 699, 7));
	BossHPbar.setPosition(620, 1005);

	Inventory.setTexture(textureUI);
	Inventory.setTextureRect(IntRect(503, 675, 102, 118));
	Inventory.setScale(Vector2f(0.5f, 0.5f));
	Inventory.setPosition(370, 20);

	Mapicon.setTexture(textureUI);
	Mapicon.setTextureRect(IntRect(612, 683, 98, 102));
	Mapicon.setScale(Vector2f(0.5f, 0.5f));
	Mapicon.setPosition(450, 30);

	Wear1.setTexture(textureUI);
	Wear1.setTextureRect(IntRect(436, 673, 64, 64));
	Wear1.setPosition(530, 25);

	Wear2.setTexture(textureUI);
	Wear2.setTextureRect(IntRect(436, 673, 64, 64));
	Wear2.setPosition(610, 25);

	Shield.setTexture(textureUI);
	Shield.setTextureRect(IntRect(1, 673, 128, 128));
	Shield.setScale(Vector2f(0.7f, 0.7f));
	Shield.setPosition(1820, 10);

	Weapon.setTexture(textureUI);
	Weapon.setTextureRect(IntRect(1, 673, 128, 128));
	Weapon.setScale(Vector2f(0.7f, 0.7f));
	Weapon.setPosition(1730, 10);

	ScrollS.setTexture(textureUI);
	ScrollS.setTextureRect(IntRect(1, 673, 128, 128));
	ScrollS.setScale(Vector2f(0.7f, 0.7f));
	ScrollS.setPosition(1630, 10);

	ScrollA.setTexture(textureUI);
	ScrollA.setTextureRect(IntRect(1, 673, 128, 128));
	ScrollA.setScale(Vector2f(0.7f, 0.7f));
	ScrollA.setPosition(1540, 10);

	ButtonTab.setTexture(textureUI);
	ButtonTab.setTextureRect(IntRect(62, 605, 42, 40));
	ButtonTab.setScale(Vector2f(1.4f, 0.9f));
	ButtonTab.setPosition(390, 50);

	ButtonM.setTexture(textureUI);
	ButtonM.setTextureRect(IntRect(62, 605, 42, 40));
	ButtonM.setPosition(475, 50);

	ButtonX.setTexture(textureUI);
	ButtonX.setTextureRect(IntRect(62, 605, 42, 40));
	ButtonX.setPosition(1870, 60);

	ButtonZ.setTexture(textureUI);
	ButtonZ.setTextureRect(IntRect(62, 605, 42, 40));
	ButtonZ.setPosition(1780, 60);

	ButtonS.setTexture(textureUI);
	ButtonS.setTextureRect(IntRect(62, 605, 42, 40));
	ButtonS.setPosition(1680, 10);

	ButtonA.setTexture(textureUI);
	ButtonA.setTextureRect(IntRect(62, 605, 42, 40));
	ButtonA.setPosition(1590, 10);

	// UI 폰트
	fontLostRuins.loadFromFile("fonts/LiberationSans-Regular.ttf");
	
	textHPbar.setFont(fontLostRuins);
	textMPbar.setFont(fontLostRuins);
	textButtonTab.setFont(fontLostRuins);
	textButtonM.setFont(fontLostRuins);
	textButtonX.setFont(fontLostRuins);
	textButtonZ.setFont(fontLostRuins);
	textButtonS.setFont(fontLostRuins);
	textButtonA.setFont(fontLostRuins);


	// UI String
	textHPbar.setString("20/20");
	textMPbar.setString("20/20");
	textButtonTab.setString("TAB");
	textButtonM.setString("M");
	textButtonX.setString("X");
	textButtonZ.setString("Z");
	textButtonS.setString("S");
	textButtonA.setString("A");

	// UI String Size
	textHPbar.setCharacterSize(20);
	textMPbar.setCharacterSize(20);
	textButtonTab.setCharacterSize(20);
	textButtonM.setCharacterSize(20);
	textButtonX.setCharacterSize(20);
	textButtonZ.setCharacterSize(20);
	textButtonS.setCharacterSize(20);
	textButtonA.setCharacterSize(20);

	// UI String Color
	textHPbar.setFillColor(Color::White);
	textMPbar.setFillColor(Color::White);
	textButtonTab.setFillColor(Color::White);
	textButtonM.setFillColor(Color::White);
	textButtonX.setFillColor(Color::White);
	textButtonZ.setFillColor(Color::White);
	textButtonS.setFillColor(Color::White);
	textButtonA.setFillColor(Color::White);


	// UI String Position
	textHPbar.setPosition(23, 12);
	textMPbar.setPosition(23, 53);
	textButtonTab.setPosition(400, 55);
	textButtonM.setPosition(487, 57);
	textButtonX.setPosition(1884, 67);
	textButtonZ.setPosition(1794, 67);
	textButtonS.setPosition(1694, 17);
	textButtonA.setPosition(1604, 17);


	// UI 체력, 마나 게이지
	HPbar.setScale(1.f, 1.f);
	MPbar.setScale(1.f, 1.f);

	// 메뉴 이동 초기화
	menuNum = 1;		// 인벤토리 좌우
	weaponNum = 1;		// 인벤토리 -> 무기 상하
	orderNum = 1;		// 인벤토리 -> 주문서 상하
	SuppliesNum = 1;	// 인벤토리 -> 소모품 상하
	EquipmentNum = 1;	// 인벤토리 -> 장비 상하
	relicsNum = 1;

	escNum = 1;		// ESC 상하
	settingNum = 1;	// ESC -> Setting
	masterNum = 1;	// ESC -> Master Vol 좌우 초기화
	uiNum = 1;		// ESC -> UI Vol 좌우 초기화
	sfxNum = 1;		// ESC -> SFX Vol 좌우 초기화
	musicNum = 1;	// ESC -> Music Vol 좌우 초기화

	inventory = false;	// 인벤토리(Tab)
	MAP = false;		// 맵(M)
	Escmenu = false;	// ESC(메뉴)
	Escset = false;		// ESC -> Setting	
	Esckey = false;		// ESC -> Keyboard
	Zweapon = true;		// Z무기
	Zweaponview = false;// Z무기 표시
	Xweapon = true;		// X무기
	Xweaponview = false;// X무기 표시
	FullCSsetview = false;
	VsyCSSetview = false;
	BattleCSSetview = false;
	Zscroll = true;
	Zscrollview = false;
	Xscroll = true;
	Xscrollview = false;
	Zfood = true;
	Zfoodview = false;
	ZEquip = true;
	ZEquipview = false;
	XEquip = true;
	XEquipview = false;
	Zrelics = true;
	Zrelicsview = false;
}

void TestUi::EscKeyboard() // ESC -> Setting -> Keyboard
{
	texturesetting = TextureHolder::GetTexture("graphics/setting.png");
	setBlur1 = TextureHolder::GetTexture("graphics/esc.png");
	settingLan.loadFromFile("fonts/LiberationSans-Bold.ttf");
	textureSQ = TextureHolder::GetTexture("graphics/SQ.png");
	fontLostRuins.loadFromFile("fonts/LiberationSans-Regular.ttf");

	setBlur.setTexture(setBlur1); // 설정 배경
	setBlur.setTextureRect(IntRect(39, 2385, 1339, 887));
	setBlur.setScale(Vector2f(0.709f, 2.0f));
	setBlur.setPosition(480, 0); //280, 280

	spriteset1.setTexture(texturesetting); //설정 기둥(좌) 1
	spriteset1.setTextureRect(IntRect(1125, 55, 9, 769));
	spriteset1.setScale(Vector2f(1.0f, 2.0f));
	spriteset1.setPosition(475, 0);

	spriteset2.setTexture(texturesetting); //설정 기둥(우) 2
	spriteset2.setTextureRect(IntRect(1125, 55, 9, 769));
	spriteset2.setScale(Vector2f(1.0f, 2.0f));
	spriteset2.setPosition(1425, 0);

	SettingSet.setTexture(textureSQ); // Setting 이름
	SettingSet.setTextureRect(IntRect(1021, 638, 346, 115));
	SettingSet.setScale(Vector2f(0.6f, 0.7f));
	SettingSet.setPosition(760, 10);
	Setname.setFont(settingLan);
	Setname.setString("Settings");
	Setname.setCharacterSize(30);
	Setname.setFillColor(Color::White);
	Setname.setPosition(805, 30);


	SettingKey.setTexture(textureSQ); // Keyboard 이름
	SettingKey.setTextureRect(IntRect(1021, 638, 346, 115));
	SettingKey.setScale(Vector2f(0.6f, 0.7f));
	SettingKey.setPosition(980, 10);
	Keyname.setFont(settingLan);
	Keyname.setString("Keyboard");
	Keyname.setCharacterSize(30);
	Keyname.setFillColor(Color::Green);
	Keyname.setPosition(1015, 30);


	SettingBtQ.setTexture(textureUI); // 설정 버튼Q
	SettingBtQ.setTextureRect(IntRect(62, 605, 42, 40));
	SettingBtQ.setPosition(710, 50);
	SetBtQ.setFont(fontLostRuins);
	SetBtQ.setString("Q");
	SetBtQ.setCharacterSize(20);
	SetBtQ.setFillColor(Color::White);
	SetBtQ.setPosition(722, 56);


	SettingBtW.setTexture(textureUI); // 설정 버튼W
	SettingBtW.setTextureRect(IntRect(62, 605, 42, 40));
	SettingBtW.setPosition(1195, 50);
	SetBtW.setFont(fontLostRuins);
	SetBtW.setString("W");
	SetBtW.setCharacterSize(20);
	SetBtW.setFillColor(Color::White);
	SetBtW.setPosition(1207, 58);

	////////////////////////////////////

	KeyboardLeft.setFont(settingLan); // 왼쪽
	KeyboardLeft.setString("Left");
	KeyboardLeft.setCharacterSize(25);
	KeyboardLeft.setFillColor(Color::White);
	KeyboardLeft.setPosition(750, 118);

	KeyboardLeftBox.setTexture(textureUI); // 왼쪽 버튼 박스
	KeyboardLeftBox.setTextureRect(IntRect(62, 605, 42, 40));
	KeyboardLeftBox.setPosition(1150, 113);

	KeyboardLeftDire.setFont(fontLostRuins); // 왼쪽
	KeyboardLeftDire.setString("<-");
	KeyboardLeftDire.setCharacterSize(20);
	KeyboardLeftDire.setFillColor(Color::White);
	KeyboardLeftDire.setPosition(1162, 119);

	////////////////////////////////////

	KeyboardRight.setFont(settingLan);
	KeyboardRight.setString("Right");
	KeyboardRight.setCharacterSize(25);
	KeyboardRight.setFillColor(Color::White);
	KeyboardRight.setPosition(750, 168);

	KeyboardRightBox.setTexture(textureUI);
	KeyboardRightBox.setTextureRect(IntRect(62, 605, 42, 40));
	KeyboardRightBox.setPosition(1150, 163);

	KeyboardRightDire.setFont(fontLostRuins);
	KeyboardRightDire.setString("->");
	KeyboardRightDire.setCharacterSize(20);
	KeyboardRightDire.setFillColor(Color::White);
	KeyboardRightDire.setPosition(1162, 169);

	////////////////////////////////////

	KeyboardUP.setFont(settingLan);
	KeyboardUP.setString("Up");
	KeyboardUP.setCharacterSize(25);
	KeyboardUP.setFillColor(Color::White);
	KeyboardUP.setPosition(750, 218);

	KeyboardUPBox.setTexture(textureUI);
	KeyboardUPBox.setTextureRect(IntRect(62, 605, 42, 40));
	KeyboardUPBox.setPosition(1150, 213);

	KeyboardUPDire.setFont(fontLostRuins);
	KeyboardUPDire.setString("UP");
	KeyboardUPDire.setCharacterSize(20);
	KeyboardUPDire.setFillColor(Color::White);
	KeyboardUPDire.setPosition(1157, 219);

	////////////////////////////////////

	KeyboardDown.setFont(settingLan);
	KeyboardDown.setString("Down");
	KeyboardDown.setCharacterSize(25);
	KeyboardDown.setFillColor(Color::White);
	KeyboardDown.setPosition(750, 268);

	KeyboardDownBox.setTexture(textureUI);
	KeyboardDownBox.setTextureRect(IntRect(62, 605, 42, 40));
	KeyboardDownBox.setPosition(1147, 263);
	KeyboardDownBox.setScale(1.2f, 1.0f);

	KeyboardDownDire.setFont(fontLostRuins);
	KeyboardDownDire.setString("DW");
	KeyboardDownDire.setCharacterSize(20);
	KeyboardDownDire.setFillColor(Color::White);
	KeyboardDownDire.setPosition(1154, 269);

	////////////////////////////////////

	KeyboardSpace.setFont(settingLan);
	KeyboardSpace.setString("Jump");
	KeyboardSpace.setCharacterSize(25);
	KeyboardSpace.setFillColor(Color::White);
	KeyboardSpace.setPosition(750, 318);

	KeyboardSpaceBox.setTexture(textureUI);
	KeyboardSpaceBox.setTextureRect(IntRect(62, 605, 42, 40));
	KeyboardSpaceBox.setPosition(1126, 363);
	KeyboardSpaceBox.setScale(2.4f, 1.0f);

	KeyboardSpaceDire.setFont(fontLostRuins);
	KeyboardSpaceDire.setString("C");
	KeyboardSpaceDire.setCharacterSize(20);
	KeyboardSpaceDire.setFillColor(Color::White);
	KeyboardSpaceDire.setPosition(1162, 319); // 1162

	////////////////////////////////////

	KeyboardC.setFont(settingLan);
	KeyboardC.setString("Roll");
	KeyboardC.setCharacterSize(25);
	KeyboardC.setFillColor(Color::White);
	KeyboardC.setPosition(750, 368);

	KeyboardCBox.setTexture(textureUI);
	KeyboardCBox.setTextureRect(IntRect(62, 605, 42, 40));
	KeyboardCBox.setPosition(1150, 313); // 1126 313
	KeyboardSpaceBox.setScale(2.4f, 1.0f);

	KeyboardCDire.setFont(fontLostRuins);
	KeyboardCDire.setString("Space");
	KeyboardCDire.setCharacterSize(20);
	KeyboardCDire.setFillColor(Color::White);
	KeyboardCDire.setPosition(1147, 369); //1147

	////////////////////////////////////

	KeyboardZ.setFont(settingLan);
	KeyboardZ.setString("Weapon1");
	KeyboardZ.setCharacterSize(25);
	KeyboardZ.setFillColor(Color::White);
	KeyboardZ.setPosition(750, 418);

	KeyboardZBox.setTexture(textureUI);
	KeyboardZBox.setTextureRect(IntRect(62, 605, 42, 40));
	KeyboardZBox.setPosition(1150, 413);

	KeyboardZDire.setFont(fontLostRuins);
	KeyboardZDire.setString("Z");
	KeyboardZDire.setCharacterSize(20);
	KeyboardZDire.setFillColor(Color::White);
	KeyboardZDire.setPosition(1162, 419);

	////////////////////////////////////

	KeyboardX.setFont(settingLan);
	KeyboardX.setString("Weapon2");
	KeyboardX.setCharacterSize(25);
	KeyboardX.setFillColor(Color::White);
	KeyboardX.setPosition(750, 468);

	KeyboardXBox.setTexture(textureUI);
	KeyboardXBox.setTextureRect(IntRect(62, 605, 42, 40));
	KeyboardXBox.setPosition(1150, 463);

	KeyboardXDire.setFont(fontLostRuins);
	KeyboardXDire.setString("X");
	KeyboardXDire.setCharacterSize(20);
	KeyboardXDire.setFillColor(Color::White);
	KeyboardXDire.setPosition(1162, 469);

	////////////////////////////////////

	KeyboardA.setFont(settingLan);
	KeyboardA.setString("Spell1");
	KeyboardA.setCharacterSize(25);
	KeyboardA.setFillColor(Color::White);
	KeyboardA.setPosition(750, 518);

	KeyboardABox.setTexture(textureUI);
	KeyboardABox.setTextureRect(IntRect(62, 605, 42, 40));
	KeyboardABox.setPosition(1150, 513);

	KeyboardADire.setFont(fontLostRuins);
	KeyboardADire.setString("A");
	KeyboardADire.setCharacterSize(20);
	KeyboardADire.setFillColor(Color::White);
	KeyboardADire.setPosition(1162, 519);

	////////////////////////////////////

	KeyboardS.setFont(settingLan);
	KeyboardS.setString("Spell2");
	KeyboardS.setCharacterSize(25);
	KeyboardS.setFillColor(Color::White);
	KeyboardS.setPosition(750, 568);

	KeyboardSBox.setTexture(textureUI);
	KeyboardSBox.setTextureRect(IntRect(62, 605, 42, 40));
	KeyboardSBox.setPosition(1150, 563);

	KeyboardSDire.setFont(fontLostRuins);
	KeyboardSDire.setString("S");
	KeyboardSDire.setCharacterSize(20);
	KeyboardSDire.setFillColor(Color::White);
	KeyboardSDire.setPosition(1162, 569);

	////////////////////////////////////

	KeyboardTab.setFont(settingLan);
	KeyboardTab.setString("Inventory");
	KeyboardTab.setCharacterSize(25);
	KeyboardTab.setFillColor(Color::White);
	KeyboardTab.setPosition(750, 618);

	KeyboardTabBox.setTexture(textureUI);
	KeyboardTabBox.setTextureRect(IntRect(62, 605, 42, 40));
	KeyboardTabBox.setScale(1.3f, 1.0f);
	KeyboardTabBox.setPosition(1144, 613);

	KeyboardTabDire.setFont(fontLostRuins);
	KeyboardTabDire.setString("Tab");
	KeyboardTabDire.setCharacterSize(20);
	KeyboardTabDire.setFillColor(Color::White);
	KeyboardTabDire.setPosition(1155, 619);

	////////////////////////////////////

	KeyboardM.setFont(settingLan);
	KeyboardM.setString("Map");
	KeyboardM.setCharacterSize(25);
	KeyboardM.setFillColor(Color::White);
	KeyboardM.setPosition(750, 668);

	KeyboardMBox.setTexture(textureUI);
	KeyboardMBox.setTextureRect(IntRect(62, 605, 42, 40));
	KeyboardMBox.setPosition(1150, 663);

	KeyboardMDire.setFont(fontLostRuins);
	KeyboardMDire.setString("M");
	KeyboardMDire.setCharacterSize(20);
	KeyboardMDire.setFillColor(Color::White);
	KeyboardMDire.setPosition(1162, 669);

	////////////////////////////////////

	KeyboardV.setFont(settingLan);
	KeyboardV.setString("Sort");
	KeyboardV.setCharacterSize(25);
	KeyboardV.setFillColor(Color::White);
	KeyboardV.setPosition(750, 718);

	KeyboardVBox.setTexture(textureUI);
	KeyboardVBox.setTextureRect(IntRect(62, 605, 42, 40));
	KeyboardVBox.setPosition(1150, 713);

	KeyboardVDire.setFont(fontLostRuins);
	KeyboardVDire.setString("V");
	KeyboardVDire.setCharacterSize(20);
	KeyboardVDire.setFillColor(Color::White);
	KeyboardVDire.setPosition(1162, 719);

	////////////////////////////////////

	KeyboardF.setFont(settingLan);
	KeyboardF.setString("Favorite");
	KeyboardF.setCharacterSize(25);
	KeyboardF.setFillColor(Color::White);
	KeyboardF.setPosition(750, 768);

	KeyboardFBox.setTexture(textureUI);
	KeyboardFBox.setTextureRect(IntRect(62, 605, 42, 40));
	KeyboardFBox.setPosition(1150, 763);

	KeyboardFDire.setFont(fontLostRuins);
	KeyboardFDire.setString("F");
	KeyboardFDire.setCharacterSize(20);
	KeyboardFDire.setFillColor(Color::White);
	KeyboardFDire.setPosition(1162, 769);

	////////////////////////////////////

	KeyboardQ.setFont(settingLan);
	KeyboardQ.setString("Left Tab");
	KeyboardQ.setCharacterSize(25);
	KeyboardQ.setFillColor(Color::White);
	KeyboardQ.setPosition(750, 818);

	KeyboardQBox.setTexture(textureUI);
	KeyboardQBox.setTextureRect(IntRect(62, 605, 42, 40));
	KeyboardQBox.setPosition(1150, 813);

	KeyboardQDire.setFont(fontLostRuins);
	KeyboardQDire.setString("Q");
	KeyboardQDire.setCharacterSize(20);
	KeyboardQDire.setFillColor(Color::White);
	KeyboardQDire.setPosition(1162, 819);

	////////////////////////////////////

	KeyboardW.setFont(settingLan);
	KeyboardW.setString("Right Tab");
	KeyboardW.setCharacterSize(25);
	KeyboardW.setFillColor(Color::White);
	KeyboardW.setPosition(750, 868);

	KeyboardWBox.setTexture(textureUI);
	KeyboardWBox.setTextureRect(IntRect(62, 605, 42, 40));
	KeyboardWBox.setPosition(1150, 863);

	KeyboardWDire.setFont(fontLostRuins);
	KeyboardWDire.setString("W");
	KeyboardWDire.setCharacterSize(20);
	KeyboardWDire.setFillColor(Color::White);
	KeyboardWDire.setPosition(1162, 869);

	////////////////////////////////////

	SetBack.setFont(settingLan);
	SetBack.setString("Back");
	SetBack.setCharacterSize(25);
	SetBack.setFillColor(Color::White);
	SetBack.setPosition(1000, 1000);

	ESCBack.setTexture(textureUI); // ESC 버튼 박스
	ESCBack.setTextureRect(IntRect(62, 605, 42, 40));
	ESCBack.setScale(Vector2f(1.5f, 1.0f));
	ESCBack.setPosition(925, 995);

	SetESC.setFont(fontLostRuins); // ESC 텍스트
	SetESC.setString("Esc");
	SetESC.setCharacterSize(20);
	SetESC.setFillColor(Color::White);
	SetESC.setPosition(939, 1001);
}

void TestUi::weaponlist1()
{
	weaponNum = 1;
	textureSQ = TextureHolder::GetTexture("graphics/SQ.png");
	fontLostRuins.loadFromFile("fonts/LiberationSans-Regular.ttf");
	weaponpng = TextureHolder::GetTexture("graphics/Weapon.png");

	InvenWeaponZblock1.setTexture(textureSQ); //  1. 마름모 빈칸
	InvenWeaponZblock1.setTextureRect(IntRect(33, 1016, 39, 31));
	InvenWeaponZblock1.setScale(Vector2f(1.0f, 1.0f));
	InvenWeaponZblock1.setPosition(320, 400);

	textInvenweapon1.setFont(fontLostRuins); // 1. 리스트 내 아이템 이름
	textInvenweapon1.setString("Gladius");
	textInvenweapon1.setCharacterSize(30);
	textInvenweapon1.setFillColor(Color::Red);
	textInvenweapon1.setPosition(380, 395);

	InvenWeaponXblock2.setTexture(textureSQ); // 2. 마름모 빈칸
	InvenWeaponXblock2.setTextureRect(IntRect(33, 1016, 39, 31));
	InvenWeaponXblock2.setScale(Vector2f(1.0f, 1.0f));
	InvenWeaponXblock2.setPosition(320, 450);

	textInvenweapon2.setFont(fontLostRuins); // 2. 리스트 내 아이템 이름
	textInvenweapon2.setString("Dagger");
	textInvenweapon2.setCharacterSize(30);
	textInvenweapon2.setFillColor(Color::Red);
	textInvenweapon2.setPosition(380, 445);


	///////////////////////////////////////////////////////////////

	InvenWeaponblock3.setTexture(textureSQ); // 우측 아이템 네모칸
	InvenWeaponblock3.setTextureRect(IntRect(254, 673, 92, 96));
	InvenWeaponblock3.setScale(Vector2f(1.0f, 1.0f));
	InvenWeaponblock3.setPosition(980, 380);

	textInvenweapon3.setFont(fontLostRuins); // 우측 아이템 이름
	textInvenweapon3.setString("Gladius");
	textInvenweapon3.setCharacterSize(40);
	textInvenweapon3.setFillColor(Color::Red);
	textInvenweapon3.setPosition(1100, 400);

	InvenWeaponblock4.setTexture(weaponpng); // 우측 아이템 이미지
	InvenWeaponblock4.setTextureRect(IntRect(13, 148, 14, 53));
	InvenWeaponblock4.setScale(Vector2f(1.1f, 1.0f));
	InvenWeaponblock4.setPosition(1020, 400);

	InvenWeaponblock5.setTexture(textureSQ); // 아이템 이미지 뒷 배경
	InvenWeaponblock5.setTextureRect(IntRect(62, 605, 42, 40));
	InvenWeaponblock5.setScale(Vector2f(2.2f, 2.4f));
	InvenWeaponblock5.setPosition(980, 380);

	InvenWeaponZblock6.setTexture(textureSQ);
	InvenWeaponZblock6.setTextureRect(IntRect(79, 1016, 39, 31)); // 채워진 마름모
	InvenWeaponZblock6.setScale(Vector2f(1.0f, 1.0f));
	InvenWeaponZblock6.setPosition(320, 400);

	InvenWeaponXblock7.setTexture(textureSQ); // 채워진 마름모
	InvenWeaponXblock7.setTextureRect(IntRect(79, 1016, 39, 31));
	InvenWeaponXblock7.setScale(Vector2f(1.0f, 1.0f));
	InvenWeaponXblock7.setPosition(320, 450);

	textInvenweapon4.setFont(fontLostRuins);
	textInvenweapon4.setString("Weapon type : One-handed");
	textInvenweapon4.setCharacterSize(25);
	textInvenweapon4.setFillColor(Color::White);
	textInvenweapon4.setPosition(980, 520);

	textInvenweapon5.setFont(fontLostRuins);
	textInvenweapon5.setString("Attack Speed : Middle");
	textInvenweapon5.setCharacterSize(25);
	textInvenweapon5.setFillColor(Color::White);
	textInvenweapon5.setPosition(980, 560);

	textInvenweapon6.setFont(fontLostRuins);
	textInvenweapon6.setString("Damage : Physical 3");
	textInvenweapon6.setCharacterSize(25);
	textInvenweapon6.setFillColor(Color::White);
	textInvenweapon6.setPosition(980, 600);

	textInvenweapon7.setFont(fontLostRuins);
	textInvenweapon7.setString("This is a short one-handed sword chosen ");
	textInvenweapon7.setCharacterSize(25);
	textInvenweapon7.setFillColor(Color::White);
	textInvenweapon7.setPosition(980, 720);

	textInvenweapon8.setFont(fontLostRuins);
	textInvenweapon8.setString("by Lee Min-hyeong,");
	textInvenweapon8.setCharacterSize(25);
	textInvenweapon8.setFillColor(Color::White);
	textInvenweapon8.setPosition(980, 760);

	textInvenweapon9.setFont(fontLostRuins);
	textInvenweapon9.setString("the master of animation production.");
	textInvenweapon9.setCharacterSize(25);
	textInvenweapon9.setFillColor(Color::White);
	textInvenweapon9.setPosition(980, 800);	
}

void TestUi::weaponlist2()
{
	InvenWeaponZblock21.setTexture(textureSQ);
	InvenWeaponZblock21.setTextureRect(IntRect(33, 1016, 39, 31));
	InvenWeaponZblock21.setScale(Vector2f(1.0f, 1.0f));
	InvenWeaponZblock21.setPosition(320, 400);

	textInvenweapon21.setFont(fontLostRuins);
	textInvenweapon21.setString("Gladius");
	textInvenweapon21.setCharacterSize(30);
	textInvenweapon21.setFillColor(Color::Red);
	textInvenweapon21.setPosition(380, 395);

	InvenWeaponXblock22.setTexture(textureSQ);
	InvenWeaponXblock22.setTextureRect(IntRect(33, 1016, 39, 31));
	InvenWeaponXblock22.setScale(Vector2f(1.0f, 1.0f));
	InvenWeaponXblock22.setPosition(320, 450);

	textInvenweapon22.setFont(fontLostRuins);
	textInvenweapon22.setString("Dagger");
	textInvenweapon22.setCharacterSize(30);
	textInvenweapon22.setFillColor(Color::Red);
	textInvenweapon22.setPosition(380, 445);

	textureSQ = TextureHolder::GetTexture("graphics/SQ.png");
	fontLostRuins.loadFromFile("fonts/LiberationSans-Regular.ttf");
	weaponpng = TextureHolder::GetTexture("graphics/Weapon.png");

	InvenWeaponblock23.setTexture(textureSQ);
	InvenWeaponblock23.setTextureRect(IntRect(254, 673, 92, 96));
	InvenWeaponblock23.setScale(Vector2f(1.0f, 1.0f));
	InvenWeaponblock23.setPosition(980, 380);

	textInvenweapon23.setFont(fontLostRuins);
	textInvenweapon23.setString("Dagger");
	textInvenweapon23.setCharacterSize(40);
	textInvenweapon23.setFillColor(Color::Red);
	textInvenweapon23.setPosition(1100, 400);

	InvenWeaponblock24.setTexture(weaponpng);
	InvenWeaponblock24.setTextureRect(IntRect(3, 17, 4, 25));
	InvenWeaponblock24.setScale(Vector2f(2.0f, 2.0f));
	InvenWeaponblock24.setPosition(1025, 405);

	InvenWeaponblock25.setTexture(textureSQ);
	InvenWeaponblock25.setTextureRect(IntRect(62, 605, 42, 40));
	InvenWeaponblock25.setScale(Vector2f(2.2f, 2.4f));
	InvenWeaponblock25.setPosition(980, 380);

	InvenWeaponZblock26.setTexture(textureSQ);
	InvenWeaponZblock26.setTextureRect(IntRect(79, 1016, 39, 31));
	InvenWeaponZblock26.setScale(Vector2f(1.0f, 1.0f));
	InvenWeaponZblock26.setPosition(320, 400);

	InvenWeaponXblock27.setTexture(textureSQ);
	InvenWeaponXblock27.setTextureRect(IntRect(79, 1016, 39, 31));
	InvenWeaponXblock27.setScale(Vector2f(1.0f, 1.0f));
	InvenWeaponXblock27.setPosition(320, 450);

	textInvenweapon24.setFont(fontLostRuins);
	textInvenweapon24.setString("Weapon type : Dagger");
	textInvenweapon24.setCharacterSize(25);
	textInvenweapon24.setFillColor(Color::White);
	textInvenweapon24.setPosition(980, 520);

	textInvenweapon25.setFont(fontLostRuins);
	textInvenweapon25.setString("Attack Speed : Fast");
	textInvenweapon25.setCharacterSize(25);
	textInvenweapon25.setFillColor(Color::White);
	textInvenweapon25.setPosition(980, 560);

	textInvenweapon26.setFont(fontLostRuins);
	textInvenweapon26.setString("Damage : Physical 3");
	textInvenweapon26.setCharacterSize(25);
	textInvenweapon26.setFillColor(Color::White);
	textInvenweapon26.setPosition(980, 600);

	textInvenweapon27.setFont(fontLostRuins);
	textInvenweapon27.setString("This is a short Dagger chosen ");
	textInvenweapon27.setCharacterSize(25);
	textInvenweapon27.setFillColor(Color::White);
	textInvenweapon27.setPosition(980, 720);

	textInvenweapon28.setFont(fontLostRuins);
	textInvenweapon28.setString("by Lee Min-hyeong,");
	textInvenweapon28.setCharacterSize(25);
	textInvenweapon28.setFillColor(Color::White);
	textInvenweapon28.setPosition(980, 760);

	textInvenweapon29.setFont(fontLostRuins);
	textInvenweapon29.setString("the master of animation production.");
	textInvenweapon29.setCharacterSize(25);
	textInvenweapon29.setFillColor(Color::White);
	textInvenweapon29.setPosition(980, 800);
}

void TestUi::scrollList1()
{
	orderNum = 1;
	textureSQ = TextureHolder::GetTexture("graphics/SQ.png");
	fontLostRuins.loadFromFile("fonts/LiberationSans-Regular.ttf");
	scrollpng = TextureHolder::GetTexture("graphics/Scroll.png");

	Orderblankrhombus1.setTexture(textureSQ); //  1. 마름모 빈칸
	Orderblankrhombus1.setTextureRect(IntRect(33, 1016, 39, 31));
	Orderblankrhombus1.setScale(Vector2f(1.0f, 1.0f));
	Orderblankrhombus1.setPosition(320, 400);

	Otextscrollname1.setFont(fontLostRuins); // 1. 리스트 내 아이템 이름
	Otextscrollname1.setString("Fire fist");
	Otextscrollname1.setCharacterSize(30);
	Otextscrollname1.setFillColor(Color::Red);
	Otextscrollname1.setPosition(380, 395);

	Orderblankrhombus2.setTexture(textureSQ); // 2. 마름모 빈칸
	Orderblankrhombus2.setTextureRect(IntRect(33, 1016, 39, 31));
	Orderblankrhombus2.setScale(Vector2f(1.0f, 1.0f));
	Orderblankrhombus2.setPosition(320, 450);

	Otextscrollname2.setFont(fontLostRuins); // 2. 리스트 내 아이템 이름
	Otextscrollname2.setString("Ice pick");
	Otextscrollname2.setCharacterSize(30);
	Otextscrollname2.setFillColor(Color::Red);
	Otextscrollname2.setPosition(380, 445);

	Orderfullrhombus1.setTexture(textureSQ);
	Orderfullrhombus1.setTextureRect(IntRect(79, 1016, 39, 31)); // 1-1. 채워진 마름모
	Orderfullrhombus1.setScale(Vector2f(1.0f, 1.0f));
	Orderfullrhombus1.setPosition(320, 400);

	Orderfullrhombus2.setTexture(textureSQ); // 1-2. 채워진 마름모
	Orderfullrhombus2.setTextureRect(IntRect(79, 1016, 39, 31));
	Orderfullrhombus2.setScale(Vector2f(1.0f, 1.0f));
	Orderfullrhombus2.setPosition(320, 450);

	///////////////////////////////////////////////////////////////

	orderitemphotoframe1.setTexture(textureSQ); // 1. 우측 아이템 네모칸
	orderitemphotoframe1.setTextureRect(IntRect(254, 673, 92, 96));
	orderitemphotoframe1.setScale(Vector2f(1.0f, 1.0f));
	orderitemphotoframe1.setPosition(980, 380);

	OtextItemnamefield1.setFont(fontLostRuins); // 1. 우측 아이템 이름
	OtextItemnamefield1.setString("Fire fist");
	OtextItemnamefield1.setCharacterSize(40);
	OtextItemnamefield1.setFillColor(Color::Red);
	OtextItemnamefield1.setPosition(1100, 400);

	OdescriptionImage1.setTexture(scrollpng); // 1. 우측 아이템 이미지
	OdescriptionImage1.setTextureRect(IntRect(3, 131, 20, 22));
	OdescriptionImage1.setScale(Vector2f(1.1f, 1.0f));
	OdescriptionImage1.setPosition(1020, 400);

	Oitembackground1.setTexture(textureSQ); // 1. 우측 아이템 이미지 뒷배경
	Oitembackground1.setTextureRect(IntRect(62, 605, 42, 40));
	Oitembackground1.setScale(Vector2f(2.2f, 2.4f));
	Oitembackground1.setPosition(980, 380);	

	Omagictype1.setFont(fontLostRuins); // 1. 마법 타입
	Omagictype1.setString("Weapon type : Fire magic");
	Omagictype1.setCharacterSize(25);
	Omagictype1.setFillColor(Color::White);
	Omagictype1.setPosition(980, 520);

	Oattackspeed1.setFont(fontLostRuins); // 1. 공격속도
	Oattackspeed1.setString("Attack Speed : Ranged magic");
	Oattackspeed1.setCharacterSize(25);
	Oattackspeed1.setFillColor(Color::White);
	Oattackspeed1.setPosition(980, 560);

	ODamage1.setFont(fontLostRuins); // 1. 데미지
	ODamage1.setString("Damage : Physical 3");
	ODamage1.setCharacterSize(25);
	ODamage1.setFillColor(Color::White);
	ODamage1.setPosition(980, 600);

	OItemDescription1.setFont(fontLostRuins); // 1. 아이템 설명 텍스트
	OItemDescription1.setString("This magic was created by a fiery artisan");
	OItemDescription1.setCharacterSize(25);
	OItemDescription1.setFillColor(Color::White);
	OItemDescription1.setPosition(980, 720);

	OItemDescription2.setFont(fontLostRuins); // 1. 아이템 설명 텍스트
	OItemDescription2.setString("Lee Min-hyeong,");
	OItemDescription2.setCharacterSize(25);
	OItemDescription2.setFillColor(Color::White);
	OItemDescription2.setPosition(980, 760);

	OItemDescription3.setFont(fontLostRuins); // 1. 아이템 설명 텍스트
	OItemDescription3.setString("who puts his soul into animation.");
	OItemDescription3.setCharacterSize(25);
	OItemDescription3.setFillColor(Color::White);
	OItemDescription3.setPosition(980, 800);
}

void TestUi::scrollList2()
{
	textureSQ = TextureHolder::GetTexture("graphics/SQ.png");
	fontLostRuins.loadFromFile("fonts/LiberationSans-Regular.ttf");
	scrollpng = TextureHolder::GetTexture("graphics/Scroll.png");

	Orderblankrhombus1.setTexture(textureSQ); //  1. 마름모 빈칸
	Orderblankrhombus1.setTextureRect(IntRect(33, 1016, 39, 31));
	Orderblankrhombus1.setScale(Vector2f(1.0f, 1.0f));
	Orderblankrhombus1.setPosition(320, 400);

	Otextscrollname1.setFont(fontLostRuins); // 1. 리스트 내 아이템 이름
	Otextscrollname1.setString("Fire fist");
	Otextscrollname1.setCharacterSize(30);
	Otextscrollname1.setFillColor(Color::Red);
	Otextscrollname1.setPosition(380, 395);

	Orderblankrhombus2.setTexture(textureSQ); // 2. 마름모 빈칸
	Orderblankrhombus2.setTextureRect(IntRect(33, 1016, 39, 31));
	Orderblankrhombus2.setScale(Vector2f(1.0f, 1.0f));
	Orderblankrhombus2.setPosition(320, 450);

	Otextscrollname2.setFont(fontLostRuins); // 2. 리스트 내 아이템 이름
	Otextscrollname2.setString("Ice pick");
	Otextscrollname2.setCharacterSize(30);
	Otextscrollname2.setFillColor(Color::Red);
	Otextscrollname2.setPosition(380, 445);

	Orderfullrhombus3.setTexture(textureSQ);
	Orderfullrhombus3.setTextureRect(IntRect(79, 1016, 39, 31)); // 1. 채워진 마름모
	Orderfullrhombus3.setScale(Vector2f(1.0f, 1.0f));
	Orderfullrhombus3.setPosition(320, 400);

	Orderfullrhombus4.setTexture(textureSQ); // 2. 채워진 마름모
	Orderfullrhombus4.setTextureRect(IntRect(79, 1016, 39, 31));
	Orderfullrhombus4.setScale(Vector2f(1.0f, 1.0f));
	Orderfullrhombus4.setPosition(320, 450);


	///////////////////////////////////////////////////////////////

	orderitemphotoframe2.setTexture(textureSQ); // 2. 우측 아이템 네모칸
	orderitemphotoframe2.setTextureRect(IntRect(254, 673, 92, 96));
	orderitemphotoframe2.setScale(Vector2f(1.0f, 1.0f));
	orderitemphotoframe2.setPosition(980, 380);

	OtextItemnamefield2.setFont(fontLostRuins); // 2. 우측 아이템 이름
	OtextItemnamefield2.setString("Fire fist");
	OtextItemnamefield2.setCharacterSize(40);
	OtextItemnamefield2.setFillColor(Color::Red);
	OtextItemnamefield2.setPosition(1100, 400);

	OdescriptionImage2.setTexture(scrollpng); // 2. 우측 아이템 이미지
	OdescriptionImage2.setTextureRect(IntRect(103, 131, 20, 22));
	OdescriptionImage2.setScale(Vector2f(1.1f, 1.0f));
	OdescriptionImage2.setPosition(1020, 400);

	Oitembackground2.setTexture(textureSQ); // 2. 우측 아이템 이미지 뒷배경
	Oitembackground2.setTextureRect(IntRect(62, 605, 42, 40));
	Oitembackground2.setScale(Vector2f(2.2f, 2.4f));
	Oitembackground2.setPosition(980, 380);

	Omagictype2.setFont(fontLostRuins); // 2. 마법 타입
	Omagictype2.setString("Weapon type : Fire magic");
	Omagictype2.setCharacterSize(25);
	Omagictype2.setFillColor(Color::White);
	Omagictype2.setPosition(980, 520);

	Oattackspeed2.setFont(fontLostRuins); // 2. 공격속도
	Oattackspeed2.setString("Attack Speed : Ranged magic");
	Oattackspeed2.setCharacterSize(25);
	Oattackspeed2.setFillColor(Color::White);
	Oattackspeed2.setPosition(980, 560);

	ODamage2.setFont(fontLostRuins); // 1. 데미지
	ODamage2.setString("Damage : Physical 3");
	ODamage2.setCharacterSize(25);
	ODamage2.setFillColor(Color::White);
	ODamage2.setPosition(980, 600);

	OItemDescription01.setFont(fontLostRuins); // 1. 아이템 설명 텍스트
	OItemDescription01.setString("This magic was created out of the coolness of");
	OItemDescription01.setCharacterSize(25);
	OItemDescription01.setFillColor(Color::White);
	OItemDescription01.setPosition(980, 720);

	OItemDescription02.setFont(fontLostRuins); // 1. 아이템 설명 텍스트
	OItemDescription02.setString("animation director Lee Min-hyung,");
	OItemDescription02.setCharacterSize(25);
	OItemDescription02.setFillColor(Color::White);
	OItemDescription02.setPosition(980, 760);

	OItemDescription03.setFont(fontLostRuins); // 1. 아이템 설명 텍스트
	OItemDescription03.setString("who only gave his teammates a job");
	OItemDescription03.setCharacterSize(25);
	OItemDescription03.setFillColor(Color::White);
	OItemDescription03.setPosition(980, 800);

	OItemDescription04.setFont(fontLostRuins); // 1. 아이템 설명 텍스트
	OItemDescription04.setString("without giving them carrots.");
	OItemDescription04.setCharacterSize(25);
	OItemDescription04.setFillColor(Color::White);
	OItemDescription04.setPosition(980, 840);
}

void TestUi::Supplies()
{
	textureSQ = TextureHolder::GetTexture("graphics/SQ.png");
	fontLostRuins.loadFromFile("fonts/LiberationSans-Regular.ttf");	

	Suppliesblankrhombus1.setTexture(textureSQ); //  1. 마름모 빈칸
	Suppliesblankrhombus1.setTextureRect(IntRect(33, 1016, 39, 31));
	Suppliesblankrhombus1.setScale(Vector2f(1.0f, 1.0f));
	Suppliesblankrhombus1.setPosition(320, 400);

	Suppliestextscrollname1.setFont(fontLostRuins); // 1. 리스트 내 아이템 이름
	Suppliestextscrollname1.setString("one chicken");
	Suppliestextscrollname1.setCharacterSize(30);
	Suppliestextscrollname1.setFillColor(Color::Red);
	Suppliestextscrollname1.setPosition(380, 395);
	
	Suppliesrderfullrhombus1.setTexture(textureSQ);
	Suppliesrderfullrhombus1.setTextureRect(IntRect(79, 1016, 39, 31)); // 1-1. 채워진 마름모
	Suppliesrderfullrhombus1.setScale(Vector2f(1.0f, 1.0f));
	Suppliesrderfullrhombus1.setPosition(320, 400);

	Suppliesitemphotoframe1.setTexture(textureSQ); // 1. 우측 아이템 네모칸
	Suppliesitemphotoframe1.setTextureRect(IntRect(254, 673, 92, 96));
	Suppliesitemphotoframe1.setScale(Vector2f(1.0f, 1.0f));
	Suppliesitemphotoframe1.setPosition(980, 380);

	SuppliestextItemnamefield1.setFont(fontLostRuins); // 1. 우측 아이템 이름
	SuppliestextItemnamefield1.setString("Picture of chicken");
	SuppliestextItemnamefield1.setCharacterSize(40);
	SuppliestextItemnamefield1.setFillColor(Color::Red);
	SuppliestextItemnamefield1.setPosition(1100, 400);

	SuppliesdescriptionImage1.setTexture(textureSQ); // 1. 우측 아이템 이미지
	SuppliesdescriptionImage1.setTextureRect(IntRect(314, 478, 52, 26));
	SuppliesdescriptionImage1.setScale(Vector2f(1.1f, 1.0f));
	SuppliesdescriptionImage1.setPosition(1020, 400);

	Suppliesitembackground1.setTexture(textureSQ); // 1. 우측 아이템 이미지 뒷배경
	Suppliesitembackground1.setTextureRect(IntRect(62, 605, 42, 40));
	Suppliesitembackground1.setScale(Vector2f(2.2f, 2.4f));
	Suppliesitembackground1.setPosition(980, 380);

	Suppliesmagictype1.setFont(fontLostRuins); // 1. 음식 타입
	Suppliesmagictype1.setString("Food type : Chicken with eyes only");
	Suppliesmagictype1.setCharacterSize(25);
	Suppliesmagictype1.setFillColor(Color::White);
	Suppliesmagictype1.setPosition(980, 520);

	Suppliesattackspeed1.setFont(fontLostRuins); // 1. 효과
	Suppliesattackspeed1.setString("Effect : Just looking at it makes me hungry.");
	Suppliesattackspeed1.setCharacterSize(25);
	Suppliesattackspeed1.setFillColor(Color::White);
	Suppliesattackspeed1.setPosition(980, 560);

	SuppliesDamage1.setFont(fontLostRuins); // 1. 데미지
	SuppliesDamage1.setString("Damage : Physical 0");
	SuppliesDamage1.setCharacterSize(25);
	SuppliesDamage1.setFillColor(Color::White);
	SuppliesDamage1.setPosition(980, 600);

	SuppliesItemDescription1.setFont(fontLostRuins); // 1. 아이템 설명 텍스트
	SuppliesItemDescription1.setString("A chicken image created");
	SuppliesItemDescription1.setCharacterSize(25);
	SuppliesItemDescription1.setFillColor(Color::White);
	SuppliesItemDescription1.setPosition(980, 720);

	SuppliesItemDescription2.setFont(fontLostRuins); // 1. 아이템 설명 텍스트
	SuppliesItemDescription2.setString("by UI creator Lee Ji-woo");
	SuppliesItemDescription2.setCharacterSize(25);
	SuppliesItemDescription2.setFillColor(Color::White);
	SuppliesItemDescription2.setPosition(980, 760);

	SuppliesItemDescription3.setFont(fontLostRuins); // 1. 아이템 설명 텍스트
	SuppliesItemDescription3.setString("because he was hungry.");
	SuppliesItemDescription3.setCharacterSize(25);
	SuppliesItemDescription3.setFillColor(Color::White);
	SuppliesItemDescription3.setPosition(980, 800);
}

void TestUi::EquipList1()
{
	EquipmentNum = 1;
	textureSQ = TextureHolder::GetTexture("graphics/SQ.png");
	fontLostRuins.loadFromFile("fonts/LiberationSans-Regular.ttf");
	scrollpng = TextureHolder::GetTexture("graphics/Scroll.png");

	Equipblankrhombus1.setTexture(textureSQ); //  1. 마름모 빈칸
	Equipblankrhombus1.setTextureRect(IntRect(33, 1016, 39, 31));
	Equipblankrhombus1.setScale(Vector2f(1.0f, 1.0f));
	Equipblankrhombus1.setPosition(320, 400);

	Equiptextscrollname1.setFont(fontLostRuins); // 1. 리스트 내 아이템 이름
	Equiptextscrollname1.setString("Red necklace of harmony");
	Equiptextscrollname1.setCharacterSize(30);
	Equiptextscrollname1.setFillColor(Color::Red);
	Equiptextscrollname1.setPosition(380, 395);

	Equipblankrhombus2.setTexture(textureSQ); // 2. 마름모 빈칸
	Equipblankrhombus2.setTextureRect(IntRect(33, 1016, 39, 31));
	Equipblankrhombus2.setScale(Vector2f(1.0f, 1.0f));
	Equipblankrhombus2.setPosition(320, 450);

	Equiptextscrollname2.setFont(fontLostRuins); // 2. 리스트 내 아이템 이름
	Equiptextscrollname2.setString("Blue necklace of harmony");
	Equiptextscrollname2.setCharacterSize(30);
	Equiptextscrollname2.setFillColor(Color::Red);
	Equiptextscrollname2.setPosition(380, 445);

	Equiprderfullrhombus1.setTexture(textureSQ);
	Equiprderfullrhombus1.setTextureRect(IntRect(79, 1016, 39, 31)); // 1-1. 채워진 마름모
	Equiprderfullrhombus1.setScale(Vector2f(1.0f, 1.0f));
	Equiprderfullrhombus1.setPosition(320, 400);

	Equiprderfullrhombus2.setTexture(textureSQ); // 1-2. 채워진 마름모
	Equiprderfullrhombus2.setTextureRect(IntRect(79, 1016, 39, 31));
	Equiprderfullrhombus2.setScale(Vector2f(1.0f, 1.0f));
	Equiprderfullrhombus2.setPosition(320, 450);

	///////////////////////////////////////////////////////////////

	Equipitemphotoframe1.setTexture(textureSQ); // 1. 우측 아이템 네모칸
	Equipitemphotoframe1.setTextureRect(IntRect(254, 673, 92, 96));
	Equipitemphotoframe1.setScale(Vector2f(1.0f, 1.0f));
	Equipitemphotoframe1.setPosition(980, 380);

	EquiptextItemnamefield1.setFont(fontLostRuins); // 1. 우측 아이템 이름
	EquiptextItemnamefield1.setString("Red necklace of harmony");
	EquiptextItemnamefield1.setCharacterSize(40);
	EquiptextItemnamefield1.setFillColor(Color::Red);
	EquiptextItemnamefield1.setPosition(1100, 400);

	EquipdescriptionImage1.setTexture(scrollpng); // 1. 우측 아이템 이미지
	EquipdescriptionImage1.setTextureRect(IntRect(3, 226, 12, 15));
	EquipdescriptionImage1.setScale(Vector2f(2.5f, 2.5f));
	EquipdescriptionImage1.setPosition(1020, 400);

	Equipitembackground1.setTexture(textureSQ); // 1. 우측 아이템 이미지 뒷배경
	Equipitembackground1.setTextureRect(IntRect(62, 605, 42, 40));
	Equipitembackground1.setScale(Vector2f(2.2f, 2.4f));
	Equipitembackground1.setPosition(980, 380);

	Equipmagictype1.setFont(fontLostRuins); // 1. 장비 타입
	Equipmagictype1.setString("Equipment type : necklace");
	Equipmagictype1.setCharacterSize(25);
	Equipmagictype1.setFillColor(Color::White);
	Equipmagictype1.setPosition(980, 520);

	Equipattackspeed1.setFont(fontLostRuins); // 1. 아이템 희귀도
	Equipattackspeed1.setString("Equipment rare : unique");
	Equipattackspeed1.setCharacterSize(25);
	Equipattackspeed1.setFillColor(Color::White);
	Equipattackspeed1.setPosition(980, 560);

	EquipDamage1.setFont(fontLostRuins); // 1. 효과
	EquipDamage1.setString("Effect : A red necklace is displayed on the screen.");
	EquipDamage1.setCharacterSize(25);
	EquipDamage1.setFillColor(Color::White);
	EquipDamage1.setPosition(980, 600);

	EquipItemDescription1.setFont(fontLostRuins); // 1. 아이템 설명 텍스트
	EquipItemDescription1.setString("This necklace is modeled after the");
	EquipItemDescription1.setCharacterSize(25);
	EquipItemDescription1.setFillColor(Color::White);
	EquipItemDescription1.setPosition(980, 720);

	EquipItemDescription2.setFont(fontLostRuins); // 1. 아이템 설명 텍스트
	EquipItemDescription2.setString("central red part of the Taegeukgi.");
	EquipItemDescription2.setCharacterSize(25);
	EquipItemDescription2.setFillColor(Color::White);
	EquipItemDescription2.setPosition(980, 760);

	EquipItemDescription3.setFont(fontLostRuins); // 1. 아이템 설명 텍스트
	EquipItemDescription3.setString("Detailed instructions are on the blue necklace.");
	EquipItemDescription3.setCharacterSize(25);
	EquipItemDescription3.setFillColor(Color::White);
	EquipItemDescription3.setPosition(980, 800);
}

void TestUi::EquipList2()
{
	textureSQ = TextureHolder::GetTexture("graphics/SQ.png");
	fontLostRuins.loadFromFile("fonts/LiberationSans-Regular.ttf");
	scrollpng = TextureHolder::GetTexture("graphics/Scroll.png");

	Equipblankrhombus1.setTexture(textureSQ); //  1. 마름모 빈칸
	Equipblankrhombus1.setTextureRect(IntRect(33, 1016, 39, 31));
	Equipblankrhombus1.setScale(Vector2f(1.0f, 1.0f));
	Equipblankrhombus1.setPosition(320, 400);

	Equiptextscrollname1.setFont(fontLostRuins); // 1. 리스트 내 아이템 이름
	Equiptextscrollname1.setString("Red necklace of harmony");
	Equiptextscrollname1.setCharacterSize(30);
	Equiptextscrollname1.setFillColor(Color::Red);
	Equiptextscrollname1.setPosition(380, 395);

	Equipblankrhombus2.setTexture(textureSQ); // 2. 마름모 빈칸
	Equipblankrhombus2.setTextureRect(IntRect(33, 1016, 39, 31));
	Equipblankrhombus2.setScale(Vector2f(1.0f, 1.0f));
	Equipblankrhombus2.setPosition(320, 450);

	Equiptextscrollname2.setFont(fontLostRuins); // 2. 리스트 내 아이템 이름
	Equiptextscrollname2.setString("Blue necklace of harmony");
	Equiptextscrollname2.setCharacterSize(30);
	Equiptextscrollname2.setFillColor(Color::Red);
	Equiptextscrollname2.setPosition(380, 445);

	Equiprderfullrhombus3.setTexture(textureSQ);
	Equiprderfullrhombus3.setTextureRect(IntRect(79, 1016, 39, 31)); // 2-1. 채워진 마름모
	Equiprderfullrhombus3.setScale(Vector2f(1.0f, 1.0f));
	Equiprderfullrhombus3.setPosition(320, 400);

	Equiprderfullrhombus4.setTexture(textureSQ); // 2-2. 채워진 마름모
	Equiprderfullrhombus4.setTextureRect(IntRect(79, 1016, 39, 31));
	Equiprderfullrhombus4.setScale(Vector2f(1.0f, 1.0f));
	Equiprderfullrhombus4.setPosition(320, 450);


	///////////////////////////////////////////////////////////////


	Equipitemphotoframe2.setTexture(textureSQ); // 2. 우측 아이템 네모칸
	Equipitemphotoframe2.setTextureRect(IntRect(254, 673, 92, 96));
	Equipitemphotoframe2.setScale(Vector2f(1.0f, 1.0f));
	Equipitemphotoframe2.setPosition(980, 380);

	EquiptextItemnamefield2.setFont(fontLostRuins); // 2. 우측 아이템 이름
	EquiptextItemnamefield2.setString("Blue necklace of harmony");
	EquiptextItemnamefield2.setCharacterSize(40);
	EquiptextItemnamefield2.setFillColor(Color::Red);
	EquiptextItemnamefield2.setPosition(1100, 400);

	EquipdescriptionImage2.setTexture(scrollpng); // 2. 우측 아이템 이미지
	EquipdescriptionImage2.setTextureRect(IntRect(20, 226, 11, 14));
	EquipdescriptionImage2.setScale(Vector2f(2.5f, 2.5f));
	EquipdescriptionImage2.setPosition(1020, 400);

	Equipitembackground2.setTexture(textureSQ); // 2. 우측 아이템 이미지 뒷배경
	Equipitembackground2.setTextureRect(IntRect(62, 605, 42, 40));
	Equipitembackground2.setScale(Vector2f(2.2f, 2.4f));
	Equipitembackground2.setPosition(980, 380);

	Equipmagictype2.setFont(fontLostRuins); // 2. 장비 타입
	Equipmagictype2.setString("Equipment type : necklace");
	Equipmagictype2.setCharacterSize(25);
	Equipmagictype2.setFillColor(Color::White);
	Equipmagictype2.setPosition(980, 520);

	Equipattackspeed2.setFont(fontLostRuins); // 2. 아이템 희귀도
	Equipattackspeed2.setString("Equipment rare : unique");
	Equipattackspeed2.setCharacterSize(25);
	Equipattackspeed2.setFillColor(Color::White);
	Equipattackspeed2.setPosition(980, 560);

	EquipDamage2.setFont(fontLostRuins); // 1. 효과
	EquipDamage2.setString("Effect : A red necklace is displayed on the screen.");
	EquipDamage2.setCharacterSize(25);
	EquipDamage2.setFillColor(Color::White);
	EquipDamage2.setPosition(980, 600);

	EquipItemDescription01.setFont(fontLostRuins); // 1. 아이템 설명 텍스트
	EquipItemDescription01.setString("A necklace set created by team leader");
	EquipItemDescription01.setCharacterSize(25);
	EquipItemDescription01.setFillColor(Color::White);
	EquipItemDescription01.setPosition(980, 720);

	EquipItemDescription02.setFont(fontLostRuins); // 1. 아이템 설명 텍스트
	EquipItemDescription02.setString("Jeong-hoon Kim, who made the UI maker");
	EquipItemDescription02.setCharacterSize(25);
	EquipItemDescription02.setFillColor(Color::White);
	EquipItemDescription02.setPosition(980, 760);

	EquipItemDescription03.setFont(fontLostRuins); // 1. 아이템 설명 텍스트
	EquipItemDescription03.setString("with the desire to lead the team harmoniously. ");
	EquipItemDescription03.setCharacterSize(25);
	EquipItemDescription03.setFillColor(Color::White);
	EquipItemDescription03.setPosition(980, 800);

	EquipItemDescription04.setFont(fontLostRuins); // 1. 아이템 설명 텍스트
	EquipItemDescription04.setString("UI creators have escaped.");
	EquipItemDescription04.setCharacterSize(25);
	EquipItemDescription04.setFillColor(Color::White);
	EquipItemDescription04.setPosition(980, 840);
}

void TestUi::relics()
{
	textureSQ = TextureHolder::GetTexture("graphics/SQ.png");
	fontLostRuins.loadFromFile("fonts/LiberationSans-Regular.ttf");
	scrollpng = TextureHolder::GetTexture("graphics/Scroll.png");

	Relicblankrhombus1.setTexture(textureSQ); //  1. 마름모 빈칸
	Relicblankrhombus1.setTextureRect(IntRect(33, 1016, 39, 31));
	Relicblankrhombus1.setScale(Vector2f(1.0f, 1.0f));
	Relicblankrhombus1.setPosition(320, 400);

	Relictextscrollname1.setFont(fontLostRuins); // 1. 리스트 내 아이템 이름
	Relictextscrollname1.setString("one chicken");
	Relictextscrollname1.setCharacterSize(30);
	Relictextscrollname1.setFillColor(Color::Red);
	Relictextscrollname1.setPosition(380, 395);

	Relicrderfullrhombus1.setTexture(textureSQ);
	Relicrderfullrhombus1.setTextureRect(IntRect(79, 1016, 39, 31)); // 1-1. 채워진 마름모
	Relicrderfullrhombus1.setScale(Vector2f(1.0f, 1.0f));
	Relicrderfullrhombus1.setPosition(320, 400);

	Relicitemphotoframe1.setTexture(textureSQ); // 1. 우측 아이템 네모칸
	Relicitemphotoframe1.setTextureRect(IntRect(254, 673, 92, 96));
	Relicitemphotoframe1.setScale(Vector2f(1.0f, 1.0f));
	Relicitemphotoframe1.setPosition(980, 380);

	RelictextItemnamefield1.setFont(fontLostRuins); // 1. 우측 아이템 이름
	RelictextItemnamefield1.setString("Picture of chicken");
	RelictextItemnamefield1.setCharacterSize(40);
	RelictextItemnamefield1.setFillColor(Color::Red);
	RelictextItemnamefield1.setPosition(1100, 400);

	RelicdescriptionImage1.setTexture(scrollpng); // 1. 우측 아이템 이미지
	RelicdescriptionImage1.setTextureRect(IntRect(3, 62, 26, 23));
	RelicdescriptionImage1.setScale(Vector2f(1.1f, 1.0f));
	RelicdescriptionImage1.setPosition(1020, 400);

	Relicitembackground1.setTexture(textureSQ); // 1. 우측 아이템 이미지 뒷배경
	Relicitembackground1.setTextureRect(IntRect(62, 605, 42, 40));
	Relicitembackground1.setScale(Vector2f(2.2f, 2.4f));
	Relicitembackground1.setPosition(980, 380);

	Relicmagictype1.setFont(fontLostRuins); // 1. 유물 타입
	Relicmagictype1.setString("Relic type : Chicken with eyes only");
	Relicmagictype1.setCharacterSize(25);
	Relicmagictype1.setFillColor(Color::White);
	Relicmagictype1.setPosition(980, 520);

	Relicattackspeed1.setFont(fontLostRuins); // 1. 아이템 희귀도
	Relicattackspeed1.setString("Item rare : Relic");
	Relicattackspeed1.setCharacterSize(25);
	Relicattackspeed1.setFillColor(Color::White);
	Relicattackspeed1.setPosition(980, 560);

	RelicDamage1.setFont(fontLostRuins); // 1. 효과
	RelicDamage1.setString("Effect : If you have it, you have to code it.");
	RelicDamage1.setCharacterSize(25);
	RelicDamage1.setFillColor(Color::White);
	RelicDamage1.setPosition(980, 600);

	RelicItemDescription1.setFont(fontLostRuins); // 1. 아이템 설명 텍스트
	RelicItemDescription1.setString("It's a relic that UI creators had a hard time making.");
	RelicItemDescription1.setCharacterSize(25);
	RelicItemDescription1.setFillColor(Color::White);
	RelicItemDescription1.setPosition(980, 720);

	RelicItemDescription2.setFont(fontLostRuins); // 1. 아이템 설명 텍스트
	RelicItemDescription2.setString("There is a longing to go home,");
	RelicItemDescription2.setCharacterSize(25);
	RelicItemDescription2.setFillColor(Color::White);
	RelicItemDescription2.setPosition(980, 760);

	RelicItemDescription3.setFont(fontLostRuins); // 1. 아이템 설명 텍스트
	RelicItemDescription3.setString("actually got off work.");
	RelicItemDescription3.setCharacterSize(25);
	RelicItemDescription3.setFillColor(Color::White);
	RelicItemDescription3.setPosition(980, 800);
}

bool TestUi::GetEscMenu()
{
	return Escmenu;
}

void TestUi::EscSetting()
{
	settingNum = 1;
	masterNum = 1;
	uiNum = 1;
	sfxNum = 1;
	musicNum = 1;

	texturesetting = TextureHolder::GetTexture("graphics/setting.png");
	setBlur1 = TextureHolder::GetTexture("graphics/esc.png");
	settingLan.loadFromFile("fonts/LiberationSans-Bold.ttf");
	textureSQ = TextureHolder::GetTexture("graphics/SQ.png");
	fontLostRuins.loadFromFile("fonts/LiberationSans-Regular.ttf");
	textureUI = TextureHolder::GetTexture("graphics/UI.png");

	settingCS.setTexture(textureUI); // Setting 상하 커서
	settingCS.setTextureRect(IntRect(139, 1369, 70, 68));
	settingCS.setScale(Vector2f(0.5f, 0.5f));
	settingCS.setPosition(642, 175);

	setBlur.setTexture(setBlur1); // 설정 배경
	setBlur.setTextureRect(IntRect(39, 2385, 1339, 887));
	setBlur.setScale(Vector2f(0.709f, 2.0f));
	setBlur.setPosition(480, 0); //280, 280

	spriteset1.setTexture(texturesetting); //설정 기둥 1
	spriteset1.setTextureRect(IntRect(1125, 55, 9, 769));
	spriteset1.setScale(Vector2f(1.0f, 2.0f));
	spriteset1.setPosition(475, 0);

	spriteset2.setTexture(texturesetting); //설정 기둥 2
	spriteset2.setTextureRect(IntRect(1125, 55, 9, 769));
	spriteset2.setScale(Vector2f(1.0f, 2.0f));
	spriteset2.setPosition(1425, 0);

	SettingSet.setTexture(textureSQ); // ESC -> Setting 이름
	SettingSet.setTextureRect(IntRect(1021, 638, 346, 115));
	SettingSet.setScale(Vector2f(0.6f, 0.7f));
	SettingSet.setPosition(760, 10);
	Setname.setFont(settingLan);
	Setname.setString("Settings");
	Setname.setCharacterSize(30);
	Setname.setFillColor(Color::Green);
	Setname.setPosition(805, 30);


	SettingKey.setTexture(textureSQ); // ESC -> Keybord 이름
	SettingKey.setTextureRect(IntRect(1021, 638, 346, 115));
	SettingKey.setScale(Vector2f(0.6f, 0.7f));
	SettingKey.setPosition(980, 10);
	Keyname.setFont(settingLan);
	Keyname.setString("Keyboard");
	Keyname.setCharacterSize(30);
	Keyname.setFillColor(Color::White);
	Keyname.setPosition(1015, 30);


	SettingBtQ.setTexture(textureUI); // ESC -> Setting -> 버튼Q
	SettingBtQ.setTextureRect(IntRect(62, 605, 42, 40));
	SettingBtQ.setPosition(710, 50);
	SetBtQ.setFont(fontLostRuins);
	SetBtQ.setString("Q");
	SetBtQ.setCharacterSize(20);
	SetBtQ.setFillColor(Color::White);
	SetBtQ.setPosition(722, 56);


	SettingBtW.setTexture(textureUI); // ESC -> Setting -> 버튼W
	SettingBtW.setTextureRect(IntRect(62, 605, 42, 40));
	SettingBtW.setPosition(1195, 50);
	SetBtW.setFont(fontLostRuins);
	SetBtW.setString("W");
	SetBtW.setCharacterSize(20);
	SetBtW.setFillColor(Color::White);
	SetBtW.setPosition(1207, 58);

	/////////////////////////////////// Esc -> Setting -> Language

	textLanguage.setFont(settingLan);
	textLanguage.setString("Language");
	textLanguage.setCharacterSize(30);
	textLanguage.setFillColor(Color::White);
	textLanguage.setPosition(682, 178);

	LanCSL.setTexture(textureSQ);
	LanCSL.setTextureRect(IntRect(187, 1573, 21, 16));
	LanCSL.setScale(Vector2f(1.5f, 1.5f));
	LanCSL.setPosition(980, 190);

	English.setFont(settingLan);
	English.setString("English");
	English.setCharacterSize(30);
	English.setFillColor(Color::White);
	English.setPosition(1110, 182);

	LanCSR.setTexture(textureSQ);
	LanCSR.setTextureRect(IntRect(212, 1573, 21, 16));
	LanCSR.setScale(Vector2f(1.5f, 1.5f));
	LanCSR.setPosition(1300, 190);

	/////////////////////////////////// Esc -> Setting -> Resolution

	textResolution.setFont(settingLan);
	textResolution.setString("Resolution");
	textResolution.setCharacterSize(30);
	textResolution.setFillColor(Color::White);
	textResolution.setPosition(682, 258); // 80

	ResCSL.setTexture(textureSQ);
	ResCSL.setTextureRect(IntRect(187, 1573, 21, 16));
	ResCSL.setScale(Vector2f(1.5f, 1.5f));
	ResCSL.setPosition(980, 270);

	screensize.setFont(settingLan);
	screensize.setString("1920x1080");
	screensize.setCharacterSize(30);
	screensize.setFillColor(Color::White);
	screensize.setPosition(1090, 262);

	ResCSR.setTexture(textureSQ);
	ResCSR.setTextureRect(IntRect(212, 1573, 21, 16));
	ResCSR.setScale(Vector2f(1.5f, 1.5f));
	ResCSR.setPosition(1300, 270);



	/////////////////////////////////// Esc -> Setting -> Full Screen

	textFullScreen.setFont(settingLan);
	textFullScreen.setString("Full Screen");
	textFullScreen.setCharacterSize(30);
	textFullScreen.setFillColor(Color::White);
	textFullScreen.setPosition(682, 338); //80

	FullCS.setTexture(textureSQ);
	FullCS.setTextureRect(IntRect(125, 1017, 31, 23));
	FullCS.setScale(Vector2f(1.5f, 1.5f));
	FullCS.setPosition(1145, 342);

	/////////////////////////////////// Esc -> Setting -> Vsync

	textVsync.setFont(settingLan);
	textVsync.setString("Vsync");
	textVsync.setCharacterSize(30);
	textVsync.setFillColor(Color::White);
	textVsync.setPosition(682, 418);

	VsyCS.setTexture(textureSQ);
	VsyCS.setTextureRect(IntRect(125, 1017, 31, 23));
	VsyCS.setScale(Vector2f(1.5f, 1.5f));
	VsyCS.setPosition(1145, 422);

	/////////////////////////////////// Esc -> Setting -> Render Mode

	textRenderMode.setFont(settingLan);
	textRenderMode.setString("Render Mode");
	textRenderMode.setCharacterSize(30);
	textRenderMode.setFillColor(Color::White);
	textRenderMode.setPosition(682, 498);

	RenCSL.setTexture(textureSQ);
	RenCSL.setTextureRect(IntRect(187, 1573, 21, 16));
	RenCSL.setScale(Vector2f(1.5f, 1.5f));
	RenCSL.setPosition(980, 510);

	ModeFull.setFont(settingLan);
	ModeFull.setString("Full");
	ModeFull.setCharacterSize(30);
	ModeFull.setFillColor(Color::White);
	ModeFull.setPosition(1138, 502);

	RenCSR.setTexture(textureSQ);
	RenCSR.setTextureRect(IntRect(212, 1573, 21, 16));
	RenCSR.setScale(Vector2f(1.5f, 1.5f));
	RenCSR.setPosition(1300, 510);

	/////////////////////////////////// Esc -> Setting -> Battle Log

	textBattleLog.setFont(settingLan);
	textBattleLog.setString("Battle Log");
	textBattleLog.setCharacterSize(30);
	textBattleLog.setFillColor(Color::White);
	textBattleLog.setPosition(682, 578);

	BattleCS.setTexture(textureSQ);
	BattleCS.setTextureRect(IntRect(125, 1017, 31, 23));
	BattleCS.setScale(Vector2f(1.5f, 1.5f));
	BattleCS.setPosition(1145, 582);

	/////////////////////////////////// Esc -> Setting -> Master Volume

	textMasterVolume.setFont(settingLan);
	textMasterVolume.setString("Master Volume");
	textMasterVolume.setCharacterSize(30);
	textMasterVolume.setFillColor(Color::White);
	textMasterVolume.setPosition(682, 658);

	MasterBar.setTexture(textureSQ);
	MasterBar.setTextureRect(IntRect(3, 1507, 718, 17));
	MasterBar.setScale(Vector2f(0.5f, 0.5f));
	MasterBar.setPosition(985, 675);

	MasterCS.setTexture(textureSQ);
	MasterCS.setTextureRect(IntRect(235, 1573, 15, 24));
	MasterCS.setScale(Vector2f(1.5f, 1.5f));
	MasterCS.setPosition(985, 660); // 985~1320 = 67(5등분)

	/////////////////////////////////// Esc -> Setting -> UI Volume

	textUIVolume.setFont(settingLan);
	textUIVolume.setString("UI Volume");
	textUIVolume.setCharacterSize(30);
	textUIVolume.setFillColor(Color::White);
	textUIVolume.setPosition(682, 738);

	UIBar.setTexture(textureSQ);
	UIBar.setTextureRect(IntRect(3, 1507, 718, 17));
	UIBar.setScale(Vector2f(0.5f, 0.5f));
	UIBar.setPosition(985, 755);

	UICS.setTexture(textureSQ);
	UICS.setTextureRect(IntRect(235, 1573, 15, 24));
	UICS.setScale(Vector2f(1.5f, 1.5f));
	UICS.setPosition(985, 740);

	/////////////////////////////////// Esc -> Setting -> SFX Volume

	textSFXVolume.setFont(settingLan);
	textSFXVolume.setString("SFX Volume");
	textSFXVolume.setCharacterSize(30);
	textSFXVolume.setFillColor(Color::White);
	textSFXVolume.setPosition(682, 818);

	SFXBar.setTexture(textureSQ);
	SFXBar.setTextureRect(IntRect(3, 1507, 718, 17));
	SFXBar.setScale(Vector2f(0.5f, 0.5f));
	SFXBar.setPosition(985, 835);

	SFXCS.setTexture(textureSQ);
	SFXCS.setTextureRect(IntRect(235, 1573, 15, 24));
	SFXCS.setScale(Vector2f(1.5f, 1.5f));
	SFXCS.setPosition(985, 820);

	/////////////////////////////////// Esc -> Setting -> Music Volume

	textMusicVolume.setFont(settingLan);
	textMusicVolume.setString("Music Volume");
	textMusicVolume.setCharacterSize(30);
	textMusicVolume.setFillColor(Color::White);
	textMusicVolume.setPosition(682, 898);

	MusicBar.setTexture(textureSQ);
	MusicBar.setTextureRect(IntRect(3, 1507, 718, 17));
	MusicBar.setScale(Vector2f(0.5f, 0.5f));
	MusicBar.setPosition(985, 915);

	MusicCS.setTexture(textureSQ);
	MusicCS.setTextureRect(IntRect(235, 1573, 15, 24));
	MusicCS.setScale(Vector2f(1.5f, 1.5f));
	MusicCS.setPosition(985, 900);

	/////////////////////////////////// Esc -> Setting -> Toggle

	Toggle.setFont(settingLan);
	Toggle.setString("Toggle");
	Toggle.setCharacterSize(25);
	Toggle.setFillColor(Color::White);
	Toggle.setPosition(797, 1000);

	ToggleLeft.setTexture(textureUI); // 토글 버튼 왼쪽 박스
	ToggleLeft.setTextureRect(IntRect(62, 605, 42, 40));
	ToggleLeft.setPosition(675, 995);

	ToggleRight.setTexture(textureUI); // 토글 버튼 오른쪽 박스
	ToggleRight.setTextureRect(IntRect(62, 605, 42, 40));
	ToggleRight.setPosition(745, 995);

	TogLeft.setFont(fontLostRuins); // 토글 ←
	TogLeft.setString("<-");
	TogLeft.setCharacterSize(20);
	TogLeft.setFillColor(Color::White);
	TogLeft.setPosition(687, 1001);

	TogRight.setFont(fontLostRuins); // 토글 →
	TogRight.setString("->");
	TogRight.setCharacterSize(20);
	TogRight.setFillColor(Color::White);
	TogRight.setPosition(757, 1001);

	/////////////////////////////////// Esc -> Setting -> Back

	SetBack.setFont(settingLan);
	SetBack.setString("Back");
	SetBack.setCharacterSize(25);
	SetBack.setFillColor(Color::White);
	SetBack.setPosition(1200, 1000);

	ESCBack.setTexture(textureUI); // ESC 버튼 박스
	ESCBack.setTextureRect(IntRect(62, 605, 42, 40));
	ESCBack.setScale(Vector2f(1.5f, 1.0f));
	ESCBack.setPosition(1125, 995);

	SetESC.setFont(fontLostRuins); // ESC 텍스트
	SetESC.setString("Esc");
	SetESC.setCharacterSize(20);
	SetESC.setFillColor(Color::White);
	SetESC.setPosition(1139, 1001);

	///////////////////////////////////	
}

void TestUi::ESCsettag()
{
	FullCS.setTexture(textureSQ);
	FullCS.setTextureRect(IntRect(79, 1016, 39, 31));
	FullCS.setScale(Vector2f(1.2f, 1.2f));
	FullCS.setPosition(1145, 342);

	FullCS2.setTexture(textureSQ);
	FullCS2.setTextureRect(IntRect(125, 1017, 31, 23));
	FullCS2.setScale(Vector2f(1.5f, 1.5f));
	FullCS2.setPosition(1145, 342);

	VsyCS.setTexture(textureSQ);
	VsyCS.setTextureRect(IntRect(79, 1016, 39, 31));
	VsyCS.setScale(Vector2f(1.2f, 1.2f));
	VsyCS.setPosition(1145, 422);

	VsyCS2.setTexture(textureSQ);
	VsyCS2.setTextureRect(IntRect(125, 1017, 31, 23));
	VsyCS2.setScale(Vector2f(1.5f, 1.5f));
	VsyCS2.setPosition(1145, 422);

	BattleCS.setTexture(textureSQ);
	BattleCS.setTextureRect(IntRect(79, 1016, 39, 31));
	BattleCS.setScale(Vector2f(1.2f, 1.2f));
	BattleCS.setPosition(1145, 582);

	BattleCS2.setTexture(textureSQ);
	BattleCS2.setTextureRect(IntRect(125, 1017, 31, 23));
	BattleCS2.setScale(Vector2f(1.5f, 1.5f));
	BattleCS2.setPosition(1145, 582);
}

void TestUi::SeeMap()
{
	textureMAP = TextureHolder::GetTexture("graphics/MAP make.png");
	Blur1 = TextureHolder::GetTexture("graphics/esc.png");

	Blur.setTexture(Blur1); // 맵 블러처리된 배경
	Blur.setTextureRect(IntRect(39, 2385, 1339, 887));
	Blur.setScale(Vector2f(0.97f, 0.86f));
	Blur.setPosition(299, 223); //280, 280

	InventoryMAP.setTexture(textureMAP); // 맵 창
	InventoryMAP.setTextureRect(IntRect(39, 2385, 1339, 887));
	InventoryMAP.setScale(Vector2f(1.0f, 0.9f));
	InventoryMAP.setPosition(280, 205); //280, 280

	textureSQ = TextureHolder::GetTexture("graphics/SQ.png");

	Invenname.setTexture(textureSQ); // Tab -> inventory 글씨
	Invenname.setTextureRect(IntRect(1021, 638, 346, 115));
	Invenname.setScale(Vector2f(0.6f, 0.7f));
	Invenname.setPosition(720, 132);

	InvenMap.setTexture(textureSQ); // Tab -> MAP 글씨
	InvenMap.setTextureRect(IntRect(1021, 638, 346, 115));
	InvenMap.setScale(Vector2f(0.6f, 0.7f));
	InvenMap.setPosition(940, 132);

	InvenBtQ.setTexture(textureUI); // Tab -> inventory -> 버튼Q
	InvenBtQ.setTextureRect(IntRect(62, 605, 42, 40));
	InvenBtQ.setPosition(670, 172);

	InvenBtW.setTexture(textureUI); // Tab -> inventory -> 버튼W
	InvenBtW.setTextureRect(IntRect(62, 605, 42, 40));
	InvenBtW.setPosition(1155, 172);

	fontLostRuins.loadFromFile("fonts/LiberationSans-Regular.ttf");

	textInvenBtQ.setFont(fontLostRuins);
	textInvenBtW.setFont(fontLostRuins);
	textInven.setFont(fontLostRuins);
	textMap.setFont(fontLostRuins);

	textInvenBtQ.setString("Q");
	textInvenBtW.setString("W");
	textInven.setString("INVENTORY");
	textMap.setString("MAP");

	textInvenBtQ.setCharacterSize(20);
	textInvenBtW.setCharacterSize(20);
	textInven.setCharacterSize(33);
	textMap.setCharacterSize(33);

	textInvenBtQ.setFillColor(Color::White);
	textInvenBtW.setFillColor(Color::White);
	textInven.setFillColor(Color::White);
	textMap.setFillColor(Color::Green);

	textInvenBtQ.setPosition(682, 178); //670, 172
	textInvenBtW.setPosition(1167, 180);
	textInven.setPosition(728, 150);
	textMap.setPosition(1010, 150);
}

void TestUi::Escapemenu()
{
	escNum = 1;

	Escmenu = true;

	Escback1 = TextureHolder::GetTexture("graphics/esc.png");
	Escback.setTexture(Escback1);
	Escback.setPosition(0, 0);

	EscCS.setTexture(textureUI);
	EscCS.setTextureRect(IntRect(139, 1369, 70, 68));
	EscCS.setScale(Vector2f(0.5f, 0.5f));
	EscCS.setPosition(280, 690);


	fontLostRuins.loadFromFile("fonts/LiberationSans-Regular.ttf");

	Continue.setFont(fontLostRuins);
	Setting.setFont(fontLostRuins);
	End.setFont(fontLostRuins);

	Continue.setString("Continue");
	Setting.setString("Setting");
	End.setString("END");

	Continue.setCharacterSize(35);
	Setting.setCharacterSize(35);
	End.setCharacterSize(35);

	Continue.setFillColor(Color::White);
	Setting.setFillColor(Color::White);
	End.setFillColor(Color::White);

	Continue.setPosition(100, 700);
	Setting.setPosition(100, 770);
	End.setPosition(100, 840);
}

void TestUi::SeeInven()
{
	textureIN = TextureHolder::GetTexture("graphics/inven make.png");
	Blur1 = TextureHolder::GetTexture("graphics/esc.png");

	Blur.setTexture(Blur1); // inventory 블러처리된 배경
	Blur.setTextureRect(IntRect(39, 2385, 1339, 887));
	Blur.setScale(Vector2f(0.97f, 0.86f));
	Blur.setPosition(299, 223); //280, 280


	Invenwindow.setTexture(textureIN); // 인벤토리 창
	Invenwindow.setTextureRect(IntRect(39, 2385, 1339, 887));
	Invenwindow.setScale(Vector2f(1.0f, 0.9f));
	Invenwindow.setPosition(280, 205); //280, 280

	InvenLongWeapon.setTexture(textureUI); // 인벤토리 무기
	InvenLongWeapon.setTextureRect(IntRect(2, 934, 61, 56));
	InvenLongWeapon.setPosition(330, 270);

	InvenOrder.setTexture(textureUI); // 인벤토리 주문
	InvenOrder.setTextureRect(IntRect(69, 933, 58, 58));
	InvenOrder.setPosition(411, 270);

	InvenSupplies.setTexture(textureUI); // 인벤토리 소모품
	InvenSupplies.setTextureRect(IntRect(140, 931, 47, 62));
	InvenSupplies.setPosition(499, 270);

	InvenEquipment.setTexture(textureUI); // 인벤토리 장비
	InvenEquipment.setTextureRect(IntRect(206, 937, 45, 50));
	InvenEquipment.setPosition(577, 275);

	InvenRelic.setTexture(textureUI); // 인벤토리 유물
	InvenRelic.setTextureRect(IntRect(267, 937, 52, 51));
	InvenRelic.setPosition(653, 275);

	InvenRecord.setTexture(textureUI); // 인벤토리 기록
	InvenRecord.setTextureRect(IntRect(337, 936, 43, 53));
	InvenRecord.setPosition(739, 273);

	InvenKey.setTexture(textureUI); // 인벤토리 열쇠
	InvenKey.setTextureRect(IntRect(408, 933, 31, 59));
	InvenKey.setPosition(827, 270);

	InvenCS.setTexture(textureUI); // 인벤토리 커서
	InvenCS.setTextureRect(IntRect(103, 1571, 79, 30));
	InvenCS.setPosition(320, 328);

	textureSQ = TextureHolder::GetTexture("graphics/SQ.png");

	Invenname.setTexture(textureSQ); // 인벤토리 이름
	Invenname.setTextureRect(IntRect(1021, 638, 346, 115));
	Invenname.setScale(Vector2f(0.6f, 0.7f));
	Invenname.setPosition(720, 132);

	InvenMap.setTexture(textureSQ); // 인벤토리 맵
	InvenMap.setTextureRect(IntRect(1021, 638, 346, 115));
	InvenMap.setScale(Vector2f(0.6f, 0.7f));
	InvenMap.setPosition(940, 132);

	InvenBtQ.setTexture(textureUI); // 인벤토리 버튼Q
	InvenBtQ.setTextureRect(IntRect(62, 605, 42, 40));
	InvenBtQ.setPosition(670, 172);

	InvenBtW.setTexture(textureUI); // 인벤토리 버튼W
	InvenBtW.setTextureRect(IntRect(62, 605, 42, 40));
	InvenBtW.setPosition(1155, 172);

	fontLostRuins.loadFromFile("fonts/LiberationSans-Regular.ttf");

	textInvenBtQ.setFont(fontLostRuins);
	textInvenBtW.setFont(fontLostRuins);
	textInven.setFont(fontLostRuins);
	textMap.setFont(fontLostRuins);

	textInvenBtQ.setString("Q");
	textInvenBtW.setString("W");
	textInven.setString("INVENTORY");
	textMap.setString("MAP");

	textInvenBtQ.setCharacterSize(20);
	textInvenBtW.setCharacterSize(20);
	textInven.setCharacterSize(33);
	textMap.setCharacterSize(33);

	textInvenBtQ.setFillColor(Color::White);
	textInvenBtW.setFillColor(Color::White);
	textInven.setFillColor(Color::Green);
	textMap.setFillColor(Color::White);

	textInvenBtQ.setPosition(682, 178); //670, 172
	textInvenBtW.setPosition(1167, 180); //1155 172
	textInven.setPosition(728, 150);
	textMap.setPosition(1010, 150);
}