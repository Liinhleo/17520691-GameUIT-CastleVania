#pragma once
#include "GameObject.h"
class UpStair :
	public CGameObject
{
	int width;	// rong
	int height;	// cao

public:
	UpStair(int _width, int _height)
	{
		type = ObjectType::HIDE_OBJECT;

		this->width = _width;
		this->height = _height;

		AddAnimation(601);
	}
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

