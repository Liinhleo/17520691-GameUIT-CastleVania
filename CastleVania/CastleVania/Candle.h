#pragma once
#include "GameObject.h"
#include "debug.h"
#include "Sprites.h"
#include "Game.h"
#include "Whip.h"
#include "Dagger.h"

#define CANDLE_STATE_DISABLE			0
#define CANDLE_BIG_STATE_ABLE			100
#define CANDLE_SMALL_STATE_ABLE			200
#define CANDLE_STATE_FIRE				300

#define CANDLE_BIG_ANI_ABLE			0
#define CANDLE_SMALL_ANI_ABLE		1
#define CANDLE_ANI_FIRE				2

#define CANDLE_BIG_BBOX_WIDTH		32
#define CANDLE_BIG_BBOX_HEIGHT		64

#define CANDLE_SMALL_BBOX_WIDTH		16
#define CANDLE_SMALL_BBOX_HEIGHT	26


#define MAX_TIME_STATE_FIRE		2000

class CCandle : public CGameObject
{
	int timeStart = 0;
	int width;
	int height;
public:

	int ani;

	CCandle() : CGameObject() {}

	bool isShow = false;
	bool isFire = false;
	bool isItem = false;
	void SetWidthHeigth(int width, int heigth)
	{
		this->width = width;
		this->height = heigth;
	}
	void CCandle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	
	virtual void SetState(int state);

};