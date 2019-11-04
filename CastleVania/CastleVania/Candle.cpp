#include "Candle.h"

void CCandle::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + CANDLE_BIG_BBOX_WIDTH ;
	bottom = y + CANDLE_BIG_BBOX_HEIGHT;
}

void CCandle::Render()
{	
	int ani = CANDLE_BIG_ANI_ABLE;
	int alpha = 255;
	animations[ani]->Render(x, y, alpha);
	RenderBoundingBox();
}

void CCandle::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case CANDLE_BIG_STATE_ABLE:
		break;

	case CANDLE_STATE_DISABLE:
		isAble = false;
		break;

	}
}