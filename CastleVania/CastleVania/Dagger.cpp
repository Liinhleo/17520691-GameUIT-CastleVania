#include "Dagger.h"
#define SCREEN_WIDTH 512

CDagger* CDagger::__instance = NULL;

CDagger* CDagger::GetInstance()
{
	if (__instance == NULL) __instance = new CDagger();
	return __instance;
}

void CDagger::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + DAGGER_BBOX_WIDTH;
	bottom = top + DAGGER_BBOX_HEIGHT;

}


void CDagger::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);
	
	x += vx * dt;

	if (x > CGame::GetInstance()->GetCam_x() + SCREEN_WIDTH)
		return;

	//Xet va cham voi candle bang bbox 
	for (UINT i = 1; i < coObjects->size(); i++)
	{
		float left_a, top_a, right_a, bottom_a;// obj khac
		float left, top, right, bottom; // dagger
		coObjects->at(i)->GetBoundingBox(left_a, top_a, right_a, bottom_a); // bbox obj khac
		GetBoundingBox(left, top, right, bottom);					// bbox dagger 

		if (CheckAABB(left_a, top_a, right_a, bottom_a, left, top, right, bottom))
		{

			if (dynamic_cast<CCandle*>(coObjects->at(i))) // if e->obj is CANDLE 				
			{
				coObjects->at(i)->SetState(CANDLE_STATE_FIRE);
			}
		}
	}
}


void CDagger::Render()
{
	if (isFlying)
	{
		if (nx > 0) ani = DAGGER_ANI_HIT_RIGHT;
		else ani = DAGGER_ANI_HIT_LEFT;

		int alpha = 255;
		animations[ani]->Render(x, y, alpha);
		RenderBoundingBox();
	}
}

void CDagger::SetState(int state)
{
	switch (state)
	{
	case DAGGER_STATE_HIT:
		isFlying = true;
		vx = DAGGER_SPEED * nx;
		vy = 0;
		break;

	case DAGGER_STATE_DISABLE:
		break;
	}
}