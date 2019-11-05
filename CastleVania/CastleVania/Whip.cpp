#include "Whip.h"
#include "Simon.h"

CWhip* CWhip::__instance = NULL;
CWhip* CWhip::GetInstance()
{
	if (__instance == NULL) __instance = new CWhip();
	return __instance;
}

void CWhip::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
	
	if (CSimon::GetInstance()->isAttacking && animations[ani]->getCurrentFrame() == 2 ) // 2: frame roi duoc danh ra 
	{
		for (UINT i = 1; i < coObjects->size(); i++)
		{
			float left_a, top_a, right_a, bottom_a;// obj khac
			float left, top, right, bottom; // whip
			coObjects->at(i)->GetBoundingBox(left_a, top_a, right_a, bottom_a); // bbox obj khac
			GetBoundingBox(left, top, right, bottom);					// bbox whip 

			if (CheckAABB(left_a, top_a, right_a, bottom_a, left, top, right, bottom))
			{
				if (dynamic_cast<CCandle*>(coObjects->at(i))) // if e->obj is CANDLE 				
				{
					coObjects->at(i)->SetState(CANDLE_STATE_FIRE);
					
				}
			}
		}
	}

}

void CWhip::Render()
{
	if (CSimon::GetInstance()->isAttacking)
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

