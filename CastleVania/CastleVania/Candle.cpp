#include "Candle.h"
#include <iostream>


void CCandle::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	if (state == CANDLE_BIG_STATE_ABLE)
	{
		
		right = x + CANDLE_BIG_BBOX_WIDTH;
		bottom = y + CANDLE_BIG_BBOX_HEIGHT;
	}
	else
	{
		right = x + CANDLE_SMALL_BBOX_WIDTH;
		bottom = y + CANDLE_SMALL_BBOX_HEIGHT;
	}
}

void CCandle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	if (isFire)
	{
		timeStart += dt;

		if (timeStart > MAX_TIME_STATE_FIRE)
		{
			isFire = false;
			isItem = true;
			SetState(CANDLE_STATE_DISABLE);
			timeStart = 0;
		}
	}
}

void CCandle::Render()
{	
	int ani = CANDLE_BIG_ANI_ABLE;
	
	if(isFire)
		ani = CANDLE_ANI_FIRE;
	
	int alpha = 255;
	animations[ani]->Render(x, y, alpha);
	//RenderBoundingBox();

}

void CCandle::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case CANDLE_BIG_STATE_ABLE:
		isShow = true;
		break;


	case CANDLE_SMALL_STATE_ABLE:
		isShow = true;
		break;


	case CANDLE_STATE_FIRE:
		isShow = false;
		isFire = true;
		break;

	case CANDLE_STATE_DISABLE:
		isAble = false;
		break;

	}
}