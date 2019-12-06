#include "Zombie.h"

CZombie::CZombie()
{
	enemyID = EnemyType::ZOMBIE;

}


void CZombie::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + ZOMBIE_BBOX_WIDTH;
	bottom = y + ZOMBIE_BBOX_HEIGHT;
}

void CZombie::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!isAble)
		return;

	CGameObject::Update(dt, coObjects);
	vx = -0.02f;
	vy += 0.015f * dt;


	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{

		x += dx; //dx=vx*dt
		y += dy;

	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;				//va cham theo phuong x
		if (ny != 0) vy = 0;				//va cham theo truc y
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

}

void CZombie::Render()
{
	if (!isAble)
		return;
	/*ani = ZOMBIE_ANI_WALKING_LEFT;

	if (nx > 0) ani = ZOMBIE_ANI_WALKING_RIGHT;
	else ani = ZOMBIE_ANI_WALKING_LEFT;*/

	animations[ZOMBIE_ANI_WALKING_LEFT]->Render(x, y);
	RenderBoundingBox();
}
