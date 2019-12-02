#include "Whip.h"
#include "Simon.h"
#include "Enemy.h"
#include "Candle.h"

CWhip* CWhip::__instance = NULL;
CWhip* CWhip::GetInstance()
{
	if (__instance == NULL) __instance = new CWhip();
	return __instance;
}

void CWhip::UpgradeWhip()
{
	if (level == MAX_LEVEL)
		return;
	level = level + 1;
}

void CWhip::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);

	/*======	XET VA CHAM	 CHO SIMON	======*/


	vector<LPCOLLISIONEVENT> coEvents;	// su kien va cham
	vector<LPCOLLISIONEVENT> coEventsResult;	// danh sach ket qua tra ve 

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);	// tinh toan va cham (objects co kha nang va cham, su kien va cham )

	// turn off collision when die 


	// No collision occured, proceed normally
	if (CSimon::GetInstance()->isAttacking && animations[ani]->getCurrentFrame() == 2) // 2: frame roi duoc danh ra 
	{

		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;				//va cham theo phuong x
		if (ny != 0) vy = 0;				//va cham theo truc y






		for (UINT i = 0; i < coObjects->size(); i++)
		{
			float left_a, top_a, right_a, bottom_a;// obj khac
			float left, top, right, bottom; // whip

			coObjects->at(i)->GetBoundingBox(left_a, top_a, right_a, bottom_a); // bbox obj khac
			GetBoundingBox(left, top, right, bottom);					// bbox whip 
			LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i));



			if (CheckAABB(left_a, top_a, right_a, bottom_a, left, top, right, bottom))
			{
				if (dynamic_cast<CCandle*>(coObjects->at(i))) // if e->obj is CANDLE 				
				{
					DebugOut(L"Vo update whip");

					coObjects->at(i)->SetState(CANDLE_STATE_FIRE);
				}


				if (dynamic_cast<CEnemy*>(coObjects->at(i)))// if e->obj is zombie 
				{
					coObjects->at(i)->SetState(ENEMY_STATE_DEAD);
				}
			}

		}
		
	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}


void CWhip::Render()
{
	if (CSimon::GetInstance()->isAttacking && isWhip)
	{

		if (level == WHIP_LEVEL_1)
		{
			if (nx > 0) ani = WHIP_ANI_LEVEL1_HIT_RIGHT;
			else ani = WHIP_ANI_LEVEL1_HIT_LEFT;
		}
		else if (level == WHIP_LEVEL_2)
		{
			if (nx > 0) ani = WHIP_ANI_LEVEL2_HIT_RIGHT;
			else ani = WHIP_ANI_LEVEL2_HIT_LEFT;
		}
		else
		{
			if (nx > 0) ani = WHIP_ANI_LEVEL3_HIT_RIGHT;
			else ani = WHIP_ANI_LEVEL3_HIT_LEFT;
		}
		int alpha = 255;
		animations[ani]->Render(x, y, alpha);
		RenderBoundingBox();
	}
}

void CWhip::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (CSimon::GetInstance()->isAttacking)
	{
		if (nx > 0) //SIMON QUAY PHAI
		{
			left = x + DISTANCE_XWHIP_HANDSIMON;
			top = y + 15; // 15: head of simon 

			if (level == WHIP_LEVEL_1 || level == WHIP_LEVEL_2)
			{
				right = left + WHIP_BBOX_WIDTH_LEVEL_1;
				bottom = top + WHIP_BBOX_HEIGHT;
			}
			else
			{
				right = left + WHIP_BBOX_WIDTH_LEVEL_3;
				bottom = top + WHIP_BBOX_HEIGHT;
			}
		}


		else  // TH: SIMON QUAY TRAI
		{
			top = y + 15; // 15: head of simon 
			bottom = top + WHIP_BBOX_HEIGHT;

			if (level == WHIP_LEVEL_1 || level == WHIP_LEVEL_2)
			{
				left = CSimon::GetInstance()->x - WHIP_BBOX_WIDTH_LEVEL_1;
				right = left + WHIP_BBOX_WIDTH_LEVEL_1;

			}
			else
			{
				left = CSimon::GetInstance()->x - WHIP_BBOX_WIDTH_LEVEL_3;
				right = left + WHIP_BBOX_WIDTH_LEVEL_3;
			}
		}
	}
		
}

void CWhip::SetState(int state)
{
	switch (state)
	{
	case WHIP_STATE_HIT:
		isWhip = true;
		break;

	case WHIP_STATE_DISABLE:
		isWhip = false;
		break;
	}
}

