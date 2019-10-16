#include "SpriteAnimation.h"
#include "Sprite.h"

DWORD CAnimationFrame::GetTime() 
{ 
	return time; 
}
LPSPRITE CAnimationFrame::GetSprite() 
{ 
	return sprite;
}