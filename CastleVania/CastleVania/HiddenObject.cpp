#include "HiddenObject.h"

void HiddenObject::Render()
{
	//animations[0]->Render(x, y);
	RenderBoundingBox();
}

void HiddenObject::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}