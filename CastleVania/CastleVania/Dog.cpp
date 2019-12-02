#include "Dog.h"


CDog::CDog()
{
	enemyID = EnemyType::DOG;
}


void CDog::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + DOG_BBOX_WIDTH;
	bottom = y + DOG_BBOX_HEIGHT;
}

//void CDog::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
//{
//	CGameObject::Update(dt, coObjects);
//
//	// TO-DO: make sure Goomba can interact with the world and to each of them too!
//
//	x += dx;
//	y += dy;
//
//	if (x <= 0 || x >= 512) //screen_width
//	{
//		nx = -nx;
//		vx = vx * nx;
//	}
//
//	// chua xet va cham
//}

void CDog::Render()
{
	ani = DOG_ANI_SIT;
	/*if (state == ENEMY_STATE_WALKING)
	{
		if (nx > 0) ani = DOG_ANI_RIGHT;
		else ani = DOG_ANI_LEFT;
	}*/
	animations[ani]->Render(x, y);
	RenderBoundingBox();
}

void CDog::SetState(int state)
{
	//CEnemy::SetState(state);
	switch (state)
	{
	case ENEMY_STATE_DEAD:
		isAble = false;
		break;

	case ENEMY_STATE_WALKING:
		vx = -ZOMBIE_WALKING_SPEED;
		break;
	}

}
