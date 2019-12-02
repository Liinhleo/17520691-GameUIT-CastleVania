#pragma once
#include "define.h"
#include "GameObject.h"

class CBrick : public CGameObject
{
	int width; 
	int height;
public:
	CBrick() {
		AddAnimation(601);

	}
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	void SetWidthHeigth(int width, int heigth) 
	{
		this->width = width;
		this->height = heigth;
	}
};