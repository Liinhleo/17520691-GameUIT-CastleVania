#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>

#include "Sprites.h"


using namespace std;

#define ID_TEX_BBOX 3		// special texture to draw object bounding box

class CGameObject; 
typedef CGameObject * LPGAMEOBJECT;

struct CCollisionEvent;
typedef CCollisionEvent * LPCOLLISIONEVENT;
struct CCollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;
	CCollisionEvent(float t, float nx, float ny, LPGAMEOBJECT obj = NULL) { this->t = t; this->nx = nx; this->ny = ny; this->obj = obj; }

	static bool compare(const LPCOLLISIONEVENT &a, LPCOLLISIONEVENT &b)
	{
		return a->t < b->t;
	}
};

enum ObjectType {
	CANDLE,
	ITEM,
	WEAPON,
	ENEMY,
	HIDE_OBJECT
};

enum ItemType {
	ITEM_BIG_HEART,
	ITEM_SMALL_HEART,
	ITEM_UPGRADE_WHIP,
	ITEM_DAGGER,
	ITEM_AXE,
	ITEM_STOP_WATCH,
	ITEM_HOLLY_WATER
};

class CGameObject
{
public:
	ObjectType type;
	ItemType itemtype;
	float x; 
	float y;

	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt

	float vx;
	float vy;

	int nx;	 

	int state;
	//int itemstate;

	DWORD dt; 

	vector<LPANIMATION> animations;

public: 
	bool isAble = true;
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetPosition(float &x, float &y) { x = this->x; y = this->y; }
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }




	//ktra update cua game
	float GetVx() { return this->vx; }

	void RenderBoundingBox();

	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);
	virtual void FilterCollision(
		vector<LPCOLLISIONEVENT> &coEvents, 
		vector<LPCOLLISIONEVENT> &coEventsResult, 
		float &min_tx, 
		float &min_ty, 
		float &nx, 
		float &ny);

	void AddAnimation(int aniId);

	CGameObject();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render() = 0;
	

	void SetType(ObjectType _type)
	{ 
		this->type = _type;			
	}
	ObjectType GetType() { return type; }

	virtual void SetState(int state) { this->state = state; }
	int GetState() { return this->state; }

	// ktra bbox co trung nhau khong
	bool CheckAABB(float left_a, float top_a, float right_a, float bottom_a, float left_b, float top_b, float right_b, float bottom_b)
	{
		return left_a < right_b && right_a > left_b && top_a < bottom_b && bottom_a > top_b;
	}


	// DIRTY CODE -> NEED TO IMPROVE
	virtual void SetItemState(ItemType _itemtype) { this->itemtype = _itemtype; }
	ItemType GetItem() { return itemtype; }


	~CGameObject();
};

