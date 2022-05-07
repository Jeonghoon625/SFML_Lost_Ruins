#include "TwohandWeapon.h"

TwohandWeapon::TwohandWeapon(float xpos, float ypos, float angle)
{
	position = Vector2f(xpos, ypos);
	rotation = angle;

	spriteWeapon.setTexture(TextureHolder::GetTexture("graphics/weapon.png"));
	spriteWeapon.setTextureRect(IntRect(13, 148, 14, 53));
	spriteWeapon.setOrigin(7.f, 53.f);
	spriteWeapon.setScale(3.f, 3.f);

	spriteWeapon.setPosition(position);
	spriteWeapon.setRotation(rotation);
}

void TwohandWeapon::SetPosition(Sprite sprite)
{
	float xpos = 0.f;
	float ypos = 0.f;

	if (sprite.getScale().x > 0.f)
	{
		xpos = sprite.getGlobalBounds().left + position.x;
		spriteWeapon.setRotation(rotation);

	}
	else if (sprite.getScale().x < 0.f)
	{
		xpos = sprite.getGlobalBounds().left + sprite.getGlobalBounds().width - position.x;
		spriteWeapon.setRotation(rotation * -1.f);
	}
	ypos = sprite.getGlobalBounds().top + position.y;
	spriteWeapon.setPosition(Vector2f(xpos, ypos));
}

const Sprite TwohandWeapon::GetSprite()
{
	return spriteWeapon;
}

const Vector2f TwohandWeapon::GetPosition()
{
	return position;
}

const float TwohandWeapon::GetRotation()
{
	return rotation;
}
