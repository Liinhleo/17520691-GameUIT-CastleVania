#include "Zombie.h"


CZombie::CZombie()
{
	ani = ZOMBIE_STATE_WALKING;
	AddAnimation(265);
	AddAnimation(264);
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
	CGameObject::Update(dt, coObjects);

	// TO-DO: make sure Goomba can interact with the world and to each of them too!

	x += dx;
	y += dy;

	if (x <= 0 || x >= 512) //screen_width
	{
		nx = -nx;
		vx = vx * nx;
	}

	// chua xet va cham
}

void CZombie::Render()
{
	if (state == ZOMBIE_STATE_WALKING)
	{
		if (nx > 0) ani = ZOMBIE_ANI_WALKING_RIGHT;
		else ani = ZOMBIE_ANI_WALKING_LEFT;
	}
	animations[ani]->Render(x, y);
	RenderBoundingBox();
}

void CZombie::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ZOMBIE_STATE_DIE:
		isAble = false;
		break;

	case ZOMBIE_STATE_WALKING:
		vx = -ZOMBIE_WALKING_SPEED;
		break;
	}

}
