#pragma once
#include "GameObject.h"

class BottomStair : public CGameObject
{
	int id;
	int width;	// rong
	int height;	// cao

public:
	BottomStair(int _id, int _width, int _height)
	{
		type = ObjectType::BOTTOM_STAIR; 

		this->id = _id;
		this->width = _width;
		this->height = _height;

		AddAnimation(601);
	}
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};


