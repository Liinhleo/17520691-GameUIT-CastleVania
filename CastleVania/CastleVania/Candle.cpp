#include "Candle.h"
#include <iostream>
#include <time.h>
#include "Brick.h"
#include "Whip.h"

CCandle::CCandle()
{
	type = ObjectType::CANDLE;

	state = CANDLE_STATE_ABLE;
	SetAniCandle(type_candle);

	AddAnimation(250); // big candle
	AddAnimation(251); // small candle
	AddAnimation(252); // fire
}


void CCandle::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	if (type_candle == BIG_CANDLE)
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
	if (isFire)
	{
		timeStart += dt;
		if (timeStart > MAX_TIME_STATE_FIRE)
		{
			isFire = false;
			SetState(CANDLE_STATE_DISABLE);
			timeStart = 0;
		}
	}
}

void CCandle::Render()
{
	if (!isAble)
		return;

	else
	{
		SetAniCandle(type_candle);
		if (isFire)
			ani = ANI_FIRE;
	}
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
		SetAniCandle(type_candle);
		break;

	case CANDLE_STATE_FIRE:
		isFire = true;
		break;

	case CANDLE_STATE_DISABLE:
		isAble = false;
		break;
	}
}

void CCandle::SetAniCandle(CandleType type_candle) // set ani cho candle cu the (xu ly man sau)
{	
	this->type_candle = type_candle;
	switch (type_candle)
	{
	case BIG_CANDLE:
		ani = ANI_BIG_CANDLE;
		break;

	case SMALL_CANDLE:
		ani = ANI_SMALL_CANDLE;
		break;
	}
}

//void CCandle::SetItemState(ItemType itemstate)
//{	
//	item->SetState(itemstate);
//	switch (itemstate)
//	{
//	case ItemType::ITEM_BIG_HEART:
//		ani = ITEM_ANI_BIG_HEART;
//		vy = ITEM_GRAVITY;
//		break;
//
//	case ItemType::ITEM_SMALL_HEART:
//		ani = ITEM_ANI_SMALL_HEART;
//		vy = SMALL_HEART_GRAVITY;
//		break;
//
//	case ItemType::ITEM_UPGRADE_WHIP:
//		ani = ITEM_ANI_UPGRADE_WHIP;
//		vy = ITEM_GRAVITY;
//		break;
//
//	case ItemType::ITEM_DAGGER:
//		ani = ITEM_ANI_DAGGER;
//		vy = ITEM_GRAVITY;
//		break;
//
//	case ItemType::ITEM_AXE:
//		ani = ITEM_ANI_AXE;
//		vy = ITEM_GRAVITY;
//		break;
//
//	case ItemType::ITEM_STOP_WATCH:
//		ani = ITEM_ANI_STOP_WATCH;
//		vy = ITEM_GRAVITY;
//		break;
//
//	case ItemType::ITEM_HOLLY_WATER:
//		ani = ITEM_ANI_HOLLY_WATER;
//		vy = ITEM_GRAVITY;
//		break;	
//	}
//}



