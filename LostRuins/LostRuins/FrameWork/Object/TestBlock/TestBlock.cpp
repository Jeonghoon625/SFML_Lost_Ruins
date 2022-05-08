#include "TestBlock.h"

TestBlock::TestBlock(float xpos, float ypos, float width, float height)
{
	position = Vector2f(xpos, ypos);

	blockRect.top = ypos - height * 0.5f;
	blockRect.left = xpos - width * 0.5f;
	blockRect.width = width;
	blockRect.height = height;
	blockShape.setFillColor(Color(153, 153, 153));
	blockShape.setSize(Vector2f(width, height));
	blockShape.setOrigin(Vector2f(width * 0.5f, height * 0.5f));
	blockShape.setPosition(position);
}

const Vector2f TestBlock::GetPosition()
{
	return position;
}

const FloatRect TestBlock::GetBlockRect()
{
	return blockRect;
}

const RectangleShape TestBlock::GetBlockShape()
{
	return blockShape;
}

