#pragma once
#include "define.h"
#include "GameObject.h"

class HiddenObject : public CGameObject
{
	int width;	// rong
	int height;	// cao

public:
	HiddenObject(int _width,int _height) 
	{

		this->width = _width;
		this->height = _height;

		type = ObjectType::HIDE_OBJECT;

		AddAnimation(601);
	}
	virtual void Update();

	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

