#pragma once
#include "GameObject.h"

class BottomStair : public CGameObject
{
	
	int type;
	int width;	// rong
	int height;	// cao

public:
	BottomStair(int _type, int x, int y, int _width, int _height)
	{
		type = ObjectType::BOTTOM_STAIR; 
		this->x = x;
		this->y = y;
		this->type = _type;
		this->width = _width;
		this->height = _height;

		AddAnimation(601);
	}
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};


