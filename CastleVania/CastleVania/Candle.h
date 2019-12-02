#pragma once
#include "define.h"
#include "GameObject.h"
#include"Item.h"
#define CANDLE_STATE_DISABLE			0
#define CANDLE_STATE_ABLE				100
#define CANDLE_STATE_FIRE				200
//#define CANDLE_STATE_FALLING_ITEM		300

#define ANI_BIG_CANDLE					0
#define ANI_SMALL_CANDLE				1
#define ANI_FIRE						2

#define CANDLE_BIG_BBOX_WIDTH			32
#define CANDLE_BIG_BBOX_HEIGHT			64
#define CANDLE_SMALL_BBOX_WIDTH			16
#define CANDLE_SMALL_BBOX_HEIGHT		26



enum CandleType {
	BIG_CANDLE,
	SMALL_CANDLE
};

class CCandle : public CGameObject
{

	CandleType type_candle;
	int timeStart = 0;
	int id;
public:

	int ani;
	bool isFire = false;

	CCandle(); //constructor

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	
	void SetAniCandle(CandleType idCandle);
	CandleType GetCandle() { return this->type_candle; }
	int GetId() { return id; }
	void SetId(int _id) { this->id = _id; }
	
	void SetState(int state);

};