#include "Dagger.h"
#define SCREEN_HEIGHT 480

CDagger* CDagger::__instance = NULL;

CDagger* CDagger::GetInstance()
{
	if (__instance == NULL) __instance = new CDagger();
	return __instance;
}

void CDagger::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (CSimon::GetInstance()->isAttacking)
	{
		if (nx > 0) //SIMON QUAY PHAI
		{
			left = x;
			top = y;
			right = left + DAGGER_BBOX_WIDTH;
			bottom = top + DAGGER_BBOX_HEIGHT;

		}

		else  // TH: SIMON QUAY TRAI
		{
			left = x;
			top = y;
			right = left + DAGGER_BBOX_WIDTH;
			bottom = top + DAGGER_BBOX_HEIGHT;
		}
	}
}


void CDagger::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);
	x += dx;

	//// Simple fall down

	//vector<LPCOLLISIONEVENT> coEvents;
	//vector<LPCOLLISIONEVENT> coEventsResult;

	//coEvents.clear();

	//// turn off collision when die 
	//if (state != DAGGER_STATE_DISABLE)
	//	CalcPotentialCollisions(coObjects, coEvents);


	//// No collision occured, proceed normally
	//if (coEvents.size() == 0)
	//{
	//	x += dx;
	//}
	//else
	//{
	//	float min_tx, min_ty, nx = 0, ny;

	//	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

	//	// block 
	//	x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
	//	y += min_ty * dy + ny * 0.4f;

	//	if (nx != 0) vx = 0; //nx - va cham theo phuong ngang 
	//	if (ny != 0) vy = 0; // ny - va cham ground 
	//}

	/*x += vx * dt;
	vx = DAGGER_SPEED * nx;*/

	////Xet va cham voi candle bang bbox 
	//for (UINT i = 1; i < coObjects->size(); i++)
	//{
	//	float left_a, top_a, right_a, bottom_a;// obj khac
	//	float left, top, right, bottom; // dagger
	//	coObjects->at(i)->GetBoundingBox(left_a, top_a, right_a, bottom_a); // bbox obj khac
	//	GetBoundingBox(left, top, right, bottom);					// bbox dagger 

	//	if (CheckAABB(left_a, top_a, right_a, bottom_a, left, top, right, bottom))
	//	{

	//		if (dynamic_cast<CCandle*>(coObjects->at(i))) // if e->obj is CANDLE 				
	//		{
	//			coObjects->at(i)->SetState(CANDLE_STATE_DISABLE);
	//		}
	//	}
	//}


	// clean up collision events
	//for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}


void CDagger::Render()
{
	if (CSimon::GetInstance()->isAttacking && isFlyaway==true)
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
		isFlyaway = true;
		vx = DAGGER_SPEED * nx;
		vy = 0;
		break;

	case DAGGER_STATE_DISABLE:
		break;
	}
}