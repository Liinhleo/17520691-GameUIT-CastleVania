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
	HIDE_OBJECT,
	BRICK,
	DOOR,
	TOP_STAIR,
	BOTTOM_STAIR,
	ITEM,
	WEAPON,
	ENEMY
};


class CGameObject
{
public:
	ObjectType type;

	int ID;

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
	void SetId(int _id) { this->ID = _id; }
	virtual void SetState(int state) { this->state = state; }
	void SetDirection(int direction) { this->nx = direction; }
	void SetType(ObjectType _type) { this->type = _type; }
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }

	int GetID() { return this->ID; }
	int GetState() { return this->state; }
	bool GetAble() { return isAble; }
	float GetVx() { return this->vx; }
	float GetVy() { return this->vy; }
	int GetDirection() { return this->nx; }
	ObjectType GetType() { return type; }
	void GetPosition(float& x, float& y) { x = this->x; y = this->y; }
	void GetSpeed(float& vx, float& vy) { vx = this->vx; vy = this->vy; }


	CGameObject();
	void AddAnimation(int aniId);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	void RenderBoundingBox();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render() = 0;

	//CAC HAM XU LY VA CHAM
	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);
	virtual void FilterCollision(
		vector<LPCOLLISIONEVENT> &coEvents, 
		vector<LPCOLLISIONEVENT> &coEventsResult, 
		float &min_tx, 
		float &min_ty, 
		float &nx, 
		float &ny);

	// ktra bbox co trung nhau khong
	bool CheckAABB(float left_a, float top_a, float right_a, float bottom_a, float left_b, float top_b, float right_b, float bottom_b);
	bool CheckAABBwithObject(LPGAMEOBJECT object);   // static object
	bool checkAABBExwithObject(LPGAMEOBJECT object); // moving object, smallcandle 

	~CGameObject();
};

