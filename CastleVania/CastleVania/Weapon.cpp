#include "Weapon.h"

vector<CCandle*> Item_weapons;

Weapon::Weapon()
{

	AddAnimation(156); // dagger right
	AddAnimation(157); // dagger left
	AddAnimation(158); // axe right
	AddAnimation(159); // axe left
	AddAnimation(160); // hollywater right
	AddAnimation(161); // hollywater left
	AddAnimation(162); // hollywater - fire effect
}

void Weapon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	for (UINT i = 1; i < coObjects->size(); i++)
	{
		float left_a, top_a, right_a, bottom_a;// obj khac
		float left, top, right, bottom; // simon
		coObjects->at(i)->GetBoundingBox(left_a, top_a, right_a, bottom_a); // bbox obj khac
		GetBoundingBox(left, top, right, bottom);					// bbox simon 

		if (CheckAABB( left, top, right, bottom,left_a, top_a, right_a, bottom_a ))
		{
			if (dynamic_cast<CCandle*>(coObjects->at(i))) // if e->obj is CANDLE 				
			{
				coObjects->at(i)->SetState(CANDLE_STATE_FIRE);
			}

		}
	}
}

void Weapon::Render()
{
	switch (state)
	{
	case WeaponType::DAGGER:
		isFlying = true;
		break;

	case WeaponType::AXE:
		isThrowing = true;
		vx = AXE_SPEED * nx;
		vy = WEAPON_GRAVITY;
		break;

	case WeaponType::HOLLY_WATER:
		isThrowing = true;
		vx = HOLLYWATER_SPEED * nx;
		vy = WEAPON_GRAVITY;
		break;
	case WeaponType::STOP_WATCH:
		isThrowing = true;
		vx = HOLLYWATER_SPEED * nx;
		vy = WEAPON_GRAVITY;
		break;
	}
	int alpha = 255;
	animations[ani]->Render(x, y, alpha);
	RenderBoundingBox();
}



void Weapon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (CSimon::GetInstance()->isAttacking && isFlying || isThrowing)
	{
		switch (state)
		{
		case WeaponType::DAGGER:
			left = x;
			top = y;
			right = left + DAGGER_BBOX_WIDTH;
			bottom = top + DAGGER_BBOX_HEIGHT;
			break;

		case WeaponType::AXE:
			left = x;
			top = y;
			right = left + WEAPON_BBOX;
			bottom = top + WEAPON_BBOX;
			break;

		case WeaponType::HOLLY_WATER:
			left = x;
			top = y;
			right = left + WEAPON_BBOX;
			bottom = top + WEAPON_BBOX;

			break;

		case WeaponType::STOP_WATCH:
			left = x;
			top = y;
			right = left + WEAPON_BBOX;
			bottom = top + WEAPON_BBOX;
			break;
		}
	}

}

//void Weapon::UpdateCurWeapon(DWORD dt)
//{
//	CGameObject::Update(dt);
//
//}

void Weapon::SetState(int state)
{
	nx = CSimon::GetInstance()->nx;

	switch (state)
	{
	case WeaponType::DAGGER:
		isFlying = true;
		vx = DAGGER_SPEED * nx;
		vy = WEAPON_GRAVITY;
		break;

	case WeaponType::AXE:
		isThrowing = true;
		vx = AXE_SPEED * nx;
		vy = WEAPON_GRAVITY;
		break;

	case WeaponType::HOLLY_WATER:
		isThrowing = true;
		vx = HOLLYWATER_SPEED * nx;
		vy = WEAPON_GRAVITY;
		break;
	case WeaponType::STOP_WATCH:
		isThrowing = true;
		vx = HOLLYWATER_SPEED * nx;
		vy = WEAPON_GRAVITY;
		break;
	}
}

		

