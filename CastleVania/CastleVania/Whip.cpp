#include "Whip.h"

void CWhip::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when disable 
	if (state != WHIP_STATE_DISABLE)
		CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchable_start > WHIP_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		// Collision logic with Goombas
		//for (UINT i = 0; i < coEventsResult.size(); i++)
		//{
		//	LPCOLLISIONEVENT e = coEventsResult[i];

		//	if (dynamic_cast<CGoomba*>(e->obj)) // if e->obj is Goomba 
		//	{
		//		CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

		//		// jump on top >> kill Goomba and deflect a bit 
		//		if (e->ny < 0)
		//		{
		//			if (goomba->GetState() != GOOMBA_STATE_DIE)
		//			{
		//				goomba->SetState(GOOMBA_STATE_DIE);
		//				vy = -MARIO_JUMP_DEFLECT_SPEED;
		//			}
		//		}
		//		else if (e->nx != 0)
		//		{
		//			if (untouchable == 0)
		//			{
		//				if (goomba->GetState() != GOOMBA_STATE_DIE)
		//				{
		//					if (level > MARIO_LEVEL_SMALL)
		//					{
		//						level = MARIO_LEVEL_SMALL;
		//						StartUntouchable();
		//					}
		//					else
		//						SetState(MARIO_STATE_DIE);
		//				}
		//			}
		//		}
		//	}
		//}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CWhip::Render()
{
	int ani;
	if (state == WHIP_STATE_HIT)
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
	}
	else
		ani = WHIP_ANI_DISABLE;

	int alpha = 255;
	if (untouchable) alpha = 128;
	animations[ani]->Render(x, y, alpha);
	//RenderBoundingBox();
}

void CWhip::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;

	if (level == WHIP_LEVEL_1 || level == WHIP_LEVEL_2)
	{
		right = x + WHIP_BBOX_WIDTH_LEVEL_1;
		bottom = y + WHIP_BBOX_HEIGHT_LEVEL_1;
	}
	else
	{
		right = x + WHIP_BBOX_WIDTH_LEVEL_3;
		bottom = y + WHIP_BBOX_HEIGHT_LEVEL_3;
	}
}

