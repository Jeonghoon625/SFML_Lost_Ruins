#include "TestBlock.h"

TestBlock::TestBlock(float left, float top, float width, float height)
{
	blockRect.top = top;
	blockRect.left = left;
	blockRect.width = width;
	blockRect.height = height;

	blockShape.setFillColor(Color(153, 153, 153));
	blockShape.setSize(Vector2f(width, height));
	blockShape.setPosition(left, top);
}

const FloatRect TestBlock::GetBlockRect()
{
	return blockRect;
}

const RectangleShape TestBlock::GetBlockShape()
{
	return blockShape;
}

