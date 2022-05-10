#include "AnimationClip.h"

AnimationFrame::AnimationFrame(Texture& tex, const IntRect& coord)
	: texture(&tex), texCoord(coord)
{

}
