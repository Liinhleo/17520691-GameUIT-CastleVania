#pragma once
#include "define.h"

class CDoor : public CGameObject
{
	int width;
	int height;
public:
	CDoor() {
		AddAnimation(601);

	}
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	void SetWidthHeigth(int width, int heigth)
	{
		this->width = width;
		this->height = heigth;
	}
};