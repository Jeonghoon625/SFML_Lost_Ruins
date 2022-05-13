#include "LamiEye.h"

LamiEye::LamiEye()
{
}

void LamiEye::Init(Vector2f pos, int eyeSide, Sprite& sprite)
{
	this->eyeSide = eyeSide;
	spriteEye.setTexture(TextureHolder::GetTexture("graphics/Eye.png"));
	spriteEye.setOrigin(spriteEye.getTextureRect().width * 0.5f, spriteEye.getTextureRect().height * 0.5f);
	
	spriteSclera.setTexture(TextureHolder::GetTexture("graphics/Sclera.png"));
	spriteSclera.setOrigin(spriteSclera.getTextureRect().width * 0.5f, spriteSclera.getTextureRect().height * 0.5f);


	if (eyeSide == 0)
	{
		spriteEye.setPosition(sprite.getGlobalBounds().left + (49.f), sprite.getGlobalBounds().top + (52.f));
		spriteSclera.setPosition(sprite.getGlobalBounds().left + (49.0f), sprite.getGlobalBounds().top + (52.f));
	}
	
	

}

void LamiEye::Update()
{
}

void LamiEye::Draw()
{
}
