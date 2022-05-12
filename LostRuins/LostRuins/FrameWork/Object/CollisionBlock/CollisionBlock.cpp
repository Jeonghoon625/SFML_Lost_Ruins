#include "CollisionBlock.h"
#include <iostream>

CollisionBlock::CollisionBlock(float centerX, float centerY, float width, float height)
{
	position = Vector2f(centerX, centerY);

	blockRect.top = centerY - height * 0.5f;
	blockRect.left = centerX - width * 0.5f;
	blockRect.width = width;
	blockRect.height = height;
	blockShape.setFillColor(Color(153, 153, 153));
	blockShape.setSize(Vector2f(width, height));
	blockShape.setOrigin(Vector2f(width * 0.5f, height * 0.5f));
	blockShape.setPosition(position);
}

CollisionBlock::CollisionBlock(FloatRect getGlobalBounds, Vector2u mousePosGrid)
{
	position = Vector2f((float)getGlobalBounds.left, (float)getGlobalBounds.top);
	blockRect.top = getGlobalBounds.top;
	blockRect.left = getGlobalBounds.left;
	blockRect.width = getGlobalBounds.width;
	blockRect.height = getGlobalBounds.height;

	blockShape.setFillColor(Color(255, 0, 0, 125));
	blockShape.setSize(Vector2f(getGlobalBounds.width, getGlobalBounds.height));
	blockShape.setPosition(position);
}

const Vector2f CollisionBlock::GetPosition()
{
	return position;
}

const FloatRect CollisionBlock::GetBlockRect()
{
	return blockRect;
}

const RectangleShape CollisionBlock::GetBlockShape()
{
	return blockShape;
}