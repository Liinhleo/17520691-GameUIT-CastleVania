#include "Simon.h"
#include "Zombie.h"

CSimon* CSimon::__instance = NULL;
CSimon* CSimon::GetInstance()
{
	if (__instance == NULL) __instance = new CSimon();
	return __instance;
}
void CSimon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x + 15;
	top = y;
	if (isSitting)
	{
		right = left + SIMON_BBOX_WIDTH;
		bottom = y + SIMON_BBOX_HEIGHT - 10;
	}
	else
	{
		right = left + SIMON_BBOX_WIDTH;
		bottom = y + SIMON_BBOX_HEIGHT + 5;
	}
}

CSimon::CSimon()
{
	AddAnimation(400); // IDLE RIGHT
	AddAnimation(401); // IDLE LEFT
	AddAnimation(402); // WALK RIGHT
	AddAnimation(403); // WALK LEFT
	AddAnimation(404); // DIE RIGHT
	AddAnimation(405); // DIE LEFT
	AddAnimation(406); // JUMP RIGHT
	AddAnimation(407); // JUMP LEFT 
	AddAnimation(408); // ATTACK RIGHT
	AddAnimation(409); // ATTACK LEFT 
	AddAnimation(410); // SIT RIGHT
	AddAnimation(411); // SIT LEFT
	AddAnimation(412); // SIT_ATTACK RIGHT
	AddAnimation(413); // SIT_ATTACK LEFT
	AddAnimation(414); // HURT RIGHT
	AddAnimation(415); // HURT LEFT
	AddAnimation(416); // CHANGE COLOR RIGHT
	AddAnimation(417); // CHANGE COLOR LEFT

	SetPosition(0.0f, 0);

	//Simon co vu khi -> weapon state none
	subWeapon = new Weapon();
	subWeapon->SetState(curSupWeapon);

	CWhip::GetInstance()->SetState(WHIP_STATE_DISABLE);
}


void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// khi doi mau thi vx = 0 (dung yen)
	if (isChangeColor)
	{
		vx = 0;
		isWalking = false;
	}

	// Calculate dx, dy 
	CGameObject::Update(dt);

	// Simple fall down
	vy += SIMON_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state != SIMON_STATE_DIE)
	{
		CalcPotentialCollisions(coObjects, coEvents);
	}

	if (GetTickCount() - untouchable_start > SIMON_UNTOUCHABLE_TIME)
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

		if (nx != 0) vx = 0;	//va cham theo phuong x
		if (ny != 0) vy = 0;	//va cham theo truc y

		// Xu ly va cham voi item -> Set CurSupWeapon
		for (UINT i = 1; i < coObjects->size(); i++)
		{
			float left_a, top_a, right_a, bottom_a;// obj khac
			float left, top, right, bottom; // whip

			coObjects->at(i)->GetBoundingBox(left_a, top_a, right_a, bottom_a); // bbox obj khac
			GetBoundingBox(left, top, right, bottom);					// bbox whip 

			if (CheckAABB(left_a, top_a, right_a, bottom_a, left, top, right, bottom))
			{
				if (dynamic_cast<CCandle*>(coObjects->at(i)) && coObjects->at(i)->GetState() == CANDLE_STATE_FALLING_ITEM) // if e->obj is CANDLE 				
				{
					switch (coObjects->at(i)->GetItemState()) // gan itemstate = subweapon
					{
						// default weaponType::NONE
					case 2:
						SetState(SIMON_STATE_CHANGE_COLOR);
						CWhip::GetInstance()->UpgradeWhip();
						break;
					case 3:
						curSupWeapon = WeaponType::DAGGER;
						break;
					case 4:
						curSupWeapon = WeaponType::AXE;
						break;
					case 5:
						curSupWeapon = WeaponType::STOP_WATCH;
						break;
					case 6:
						curSupWeapon = WeaponType::HOLLY_WATER;
						break;
					}
					coObjects->at(i)->SetState(CANDLE_STATE_DISABLE);

				}



				if (dynamic_cast<CZombie*>(coObjects->at(i)))// if e->obj is zombie 
				{
					SetState(SIMON_STATE_HURT);
					//coObjects->at(i)->SetState(ZOMBIE_STATE_DIE);
				}


			}
			
		}

	}




		
	


	// ngan Simon rot ra man hinh
	if (x <= 0)
		x = 0;

	/* HAM KTRA DE TRANH LAP LAI ANI LIEN TUC */
	// han che nhay lien tuc
	if (vy == 0) //va cham dat
		isJumping = false;	
	
	if (vy == 0) //va cham dat
		isHurting = false;


	CWhip::GetInstance()->SetPosition(x - 80, y);
	CWhip::GetInstance()->nx = nx;

	subWeapon->nx;

	// Han che Attacking/ doi mau lien tuc
	if (animations[ani]->getCurrentFrame() >= MAX_FRAME_ATTACK)
	{
		isAttacking = false;
		isChangeColor = false;
	}

	if (isUsingSupWeapon)
	

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

}

void CSimon::Render()
{
	if (state == SIMON_STATE_DIE) {
		if (nx > 0) ani = SIMON_ANI_DIE_RIGHT;
		else ani = SIMON_ANI_DIE_LEFT;
	}

	else if (isAttacking) {
		if (isSitting) {
			if (nx > 0) ani = SIMON_ANI_SIT_ATTACK_RIGHT;
			else ani = SIMON_ANI_SIT_ATTACK_LEFT;
		}
		else {
			if (nx > 0) ani = SIMON_ANI_ATTACK_RIGHT;
			else ani = SIMON_ANI_ATTACK_LEFT;
		}
	}
	else if (isSitting) {
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
	else if (isChangeColor) {
		if (nx > 0)	ani = SIMON_ANI_CHANGE_COLOR_RIGHT;
		else ani = SIMON_ANI_CHANGE_COLOR_LEFT;
	}
	else if (isWalking) {
		if (nx > 0)	ani = SIMON_ANI_WALKING_RIGHT;
		else ani = SIMON_ANI_WALKING_LEFT;
	}
	else if (isHurting) {
		if (nx > 0) ani = SIMON_ANI_HURT_RIGHT;
		else ani = SIMON_ANI_HURT_RIGHT;
	}

	else {
		if (nx > 0) ani = SIMON_ANI_IDLE_RIGHT;
		else ani = SIMON_ANI_IDLE_LEFT;
	}

	int alpha = 255;
	if (untouchable) alpha = 128; // blur -> lam mo 
	animations[ani]->Render(x, y, alpha);

	RenderBoundingBox();

	if (isAttacking && isUsingSupWeapon && curSupWeapon != WeaponType::NONE)
		subWeapon->Render();
	else if (isAttacking && !isUsingSupWeapon)
		CWhip::GetInstance()->Render();


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

	case SIMON_STATE_CHANGE_COLOR:
		isChangeColor = true;
		vx = 0;
		break;

	case SIMON_STATE_WALKING_RIGHT:
		if (isJumping || isAttacking)
			return;

		else if (isSitting) {
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

		else if (isSitting) {
			nx = -1;
			return;
		}
		isWalking = true;
		vx = -SIMON_WALKING_SPEED;
		nx = -1;

		break;

	case SIMON_STATE_JUMP:
		if (isJumping || isSitting)
			return;
		isWalking = false;
		vy = -SIMON_JUMP_SPEED_Y;
		isJumping = true;
		break;

	case SIMON_STATE_SIT:
		if (isAttacking || isSitting) // dang ngoi thi khong thuc hien cau lenh duoi -> tranh tang bien y -> simon rot :) 
			return;
		isWalking = false;
		vx = 0;
		y = y + 10;
		isSitting = true;
		break;

	case SIMON_STATE_STAND_UP: // de tranh TH simon rot xuong(do chan dinh vien gach)
		if (isAttacking)
			return;
		y = y - 15;
		isSitting = false;
		vx = 0;
		break;

	case SIMON_STATE_ATTACK:
		AttackingState();
		break;

	case SIMON_STATE_HURT:
		isHurting = true;
		vx = -vx;
		vy = -SIMON_HURT_SPEED_Y;
		//y = y + 10;
		//isSitting = true;
		//isJumping = true;

	}
}
void CSimon::AttackingState()
{
	isWalking = false;
	isAttacking = true;

	std::cout << "curSubWeapon: " << curSupWeapon << endl;

	if (CGame::GetInstance()->IsKeyDown(DIK_UP) && curSupWeapon != WeaponType::NONE)
	{
		isUsingSupWeapon = true;
		subWeapon->isFlying = true;
		subWeapon->nx = nx;
		subWeapon->SetPosition(x, y);
		subWeapon->SetState(curSupWeapon);
		CWhip::GetInstance()->SetState(WHIP_STATE_DISABLE); // Khi using subWeapon -> off whip

	}
	else
	{
		isUsingSupWeapon = false;
		CWhip::GetInstance()->SetState(WHIP_STATE_HIT);
	}
}





//bool CSimon::IscollisionItem(CCandle* item)
//{
//	float left_a, top_a, right_a, bottom_a;		// item
//	float left, top, right, bottom;				// simon
//
//	item->GetBoundingBox(left_a, top_a, right_a, bottom_a); // bbox item 
//	GetBoundingBox(left, top, right, bottom);				// bbox simon 
//
//	if (CheckAABB(left_a, top_a, right_a, bottom_a, left, top, right, bottom))
//		return true;
//	LPCOLLISIONEVENT e = SweptAABBEx(item); // kt sweptAABB
//	bool res = e->t > 0 && e->t <= 1.0f; // e->t > 0 co the xay ra va cham (tuong lai) && tgian va cham <= 1 
//	delete(e);
//	return res;
//}

//void CSimon::CheckSubWeapon(CCandle* item)
//{
//
//	if (IscollisionItem)
//	{
//		switch (GetItemState())
//		{
//		case 2:
//			SetState(SIMON_STATE_CHANGE_COLOR);
//			CWhip::GetInstance()->UpgradeWhip();
//			break;
//		case 3:
//			subWeapon->SetState(WeaponType::DAGGER);
//			break;
//		case 4:
//			subWeapon->SetState(WeaponType::AXE);
//			break;
//		case 5:
//			subWeapon->SetState(WeaponType::STOP_WATCH);
//			break;
//		case 6:
//			subWeapon->SetState(WeaponType::HOLLY_WATER);
//			break;
//
//		}
//
//
//		coObjects->at(i)->SetState(CANDLE_STATE_DISABLE);
//	}
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


