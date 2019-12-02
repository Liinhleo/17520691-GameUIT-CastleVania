#pragma once
#include "GameObject.h"
#include "define.h"

#define ITEM_STATE_SHOW			0	
#define ITEM_STATE_DISABLE		100

enum ItemType {
	ITEM_BIG_HEART,
	ITEM_SMALL_HEART,
	ITEM_UPGRADE_WHIP,
	ITEM_DAGGER,
	ITEM_AXE,
	ITEM_STOP_WATCH,
	ITEM_HOLLY_WATER
};

class Item :	public CGameObject
{
	DWORD timeStart;
public:
	int ani;
	ItemType itemtype;

	bool isShow = false;

	Item();

	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);

	void Render();
	void SetState(int state);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	ItemType RandomItem();
	void SetItemState(ItemType _itemtype);
	ItemType GetItemState() { return this->itemtype; }
};

