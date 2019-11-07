#include "Candle.h"
#include <iostream>
#include <time.h>
#include "Brick.h"

void CCandle::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	if (state == CANDLE_STATE_ABLE)
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

CCandle::CCandle()
{
	ani = CANDLE_STATE_ABLE;
	AddAnimation(250); // big candle
	AddAnimation(251); // small candle
	AddAnimation(252); // fire
	AddAnimation(300);
	AddAnimation(301);
	AddAnimation(302);
	AddAnimation(303);
	AddAnimation(304);
	AddAnimation(305);
	AddAnimation(306);
}

void CCandle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!isAble)
		return;

	CGameObject::Update(dt);
	vy += ITEM_GRAVITY;

	if (isFire)
	{
		timeStart += dt;
		if (timeStart > MAX_TIME_STATE_FIRE)
		{
			isFire = false;
			SetState(CANDLE_STATE_FALLING_ITEM);
			timeStart = 0;
		}
	}


	if (isFallingItem)
	{
		timeStart += dt;
		if (timeStart > MAX_TIME_STATE_ITEM)
		{
			isFallingItem = false;
			SetState(CANDLE_STATE_DISABLE);
			timeStart = 0;
		}
	}
}

void CCandle::Render()
{
	ani = ANI_BIG_CANDLE; // default CANDLE BIG 

	if (!isAble)
		return;
	if (isFire)
		ani = ANI_FIRE;
	else if (isFallingItem)
		SetAniItem(1);
	int alpha = 255;
	animations[ani]->Render(x, y, alpha);
	RenderBoundingBox();

}

void CCandle::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case CANDLE_STATE_ABLE:
		isShow = true;
		break;

	case CANDLE_STATE_FIRE:
		isFire = true;
		break;

	case CANDLE_STATE_FALLING_ITEM:
		isFallingItem = true;
		SetAniItem(idItem);
		break;

	case CANDLE_STATE_DISABLE:
		isAble = false;
		break;
	}
}

void CCandle::SetAniCandle(int idCandle) // set ani cho candle cu the (xu ly man sau)
{
	
	if (isShow)
	{
		switch (idCandle)
		{
		case 0:
			ani = ANI_BIG_CANDLE;
			break;

		case 1:
			ani = ANI_SMALL_CANDLE;
			break;
		}
	}
}

void CCandle::SetAniItem(int idItem) // set ani cho tung item cu the
{
	if (isFallingItem)
	{
		this->idItem = idItem; 

		switch (idItem)
		{
		case 0:
			ani = ITEM_ANI_BIG_HEART;
			//width = BIG_HEART_BBOX;
			//height = BIG_HEART_BBOX;
			vy = ITEM_GRAVITY;
			break;

		case 1:
			ani = ITEM_ANI_SMALL_HEART;
			vy = SMALL_HEART_GRAVITY;
			x += vx * dt;
			break;

		case 2:
			ani = ITEM_ANI_UPGRADE_WHIP;
			vy = ITEM_GRAVITY;
			break;

		case 3:
			ani = ITEM_ANI_DAGGER;
			vy = ITEM_GRAVITY;
			break;

		case 4:
			ani = ITEM_ANI_AXE;
			vy = ITEM_GRAVITY;
			break;

		case 5:
			ani = ITEM_ANI_STOP_WATCH;
			vy = ITEM_GRAVITY;
			break;

		case 6:
			ani = ITEM_ANI_HOLLY_WATER;
			vy = ITEM_GRAVITY;
			break;

		}
	}
}

