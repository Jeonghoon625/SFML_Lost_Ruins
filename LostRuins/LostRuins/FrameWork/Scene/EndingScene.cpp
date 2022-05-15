#include "EndingScene.h"
#include "../Mgr/SceneManager.h"

void EndingScene::Init(SceneManager* sceneManager)
{
	this->sceneMgr = sceneManager;

	endingRoll = ENDING_ROLL_TIME;
	speed = ENDING_ROLL_SPEED;
	resolution.x = 1920.f;
	resolution.y = 1080.f;
	stop = false;

	position = Vector2f(resolution.x * 0.71f, resolution.y + 20.f);

	spriteIllust.setTexture(TextureHolder::GetTexture("graphics/ending.png"));
	spriteIllust.setTextureRect(IntRect(3238, 30, 1200, 1800));
	spriteIllust.setScale(0.6f, 0.6f);
	spriteIllust.setPosition(0.f, 0.f);

	fontLostRuins.loadFromFile("fonts/LiberationSans-Bold.ttf");

	endingStr1.setFont(fontLostRuins);
	endingStr1.setString("Advisor");
	endingStr1.setFillColor(Color::White);
	endingStr1.setCharacterSize(80);
	endingStr1.setPosition(position.x, position.y);
	Utils::SetOrigin(endingStr1, Pivots::CC);

	advisor.setFont(fontLostRuins);
	advisor.setString("Oh Jun Hwan");
	advisor.setFillColor(Color::White);
	advisor.setCharacterSize(40);
	advisor.setPosition(position.x, position.y + 200.f);
	Utils::SetOrigin(advisor, Pivots::CC);

	endingStr2.setFont(fontLostRuins);
	endingStr2.setString("Programmers");
	endingStr2.setFillColor(Color::White);
	endingStr2.setCharacterSize(80);
	endingStr2.setPosition(position.x, position.y + 800.f);
	Utils::SetOrigin(endingStr2, Pivots::CC);

	member1.setFont(fontLostRuins);
	member1.setString("Kim Jeong Hoon");
	member1.setFillColor(Color::White);
	member1.setCharacterSize(40);
	member1.setPosition(position.x, position.y + 1000.f);
	Utils::SetOrigin(member1, Pivots::CC);

	member2.setFont(fontLostRuins);
	member2.setString("Kong Kyu");
	member2.setFillColor(Color::White);
	member2.setCharacterSize(40);
	member2.setPosition(position.x, position.y + 1150.f);
	Utils::SetOrigin(member2, Pivots::CC);

	member3.setFont(fontLostRuins);
	member3.setString("Lee Jee Woo");
	member3.setFillColor(Color::White);
	member3.setCharacterSize(40);
	member3.setPosition(position.x, position.y + 1300.f);
	Utils::SetOrigin(member3, Pivots::CC);

	member4.setFont(fontLostRuins);
	member4.setString("Lee Min Hyeong");
	member4.setFillColor(Color::White);
	member4.setCharacterSize(40);
	member4.setPosition(position.x, position.y + 1450.f);
	Utils::SetOrigin(member4, Pivots::CC);

	endingStr3.setFont(fontLostRuins);
	endingStr3.setString("See you on the next Project");
	endingStr3.setFillColor(Color::White);
	endingStr3.setCharacterSize(60);
	endingStr3.setPosition(position.x, position.y + 2300.f);
	Utils::SetOrigin(endingStr3, Pivots::CC);

	skipEnding.setFont(fontLostRuins);
	skipEnding.setString("Skip : Space Bar");
	skipEnding.setFillColor(Color::White);
	skipEnding.setCharacterSize(25);
	skipEnding.setPosition(resolution.x - 250.f, resolution.y - 50.f);
	Utils::SetOrigin(member4, Pivots::CC);

	soundEnding.setBuffer(SoundHolder::GetBuffer("sound/12555450_MotionElements_upbeat-deephouse-loopable.wav"));
	soundEnding.play();
}

void EndingScene::Update(float dt, Time playTime, RenderWindow* window, View* mainView, View* uiView)
{
	endingRoll -= dt;

	if (stop == false)
	{
		position.y -= speed * dt;

		endingStr1.setPosition(position.x, position.y);
		advisor.setPosition(position.x, position.y + 200.f);
		endingStr2.setPosition(position.x, position.y + 800.f);
		member1.setPosition(position.x, position.y + 1000.f);
		member2.setPosition(position.x, position.y + 1150.f);
		member3.setPosition(position.x, position.y + 1300.f);
		member4.setPosition(position.x, position.y + 1450.f);
		endingStr3.setPosition(position.x, position.y + 2300.f);
	}

	if (endingStr3.getPosition().y < resolution.y * 0.5f)
	{
		stop = true;
		endingStr3.setPosition(position.x, resolution.y * 0.5f);
	}

	if (endingRoll < 0.f || InputManager::GetKeyDown(Keyboard::Space))
	{
		sceneMgr->SceneSwitch(SceneType::TITLE);
	}
}

void EndingScene::Draw(RenderWindow* window, View* mainView, View* uiView)
{
	window->draw(spriteIllust);
	window->draw(endingStr1);
	window->draw(advisor);
	window->draw(endingStr2);
	window->draw(member1);
	window->draw(member2);
	window->draw(member3);
	window->draw(member4);
	window->draw(endingStr3);
	window->draw(skipEnding);
}

EndingScene::~EndingScene()
{

}
