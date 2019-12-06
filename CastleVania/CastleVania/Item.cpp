#include "Item.h"
Item::Item()
{
	type = ObjectType::ITEM;
	AddAnimation(300);	// BIG_HEART
	AddAnimation(301);	// SMALL_HEART
	AddAnimation(302);	// UPGRADE_WHIP
	AddAnimation(303);	// DAGGER
	AddAnimation(304);	// AXE
	AddAnimation(305);	// STOP_WATCH
	AddAnimation(306);	// HOLLY_WATER
}

void Item::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isAble == false)
		return;

	CGameObject::Update(dt);
	//vy += ITEM_GRAVITY;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	CalcPotentialCollisions(coObjects, coEvents);

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

	if (isShow)
	{
		timeStart += dt;

		if (GetItemState()== ItemType::ITEM_SMALL_HEART)
		{

			if (vy != 0)
			{
				if (vx <= MIN_SPEED || vx >= MAX_SPEED)
					nx = -nx;
			}
			vx += SMALL_HEART_GRAVITY * nx;

		}

		if (timeStart > MAX_TIME_STATE_ITEM)
		{
			isAble = false;
			timeStart = 0;
		}
	}
}

void Item::Render()
{
	if (!isAble)
		return;

	else
		SetItemState(itemtype);
		
	int alpha = 255;
	animations[ani]->Render(x, y, alpha);
	RenderBoundingBox();
}


void Item::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ITEM_STATE_DISABLE:	// sau khi va cham -> mat luon
		isAble = false;
		break;

	case ITEM_STATE_SHOW:
		isShow = true;
		SetItemState(itemtype);
		break;
	}
}

void Item::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;

	if (itemtype == ItemType::ITEM_SMALL_HEART)
	{
		right = x + SMALL_HEART_BBOX;
		bottom = y + SMALL_HEART_BBOX;
	}
	else if (itemtype == ItemType::ITEM_BIG_HEART)
	{
		right = x + BIG_HEART_BBOX;
		bottom = y + BIG_HEART_BBOX;
	}
	else
	{
		right = x + ITEM_WEAPON_BBOX;
		bottom = y + ITEM_WEAPON_BBOX;
	}
}

ItemType Item::RandomItem()
{
	return ItemType (1 + rand() % 6); // [1,7] bo qua NONE_ITEM
}

void Item::SetItemState(ItemType _itemtype)
{
	this->itemtype = _itemtype;
	switch (itemtype)
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