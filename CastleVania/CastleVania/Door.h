#pragma once
#include "define.h"
#include "GameObject.h"

#define DOOR_STATE_ABLE		0		// default
#define DOOR_STATE_OPEN		100		// danh cho DoorType::DOOR

#define DOOR_ANI_SHOW	0
#define DOOR_ANI_OPEN	1

#define DOOR_BBOX_WIDTH		32
#define DOOR_BBOX_HEIGHT	64



//enum DoorType {
//	HIDDEN_DOOR,		// dung de xet va cham -> door se mo
//	DOOR				//default
//};

class CDoor : public CGameObject
{
	//DoorType type_door;
	DWORD timetoClose;		// tinh time qua cua -> dong cua 
public:
	int ani;
	bool isOpen = false;

	CDoor();

	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};