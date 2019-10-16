#include "Simon.h"

void CSimon::Update(DWORD dt)
{
	x += 0.1f * dt;
	if (x > 320) x = 0;
}