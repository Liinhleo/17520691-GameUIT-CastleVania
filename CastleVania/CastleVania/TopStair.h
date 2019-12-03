#pragma once
#include "GameObject.h"

class TopStair : public CGameObject
{
	int id; 

	int width;	// rong
	int height;	// cao
	
public:
	TopStair(int _id,  int _width, int _height)
	{
		type = ObjectType::TOP_STAIR; // TREN CAU THANG -> ON GRAVITY

		this->id = _id;
		this->width = _width;
		this->height = _height;

		AddAnimation(601);
	}
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

