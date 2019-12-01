#pragma once
#include "define.h"

class HiddenObject : public CGameObject
{

public:
	HiddenObject() 
	{
		//type = ObjectType::HIDE_OBJECT;
		AddAnimation(601);
	}

	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

