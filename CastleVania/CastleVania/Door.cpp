#include "Door.h"


CDoor::CDoor()
{
	type == ObjectType::DOOR;
	state = DOOR_STATE_ABLE;

	AddAnimation(602); // brick ~ ANI SHOW
	AddAnimation(602); // brick ~ ANI OPEN

	// se load them door -> 2 frame

}

void CDoor::Render()
{
	ani = DOOR_ANI_SHOW;
	if (isOpen)
		ani = DOOR_ANI_OPEN;

	int alpha = 255;
	animations[ani]->Render(x, y, alpha);
	RenderBoundingBox();
	
}

void CDoor::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	bottom = y + DOOR_BBOX_HEIGHT;

	if (isOpen)
		right = x + DOOR_BBOX_WIDTH + 30;
	else
		right = x + DOOR_BBOX_WIDTH;
	
}