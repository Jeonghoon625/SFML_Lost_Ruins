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

	fontLostRuins.loadFromFile("fonts/LiberationSans-Regular.ttf");

	textgold.setFont(fontLostRuins);
	textgold.setString("Gold:");
	textgold.setCharacterSize(25);
	textgold.setFillColor(Color::White);
	textgold.setPosition(1390, 300);

	textMoney.setFont(fontLostRuins);
	textMoney.setString("10");
	textMoney.setCharacterSize(25);
	textMoney.setFillColor(Color(255, 255, 0, 255));
	textMoney.setPosition(1460, 300);
}

void TestUi::Update(float dt, Time playTime, RenderWindow* window, View* mainView, Player& player)
{
	float HPbarwidth = 314;
	float HPbarHeight = 17;
	float MPbarwidth = 314;
	float MPbarHeight = 17;

	stringstream hp;
	hp << player.GetHealth() << "/" << player.GetMaxHealth();
	textHPbar.setString(hp.str());
	stringstream mp;
	mp << player.GetMana() << "/" << player.GetMaxMana();
	textMPbar.setString(mp.str());

	healthBarsize = Vector2f(HPbarwidth, HPbarHeight);
	HPbar.setScale(player.GetHealth() / 20.f, 1.f); //player.GetMaxHealth()
	mpBarsize = Vector2f(MPbarwidth, MPbarHeight);
	MPbar.setScale(player.GetMana() / 20.f, 1.f);

	/*float MPwidth = 314;
	float MPbarHeight = 17;
	mpBarsize = Vector2f(MPwidth, HPbarHeight);
	MPbar.setScale(player.get)*/

	ESCsettag();

	if (InputManager::GetKeyDown(Keyboard::Space) && inventory == true && weaponNum == 1 && menuNum == 1)
	{
		Zweaponview = !Zweaponview;

		if (Zweaponview == true)
		{
			player.SetZWeapon(true);
		}
		else if (Zweaponview == false)
		{
			player.SetZWeapon(false);
		}
	}
	if (InputManager::GetKeyDown(Keyboard::Space) && inventory == true && weaponNum == 2 && menuNum == 1)
	{
		Xweaponview = !Xweaponview;

		if (Xweaponview == true)
		{
			player.SetXWeapon(true);
		}
		else if (Xweaponview == false)
		{
			player.SetXWeapon(false);
		}
	}

	if (InputManager::GetKeyDown(Keyboard::Space) && inventory == true && orderNum == 1 && menuNum == 2)
	{
		Zscrollview = !Zscrollview;

		if (Zscrollview == true)
		{
			player.SetASpell(true);
		}
		else if (Zscrollview == false)
		{
			player.SetASpell(false);
		}
	}

	if (InputManager::GetKeyDown(Keyboard::Space) && inventory == true && orderNum == 2 && menuNum == 2)
	{
		Xscrollview = !Xscrollview;
	}


	if (InputManager::GetKeyDown(Keyboard::Space) && inventory == true && SuppliesNum == 1 && menuNum == 3)
	{
		Zfoodview = !Zfoodview;
	}


	if (InputManager::GetKeyDown(Keyboard::Space) && inventory == true && EquipmentNum == 1 && menuNum == 4)
	{
		ZEquipview = !ZEquipview;
	}

	if (InputManager::GetKeyDown(Keyboard::Space) && inventory == true && EquipmentNum == 2 && menuNum == 4)
	{
		XEquipview = !XEquipview;
	}



	if (InputManager::GetKeyDown(Keyboard::Space) && inventory == true && relicsNum == 1 && menuNum == 5)
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
	if (InputManager::GetKeyDown(Keyboard::Key::Up) && inventory == true && Zweapon == true && menuNum == 1 && Xweapon == true && weaponNum == 1)
	{
		weaponlist1();
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
		if (InputManager::GetKeyDown(Keyboard::Key::Down) && orderNum != 1)
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
	if (InputManager::GetKeyDown(Keyboard::Key::Up) && inventory == true && menuNum == 4 && EquipmentNum == 1 && ZEquip == true && XEquip == true)
	{
		EquipList1();
	}

	if (InputManager::GetKeyDown(Keyboard::Key::Right) && inventory == true && menuNum == 5 && relicsNum == 1 && Zrelics == true)
	{
		relics();
	}

	
	if (InputManager::GetKeyDown(Keyboard::Key::Q) && shopBuy1 == false && shopSell1 == false && MAP == false && Escset == false && Esckey == false)
	{
		inventory = false;
		MAP = true;
		SeeMap();
	}
	else if (InputManager::GetKeyDown(Keyboard::Key::Q) && shopBuy1 == false && shopSell1 == false && inventory == false && Escset == false && Esckey == false)
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


	if (InputManager::GetKeyDown(Keyboard::Key::W) && shopBuy1 == false && shopSell1 == false && MAP == false && Escset == false && Esckey == false)
	{
		inventory = false;
		MAP = true;
		SeeMap();
	}
	else if (InputManager::GetKeyDown(Keyboard::Key::W) && shopBuy1 == false && shopSell1 == false && inventory == false && Escset == false && Esckey == false)
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





	////////////////////////////////////
	// 상점 키입력부분.
	if (InputManager::GetKeyDown(Keyboard::P) && Escmenu == false && inventory == false && MAP == false)
	{
		shopBuynum = 1;
		shopSellnum = 1;
		shoporderNum1 = 1;
		shopweaNum1 = 1;
		shopSupNum1 = 1;
		shopSell1 = false;
		shopBuy1 = true;
		shopCS.setPosition(320, 328);
		InvenallCS.setPosition(340, 394);
		shopBuy();
		Buywea1();
	}

	if (InputManager::GetKeyDown(Keyboard::Escape) && shopBuy1 == true)
	{
		shopBuy1 = false;
		Escmenu = false;
	}

	if (InputManager::GetKeyDown(Keyboard::Escape) && shopSell1 == true)
	{
		shopSell1 = false;
		Escmenu = false;
	}

	if (InputManager::GetKeyDown(Keyboard::Key::Left) && shopBuy1 == true && inventory == false && shopBuynum != 1 && shopSell1 == false)
	{
		shoporderNum1 = 1;
		shopweaNum1 = 1;
		shopSupNum1 = 1;
		shopEquNum1 = 1;
		
		--shopBuynum;
		InvenallCS.setPosition(340, 394);
		shopCS.setPosition(shopCS.getPosition().x - 80, 328);
	}	

	if (InputManager::GetKeyDown(Keyboard::Key::Right) && shopBuy1 == true && inventory == false && shopBuynum != 4 && shopSell1 == false)
	{
		shoporderNum1 = 1;
		shopweaNum1 = 1;
		shopSupNum1 = 1;
		shopEquNum1 = 1;

		++shopBuynum;
		InvenallCS.setPosition(340, 394);
		shopCS.setPosition(shopCS.getPosition().x + 80, 328);
	}

	if (InputManager::GetKeyDown(Keyboard::Key::Left) && shopBuy1 == false && inventory == false && shopSellnum != 1 && shopSell1 == true)
	{
		--shopSellnum;
		SshopCS.setPosition(SshopCS.getPosition().x - 80, 328);
	}

	if (InputManager::GetKeyDown(Keyboard::Key::Right) && shopBuy1 == false && inventory == false && shopSellnum != 4 && shopSell1 == true)
	{
		++shopSellnum;
		SshopCS.setPosition(SshopCS.getPosition().x + 80, 328);
	}

	if (InputManager::GetKeyDown(Keyboard::Key::Q) && inventory == false && MAP == false && shopSell1 == false && Escset == false && Esckey == false)
	{
		shoporderNum1 = 1;
		shopweaNum1 = 1;
		shopSupNum1 = 1;
		shopEquNum1 = 1;
		shopSellnum = 1;
		shopBuy1 = false;
		shopSell1 = true;
		shopSell();
	}
	else if (InputManager::GetKeyDown(Keyboard::Key::Q) && inventory == false && MAP == false && shopBuy1 == false && Escset == false && Esckey == false)
	{
		shopBuynum = 1;
		shopSell1 = false;
		shopBuy1 = true;
		shopBuy();
	}
	if (InputManager::GetKeyDown(Keyboard::Key::W) && inventory == false && MAP == false && Escset == false && Esckey == false && shopBuy1 == true)
	{
		shopSellnum = 1;
		shopBuy1 = false;
		shopSell1 = true;
		shopSell();
	}
	else if (InputManager::GetKeyDown(Keyboard::Key::W) && inventory == false && MAP == false && inventory == false && Escset == false && Esckey == false && shopSell1 == true)
	{
		shoporderNum1 = 1;
		shopweaNum1 = 1;
		shopSupNum1 = 1;
		shopEquNum1 = 1;
		shopBuynum = 1;
		shopSell1 = false;
		shopBuy1 = true;
		shopBuy();
	}

	if (inventory == false && MAP == false && shopBuy1 == true && shopSell1 == false && shopBuynum == 1)
	{
		if (InputManager::GetKeyDown(Keyboard::Key::Up) && shopweaNum1 != 1)
		{
			--shopweaNum1;
			InvenallCS.setPosition(340, InvenallCS.getPosition().y - 50);
		}
		if (InputManager::GetKeyDown(Keyboard::Key::Down) && shopweaNum1 != 4)
		{
			++shopweaNum1;
			InvenallCS.setPosition(340, InvenallCS.getPosition().y + 50);
		}
	}
	if (inventory == false && MAP == false && shopBuy1 == true && shopSell1 == false && shopBuynum == 2)
	{
		if (InputManager::GetKeyDown(Keyboard::Key::Up) && shoporderNum1 != 1)
		{
			--shoporderNum1;
			InvenallCS.setPosition(340, InvenallCS.getPosition().y - 50);
		}
		if (InputManager::GetKeyDown(Keyboard::Key::Down) && shoporderNum1 != 3)
		{
			++shoporderNum1;
			InvenallCS.setPosition(340, InvenallCS.getPosition().y + 50);
		}
	}
	if (inventory == false && MAP == false && shopBuy1 == true && shopSell1 == false && shopBuynum == 3)
	{
		if (InputManager::GetKeyDown(Keyboard::Key::Up) && shopSupNum1 != 1)
		{
			--shopSupNum1;
			InvenallCS.setPosition(340, InvenallCS.getPosition().y - 50);
		}
		if (InputManager::GetKeyDown(Keyboard::Key::Down) && shopSupNum1 != 2)
		{
			++shopSupNum1;
			InvenallCS.setPosition(340, InvenallCS.getPosition().y + 50);
		}
	}
	if (inventory == false && MAP == false && shopBuy1 == true && shopSell1 == false && shopBuynum == 4)
	{
		if (InputManager::GetKeyDown(Keyboard::Key::Up) && shopEquNum1 != 1)
		{
			--shopEquNum1;
			InvenallCS.setPosition(340, InvenallCS.getPosition().y - 50);
		}
		if (InputManager::GetKeyDown(Keyboard::Key::Down) && shopEquNum1 != 2)
		{
			++shopEquNum1;
			InvenallCS.setPosition(340, InvenallCS.getPosition().y + 50);
		}
	}

	if (InputManager::GetKeyDown(Keyboard::Key::Down) && MAP == false && inventory == false && shopBuynum == 1 && shopweaNum1 == 2)
	{
		Buywea2();
	}
	if (InputManager::GetKeyDown(Keyboard::Key::Down) && MAP == false && inventory == false && shopBuynum == 1 && shopweaNum1 == 3)
	{
		Buywea3();
	}
	if (InputManager::GetKeyDown(Keyboard::Key::Down) && MAP == false && inventory == false && shopBuynum == 1 && shopweaNum1 == 4)
	{
		Buywea4();
	}

	if (InputManager::GetKeyDown(Keyboard::Key::Up) && MAP == false && inventory == false && shopBuynum == 1 && shopweaNum1 == 1)
	{
		Buywea1();
	}
	if (InputManager::GetKeyDown(Keyboard::Key::Up) && MAP == false && inventory == false && shopBuynum == 1 && shopweaNum1 == 2)
	{
		Buywea2();
	}
	if (InputManager::GetKeyDown(Keyboard::Key::Up) && MAP == false && inventory == false && shopBuynum == 1 && shopweaNum1 == 3)
	{
		Buywea3();
	}



	if (InputManager::GetKeyDown(Keyboard::Key::Right) && MAP == false && inventory == false && shopBuynum == 2 && shoporderNum1 == 1)
	{
		Buyord1();
	}

	if (InputManager::GetKeyDown(Keyboard::Key::Down) && MAP == false && inventory == false && shopBuynum == 2 && shoporderNum1 == 2)
	{
		Buyord2();
	}

	if (InputManager::GetKeyDown(Keyboard::Key::Down) && MAP == false && inventory == false && shopBuynum == 2 && shoporderNum1 == 3)
	{
		Buyord3();
	}
	if (InputManager::GetKeyDown(Keyboard::Key::Up) && MAP == false && inventory == false && shopBuynum == 2 && shoporderNum1 == 1)
	{
		Buyord1();
	}
	if (InputManager::GetKeyDown(Keyboard::Key::Up) && MAP == false && inventory == false && shopBuynum == 2 && shoporderNum1 == 2)
	{
		Buyord2();
	}




	if (InputManager::GetKeyDown(Keyboard::Key::Right) && MAP == false && inventory == false && shopBuynum == 3 && shopSupNum1 == 1)
	{
		Buysup1();
	}

	if (InputManager::GetKeyDown(Keyboard::Key::Down) && MAP == false && inventory == false && shopBuynum == 3 && shopSupNum1 == 2)
	{
		Buysup2();
	}
	if (InputManager::GetKeyDown(Keyboard::Key::Up) && MAP == false && inventory == false && shopBuynum == 3 && shopSupNum1 == 1)
	{
		Buysup1();
	}



	if (InputManager::GetKeyDown(Keyboard::Key::Right) && MAP == false && inventory == false && shopBuynum == 4 && shopEquNum1 == 1)
	{
		Buyequ1();
	}

	if (InputManager::GetKeyDown(Keyboard::Key::Down) && MAP == false && inventory == false && shopBuynum == 4 && shopEquNum1 == 2)
	{
		Buyequ2();
	}
	if (InputManager::GetKeyDown(Keyboard::Key::Up) && MAP == false && inventory == false && shopBuynum == 4 && shopEquNum1 == 1)
	{
		Buyequ1();
	}
}

void TestUi::Draw(RenderWindow* window, View* mainView)
{
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
	window->draw(ButtonState);
	window->draw(ButtonA);

	window->draw(textHPbar); // 체력숫자
	window->draw(textMPbar); // 마나숫자
	window->draw(textButtonTab); // TAB버튼
	window->draw(textButtonM); // M버튼
	window->draw(textButtonX); // 버튼X
	window->draw(textButtonZ); // 버튼Z
	window->draw(textButtonS); // 버튼S
	window->draw(textButtonA); // 버튼A

	////////////////////////////////////////////
	// 상점 드로우
	if (shopBuy1 == true)
	{
		window->draw(shopBlur);
		window->draw(shopWindow); // 인벤토리 창
		window->draw(shopWeapon); // 인벤토리 무기
		window->draw(shopOrder); // 인벤토리 주문
		window->draw(shopSupplies); // 인벤토리 소모품
		window->draw(shopEquipment); // 인벤토리 장비
		window->draw(shopCS); // 인벤토리 커서
		window->draw(shopBuybox); // 인벤토리 이름
		window->draw(shopSELLbox); // 인벤토리 맵
		window->draw(shopBTQbox); // 인벤토리Q버튼
		window->draw(shopBTWbox); // 인벤토리W버튼
		window->draw(InvenallCS);
		window->draw(shopbuyname);
		window->draw(textgold);
		window->draw(textMoney);

		window->draw(shopBTQ); // 인벤토리 내 Q버튼
		window->draw(shopBTW); // 인벤토리 내 W버튼
		window->draw(shopBuyname); // (인벤토리) 텍스트
		window->draw(shopSELLname); // (맵) 텍스트
	}

	if (shopSell1 == true)
	{
		window->draw(SshopBlur);
		window->draw(SshopWindow); // 인벤토리 창
		window->draw(SshopWeapon); // 인벤토리 무기
		window->draw(SshopOrder); // 인벤토리 주문
		window->draw(SshopSupplies); // 인벤토리 소모품
		window->draw(SshopEquipment); // 인벤토리 장비
		window->draw(SshopCS); // 인벤토리 커서
		window->draw(SshopBuybox); // 인벤토리 이름
		window->draw(SshopSELLbox); // 인벤토리 맵
		window->draw(SshopBTQbox); // 인벤토리Q버튼
		window->draw(SshopBTWbox); // 인벤토리W버튼
		window->draw(InvenallCS);
		window->draw(shopsellname);
		window->draw(textgold);
		window->draw(textMoney);

		window->draw(SshopBTQ); // 인벤토리 내 Q버튼
		window->draw(SshopBTW); // 인벤토리 내 W버튼
		window->draw(SshopBuyname); // (인벤토리) 텍스트
		window->draw(SshopSELLname); // (맵) 텍스트
	}

	// 무기 페이지
	if (shopBuynum == 1 && shopBuy1 == true && shopweaNum1 == 1)
	{
		window->draw(textShopweapon1Lname);
		window->draw(textShopweapon2name);
		window->draw(textShopweapon3name);
		window->draw(textShopweapon4name);

		window->draw(Shopweapon1bk);
		window->draw(Shopweapon1Box);
		window->draw(textShopweapon1Rname);
		window->draw(Shopweapon1img);
		window->draw(textShopweapon1text1);
		window->draw(textShopweapon1text2);
		window->draw(textShopweapon1text3);
	}
	if (shopBuynum == 1 && shopweaNum1 == 2 && shopBuy1 == true)
	{
		window->draw(textShopweapon1Lname);
		window->draw(textShopweapon2name);
		window->draw(textShopweapon3name);
		window->draw(textShopweapon4name);

		window->draw(Shopweapon2bk);
		window->draw(Shopweapon2Box);
		window->draw(textShopweapon2Rname);
		window->draw(Shopweapon2img);
		window->draw(textShopweapon2text1);
		window->draw(textShopweapon2text2);
		window->draw(textShopweapon2text3);
	}
	if (shopBuynum == 1 && shopweaNum1 == 3 && shopBuy1 == true)
	{
		window->draw(textShopweapon1Lname);
		window->draw(textShopweapon2name);
		window->draw(textShopweapon3name);
		window->draw(textShopweapon4name);

		window->draw(Shopweapon3bk);
		window->draw(Shopweapon3Box);
		window->draw(textShopweapon3Rname);
		window->draw(Shopweapon3img);
		window->draw(textShopweapon3text1);
		window->draw(textShopweapon3text2);
		window->draw(textShopweapon3text3);
	}
	if (shopBuynum == 1 && shopweaNum1 == 4 && shopBuy1 == true)
	{
		window->draw(textShopweapon1Lname);
		window->draw(textShopweapon2name);
		window->draw(textShopweapon3name);
		window->draw(textShopweapon4name);

		window->draw(Shopweapon4bk);
		window->draw(Shopweapon4Box);
		window->draw(textShopweapon4Rname);
		window->draw(Shopweapon4img);
		window->draw(textShopweapon4text1);
		window->draw(textShopweapon4text2);
		window->draw(textShopweapon4text3);
	}

	// 마법 페이지
	if (shopBuynum == 2 && shoporderNum1 == 1 && shopBuy1 == true)
	{
		window->draw(textShopord1Lname);
		window->draw(textShopord2Lname);
		window->draw(textShopord3Lname);

		window->draw(Shopord1bk);
		window->draw(Shopord1Box);
		window->draw(textShopord1Rname);
		window->draw(Shopord1img);
		window->draw(textShopord1text1);
		window->draw(textShopord1text2);
		window->draw(textShopord1text3);
	}
	if (shopBuynum == 2 && shoporderNum1 == 2 && shopBuy1 == true)
	{
		window->draw(textShopord1Lname);
		window->draw(textShopord2Lname);
		window->draw(textShopord3Lname);

		window->draw(Shopord2bk);
		window->draw(Shopord2Box);
		window->draw(textShopord2Rname);
		window->draw(Shopord2img);
		window->draw(textShopord2text1);
		window->draw(textShopord2text2);
		window->draw(textShopord2text3);
	}
	if (shopBuynum == 2 && shoporderNum1 == 3 && shopBuy1 == true)
	{
		window->draw(textShopord1Lname);
		window->draw(textShopord2Lname);
		window->draw(textShopord3Lname);

		window->draw(Shopord3bk);
		window->draw(Shopord3Box);
		window->draw(textShopord3Rname);
		window->draw(Shopord3img);
		window->draw(textShopord3text1);
		window->draw(textShopord3text2);
		window->draw(textShopord3text3);
	}

	// 소모품 페이지

	if (shopBuynum == 3 && shopSupNum1 == 1 && shopBuy1 == true)
	{
		window->draw(textShopsup1Lname);
		window->draw(textShopsup2name);

		window->draw(Shopsup1bk);
		window->draw(Shopsup1Box);
		window->draw(textShopsup1Rname);
		window->draw(Shopsup1img);
		window->draw(textShopsup1text1);
		window->draw(textShopsup1text2);
		window->draw(textShopsup1text3);
	}
	if (shopBuynum == 3 && shopSupNum1 == 2 && shopBuy1 == true)
	{
		window->draw(textShopsup1Lname);
		window->draw(textShopsup2name);

		window->draw(Shopsup2bk);
		window->draw(Shopsup2Box);
		window->draw(textShopsup2Rname);
		window->draw(Shopsup2img);
		window->draw(textShopsup2text1);
		window->draw(textShopsup2text2);
		window->draw(textShopsup2text3);
	}

	// 장비 페이지
	if (shopBuynum == 4 && shopEquNum1 == 1 && shopBuy1 == true)
	{
		window->draw(textShopequ1Lname);
		window->draw(textShopequ2Lname);

		window->draw(Shopequ1bk);
		window->draw(Shopequ1Box);
		window->draw(textShopequ1Rname);
		window->draw(Shopequ1img);
		window->draw(textShopequ1text1);
		window->draw(textShopequ1text2);
		window->draw(textShopequ1text3);
	}
	if (shopBuynum == 4 && shopEquNum1 == 2 && shopBuy1 == true)
	{
		window->draw(textShopequ1Lname);
		window->draw(textShopequ2Lname);

		window->draw(Shopequ2bk);
		window->draw(Shopequ2Box);
		window->draw(textShopequ2Rname);
		window->draw(Shopequ2img);
		window->draw(textShopequ2text1);
		window->draw(textShopequ2text2);
		window->draw(textShopequ2text3);
	}

	//////////////////////////////////////////////////////

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
		window->draw(InvenSpaceBar);
		window->draw(textInvenSpaceBar);
		window->draw(textInvenspace);
		window->draw(textinvenname);
		window->draw(textgold);
		window->draw(textMoney);

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
		window->draw(shopsellname);

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
			}			
		}


		if (Xscrollview)
		{
			if (inventory == true)
			{
				window->draw(Orderfullrhombus2);				
			}			
		}		
	}
	
	if (Zscrollview)
	{
		window->draw(scr1);
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

	ButtonState.setTexture(textureUI);
	ButtonState.setTextureRect(IntRect(62, 605, 42, 40));
	ButtonState.setPosition(1680, 10);

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

	/////////////////////////////////
	// 상점
	shopBuy1 = false;
	shopSell1 = false;
	shopBuynum = 1;
	shopSellnum = 1;
	shopweaNum1 = 1;
	shoporderNum1 = 1;
	shopSupNum1 = 1;
	shopEquNum1 = 1;
	shopweaNum2 = 1;
	shoporderNum2 = 1;
	shopSupNum2 = 1;
	shopEquNum2 = 1;
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
	Setname.setFillColor(Color(255, 255, 255, 50));
	Setname.setPosition(805, 30);


	SettingKey.setTexture(textureSQ); // Keyboard 이름
	SettingKey.setTextureRect(IntRect(1021, 638, 346, 115));
	SettingKey.setScale(Vector2f(0.6f, 0.7f));
	SettingKey.setPosition(980, 10);
	Keyname.setFont(settingLan);
	Keyname.setString("Keyboard");
	Keyname.setCharacterSize(30);
	Keyname.setFillColor(Color::White);
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
	textInvenweapon1.setString("Normal sword");
	textInvenweapon1.setCharacterSize(30);
	textInvenweapon1.setFillColor(Color(255, 0, 0, 255));
	textInvenweapon1.setPosition(380, 395);

	InvenWeaponXblock2.setTexture(textureSQ); // 2. 마름모 빈칸
	InvenWeaponXblock2.setTextureRect(IntRect(33, 1016, 39, 31));
	InvenWeaponXblock2.setScale(Vector2f(1.0f, 1.0f));
	InvenWeaponXblock2.setPosition(320, 450);

	textInvenweapon2.setFont(fontLostRuins); // 2. 리스트 내 아이템 이름
	textInvenweapon2.setString("Dagger");
	textInvenweapon2.setCharacterSize(30);
	textInvenweapon2.setFillColor(Color(255, 0, 0, 100));
	textInvenweapon2.setPosition(380, 445);


	///////////////////////////////////////////////////////////////

	InvenWeaponblock3.setTexture(textureSQ); // 우측 아이템 네모칸
	InvenWeaponblock3.setTextureRect(IntRect(254, 673, 92, 96));
	InvenWeaponblock3.setScale(Vector2f(1.0f, 1.0f));
	InvenWeaponblock3.setPosition(980, 380);

	textInvenweapon3.setFont(fontLostRuins); // 우측 아이템 이름
	textInvenweapon3.setString("Normal sword");
	textInvenweapon3.setCharacterSize(40);
	textInvenweapon3.setFillColor(Color(255, 0, 0, 255));
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
	textInvenweapon4.setString("Weapon type : Two-handed");
	textInvenweapon4.setCharacterSize(25);
	textInvenweapon4.setFillColor(Color::White);
	textInvenweapon4.setPosition(980, 520);

	textInvenweapon5.setFont(fontLostRuins);
	textInvenweapon5.setString("Attack Speed : Middle");
	textInvenweapon5.setCharacterSize(25);
	textInvenweapon5.setFillColor(Color::White);
	textInvenweapon5.setPosition(980, 560);

	textInvenweapon6.setFont(fontLostRuins);
	textInvenweapon6.setString("Damage : Health 10");
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
	textInvenweapon21.setString("Normal sword");
	textInvenweapon21.setCharacterSize(30);
	textInvenweapon21.setFillColor(Color(255, 0, 0, 100));
	textInvenweapon21.setPosition(380, 395);

	InvenWeaponXblock22.setTexture(textureSQ);
	InvenWeaponXblock22.setTextureRect(IntRect(33, 1016, 39, 31));
	InvenWeaponXblock22.setScale(Vector2f(1.0f, 1.0f));
	InvenWeaponXblock22.setPosition(320, 450);

	textInvenweapon22.setFont(fontLostRuins);
	textInvenweapon22.setString("Dagger");
	textInvenweapon22.setCharacterSize(30);
	textInvenweapon22.setFillColor(Color(255, 0, 0, 255));
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
	textInvenweapon23.setFillColor(Color(255, 0, 0, 255));
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
	textInvenweapon26.setString("Damage : Health 9");
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
	Otextscrollname1.setFillColor(Color(51, 153, 255, 255));
	Otextscrollname1.setPosition(380, 395);

	Orderfullrhombus1.setTexture(textureSQ);
	Orderfullrhombus1.setTextureRect(IntRect(79, 1016, 39, 31)); // 1-1. 채워진 마름모
	Orderfullrhombus1.setScale(Vector2f(1.0f, 1.0f));
	Orderfullrhombus1.setPosition(320, 400);

	///////////////////////////////////////////////////////////////

	orderitemphotoframe1.setTexture(textureSQ); // 1. 우측 아이템 네모칸
	orderitemphotoframe1.setTextureRect(IntRect(254, 673, 92, 96));
	orderitemphotoframe1.setScale(Vector2f(1.0f, 1.0f));
	orderitemphotoframe1.setPosition(980, 380);

	OtextItemnamefield1.setFont(fontLostRuins); // 1. 우측 아이템 이름
	OtextItemnamefield1.setString("Fire fist");
	OtextItemnamefield1.setCharacterSize(40);
	OtextItemnamefield1.setFillColor(Color(51, 153, 255, 255));
	OtextItemnamefield1.setPosition(1100, 400);

	OdescriptionImage1.setTexture(scrollpng); // 1. 우측 아이템 이미지
	OdescriptionImage1.setTextureRect(IntRect(3, 131, 20, 22));
	OdescriptionImage1.setScale(Vector2f(1.7f, 1.7f));
	OdescriptionImage1.setPosition(1010, 410);

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
	Oattackspeed1.setString("Attack style : Ranged magic");
	Oattackspeed1.setCharacterSize(25);
	Oattackspeed1.setFillColor(Color::White);
	Oattackspeed1.setPosition(980, 560);

	ODamage1.setFont(fontLostRuins); // 1. 데미지
	ODamage1.setString("Damage : Health 5");
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

void TestUi::Supplies()
{
	textureSQ = TextureHolder::GetTexture("graphics/SQ.png");
	fontLostRuins.loadFromFile("fonts/LiberationSans-Regular.ttf");	

	Suppliesblankrhombus1.setTexture(textureSQ); //  1. 마름모 빈칸
	Suppliesblankrhombus1.setTextureRect(IntRect(33, 1016, 39, 31));
	Suppliesblankrhombus1.setScale(Vector2f(1.0f, 1.0f));
	Suppliesblankrhombus1.setPosition(320, 400);

	Suppliestextscrollname1.setFont(fontLostRuins); // 1. 리스트 내 아이템 이름
	Suppliestextscrollname1.setString("Picture of chicken");
	Suppliestextscrollname1.setCharacterSize(30);
	Suppliestextscrollname1.setFillColor(Color(0, 204, 0, 255));
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
	SuppliestextItemnamefield1.setFillColor(Color(0, 204, 0, 255));
	SuppliestextItemnamefield1.setPosition(1100, 400);

	SuppliesdescriptionImage1.setTexture(textureSQ); // 1. 우측 아이템 이미지
	SuppliesdescriptionImage1.setTextureRect(IntRect(314, 478, 52, 26));
	SuppliesdescriptionImage1.setScale(Vector2f(1.0f, 1.0f));
	SuppliesdescriptionImage1.setPosition(1001, 415);

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
	SuppliesDamage1.setString("Damage : Health 0");
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
	Equiptextscrollname1.setFillColor(Color(255, 128, 0, 255));
	Equiptextscrollname1.setPosition(380, 395);

	Equipblankrhombus2.setTexture(textureSQ); // 2. 마름모 빈칸
	Equipblankrhombus2.setTextureRect(IntRect(33, 1016, 39, 31));
	Equipblankrhombus2.setScale(Vector2f(1.0f, 1.0f));
	Equipblankrhombus2.setPosition(320, 450);

	Equiptextscrollname2.setFont(fontLostRuins); // 2. 리스트 내 아이템 이름
	Equiptextscrollname2.setString("Blue necklace of harmony");
	Equiptextscrollname2.setCharacterSize(30);
	Equiptextscrollname2.setFillColor(Color(255, 128, 0, 100));
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
	EquiptextItemnamefield1.setFillColor(Color(255, 128, 0, 255));
	EquiptextItemnamefield1.setPosition(1100, 400);

	EquipdescriptionImage1.setTexture(scrollpng); // 1. 우측 아이템 이미지
	EquipdescriptionImage1.setTextureRect(IntRect(3, 226, 12, 15));
	EquipdescriptionImage1.setScale(Vector2f(2.5f, 2.5f));
	EquipdescriptionImage1.setPosition(1012, 405);

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
	Equiptextscrollname1.setFillColor(Color(255, 128, 0, 100));
	Equiptextscrollname1.setPosition(380, 395);

	Equipblankrhombus2.setTexture(textureSQ); // 2. 마름모 빈칸
	Equipblankrhombus2.setTextureRect(IntRect(33, 1016, 39, 31));
	Equipblankrhombus2.setScale(Vector2f(1.0f, 1.0f));
	Equipblankrhombus2.setPosition(320, 450);

	Equiptextscrollname2.setFont(fontLostRuins); // 2. 리스트 내 아이템 이름
	Equiptextscrollname2.setString("Blue necklace of harmony");
	Equiptextscrollname2.setCharacterSize(30);
	Equiptextscrollname2.setFillColor(Color(255, 128, 0, 255));
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
	EquiptextItemnamefield2.setFillColor(Color(255, 128, 0, 255));
	EquiptextItemnamefield2.setPosition(1100, 400);

	EquipdescriptionImage2.setTexture(scrollpng); // 2. 우측 아이템 이미지
	EquipdescriptionImage2.setTextureRect(IntRect(20, 226, 11, 14));
	EquipdescriptionImage2.setScale(Vector2f(2.5f, 2.5f));
	EquipdescriptionImage2.setPosition(1014, 407);

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
	Relictextscrollname1.setString("Angel's blessing");
	Relictextscrollname1.setCharacterSize(30);
	Relictextscrollname1.setFillColor(Color(204, 0, 204, 255));
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
	RelictextItemnamefield1.setString("Angel's blessing");
	RelictextItemnamefield1.setCharacterSize(40);
	RelictextItemnamefield1.setFillColor(Color(204, 0, 204, 255));
	RelictextItemnamefield1.setPosition(1100, 400);

	RelicdescriptionImage1.setTexture(scrollpng); // 1. 우측 아이템 이미지
	RelicdescriptionImage1.setTextureRect(IntRect(3, 62, 26, 23));
	RelicdescriptionImage1.setScale(Vector2f(1.5f, 1.5f));
	RelicdescriptionImage1.setPosition(1007, 410);

	Relicitembackground1.setTexture(textureSQ); // 1. 우측 아이템 이미지 뒷배경
	Relicitembackground1.setTextureRect(IntRect(62, 605, 42, 40));
	Relicitembackground1.setScale(Vector2f(2.2f, 2.4f));
	Relicitembackground1.setPosition(980, 380);

	Relicmagictype1.setFont(fontLostRuins); // 1. 유물 타입
	Relicmagictype1.setString("Relic type : possession");
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
	Setname.setFillColor(Color::White);
	Setname.setPosition(805, 30);


	SettingKey.setTexture(textureSQ); // ESC -> Keybord 이름
	SettingKey.setTextureRect(IntRect(1021, 638, 346, 115));
	SettingKey.setScale(Vector2f(0.6f, 0.7f));
	SettingKey.setPosition(980, 10);
	Keyname.setFont(settingLan);
	Keyname.setString("Keyboard");
	Keyname.setCharacterSize(30);
	Keyname.setFillColor(Color(255, 255, 255, 50));
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
	fontLostRuins.loadFromFile("fonts/LiberationSans-Regular.ttf");

	shopsellname.setFont(fontLostRuins);
	shopsellname.setString("Survivor Camp");
	shopsellname.setCharacterSize(30);
	shopsellname.setFillColor(Color::White);
	shopsellname.setPosition(840, 230);


	///////////////////////////////////////////////////

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
	textInven.setFillColor(Color(255, 255, 255, 50));
	textMap.setFillColor(Color::White);

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
	settingLan.loadFromFile("fonts/LiberationSans-Bold.ttf");
	fontLostRuins.loadFromFile("fonts/LiberationSans-Regular.ttf");

	textinvenname.setFont(fontLostRuins);
	textinvenname.setString("INVENTORY");
	textinvenname.setCharacterSize(30);
	textinvenname.setFillColor(Color::White);
	textinvenname.setPosition(1390, 230);

	//////////////////////////////////////////////

	Blur.setTexture(Blur1); // inventory 블러처리된 배경
	Blur.setTextureRect(IntRect(39, 2385, 1339, 887));
	Blur.setScale(Vector2f(0.97f, 0.86f));
	Blur.setPosition(299, 223); //280, 280

	InvenSpaceBar.setTexture(textureUI);
	InvenSpaceBar.setTextureRect(IntRect(62, 605, 42, 40));
	InvenSpaceBar.setPosition(830, 1000);
	InvenSpaceBar.setScale(2.4f, 1.0f);

	textInvenSpaceBar.setFont(fontLostRuins);
	textInvenSpaceBar.setString("Space");
	textInvenSpaceBar.setCharacterSize(20);
	textInvenSpaceBar.setFillColor(Color::White);
	textInvenSpaceBar.setPosition(851, 1006); //1147

	textInvenspace.setFont(settingLan);
	textInvenspace.setString("Wear");
	textInvenspace.setCharacterSize(25);
	textInvenspace.setFillColor(Color::White);
	textInvenspace.setPosition(950, 1005);


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
	textInven.setFillColor(Color::White);
	textMap.setFillColor(Color(255, 255, 255, 50));

	textInvenBtQ.setPosition(682, 178); //670, 172
	textInvenBtW.setPosition(1167, 180); //1155 172
	textInven.setPosition(728, 150);
	textMap.setPosition(1010, 150);
}




////////////////////////////////////
// 상점 함수

void TestUi::shopBuy()
{
	textureIN = TextureHolder::GetTexture("graphics/inven make.png");
	Blur1 = TextureHolder::GetTexture("graphics/esc.png");
	fontLostRuins.loadFromFile("fonts/LiberationSans-Regular.ttf"); // 이름 폰트

	shopbuyname.setFont(fontLostRuins);
	shopbuyname.setString("SHOP");
	shopbuyname.setCharacterSize(30);
	shopbuyname.setFillColor(Color::White);
	shopbuyname.setPosition(1390, 230);


	////////////////////////////////////////////////


	shopBlur.setTexture(Blur1); // inventory 블러처리된 배경
	shopBlur.setTextureRect(IntRect(39, 2385, 1339, 887));
	shopBlur.setScale(Vector2f(0.97f, 0.86f));
	shopBlur.setPosition(299, 223); //280, 280

	shopWindow.setTexture(textureIN); // 상점 창
	shopWindow.setTextureRect(IntRect(39, 2385, 1339, 887));
	shopWindow.setScale(Vector2f(1.0f, 0.9f));
	shopWindow.setPosition(280, 205); //280, 280

	shopWeapon.setTexture(textureUI); // 상점 무기
	shopWeapon.setTextureRect(IntRect(2, 934, 61, 56));
	shopWeapon.setPosition(330, 270);

	shopOrder.setTexture(textureUI); // 상점 주문
	shopOrder.setTextureRect(IntRect(69, 933, 58, 58));
	shopOrder.setPosition(411, 270);

	shopSupplies.setTexture(textureUI); // 상점 소모품
	shopSupplies.setTextureRect(IntRect(140, 931, 47, 62));
	shopSupplies.setPosition(499, 270);

	shopEquipment.setTexture(textureUI); // 상점 장비
	shopEquipment.setTextureRect(IntRect(206, 937, 45, 50));
	shopEquipment.setPosition(577, 275);

	shopCS.setTexture(textureUI); // 상점 커서
	shopCS.setTextureRect(IntRect(103, 1572, 79, 29));
	shopCS.setPosition(320, 328);

	textureSQ = TextureHolder::GetTexture("graphics/SQ.png");

	shopBuybox.setTexture(textureSQ); // 상점 구매칸
	shopBuybox.setTextureRect(IntRect(1021, 638, 346, 115));
	shopBuybox.setScale(Vector2f(0.6f, 0.7f));
	shopBuybox.setPosition(720, 132);

	shopSELLbox.setTexture(textureSQ); // 상점 판매칸
	shopSELLbox.setTextureRect(IntRect(1021, 638, 346, 115));
	shopSELLbox.setScale(Vector2f(0.6f, 0.7f));
	shopSELLbox.setPosition(940, 132);

	shopBTQbox.setTexture(textureUI); // 상점 버튼Q칸
	shopBTQbox.setTextureRect(IntRect(62, 605, 42, 40));
	shopBTQbox.setPosition(670, 172);

	shopBTWbox.setTexture(textureUI); // 상점 버튼W칸
	shopBTWbox.setTextureRect(IntRect(62, 605, 42, 40));
	shopBTWbox.setPosition(1155, 172);

	fontLostRuins.loadFromFile("fonts/LiberationSans-Regular.ttf");

	shopBTQ.setFont(fontLostRuins);
	shopBTW.setFont(fontLostRuins);
	shopBuyname.setFont(fontLostRuins);
	shopSELLname.setFont(fontLostRuins);

	shopBTQ.setString("Q");
	shopBTW.setString("W");
	shopBuyname.setString("BUY");
	shopSELLname.setString("SELL");

	shopBTQ.setCharacterSize(20);
	shopBTW.setCharacterSize(20);
	shopBuyname.setCharacterSize(33);
	shopSELLname.setCharacterSize(33);

	shopBTQ.setFillColor(Color::White);
	shopBTW.setFillColor(Color::White);
	shopBuyname.setFillColor(Color::White);
	shopSELLname.setFillColor(Color(255, 255, 255, 50));

	shopBTQ.setPosition(682, 178); //670, 172
	shopBTW.setPosition(1167, 180); //1155 172
	shopBuyname.setPosition(790, 150);
	shopSELLname.setPosition(1010, 150);
}

void TestUi::shopSell()
{
	textureIN = TextureHolder::GetTexture("graphics/inven make.png");
	Blur1 = TextureHolder::GetTexture("graphics/esc.png");
	fontLostRuins.loadFromFile("fonts/LiberationSans-Regular.ttf");

	shopsellname.setFont(fontLostRuins);
	shopsellname.setString("SHOP");
	shopsellname.setCharacterSize(30);
	shopsellname.setFillColor(Color::White);
	shopsellname.setPosition(1390, 230);

	SshopBlur.setTexture(Blur1); // inventory 블러처리된 배경
	SshopBlur.setTextureRect(IntRect(39, 2385, 1339, 887));
	SshopBlur.setScale(Vector2f(0.97f, 0.86f));
	SshopBlur.setPosition(299, 223); //280, 280

	SshopWindow.setTexture(textureIN); // 상점 창
	SshopWindow.setTextureRect(IntRect(39, 2385, 1339, 887));
	SshopWindow.setScale(Vector2f(1.0f, 0.9f));
	SshopWindow.setPosition(280, 205); //280, 280

	SshopWeapon.setTexture(textureUI); // 상점 무기
	SshopWeapon.setTextureRect(IntRect(2, 934, 61, 56));
	SshopWeapon.setPosition(330, 270);

	SshopOrder.setTexture(textureUI); // 상점 주문
	SshopOrder.setTextureRect(IntRect(69, 933, 58, 58));
	SshopOrder.setPosition(411, 270);

	SshopSupplies.setTexture(textureUI); // 상점 소모품
	SshopSupplies.setTextureRect(IntRect(140, 931, 47, 62));
	SshopSupplies.setPosition(499, 270);

	SshopEquipment.setTexture(textureUI); // 상점 장비
	SshopEquipment.setTextureRect(IntRect(206, 937, 45, 50));
	SshopEquipment.setPosition(577, 275);

	SshopCS.setTexture(textureUI); // 상점 커서
	SshopCS.setTextureRect(IntRect(103, 1571, 79, 30));
	SshopCS.setPosition(320, 328);

	textureSQ = TextureHolder::GetTexture("graphics/SQ.png");

	SshopBuybox.setTexture(textureSQ); // 상점 구매칸
	SshopBuybox.setTextureRect(IntRect(1021, 638, 346, 115));
	SshopBuybox.setScale(Vector2f(0.6f, 0.7f));
	SshopBuybox.setPosition(720, 132);

	SshopSELLbox.setTexture(textureSQ); // 상점 판매칸
	SshopSELLbox.setTextureRect(IntRect(1021, 638, 346, 115));
	SshopSELLbox.setScale(Vector2f(0.6f, 0.7f));
	SshopSELLbox.setPosition(940, 132);

	SshopBTQbox.setTexture(textureUI); // 상점 버튼Q칸
	SshopBTQbox.setTextureRect(IntRect(62, 605, 42, 40));
	SshopBTQbox.setPosition(670, 172);

	SshopBTWbox.setTexture(textureUI); // 상점 버튼W칸
	SshopBTWbox.setTextureRect(IntRect(62, 605, 42, 40));
	SshopBTWbox.setPosition(1155, 172);

	fontLostRuins.loadFromFile("fonts/LiberationSans-Regular.ttf");

	SshopBTQ.setFont(fontLostRuins);
	SshopBTW.setFont(fontLostRuins);
	SshopBuyname.setFont(fontLostRuins);
	SshopSELLname.setFont(fontLostRuins);

	SshopBTQ.setString("Q");
	SshopBTW.setString("W");
	SshopBuyname.setString("BUY");
	SshopSELLname.setString("SELL");

	SshopBTQ.setCharacterSize(20);
	SshopBTW.setCharacterSize(20);
	SshopBuyname.setCharacterSize(33);
	SshopSELLname.setCharacterSize(33);

	SshopBTQ.setFillColor(Color::White);
	SshopBTW.setFillColor(Color::White);
	SshopBuyname.setFillColor(Color(255, 255, 255, 50));
	SshopSELLname.setFillColor(Color::White);

	SshopBTQ.setPosition(682, 178); //670, 172
	SshopBTW.setPosition(1167, 180); //1155 172
	SshopBuyname.setPosition(790, 150);
	SshopSELLname.setPosition(1010, 150);
}

void TestUi::Buywea1()
{
	shopweaNum1 = 1;
	textureSQ = TextureHolder::GetTexture("graphics/SQ.png");
	fontLostRuins.loadFromFile("fonts/LiberationSans-Regular.ttf");
	weaponpng = TextureHolder::GetTexture("graphics/Weapon.png");

	textShopweapon1Lname.setFont(fontLostRuins); // 1. 리스트 내 아이템 이름
	textShopweapon1Lname.setString("Lightsaber     (50G)");
	textShopweapon1Lname.setCharacterSize(30);
	textShopweapon1Lname.setFillColor(Color(255, 0, 0, 255));
	textShopweapon1Lname.setPosition(380, 395);

	textShopweapon2name.setFont(fontLostRuins); // 2. 리스트 내 아이템 이름
	textShopweapon2name.setString("Torhammer    (800G)");
	textShopweapon2name.setCharacterSize(30);
	textShopweapon2name.setFillColor(Color(255, 0, 0, 100));
	textShopweapon2name.setPosition(380, 445);

	textShopweapon3name.setFont(fontLostRuins); // 3. 리스트 내 아이템 이름
	textShopweapon3name.setString("Devil arrow    (500G)");
	textShopweapon3name.setCharacterSize(30);
	textShopweapon3name.setFillColor(Color(255, 0, 0, 100));
	textShopweapon3name.setPosition(380, 495);

	textShopweapon4name.setFont(fontLostRuins); // 4. 리스트 내 아이템 이름
	textShopweapon4name.setString("God bow        (1000G)");
	textShopweapon4name.setCharacterSize(30);
	textShopweapon4name.setFillColor(Color(255, 0, 0, 100));
	textShopweapon4name.setPosition(380, 545);

	///////////////////////////////////////////////////////////////

	Shopweapon1Box.setTexture(textureSQ); // 우측 아이템 네모칸
	Shopweapon1Box.setTextureRect(IntRect(254, 673, 92, 96));
	Shopweapon1Box.setScale(Vector2f(1.0f, 1.0f));
	Shopweapon1Box.setPosition(980, 380);

	textShopweapon1Rname.setFont(fontLostRuins); // 우측 아이템 이름
	textShopweapon1Rname.setString("Lightsaber");
	textShopweapon1Rname.setCharacterSize(40);
	textShopweapon1Rname.setFillColor(Color(255, 0, 0, 255));
	textShopweapon1Rname.setPosition(1100, 400);

	Shopweapon1img.setTexture(weaponpng); // 우측 아이템 이미지
	Shopweapon1img.setTextureRect(IntRect(30, 148, 14, 53));
	Shopweapon1img.setScale(Vector2f(1.1f, 1.0f));
	Shopweapon1img.setPosition(1020, 400);

	Shopweapon1bk.setTexture(textureSQ); // 아이템 이미지 뒷 배경
	Shopweapon1bk.setTextureRect(IntRect(62, 605, 42, 40));
	Shopweapon1bk.setScale(Vector2f(2.2f, 2.4f));
	Shopweapon1bk.setPosition(980, 380);

	textShopweapon1text1.setFont(fontLostRuins);
	textShopweapon1text1.setString("Weapon type : One-handed");
	textShopweapon1text1.setCharacterSize(25);
	textShopweapon1text1.setFillColor(Color::White);
	textShopweapon1text1.setPosition(980, 520);

	textShopweapon1text2.setFont(fontLostRuins);
	textShopweapon1text2.setString("Attack Speed : Middle");
	textShopweapon1text2.setCharacterSize(25);
	textShopweapon1text2.setFillColor(Color::White);
	textShopweapon1text2.setPosition(980, 560);

	textShopweapon1text3.setFont(fontLostRuins);
	textShopweapon1text3.setString("Damage : Health -14");
	textShopweapon1text3.setCharacterSize(25);
	textShopweapon1text3.setFillColor(Color::White);
	textShopweapon1text3.setPosition(980, 600);
}

void TestUi::Buywea2()
{
	textureSQ = TextureHolder::GetTexture("graphics/SQ.png");
	fontLostRuins.loadFromFile("fonts/LiberationSans-Regular.ttf");
	weaponpng = TextureHolder::GetTexture("graphics/Weapon.png");

	textShopweapon1Lname.setFont(fontLostRuins); // 1. 리스트 내 아이템 이름
	textShopweapon1Lname.setString("Lightsaber     (50G)");
	textShopweapon1Lname.setCharacterSize(30);
	textShopweapon1Lname.setFillColor(Color(255, 0, 0, 100));
	textShopweapon1Lname.setPosition(380, 395);

	textShopweapon2name.setFont(fontLostRuins); // 2. 리스트 내 아이템 이름
	textShopweapon2name.setString("Torhammer    (800G)");
	textShopweapon2name.setCharacterSize(30);
	textShopweapon2name.setFillColor(Color(255, 0, 0, 255));
	textShopweapon2name.setPosition(380, 445);

	textShopweapon3name.setFont(fontLostRuins); // 3. 리스트 내 아이템 이름
	textShopweapon3name.setString("Devil arrow    (500G)");
	textShopweapon3name.setCharacterSize(30);
	textShopweapon3name.setFillColor(Color(255, 0, 0, 100));
	textShopweapon3name.setPosition(380, 495);

	textShopweapon4name.setFont(fontLostRuins); // 4. 리스트 내 아이템 이름
	textShopweapon4name.setString("God bow        (1000G)");
	textShopweapon4name.setCharacterSize(30);
	textShopweapon4name.setFillColor(Color(255, 0, 0, 100));
	textShopweapon4name.setPosition(380, 545);

	///////////////////////////////////////////////////////////////

	Shopweapon2Box.setTexture(textureSQ); // 우측 아이템 네모칸
	Shopweapon2Box.setTextureRect(IntRect(254, 673, 92, 96));
	Shopweapon2Box.setScale(Vector2f(1.0f, 1.0f));
	Shopweapon2Box.setPosition(980, 380);

	textShopweapon2Rname.setFont(fontLostRuins); // 우측 아이템 이름
	textShopweapon2Rname.setString("Torhammer");
	textShopweapon2Rname.setCharacterSize(40);
	textShopweapon2Rname.setFillColor(Color(255, 0, 0, 255));
	textShopweapon2Rname.setPosition(1100, 400);

	Shopweapon2img.setTexture(weaponpng); // 우측 아이템 이미지
	Shopweapon2img.setTextureRect(IntRect(90, 145, 20, 50));
	Shopweapon2img.setScale(Vector2f(1.1f, 1.0f));
	Shopweapon2img.setPosition(1017, 402);

	Shopweapon2bk.setTexture(textureSQ); // 아이템 이미지 뒷 배경
	Shopweapon2bk.setTextureRect(IntRect(62, 605, 42, 40));
	Shopweapon2bk.setScale(Vector2f(2.2f, 2.4f));
	Shopweapon2bk.setPosition(980, 380);

	textShopweapon2text1.setFont(fontLostRuins);
	textShopweapon2text1.setString("Weapon type : Two-handed");
	textShopweapon2text1.setCharacterSize(25);
	textShopweapon2text1.setFillColor(Color::White);
	textShopweapon2text1.setPosition(980, 520);

	textShopweapon2text2.setFont(fontLostRuins);
	textShopweapon2text2.setString("Attack Speed : Slow");
	textShopweapon2text2.setCharacterSize(25);
	textShopweapon2text2.setFillColor(Color::White);
	textShopweapon2text2.setPosition(980, 560);

	textShopweapon2text3.setFont(fontLostRuins);
	textShopweapon2text3.setString("Damage : Health -2");
	textShopweapon2text3.setCharacterSize(25);
	textShopweapon2text3.setFillColor(Color::White);
	textShopweapon2text3.setPosition(980, 600);
}

void TestUi::Buywea3()
{
	textureSQ = TextureHolder::GetTexture("graphics/SQ.png");
	fontLostRuins.loadFromFile("fonts/LiberationSans-Regular.ttf");
	weaponpng = TextureHolder::GetTexture("graphics/Weapon.png");

	textShopweapon1Lname.setFont(fontLostRuins); // 1. 리스트 내 아이템 이름
	textShopweapon1Lname.setString("Lightsaber     (50G)");
	textShopweapon1Lname.setCharacterSize(30);
	textShopweapon1Lname.setFillColor(Color(255, 0, 0, 100));
	textShopweapon1Lname.setPosition(380, 395);

	textShopweapon2name.setFont(fontLostRuins); // 2. 리스트 내 아이템 이름
	textShopweapon2name.setString("Torhammer    (800G)");
	textShopweapon2name.setCharacterSize(30);
	textShopweapon2name.setFillColor(Color(255, 0, 0, 100));
	textShopweapon2name.setPosition(380, 445);

	textShopweapon3name.setFont(fontLostRuins); // 3. 리스트 내 아이템 이름
	textShopweapon3name.setString("Devil arrow    (500G)");
	textShopweapon3name.setCharacterSize(30);
	textShopweapon3name.setFillColor(Color(255, 0, 0, 255));
	textShopweapon3name.setPosition(380, 495);

	textShopweapon4name.setFont(fontLostRuins); // 4. 리스트 내 아이템 이름
	textShopweapon4name.setString("God bow        (1000G)");
	textShopweapon4name.setCharacterSize(30);
	textShopweapon4name.setFillColor(Color(255, 0, 0, 100));
	textShopweapon4name.setPosition(380, 545);

	///////////////////////////////////////////////////////////////

	Shopweapon3Box.setTexture(textureSQ); // 우측 아이템 네모칸
	Shopweapon3Box.setTextureRect(IntRect(254, 673, 92, 96));
	Shopweapon3Box.setScale(Vector2f(1.0f, 1.0f));
	Shopweapon3Box.setPosition(980, 380);

	textShopweapon3Rname.setFont(fontLostRuins); // 우측 아이템 이름
	textShopweapon3Rname.setString("Devil arrow");
	textShopweapon3Rname.setCharacterSize(40);
	textShopweapon3Rname.setFillColor(Color(255, 0, 0, 255));
	textShopweapon3Rname.setPosition(1100, 400);

	Shopweapon3img.setTexture(weaponpng); // 우측 아이템 이미지
	Shopweapon3img.setTextureRect(IntRect(273, 464, 33, 39));
	Shopweapon3img.setScale(Vector2f(1.1f, 1.0f));
	Shopweapon3img.setPosition(1010, 408);

	Shopweapon3bk.setTexture(textureSQ); // 아이템 이미지 뒷 배경
	Shopweapon3bk.setTextureRect(IntRect(62, 605, 42, 40));
	Shopweapon3bk.setScale(Vector2f(2.2f, 2.4f));
	Shopweapon3bk.setPosition(980, 380);

	textShopweapon3text1.setFont(fontLostRuins);
	textShopweapon3text1.setString("Weapon type : ranged weapon");
	textShopweapon3text1.setCharacterSize(25);
	textShopweapon3text1.setFillColor(Color::White);
	textShopweapon3text1.setPosition(980, 520);

	textShopweapon3text2.setFont(fontLostRuins);
	textShopweapon3text2.setString("Attack Speed : Middle");
	textShopweapon3text2.setCharacterSize(25);
	textShopweapon3text2.setFillColor(Color::White);
	textShopweapon3text2.setPosition(980, 560);

	textShopweapon3text3.setFont(fontLostRuins);
	textShopweapon3text3.setString("Damage : Health -5");
	textShopweapon3text3.setCharacterSize(25);
	textShopweapon3text3.setFillColor(Color::White);
	textShopweapon3text3.setPosition(980, 600);
}

void TestUi::Buywea4()
{
	textureSQ = TextureHolder::GetTexture("graphics/SQ.png");
	fontLostRuins.loadFromFile("fonts/LiberationSans-Regular.ttf");
	weaponpng = TextureHolder::GetTexture("graphics/Weapon.png");

	textShopweapon1Lname.setFont(fontLostRuins); // 1. 리스트 내 아이템 이름
	textShopweapon1Lname.setString("Lightsaber     (50G)");
	textShopweapon1Lname.setCharacterSize(30);
	textShopweapon1Lname.setFillColor(Color(255, 0, 0, 100));
	textShopweapon1Lname.setPosition(380, 395);

	textShopweapon2name.setFont(fontLostRuins); // 2. 리스트 내 아이템 이름
	textShopweapon2name.setString("Torhammer    (800G)");
	textShopweapon2name.setCharacterSize(30);
	textShopweapon2name.setFillColor(Color(255, 0, 0, 100));
	textShopweapon2name.setPosition(380, 445);

	textShopweapon3name.setFont(fontLostRuins); // 3. 리스트 내 아이템 이름
	textShopweapon3name.setString("Devil arrow    (500G)");
	textShopweapon3name.setCharacterSize(30);
	textShopweapon3name.setFillColor(Color(255, 0, 0, 100));
	textShopweapon3name.setPosition(380, 495);

	textShopweapon4name.setFont(fontLostRuins); // 4. 리스트 내 아이템 이름
	textShopweapon4name.setString("God bow        (1000G)");
	textShopweapon4name.setCharacterSize(30);
	textShopweapon4name.setFillColor(Color(255, 0, 0, 255));
	textShopweapon4name.setPosition(380, 545);

	///////////////////////////////////////////////////////////////

	Shopweapon4Box.setTexture(textureSQ); // 우측 아이템 네모칸
	Shopweapon4Box.setTextureRect(IntRect(254, 673, 92, 96));
	Shopweapon4Box.setScale(Vector2f(1.0f, 1.0f));
	Shopweapon4Box.setPosition(980, 380);

	textShopweapon4Rname.setFont(fontLostRuins); // 우측 아이템 이름
	textShopweapon4Rname.setString("God bow");
	textShopweapon4Rname.setCharacterSize(40);
	textShopweapon4Rname.setFillColor(Color(255, 0, 0, 255));
	textShopweapon4Rname.setPosition(1100, 400);

	Shopweapon4img.setTexture(weaponpng); // 우측 아이템 이미지
	Shopweapon4img.setTextureRect(IntRect(515, 457, 11, 51));
	Shopweapon4img.setScale(Vector2f(1.1f, 1.0f));
	Shopweapon4img.setPosition(1022, 400);

	Shopweapon4bk.setTexture(textureSQ); // 아이템 이미지 뒷 배경
	Shopweapon4bk.setTextureRect(IntRect(62, 605, 42, 40));
	Shopweapon4bk.setScale(Vector2f(2.2f, 2.4f));
	Shopweapon4bk.setPosition(980, 380);

	textShopweapon4text1.setFont(fontLostRuins);
	textShopweapon4text1.setString("Weapon type : ranged weapon");
	textShopweapon4text1.setCharacterSize(25);
	textShopweapon4text1.setFillColor(Color::White);
	textShopweapon4text1.setPosition(980, 520);

	textShopweapon4text2.setFont(fontLostRuins);
	textShopweapon4text2.setString("Attack Speed : Fast");
	textShopweapon4text2.setCharacterSize(25);
	textShopweapon4text2.setFillColor(Color::White);
	textShopweapon4text2.setPosition(980, 560);

	textShopweapon4text3.setFont(fontLostRuins);
	textShopweapon4text3.setString("Damage : Health -9");
	textShopweapon4text3.setCharacterSize(25);
	textShopweapon4text3.setFillColor(Color::White);
	textShopweapon4text3.setPosition(980, 600);
}

void TestUi::Buyord1()
{
	shoporderNum1 = 1;
	textureSQ = TextureHolder::GetTexture("graphics/SQ.png");
	fontLostRuins.loadFromFile("fonts/LiberationSans-Regular.ttf");
	scrollpng = TextureHolder::GetTexture("graphics/Scroll.png");

	textShopord1Lname.setFont(fontLostRuins); // 1. 리스트 내 아이템 이름
	textShopord1Lname.setString("Devil spell	  (700G)");
	textShopord1Lname.setCharacterSize(30);
	textShopord1Lname.setFillColor(Color(51, 153, 255, 255));
	textShopord1Lname.setPosition(380, 395);

	textShopord2Lname.setFont(fontLostRuins); // 2. 리스트 내 아이템 이름
	textShopord2Lname.setString("White spell	 (300G)");
	textShopord2Lname.setCharacterSize(30);
	textShopord2Lname.setFillColor(Color(51, 153, 255, 100));
	textShopord2Lname.setPosition(380, 445);

	textShopord3Lname.setFont(fontLostRuins); // 2. 리스트 내 아이템 이름
	textShopord3Lname.setString("Nature spell	(150G)");
	textShopord3Lname.setCharacterSize(30);
	textShopord3Lname.setFillColor(Color(51, 153, 255, 100));
	textShopord3Lname.setPosition(380, 495);

	///////////////////////////////////////////////////////////////

	Shopord1Box.setTexture(textureSQ); // 1. 우측 아이템 네모칸
	Shopord1Box.setTextureRect(IntRect(254, 673, 92, 96));
	Shopord1Box.setScale(Vector2f(1.0f, 1.0f));
	Shopord1Box.setPosition(980, 380);

	textShopord1Rname.setFont(fontLostRuins); // 1. 우측 아이템 이름
	textShopord1Rname.setString("Devil spell");
	textShopord1Rname.setCharacterSize(40);
	textShopord1Rname.setFillColor(Color(51, 153, 255, 255));
	textShopord1Rname.setPosition(1100, 400);

	Shopord1img.setTexture(scrollpng); // 1. 우측 아이템 이미지
	Shopord1img.setTextureRect(IntRect(103, 158, 20, 22));
	Shopord1img.setScale(Vector2f(1.7f, 1.7f));
	Shopord1img.setPosition(1010, 410);

	Shopord1bk.setTexture(textureSQ); // 1. 우측 아이템 이미지 뒷배경
	Shopord1bk.setTextureRect(IntRect(62, 605, 42, 40));
	Shopord1bk.setScale(Vector2f(2.2f, 2.4f));
	Shopord1bk.setPosition(980, 380);

	textShopord1text1.setFont(fontLostRuins); // 1. 마법 타입
	textShopord1text1.setString("Spell type : Dark magic");
	textShopord1text1.setCharacterSize(25);
	textShopord1text1.setFillColor(Color::White);
	textShopord1text1.setPosition(980, 520);

	textShopord1text2.setFont(fontLostRuins); // 1. 공격속도
	textShopord1text2.setString("Attack style : Ranged magic");
	textShopord1text2.setCharacterSize(25);
	textShopord1text2.setFillColor(Color::White);
	textShopord1text2.setPosition(980, 560);

	textShopord1text3.setFont(fontLostRuins); // 1. 데미지
	textShopord1text3.setString("Magic damage : Health -4");
	textShopord1text3.setCharacterSize(25);
	textShopord1text3.setFillColor(Color::White);
	textShopord1text3.setPosition(980, 600);

}

void TestUi::Buyord2()
{
	textureSQ = TextureHolder::GetTexture("graphics/SQ.png");
	fontLostRuins.loadFromFile("fonts/LiberationSans-Regular.ttf");
	scrollpng = TextureHolder::GetTexture("graphics/Scroll.png");

	textShopord1Lname.setFont(fontLostRuins); // 1. 리스트 내 아이템 이름
	textShopord1Lname.setString("Devil spell	  (700G)");
	textShopord1Lname.setCharacterSize(30);
	textShopord1Lname.setFillColor(Color(51, 153, 255, 100));
	textShopord1Lname.setPosition(380, 395);

	textShopord2Lname.setFont(fontLostRuins); // 2. 리스트 내 아이템 이름
	textShopord2Lname.setString("White spell	 (300G)");
	textShopord2Lname.setCharacterSize(30);
	textShopord2Lname.setFillColor(Color(51, 153, 255, 255));
	textShopord2Lname.setPosition(380, 445);

	textShopord3Lname.setFont(fontLostRuins); // 2. 리스트 내 아이템 이름
	textShopord3Lname.setString("Nature spell	(150G)");
	textShopord3Lname.setCharacterSize(30);
	textShopord3Lname.setFillColor(Color(51, 153, 255, 100));
	textShopord3Lname.setPosition(380, 495);

	///////////////////////////////////////////////////////////////

	Shopord2Box.setTexture(textureSQ); // 1. 우측 아이템 네모칸
	Shopord2Box.setTextureRect(IntRect(254, 673, 92, 96));
	Shopord2Box.setScale(Vector2f(1.0f, 1.0f));
	Shopord2Box.setPosition(980, 380);

	textShopord2Rname.setFont(fontLostRuins); // 1. 우측 아이템 이름
	textShopord2Rname.setString("White spell");
	textShopord2Rname.setCharacterSize(40);
	textShopord2Rname.setFillColor(Color(51, 153, 255, 255));
	textShopord2Rname.setPosition(1100, 400);

	Shopord2img.setTexture(scrollpng); // 1. 우측 아이템 이미지
	Shopord2img.setTextureRect(IntRect(3, 185, 20, 22));
	Shopord2img.setScale(Vector2f(1.7f, 1.7f));
	Shopord2img.setPosition(1010, 410);

	Shopord2bk.setTexture(textureSQ); // 1. 우측 아이템 이미지 뒷배경
	Shopord2bk.setTextureRect(IntRect(62, 605, 42, 40));
	Shopord2bk.setScale(Vector2f(2.2f, 2.4f));
	Shopord2bk.setPosition(980, 380);

	textShopord2text1.setFont(fontLostRuins); // 1. 마법 타입
	textShopord2text1.setString("Spell type : White magic");
	textShopord2text1.setCharacterSize(25);
	textShopord2text1.setFillColor(Color::White);
	textShopord2text1.setPosition(980, 520);

	textShopord2text2.setFont(fontLostRuins); // 1. 공격속도
	textShopord2text2.setString("Hill style : Ranged magic");
	textShopord2text2.setCharacterSize(25);
	textShopord2text2.setFillColor(Color::White);
	textShopord2text2.setPosition(980, 560);

	textShopord2text3.setFont(fontLostRuins); // 1. 데미지
	textShopord2text3.setString("Hill : Health +20");
	textShopord2text3.setCharacterSize(25);
	textShopord2text3.setFillColor(Color::White);
	textShopord2text3.setPosition(980, 600);
}

void TestUi::Buyord3()
{
	textureSQ = TextureHolder::GetTexture("graphics/SQ.png");
	fontLostRuins.loadFromFile("fonts/LiberationSans-Regular.ttf");
	scrollpng = TextureHolder::GetTexture("graphics/Scroll.png");

	textShopord1Lname.setFont(fontLostRuins); // 1. 리스트 내 아이템 이름
	textShopord1Lname.setString("Devil spell	  (700G)");
	textShopord1Lname.setCharacterSize(30);
	textShopord1Lname.setFillColor(Color(51, 153, 255, 100));
	textShopord1Lname.setPosition(380, 395);

	textShopord2Lname.setFont(fontLostRuins); // 2. 리스트 내 아이템 이름
	textShopord2Lname.setString("White spell	 (300G)");
	textShopord2Lname.setCharacterSize(30);
	textShopord2Lname.setFillColor(Color(51, 153, 255, 100));
	textShopord2Lname.setPosition(380, 445);

	textShopord3Lname.setFont(fontLostRuins); // 2. 리스트 내 아이템 이름
	textShopord3Lname.setString("Nature spell	(150G)");
	textShopord3Lname.setCharacterSize(30);
	textShopord3Lname.setFillColor(Color(51, 153, 255, 255));
	textShopord3Lname.setPosition(380, 495);

	///////////////////////////////////////////////////////////////

	Shopord3Box.setTexture(textureSQ); // 1. 우측 아이템 네모칸
	Shopord3Box.setTextureRect(IntRect(254, 673, 92, 96));
	Shopord3Box.setScale(Vector2f(1.0f, 1.0f));
	Shopord3Box.setPosition(980, 380);

	textShopord3Rname.setFont(fontLostRuins); // 1. 우측 아이템 이름
	textShopord3Rname.setString("Nature spell");
	textShopord3Rname.setCharacterSize(40);
	textShopord3Rname.setFillColor(Color(51, 153, 255, 255));
	textShopord3Rname.setPosition(1100, 400);

	Shopord3img.setTexture(scrollpng); // 1. 우측 아이템 이미지
	Shopord3img.setTextureRect(IntRect(203, 158, 20, 22));
	Shopord3img.setScale(Vector2f(1.7f, 1.7f));
	Shopord3img.setPosition(1010, 410);

	Shopord3bk.setTexture(textureSQ); // 1. 우측 아이템 이미지 뒷배경
	Shopord3bk.setTextureRect(IntRect(62, 605, 42, 40));
	Shopord3bk.setScale(Vector2f(2.2f, 2.4f));
	Shopord3bk.setPosition(980, 380);

	textShopord3text1.setFont(fontLostRuins); // 1. 마법 타입
	textShopord3text1.setString("Spell type : Hill magic");
	textShopord3text1.setCharacterSize(25);
	textShopord3text1.setFillColor(Color::White);
	textShopord3text1.setPosition(980, 520);

	textShopord3text2.setFont(fontLostRuins); // 1. 공격속도
	textShopord3text2.setString("Attack style : Ranged magic");
	textShopord3text2.setCharacterSize(25);
	textShopord3text2.setFillColor(Color::White);
	textShopord3text2.setPosition(980, 560);

	textShopord3text3.setFont(fontLostRuins); // 1. 데미지
	textShopord3text3.setString("Damage : Health +10");
	textShopord3text3.setCharacterSize(25);
	textShopord3text3.setFillColor(Color::White);
	textShopord3text3.setPosition(980, 600);
}

void TestUi::Buysup1()
{
	shopSupNum1 = 1;
	textureSQ = TextureHolder::GetTexture("graphics/SQ.png");
	fontLostRuins.loadFromFile("fonts/LiberationSans-Regular.ttf");
	scrollpng = TextureHolder::GetTexture("graphics/Scroll.png");

	textShopsup1Lname.setFont(fontLostRuins); // 1. 리스트 내 아이템 이름
	textShopsup1Lname.setString("Red potion		(20G)");
	textShopsup1Lname.setCharacterSize(30);
	textShopsup1Lname.setFillColor(Color(0, 204, 0, 255));
	textShopsup1Lname.setPosition(380, 395);

	textShopsup2name.setFont(fontLostRuins); // 2. 리스트 내 아이템 이름
	textShopsup2name.setString("Blue potion		(20G)");
	textShopsup2name.setCharacterSize(30);
	textShopsup2name.setFillColor(Color(0, 204, 0, 100));
	textShopsup2name.setPosition(380, 445);

	///////////////////////////////////////////////////////////////

	Shopsup1Box.setTexture(textureSQ); // 1. 우측 아이템 네모칸
	Shopsup1Box.setTextureRect(IntRect(254, 673, 92, 96));
	Shopsup1Box.setScale(Vector2f(1.0f, 1.0f));
	Shopsup1Box.setPosition(980, 380);

	textShopsup1Rname.setFont(fontLostRuins); // 1. 우측 아이템 이름
	textShopsup1Rname.setString("Red potion");
	textShopsup1Rname.setCharacterSize(40);
	textShopsup1Rname.setFillColor(Color(0, 204, 0, 255));
	textShopsup1Rname.setPosition(1100, 400);

	Shopsup1img.setTexture(scrollpng); // 1. 우측 아이템 이미지
	Shopsup1img.setTextureRect(IntRect(56, 425, 9, 12));
	Shopsup1img.setScale(Vector2f(3.0f, 3.0f));
	Shopsup1img.setPosition(1013, 410);

	Shopsup1bk.setTexture(textureSQ); // 1. 우측 아이템 이미지 뒷배경
	Shopsup1bk.setTextureRect(IntRect(62, 605, 42, 40));
	Shopsup1bk.setScale(Vector2f(2.2f, 2.4f));
	Shopsup1bk.setPosition(980, 380);

	textShopsup1text1.setFont(fontLostRuins); // 1. 마법 타입
	textShopsup1text1.setString("Sup type : Liquid medicine");
	textShopsup1text1.setCharacterSize(25);
	textShopsup1text1.setFillColor(Color::White);
	textShopsup1text1.setPosition(980, 520);

	textShopsup1text2.setFont(fontLostRuins); // 1. 공격속도
	textShopsup1text2.setString("Drink Speed : Immediately");
	textShopsup1text2.setCharacterSize(25);
	textShopsup1text2.setFillColor(Color::White);
	textShopsup1text2.setPosition(980, 560);

	textShopsup1text3.setFont(fontLostRuins); // 1. 데미지
	textShopsup1text3.setString("Hill : Physical +50");
	textShopsup1text3.setCharacterSize(25);
	textShopsup1text3.setFillColor(Color::White);
	textShopsup1text3.setPosition(980, 600);
}

void TestUi::Buysup2()
{
	textureSQ = TextureHolder::GetTexture("graphics/SQ.png");
	fontLostRuins.loadFromFile("fonts/LiberationSans-Regular.ttf");
	scrollpng = TextureHolder::GetTexture("graphics/Scroll.png");

	textShopsup1Lname.setFont(fontLostRuins); // 1. 리스트 내 아이템 이름
	textShopsup1Lname.setString("Red potion		(20G)");
	textShopsup1Lname.setCharacterSize(30);
	textShopsup1Lname.setFillColor(Color(0, 204, 0, 100));
	textShopsup1Lname.setPosition(380, 395);

	textShopsup2name.setFont(fontLostRuins); // 2. 리스트 내 아이템 이름
	textShopsup2name.setString("Blue potion		(20G)");
	textShopsup2name.setCharacterSize(30);
	textShopsup2name.setFillColor(Color(0, 204, 0, 255));
	textShopsup2name.setPosition(380, 445);

	///////////////////////////////////////////////////////////////

	Shopsup2Box.setTexture(textureSQ); // 1. 우측 아이템 네모칸
	Shopsup2Box.setTextureRect(IntRect(254, 673, 92, 96));
	Shopsup2Box.setScale(Vector2f(1.0f, 1.0f));
	Shopsup2Box.setPosition(980, 380);

	textShopsup2Rname.setFont(fontLostRuins); // 1. 우측 아이템 이름
	textShopsup2Rname.setString("Blue potion");
	textShopsup2Rname.setCharacterSize(40);
	textShopsup2Rname.setFillColor(Color(0, 204, 0, 255));
	textShopsup2Rname.setPosition(1100, 400);

	Shopsup2img.setTexture(scrollpng); // 1. 우측 아이템 이미지
	Shopsup2img.setTextureRect(IntRect(73, 425, 9, 12));
	Shopsup2img.setScale(Vector2f(3.0f, 3.0f));
	Shopsup2img.setPosition(1013, 410);

	Shopsup2bk.setTexture(textureSQ); // 1. 우측 아이템 이미지 뒷배경
	Shopsup2bk.setTextureRect(IntRect(62, 605, 42, 40));
	Shopsup2bk.setScale(Vector2f(2.2f, 2.4f));
	Shopsup2bk.setPosition(980, 380);

	textShopsup2text1.setFont(fontLostRuins); // 1. 마법 타입
	textShopsup2text1.setString("Sup type : Liquid medicine");
	textShopsup2text1.setCharacterSize(25);
	textShopsup2text1.setFillColor(Color::White);
	textShopsup2text1.setPosition(980, 520);

	textShopsup2text2.setFont(fontLostRuins); // 1. 공격속도
	textShopsup2text2.setString("Drink Speed : Immediately");
	textShopsup2text2.setCharacterSize(25);
	textShopsup2text2.setFillColor(Color::White);
	textShopsup2text2.setPosition(980, 560);

	textShopsup2text3.setFont(fontLostRuins); // 1. 데미지
	textShopsup2text3.setString("Hill : Mana +5");
	textShopsup2text3.setCharacterSize(25);
	textShopsup2text3.setFillColor(Color::White);
	textShopsup2text3.setPosition(980, 600);
}

void TestUi::Buyequ1()
{
	shopEquNum1 = 1;
	textureSQ = TextureHolder::GetTexture("graphics/SQ.png");
	fontLostRuins.loadFromFile("fonts/LiberationSans-Regular.ttf");
	scrollpng = TextureHolder::GetTexture("graphics/Scroll.png");

	textShopequ1Lname.setFont(fontLostRuins); // 1. 리스트 내 아이템 이름
	textShopequ1Lname.setString("Maid clothes	(10000G)");
	textShopequ1Lname.setCharacterSize(30);
	textShopequ1Lname.setFillColor(Color(255, 128, 0, 255));
	textShopequ1Lname.setPosition(380, 395);

	textShopequ2Lname.setFont(fontLostRuins); // 2. 리스트 내 아이템 이름
	textShopequ2Lname.setString("Wind boots		(3000G)");
	textShopequ2Lname.setCharacterSize(30);
	textShopequ2Lname.setFillColor(Color(255, 128, 0, 100));
	textShopequ2Lname.setPosition(380, 445);

	///////////////////////////////////////////////////////////////

	Shopequ1Box.setTexture(textureSQ); // 1. 우측 아이템 네모칸
	Shopequ1Box.setTextureRect(IntRect(254, 673, 92, 96));
	Shopequ1Box.setScale(Vector2f(1.0f, 1.0f));
	Shopequ1Box.setPosition(980, 380);

	textShopequ1Rname.setFont(fontLostRuins); // 1. 우측 아이템 이름
	textShopequ1Rname.setString("Maid clothes");
	textShopequ1Rname.setCharacterSize(40);
	textShopequ1Rname.setFillColor(Color(255, 128, 0, 255));
	textShopequ1Rname.setPosition(1100, 400);

	Shopequ1img.setTexture(scrollpng); // 1. 우측 아이템 이미지
	Shopequ1img.setTextureRect(IntRect(26, 295, 18, 23));
	Shopequ1img.setScale(Vector2f(1.7f, 1.7f));
	Shopequ1img.setPosition(1011, 409);

	Shopequ1bk.setTexture(textureSQ); // 1. 우측 아이템 이미지 뒷배경
	Shopequ1bk.setTextureRect(IntRect(62, 605, 42, 40));
	Shopequ1bk.setScale(Vector2f(2.2f, 2.4f));
	Shopequ1bk.setPosition(980, 380);

	textShopequ1text1.setFont(fontLostRuins); // 1. 마법 타입
	textShopequ1text1.setString("Equ type : Body equipment");
	textShopequ1text1.setCharacterSize(25);
	textShopequ1text1.setFillColor(Color::White);
	textShopequ1text1.setPosition(980, 520);

	textShopequ1text2.setFont(fontLostRuins); // 1. 공격속도
	textShopequ1text2.setString("Texture : Cloth");
	textShopequ1text2.setCharacterSize(25);
	textShopequ1text2.setFillColor(Color::White);
	textShopequ1text2.setPosition(980, 560);

	textShopequ1text3.setFont(fontLostRuins); // 1. 데미지
	textShopequ1text3.setString("Defense : +50");
	textShopequ1text3.setCharacterSize(25);
	textShopequ1text3.setFillColor(Color::White);
	textShopequ1text3.setPosition(980, 600);
}

void TestUi::Buyequ2()
{
	textureSQ = TextureHolder::GetTexture("graphics/SQ.png");
	fontLostRuins.loadFromFile("fonts/LiberationSans-Regular.ttf");
	scrollpng = TextureHolder::GetTexture("graphics/Scroll.png");

	textShopequ1Lname.setFont(fontLostRuins); // 1. 리스트 내 아이템 이름
	textShopequ1Lname.setString("Maid clothes	(10000G)");
	textShopequ1Lname.setCharacterSize(30);
	textShopequ1Lname.setFillColor(Color(255, 128, 0, 100));
	textShopequ1Lname.setPosition(380, 395);

	textShopequ2Lname.setFont(fontLostRuins); // 2. 리스트 내 아이템 이름
	textShopequ2Lname.setString("Wind boots		(3000G)");
	textShopequ2Lname.setCharacterSize(30);
	textShopequ2Lname.setFillColor(Color(255, 128, 0, 255));
	textShopequ2Lname.setPosition(380, 445);

	///////////////////////////////////////////////////////////////

	Shopequ2Box.setTexture(textureSQ); // 1. 우측 아이템 네모칸
	Shopequ2Box.setTextureRect(IntRect(254, 673, 92, 96));
	Shopequ2Box.setScale(Vector2f(1.0f, 1.0f));
	Shopequ2Box.setPosition(980, 380);

	textShopequ2Rname.setFont(fontLostRuins); // 1. 우측 아이템 이름
	textShopequ2Rname.setString("Wind boots");
	textShopequ2Rname.setCharacterSize(40);
	textShopequ2Rname.setFillColor(Color(255, 128, 0, 255));
	textShopequ2Rname.setPosition(1100, 400);

	Shopequ2img.setTexture(scrollpng); // 1. 우측 아이템 이미지
	Shopequ2img.setTextureRect(IntRect(71, 328, 14, 14));
	Shopequ2img.setScale(Vector2f(2.0f, 2.0f));
	Shopequ2img.setPosition(1012, 412);

	Shopequ2bk.setTexture(textureSQ); // 1. 우측 아이템 이미지 뒷배경
	Shopequ2bk.setTextureRect(IntRect(62, 605, 42, 40));
	Shopequ2bk.setScale(Vector2f(2.2f, 2.4f));
	Shopequ2bk.setPosition(980, 380);

	textShopequ2text1.setFont(fontLostRuins); // 1. 마법 타입
	textShopequ2text1.setString("Equ type : Foot equipment");
	textShopequ2text1.setCharacterSize(25);
	textShopequ2text1.setFillColor(Color::White);
	textShopequ2text1.setPosition(980, 520);

	textShopequ2text2.setFont(fontLostRuins); // 1. 공격속도
	textShopequ2text2.setString("Texture : Cloth");
	textShopequ2text2.setCharacterSize(25);
	textShopequ2text2.setFillColor(Color::White);
	textShopequ2text2.setPosition(980, 560);

	textShopequ2text3.setFont(fontLostRuins); // 1. 데미지
	textShopequ2text3.setString("Speed : +20");
	textShopequ2text3.setCharacterSize(25);
	textShopequ2text3.setFillColor(Color::White);
	textShopequ2text3.setPosition(980, 600);
}