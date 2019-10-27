#include <algorithm>
#include "debug.h"

#include "Simon.h"
#include "Game.h"
#include "Goomba.h"

CSimon* CSimon::__instance = NULL;

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
	if (state!=SIMON_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount() - untouchable_start > SIMON_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	// No collision occured, proceed normally
	if (coEvents.size()==0)
	{
		x += dx; 
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx*dx + nx*0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty*dy + ny*0.4f;
		
		if (nx!=0) vx = 0; //va cham theo phuong ngang (static item) 
		if (ny!=0) vy = 0; // va cham ground 



		// Collision logic with Goombas
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CGoomba *>(e->obj)) // if e->obj is Goomba 
			{
				CGoomba *goomba = dynamic_cast<CGoomba *>(e->obj);

				// jump on top >> kill Goomba and deflect a bit 
				if (e->ny < 0)
				{
					if (goomba->GetState()!= GOOMBA_STATE_DIE)
					{
						goomba->SetState(GOOMBA_STATE_DIE);
						vy = -SIMON_JUMP_DEFLECT_SPEED;
					}
				}
				else if (e->nx != 0)
				{
					if (untouchable==0)
					{
						if (goomba->GetState()!=GOOMBA_STATE_DIE)
						{
							SetState(SIMON_STATE_DIE);
						}
					}
				}
			}
		}
	}

	/* HAM KTRA DE TRANH LAP LAI ANI LIEN TUC */
	if (vy == 0)
		isJumping = false;


	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CSimon::Render()
{
	int ani;
	if (state == SIMON_STATE_DIE)
	{
		if (nx > 0) ani = SIMON_ANI_DIE_RIGHT;
		else ani = SIMON_ANI_DIE_LEFT;
	}

	else if (isWalking)
	{	
		if (nx > 0)	ani = SIMON_ANI_WALKING_RIGHT;
		else ani = SIMON_ANI_WALKING_LEFT;
	}

	else if (isJumping)
	{
		if (nx > 0) ani = SIMON_ANI_JUMP_RIGHT;
		else ani = SIMON_ANI_JUMP_LEFT;
	}

	else if (isSitting)
	{
		if (nx > 0) ani = SIMON_ANI_SIT_RIGHT;
		else ani = SIMON_ANI_SIT_LEFT;
	}

	else if (isAttacking)
	{
		if (isSitting)
		{
			if (nx > 0) ani = SIMON_ANI_SIT_ATTACK_RIGHT;
			else ani = SIMON_ANI_SIT_ATTACK_LEFT;
		}
		else {
			if (nx > 0) ani = SIMON_ANI_ATTACK_LEFT;
			else ani = SIMON_ANI_ATTACK_RIGHT;
		}
	}

	else
	{
		if (nx > 0) ani = SIMON_ANI_IDLE_RIGHT;
		else ani = SIMON_ANI_IDLE_LEFT;
	}

	int alpha = 255;
	if (untouchable) alpha = 128;
	animations[ani]->Render(x, y, alpha);

	RenderBoundingBox();
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
		isWalking = false;
		vx = 0;
		break;

	case SIMON_STATE_WALKING_RIGHT:
		isWalking = true;
		vx = SIMON_WALKING_SPEED;
		nx = 1;
		break;

	case SIMON_STATE_WALKING_LEFT: 
		isWalking = true;
		vx = -SIMON_WALKING_SPEED;
		nx = -1;
		break;

	case SIMON_STATE_JUMP: 
		if (isJumping == true)
			return;
		vy = -SIMON_JUMP_SPEED_Y;
		isJumping = true;
		break;

	case SIMON_STATE_SIT:			
		isSitting = true;
		vx = 0;
		break;

	case SIMON_STATE_ATTACK:
		isAttacking = true;
		vx = 0;
		break;
	}
}

void CSimon::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y; 

	right = x;
	bottom = y + SIMON_BBOX_HEIGHT;
	
}

CSimon* CSimon::GetInstance()
{
	if (__instance == NULL) __instance = new CSimon();
	return __instance;
}
