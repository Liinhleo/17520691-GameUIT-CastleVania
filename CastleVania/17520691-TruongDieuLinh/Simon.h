#pragma once
#include "GameObject.h"

class CSimon : public CGameObject
{
public:
	CSimon(LPCWSTR texturePath) :CGameObject(texturePath) {};
	void Update(DWORD dt);
};