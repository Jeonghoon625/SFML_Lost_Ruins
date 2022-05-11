#include "DamageAndRecovery.h"


DamageAndRecovery::DamageAndRecovery()
	: speed(MASSAGE_SPEED), isActive(false)
{
	fontLostRuins.loadFromFile("fonts/LiberationSans-Bold.ttf");
	textDorR.setFont(fontLostRuins);
	textDorR.setCharacterSize(30);
}

void DamageAndRecovery::SetActive(bool active)
{
	isActive = active;
}

bool DamageAndRecovery::IsActive()
{
	return isActive;
}

void DamageAndRecovery::HitPlayer(Vector2f pos, int damage)
{
	SetActive(true);
	distance = 0.f;
	postion = pos;

	std::stringstream isDamage;
	isDamage << "-" << damage;
	textDorR.setString(isDamage.str());
	Utils::SetOrigin(textDorR, Pivots::CC);
	textDorR.setFillColor(Color::Red);
	textDorR.setPosition(postion);
}

void DamageAndRecovery::Stop()
{
	SetActive(false);
}

void DamageAndRecovery::Update(float dt)
{
	postion.y -= speed * dt;
	textDorR.setPosition(postion);

	distance += speed * dt;
	if (distance > DEFAULT_DISTANCE)
	{
		Stop();
	}
}

Text DamageAndRecovery::GetText()
{
	return textDorR;
}