#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include "Sprite.h"

class CAnimationFrame
{
	LPSPRITE sprite;
	DWORD time;

public:
	CAnimationFrame(LPSPRITE sprite, int time) { this->sprite = sprite; this->time = time; }
	DWORD GetTime();
	LPSPRITE GetSprite();
};

typedef CAnimationFrame* LPANIMATION_FRAME;


