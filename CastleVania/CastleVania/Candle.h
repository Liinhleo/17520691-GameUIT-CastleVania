#pragma once
#include "GameObject.h"
#include "debug.h"
#include "Sprites.h"
#include "Game.h"
#include "Whip.h"
#include "Dagger.h"




#define CANDLE_STATE_DISABLE			0

#define CANDLE_BIG_STATE_ABLE			100
//#define CANDLE_BIG_STATE_FIRE			200
//#define CANDLE_BIG_STATE_ITEM			300

//#define CANDLE_SMALL_STATE_ABLE		400
//#define CANDLE_SMALL_STATE_FIRE		500
//#define CANDLE_SMALL_STATE_PRESENT	600



#define CANDLE_BIG_ANI_ABLE			0
//#define CANDLE_BIG_ANI_FIRE		1
//#define CANDLE_BIG_ANI_ITEM		2

//#define CANDLE_SMALL_ANI_ABLE		3
//#define CANDLE_SMALL_ANI_FIRE		4
//#define CANDLE_SMALL_ANI_PRESENT	5


#define CANDLE_BIG_BBOX_WIDTH  32
#define CANDLE_BIG_BBOX_HEIGHT 64
//
//#define CANDLE_SMALL_BBOX_WIDTH  16
//#define CANDLE_SMALL_BBOX_HEIGHT 26



class CCandle : public CGameObject
{
	//int untouchable;
	//DWORD untouchable_start;


public:
	int ani;


	CCandle() : CGameObject()
	{
		/*untouchable = 0;*/
	}
	virtual void Render();
	virtual void SetState(int state);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};