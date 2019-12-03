#include "BottomStair.h"
void BottomStair::Render()
{
	//animations[0]->Render(x, y);
	RenderBoundingBox();
}

void BottomStair::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}