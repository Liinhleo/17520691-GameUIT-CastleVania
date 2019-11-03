#include "Candle.h"

void CCandle::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + CANDLE_BIG_BBOX_WIDTH ;
	bottom = y + CANDLE_BIG_BBOX_HEIGHT;
}

void CCandle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//
		// TO-DO: make sure Goomba can interact with the world and to each of them too!
		// 

	x += dx;
	y += dy;

	if (vx < 0 && x < 0) {
		x = 0; vx = -vx;
	}

	if (vx > 0 && x > 290) {
		x = 290; vx = -vx;
	}
}

void CCandle::Render()
{
	int ani = CANDLE_BIG_ANI_ABLE;

	if (!isAble)
		ani = CANDLE_ANI_DISABLE;

	animations[ani]->Render(x, y);
	RenderBoundingBox();
}

void CCandle::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case CANDLE_BIG_STATE_ABLE:
		isAble = true;
		break;

	case CANDLE_STATE_DISABLE:
		isDisable = true;
		break;

	}
}