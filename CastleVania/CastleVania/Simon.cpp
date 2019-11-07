#include <algorithm>
#include "debug.h"
#include <iostream>
#include "Simon.h"
#include "Game.h"
#include "Goomba.h"

CSimon* CSimon::__instance = NULL;

CSimon* CSimon::GetInstance()
{
	if (__instance == NULL) __instance = new CSimon();
	return __instance;
}

void CSimon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (isSitting)
	{
		left = x;
		top = y;

		right = x;
		bottom = y + SIMON_BBOX_HEIGHT - 10;
	}
	else
	{
		left = x;
		top = y;

		right = x;
		bottom = y + SIMON_BBOX_HEIGHT ;

	}

}


void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{

	// Calculate dx, dy 
	CGameObject::Update(dt);

	// Simple fall down
	vy += SIMON_GRAVITY*dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state != SIMON_STATE_DIE)
	{
		
		CalcPotentialCollisions(coObjects, coEvents);

	}

	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount() - untouchable_start > SIMON_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	// No collision occured, proceed normally
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

		//// Collision logic with Goombas
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
		/*	}
		}*/
	}


	//	// Collision logic with Goombas
	//	for (UINT i = 0; i < coEventsResult.size(); i++)
	//	{
	//		LPCOLLISIONEVENT e = coEventsResult[i];

	//		if (dynamic_cast<CGoomba *>(e->obj)) // if e->obj is Goomba 
	//		{
	//			CGoomba *goomba = dynamic_cast<CGoomba *>(e->obj);

	//			// jump on top >> kill Goomba and deflect a bit 
	//			if (e->ny < 0)
	//			{
	//				if (goomba->GetState()!= GOOMBA_STATE_DIE)
	//				{
	//					goomba->SetState(GOOMBA_STATE_DIE);
	//					vy = -SIMON_JUMP_DEFLECT_SPEED;
	//				}
	//			}
	//			else if (e->nx != 0)
	//			{
	//				if (untouchable==0)
	//				{
	//					if (goomba->GetState()!=GOOMBA_STATE_DIE)
	//					{
	//						SetState(SIMON_STATE_DIE);
	//					}
	//				}
	//			}
	//		}
	//	}
	//}


	// ngan Simon rot ra man hinh
	if (x <= 0)
		x = 0;


	/* HAM KTRA DE TRANH LAP LAI ANI LIEN TUC */
	// han che nhay lien tuc
	if (vy == 0) //va cham dat
	{
		isJumping = false;
	}

	// Han che Attacking lien tuc
	if (animations[ani]->getCurrentFrame() >= MAX_FRAME_ATTACK)
		isAttacking = false;

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	CWhip::GetInstance()->SetPosition(x - 80, y);
	CWhip::GetInstance()->nx = nx;

}

void CSimon::Render()
{
	if (state == SIMON_STATE_DIE)
	{
		if (nx > 0) ani = SIMON_ANI_DIE_RIGHT;
		else ani = SIMON_ANI_DIE_LEFT;
	}

	else if (isAttacking)
	{

		if (isSitting) {
			if (nx > 0) ani = SIMON_ANI_SIT_ATTACK_RIGHT;
			else ani = SIMON_ANI_SIT_ATTACK_LEFT;
		}
		else {
			if (nx > 0) ani = SIMON_ANI_ATTACK_RIGHT;
			else ani = SIMON_ANI_ATTACK_LEFT;
		}

	}

	else if (isSitting)
	{
		if (nx > 0) ani = SIMON_ANI_SIT_RIGHT;
		else ani = SIMON_ANI_SIT_LEFT;
	}


	else if (isJumping)
	{
		if (isAttacking) {
			if (nx > 0) ani = SIMON_ANI_ATTACK_RIGHT;
			else ani = SIMON_ANI_ATTACK_LEFT;
		}
		else {
			if (nx > 0) ani = SIMON_ANI_JUMP_RIGHT;
			else ani = SIMON_ANI_JUMP_LEFT;
		}
	}

	else if (isWalking)
	{	
		if (nx > 0)	ani = SIMON_ANI_WALKING_RIGHT;
		else ani = SIMON_ANI_WALKING_LEFT;
	}


	else
	{
		if (nx > 0) ani = SIMON_ANI_IDLE_RIGHT;
		else ani = SIMON_ANI_IDLE_LEFT;
	}

	

	int alpha = 255;
	if (untouchable) alpha = 128; // blur -> lam mo 
	animations[ani]->Render(x, y, alpha);

	//RenderBoundingBox();
}

void CSimon::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case SIMON_STATE_DIE:
		vy = -SIMON_DIE_DEFLECT_SPEED;
		break;

	case SIMON_STATE_IDLE:
		if (isJumping)
			return;
		isWalking = false;
		vx = 0;
		break;

	case SIMON_STATE_WALKING_RIGHT:
		if (isJumping||isAttacking)
			return;

		else if (isSitting)
		{
			nx = 1;
			return;
		}
		isWalking = true;		
		vx = SIMON_WALKING_SPEED;
		nx = 1;
		break;

	case SIMON_STATE_WALKING_LEFT: 
		if (isJumping || isAttacking)
			return;

		else if (isSitting)
		{
			nx = -1;
			return;
		}

		isWalking = true;
		vx = -SIMON_WALKING_SPEED;
		nx = -1;
		
		break;

	case SIMON_STATE_JUMP: 				
		if (isJumping||isSitting)
			return;		
		isWalking = false;
		vy = -SIMON_JUMP_SPEED_Y;
		isJumping = true;
		break;

	case SIMON_STATE_SIT:	
		if (isAttacking||isSitting) // dang ngoi thi khong thuc hien cau lenh duoi -> tranh tang bien y -> simon rot :) 
			return;
		isWalking = false;
		vx = 0;
		y = y + 10;
		isSitting = true;
		break;

	case SIMON_STATE_STAND_UP: // de tranh TH simon rot xuong(do chan dinh vien gach)
		if (isAttacking)
			return;
		y = y - 10;
		isSitting = false;
		vx = 0;
		break;

	case SIMON_STATE_ATTACK:
		if (CDagger::GetInstance()->isFlying)
		{
			CDagger::GetInstance()->SetPosition(x + 10, y);
			CWhip::GetInstance()->SetState(WHIP_STATE_DISABLE);
		}


		isWalking = false;
		isAttacking = true;
		break;	
	}
}


//void CSimon::AttackingState()
//{
//
//}
//void CSimon::WalkingState()
//{
//	
//}
//void CSimon::JumpingState()
//{
//	
//}
//
//void CSimon::SittingState()
//{
//	
//}


