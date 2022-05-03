#include "TestSceneUi.h"

void TestUi::Init(SceneManager* sceneManager)
{
	this->sceneMgr = sceneManager;

	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

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
	ButtonX.setPosition(1870, 60); // 1820, 10

	ButtonZ.setTexture(textureUI);
	ButtonZ.setTextureRect(IntRect(62, 605, 42, 40));
	ButtonZ.setPosition(1780, 60); // 1730, 10

	ButtonS.setTexture(textureUI);
	ButtonS.setTextureRect(IntRect(62, 605, 42, 40));
	ButtonS.setPosition(1680, 10); // 1630, 10

	ButtonA.setTexture(textureUI);
	ButtonA.setTextureRect(IntRect(62, 605, 42, 40));
	ButtonA.setPosition(1590, 10); // 1540, 10

	Invenwindow.setTexture(textureUI);
	Invenwindow.setTextureRect(IntRect(1, 1068, 256, 256));
	//Invenwindow.setScale(Vector2f(2.0f, 2.0f));
	Invenwindow.setPosition(500, 500);
}

void TestUi::Update(float dt, Time playTime, RenderWindow* window, View* mainView)
{
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

	window->draw(Invenwindow);
}
