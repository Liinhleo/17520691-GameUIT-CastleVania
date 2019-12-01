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
	SetItemState(itemstate);
	AddAnimation(250); // big candle
	AddAnimation(251); // small candle
	AddAnimation(252); // fire

	AddAnimation(300);	// BIG_HEART
	AddAnimation(301);	// SMALL_HEART
	AddAnimation(302);	// UPGRADE_WHIP
	AddAnimation(303);	// DAGGER
	AddAnimation(304);	// AXE
	AddAnimation(305);	// STOP_WATCH
	AddAnimation(306);	// HOLLY_WATER
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

	if (state == CANDLE_STATE_FALLING_ITEM)
	{
		switch (itemstate)
		{
		case 0:
			right = x + SMALL_HEART_BBOX;
			bottom = y + SMALL_HEART_BBOX;
			break;

		case 1:
			right = x + BIG_HEART_BBOX;
			bottom = y + BIG_HEART_BBOX;
			break;

		case 2:
			right = x + ITEM_WEAPON_BBOX;
			bottom = y + ITEM_WEAPON_BBOX;
			break;

		case 3:
			right = x + ITEM_WEAPON_BBOX;
			bottom = y + ITEM_WEAPON_BBOX;
			break;

		case 4:
			right = x + ITEM_WEAPON_BBOX;
			bottom = y + ITEM_WEAPON_BBOX;
			break;

		case 5:
			right = x + ITEM_WEAPON_BBOX;
			bottom = y + ITEM_WEAPON_BBOX;
			break;

		case 6:
			right = x + ITEM_WEAPON_BBOX;
			bottom = y + ITEM_WEAPON_BBOX;
			break;
		}
	}
}


void CCandle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isAble==false)
		return;

	CGameObject::Update(dt);
	//vy += ITEM_GRAVITY;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	CalcPotentialCollisions(coObjects, coEvents);
	
	if (type_candle == BIG_CANDLE)// neu la candle big => xet va cham voi ground
	{
		if (coEvents.size() == 0)
		{
			x += dx;
			y += dy;
		}
		else
		{
			float min_tx, min_ty, nx = 0, ny;

			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

			// block 
			x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
			y += min_ty * dy + ny * 0.4f;

			if (nx != 0) vx = 0;
			if (ny != 0) vy = 0;
		}
	}

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

		if (ani == ITEM_ANI_SMALL_HEART)
		{

			if (vy != 0 )
			{
				if (vx <= MIN_SPEED || vx >= MAX_SPEED)
					nx = -nx;
			}
			vx += SMALL_HEART_GRAVITY * nx;

		}

		if (timeStart > MAX_TIME_STATE_ITEM)
		{
			isFallingItem = false;
			SetState(CANDLE_STATE_DISABLE);
			timeStart = 0;
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

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
		else if (isFallingItem)
			SetItemState(itemstate);
		int alpha = 255;
		animations[ani]->Render(x, y, alpha);
		RenderBoundingBox();
	}
}

void CCandle::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case CANDLE_STATE_ABLE:	
		isShow = true;
		SetAniCandle(type_candle);
		break;

	case CANDLE_STATE_FIRE:
		isFire = true;
		break;

	case CANDLE_STATE_FALLING_ITEM:
		isFallingItem = true;
		SetItemState(itemstate);
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

void CCandle::SetItemState(ItemType itemstate)
{	
	this->itemstate = itemstate;
	switch (itemstate)
	{
	case ItemType::ITEM_BIG_HEART:
		ani = ITEM_ANI_BIG_HEART;
		vy = ITEM_GRAVITY;
		break;

	case ItemType::ITEM_SMALL_HEART:
		ani = ITEM_ANI_SMALL_HEART;
		vy = SMALL_HEART_GRAVITY;
		break;

	case ItemType::ITEM_UPGRADE_WHIP:
		ani = ITEM_ANI_UPGRADE_WHIP;
		vy = ITEM_GRAVITY;
		break;

	case ItemType::ITEM_DAGGER:
		ani = ITEM_ANI_DAGGER;
		vy = ITEM_GRAVITY;
		break;

	case ItemType::ITEM_AXE:
		ani = ITEM_ANI_AXE;
		vy = ITEM_GRAVITY;
		break;

	case ItemType::ITEM_STOP_WATCH:
		ani = ITEM_ANI_STOP_WATCH;
		vy = ITEM_GRAVITY;
		break;

	case ItemType::ITEM_HOLLY_WATER:
		ani = ITEM_ANI_HOLLY_WATER;
		vy = ITEM_GRAVITY;
		break;	
	}
}



