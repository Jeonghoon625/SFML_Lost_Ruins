#include "Dagger.h"

Dagger::Dagger(float xpos, float ypos, float angle)
{
	position = Vector2f(xpos, ypos);
	rotation = angle;

	spriteWeapon.setTexture(TextureHolder::GetTexture("graphics/weapon.png"));
	spriteWeapon.setTextureRect(IntRect(3, 17, 4, 25));
	spriteWeapon.setOrigin(2.f, 25.f);
	spriteWeapon.setScale(scale);

	spriteWeapon.setPosition(position);
	spriteWeapon.setRotation(rotation);
}

void Dagger::SetPosition(Sprite sprite)
{
	float xpos = 0.f;
	float ypos = 0.f;

	if (sprite.getScale().x > 0.f)
	{
		xpos = sprite.getGlobalBounds().left + position.x;
		spriteWeapon.setScale(scale);
		spriteWeapon.setRotation(rotation);
	}
	else if (sprite.getScale().x < 0.f)
	{
		xpos = sprite.getGlobalBounds().left + sprite.getGlobalBounds().width - position.x;
		spriteWeapon.setScale(scaleFlipX);
		spriteWeapon.setRotation(rotation * -1.f);
	}
	ypos = sprite.getGlobalBounds().top + position.y;
	spriteWeapon.setPosition(Vector2f(xpos, ypos));
}

const Sprite Dagger::GetSprite()
{
	return spriteWeapon;
}

const Vector2f Dagger::GetPosition()
{
	return position;
}

const float Dagger::GetRotation()
{
	return rotation;
}
