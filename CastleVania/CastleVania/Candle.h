#pragma once
#include "GameObject.h"
#include "debug.h"


#define ITEM_GRAVITY				0.2f
#define SMALL_HEART_GRAVITY			0.02f

// xet bien do roi cua small heart
#define MAX_SPEED					0.2f
#define MIN_SPEED					-0.2f

#define CANDLE_STATE_DISABLE			0
#define CANDLE_STATE_ABLE				100
#define CANDLE_STATE_FIRE				200
#define CANDLE_STATE_FALLING_ITEM		300


#define ANI_BIG_CANDLE					0
#define ANI_SMALL_CANDLE				1
#define ANI_FIRE						2

#define ITEM_ANI_BIG_HEART				3
#define ITEM_ANI_SMALL_HEART			4
#define ITEM_ANI_UPGRADE_WHIP			5
#define ITEM_ANI_DAGGER					6
#define ITEM_ANI_AXE					7
#define ITEM_ANI_STOP_WATCH				8
#define ITEM_ANI_HOLLY_WATER			9


#define CANDLE_BIG_BBOX_WIDTH			32
#define CANDLE_BIG_BBOX_HEIGHT			64
#define CANDLE_SMALL_BBOX_WIDTH			16
#define CANDLE_SMALL_BBOX_HEIGHT		26

#define BIG_HEART_BBOX					23
#define SMALL_HEART_BBOX				15
#define ITEM_WEAPON_BBOX						32

#define MAX_TIME_STATE_FIRE				500
#define MAX_TIME_STATE_ITEM				2000

class CCandle : public CGameObject
{
	int timeStart = 0;
	int width;
	int height;
public:
	int ani;
	bool isShow = true;
	bool isFire = false;
	bool isFallingItem = false;

	CCandle(); //constructor

	void SetWidthHeigth(int width, int heigth)
	{
		this->width = width;
		this->height = heigth;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	
	void SetAniCandle(int idCandle);


	void SetState(int state);

	void SetItemState(int itemstate);
	int GetStateItem() { return itemstate; }

};