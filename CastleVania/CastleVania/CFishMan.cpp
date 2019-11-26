#include "CFishMan.h"

#include "Zombie.h"


CFishMan::CFishMan()
{
	ani = ENEMY_STATE_WALKING;
	enemyID = EnemyType::FISHMAN;
}


void CFishMan::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + ZOMBIE_BBOX_WIDTH;
	bottom = y + ZOMBIE_BBOX_HEIGHT;
}

void CFishMan::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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

void CFishMan::Render()
{
	if (state == ENEMY_STATE_WALKING)
	{
		if (nx > 0) ani = FISHMAN_ANI_RIGHT;
		else ani = FISHMAN_ANI_LEFT;
	}
	animations[ani]->Render(x, y);
	RenderBoundingBox();
}

void CFishMan::SetState(int state)
{
	vx = -FISHMAN_WALKING_SPEED;
}
