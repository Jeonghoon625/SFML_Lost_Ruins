#include "TestSceneUi.h"

void TestUi::Init(SceneManager* sceneManager)
{
	this->sceneMgr = sceneManager;

	resolution.x = VideoMode::getDesktopMode().width; //1920
	resolution.y = VideoMode::getDesktopMode().height; //1080

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

	textureIN = TextureHolder::GetTexture("graphics/inven make.png");

	Invenwindow.setTexture(textureIN); // 인벤토리 창
	Invenwindow.setTextureRect(IntRect(39, 2385, 1339, 887));
	Invenwindow.setScale(Vector2f(1.0f, 0.9f));
	Invenwindow.setPosition(280, 205); //280, 280

	InvenWeapon.setTexture(textureUI); // 인벤토리 무기
	InvenWeapon.setTextureRect(IntRect(2, 934, 61, 56));	
	InvenWeapon.setPosition(330, 270);

	InvenOrder.setTexture(textureUI); // 인벤토리 주문
	InvenOrder.setTextureRect(IntRect(69, 933, 58, 58));
	InvenOrder.setPosition(410, 270);

	InvenSupplies.setTexture(textureUI); // 인벤토리 소모품
	InvenSupplies.setTextureRect(IntRect(140, 931, 47, 62));
	InvenSupplies.setPosition(490, 270);

	InvenEquipment.setTexture(textureUI); // 인벤토리 장비
	InvenEquipment.setTextureRect(IntRect(206, 937, 45, 50));
	InvenEquipment.setPosition(570, 270);

	InvenRelic.setTexture(textureUI); // 인벤토리 유물
	InvenRelic.setTextureRect(IntRect(267, 937, 52, 51));
	InvenRelic.setPosition(650, 270);

	InvenRecord.setTexture(textureUI); // 인벤토리 기록
	InvenRecord.setTextureRect(IntRect(337, 936, 43, 53));
	InvenRecord.setPosition(730, 270);

	InvenKey.setTexture(textureUI); // 인벤토리 열쇠
	InvenKey.setTextureRect(IntRect(408, 933, 31, 59));
	InvenKey.setPosition(810, 270);

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

	//ui.UiPlayInit();
	
	//텍스트//

	fontLostRuins.loadFromFile("fonts/LiberationSans-Regular.ttf");

	// 폰트설정
	textHPbar.setFont(fontLostRuins);
	textMPbar.setFont(fontLostRuins);
	textInvenname.setFont(fontLostRuins);
	textInvenMap.setFont(fontLostRuins);
	textInvenBtQ.setFont(fontLostRuins);
	textInvenBtW.setFont(fontLostRuins);

	//string
	textHPbar.setString("20/20");
	textMPbar.setString("20/20");
	textInvenname.setString("TAB");
	textInvenMap.setString("M");
	textInvenBtQ.setString("Q");
	textInvenBtW.setString("E");

	//CharacterSize
	textHPbar.setCharacterSize(10);
	textMPbar.setCharacterSize(10);
	textInvenname.setCharacterSize(10);
	textInvenMap.setCharacterSize(10);
	textInvenBtQ.setCharacterSize(10);
	textInvenBtW.setCharacterSize(10);

	//Color
	textHPbar.setFillColor(Color::White);
	textMPbar.setFillColor(Color::White);
	textInvenname.setFillColor(Color::White);
	textInvenMap.setFillColor(Color::White);
	textInvenBtQ.setFillColor(Color::White);
	textInvenBtW.setFillColor(Color::White);

	//Position
	textHPbar.setPosition(18, 18);

}

void TestUi::Update(float dt, Time playTime, RenderWindow* window, View* mainView)
{
	//ui.UiPlayUpdate();
}

void TestUi::Draw(RenderWindow* window, View* mainView)
{
	window->draw(HPbarLine);
	window->draw(HPbar);
	window->draw(MPbarLine);
	window->draw(MPbar);

	window->draw(BossHPbarLine);
	window->draw(BossHPbar);

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

	window->draw(Invenwindow); // 인벤토리 창
	window->draw(InvenWeapon); // 인벤토리 무기
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

	//ui.UiPlayDraw(*window);

	window->draw(textHPbar);
	/*window->draw(textMPbar);
	window->draw(textInvenname);
	window->draw(textInvenMap);
	window->draw(textInvenBtQ);
	window->draw(textInvenBtW);*/


}