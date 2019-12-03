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


void CWhip::WhipCollisionObject(vector<LPGAMEOBJECT> coObjects)
{
	if (CSimon::GetInstance()->isAttacking && animations[ani]->getCurrentFrame() == 2)
	{
		for (int i = 0; i < coObjects.size(); i++)
		{
			if (dynamic_cast<CCandle*>(coObjects[i]) && this->checkAABBExwithObject(coObjects[i]))
			{
				coObjects[i]->SetState(CANDLE_STATE_FIRE);
			}

			else if (dynamic_cast<CEnemy*>(coObjects[i]) && this->checkAABBExwithObject(coObjects[i]))
			{
				coObjects[i]->SetState(ENEMY_STATE_DEAD);
			}
		}
	}
}

