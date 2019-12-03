#include "Simon.h"
#include "Enemy.h"
#include "HiddenObject.h"
#include "Candle.h"
#include "Game.h"

CSimon* CSimon::__instance = NULL;
CSimon* CSimon::GetInstance()
{
	if (__instance == NULL) __instance = new CSimon();
	return __instance;
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

	AddAnimation(418); // UPSTAIR RIGHT
	AddAnimation(419); // UPSTAIR LEFT
	AddAnimation(420); // DOWNSTAIR RIGHT
	AddAnimation(421); // DOWNSTAIR LEFT
	AddAnimation(422); // UPSTAIR ATTACK RIGHT
	AddAnimation(423); // UPSTAIR ATTACK LEFT
	AddAnimation(424); // DOWNSTAIR ATTACK RIGHT
	AddAnimation(425); // DOWNSTAIR ATTACK LEFT
	SetPosition(0.0f, 0);

	//Simon co vu khi -> weapon state none
	subWeapon = new Weapon();
	subWeapon->SetState(curSupWeapon);

	CWhip::GetInstance()->SetState(WHIP_STATE_DISABLE);
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

									/*======	XET VA CHAM	 CHO SIMON	======*/
	// Simple fall down
	vy += SIMON_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;	// su kien va cham
	vector<LPCOLLISIONEVENT> coEventsResult;	// danh sach ket qua tra ve 

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);	// tinh toan va cham (objects co kha nang va cham, su kien va cham )

	// turn off collision when die 
	if (GetTickCount() - untouchable_start > SIMON_UNTOUCHABLE_TIME)
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

		if (nx != 0) vx = 0;				//va cham theo phuong x
		if (ny != 0) vy = 0;				//va cham theo truc y


		//for (UINT i = 0; i < coObjects->size(); i++)
		//{
		//	float left_a, top_a, right_a, bottom_a;// obj khac
		//	float left, top, right, bottom; // whip
		//	coObjects->at(i)->GetBoundingBox(left_a, top_a, right_a, bottom_a);		 // bbox obj khac
		//	GetBoundingBox(left, top, right, bottom);									// bbox whip 
		//	if (CheckAABB(left_a, top_a, right_a, bottom_a, left, top, right, bottom))
		//	{
		//		// Xu ly va cham voi item -> Set CurSupWeapon
		//		if (dynamic_cast<Item*>(coObjects->at(i)))			// if e->obj is ITEM 				
		//		{
		//			DebugOut(L"La item");
		//			switch (dynamic_cast<Item*>(coObjects->at(i))->GetItemState()) // gan itemstate = subweapon
		//			{
		//			// XU LY SAU
		//			case ItemType::ITEM_BIG_HEART:
		//				DebugOut(L"Dung vao tim bu");
		//				break;
		//			case ItemType::ITEM_SMALL_HEART:
		//				break;
		//			// default weaponType::NONE
		//			case ItemType::ITEM_UPGRADE_WHIP:
		//				SetState(SIMON_STATE_CHANGE_COLOR);
		//				CWhip::GetInstance()->UpgradeWhip();
		//				break;
		//			case ItemType::ITEM_DAGGER:
		//				curSupWeapon = WeaponType::DAGGER;
		//				break;
		//			case ItemType::ITEM_AXE:
		//				curSupWeapon = WeaponType::AXE;
		//				break;
		//			case ItemType::ITEM_STOP_WATCH:
		//				curSupWeapon = WeaponType::STOP_WATCH;
		//				break;
		//			case ItemType::ITEM_HOLLY_WATER:
		//				curSupWeapon = WeaponType::HOLLY_WATER;
		//				break;
		//			}
		//			coObjects->at(i)->SetState(ITEM_STATE_DISABLE);
		//		}
		//		if (dynamic_cast<CDoor*>(coObjects->at(i)))
		//		{
		//			DebugOut(L"Da cham cua");
		//			isCollisionDoor = true;
		//			/*door->SetState(DOOR_STATE_OPEN);
		//			SetState(SIMON_STATE_AUTOGO);*/
		//		}
		//	}
		//	
		//}
	}
	// ngan Simon rot ra man hinh
	if (x <= 0)
		x = 0;

	/* HAM KTRA DE TRANH LAP LAI ANI LIEN TUC */
	// han che nhay lien tuc
	if (vy == 0) //va cham dat
		isJumping = false;	
	
	//if (vy == 0) //va cham dat
	//	isHurting = false;


	if (isAttacking)
	{
		CWhip::GetInstance()->SetPosition(x - 80, y);
		CWhip::GetInstance()->nx = nx;
		CWhip::GetInstance()->Update(dt, coObjects);

		subWeapon->nx; // lay huong cua Simon
	}
	if (isUsingSupWeapon)
	{
		subWeapon->Update(dt, coObjects);
	}

	// Han che Attacking/ doi mau lien tuc
	if (animations[ani]->getCurrentFrame() >= MAX_FRAME_ATTACK)
	{
		isAttacking = false;
		isChangeColor = false;
	}
	
	if (animations[ani]->getCurrentFrame() >= MAX_FRAME_ONSTAIR)
	{
		isUpStair = false;
		isDownStair = false;
	}

	if (isHurting)
	{
		if (timeWait < SIMON_UNTOUCHABLE_TIME)
			timeWait += dt;
		else
		{
			timeWait = 0;
			isHurting = false;
			SetState(SIMON_STATE_IDLE);
		}
	}

	//// clean up collision events
	//for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

}
void CSimon::Render()
{
	int alpha = 255;

	if (state == SIMON_STATE_DIE) {
		if (nx > 0) ani = SIMON_ANI_DIE_RIGHT;
		else ani = SIMON_ANI_DIE_LEFT;
	}

	else if (isAttacking) {
		if (isSitting) {
			if (nx > 0) ani = SIMON_ANI_SIT_ATTACK_RIGHT;
			else ani = SIMON_ANI_SIT_ATTACK_LEFT;
		}
		else if (isUpStair)
		{
			if (nx > 0) ani = SIMON_ANI_UPSTAIR_ATTACK_RIGHT;
			else ani = SIMON_ANI_UPSTAIR_ATTACK_LEFT;
		}
		else if (isDownStair)
		{
			if (nx > 0) ani = SIMON_ANI_DOWNSTAIR_ATTACK_RIGHT;
			else ani = SIMON_ANI_DOWNSTAIR_ATTACK_LEFT;
		}
		else {
			if (nx > 0) ani = SIMON_ANI_ATTACK_RIGHT;
			else ani = SIMON_ANI_ATTACK_LEFT;
		}
	}
	else if (isUpStair){
		if (isAttacking) {
			if (nx > 0) ani = SIMON_ANI_UPSTAIR_ATTACK_RIGHT;
			else ani = SIMON_ANI_UPSTAIR_ATTACK_LEFT;
		}
		if (nx > 0) ani = SIMON_ANI_UPSTAIR_RIGHT;
		else ani = SIMON_ANI_UPSTAIR_LEFT;
	}
	else if (isDownStair){
		if (isAttacking) {
			if (nx > 0) ani = SIMON_ANI_DOWNSTAIR_ATTACK_RIGHT;
			else ani = SIMON_ANI_DOWNSTAIR_ATTACK_LEFT;
		}
		if (nx > 0) ani = SIMON_ANI_DOWNSTAIR_RIGHT;
		else ani = SIMON_ANI_DOWNSTAIR_LEFT;
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
	
	else {
		if (nx > 0) ani = SIMON_ANI_IDLE_RIGHT;
		else ani = SIMON_ANI_IDLE_LEFT;
	}

	if (isHurting) {
		alpha = 128; //blur
		if (nx > 0) ani = SIMON_ANI_HURT_RIGHT;
		else ani = SIMON_ANI_HURT_LEFT;
	}

	//if (untouchable) alpha = 128; // blur -> lam mo 
	animations[ani]->Render(x, y, alpha);
	RenderBoundingBox();

	//RENDER WEAPON WITH SIMON
	if (isUsingSupWeapon && curSupWeapon != WeaponType::NONE)
		subWeapon->Render();
	 if (isAttacking && !isUsingSupWeapon)
		CWhip::GetInstance()->Render();
}
void CSimon::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case SIMON_STATE_DIE:
		vx = 0.2f * -nx;
		vy = -SIMON_HURT_SPEED_Y;
		y = y + 40;
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
		vx = 0.2f * -nx;
		vy = -SIMON_HURT_SPEED_Y;
		isAttacking = false;
		isWalking = false;

	case SIMON_STATE_UPSTAIR:
		if (isAttacking)
			return;
		isUpStair = true;

		break;

	case SIMON_STATE_DOWNSTAIR:
		if (isAttacking)
			return;
		isDownStair = true;

		break;

	case SIMON_STATE_AUTOGO:
		isWalking = true;
		vx = SIMON_WALKING_SPEED;
		x += dt;
		nx = 1;
		break;
	}
}
void CSimon::AttackingState()
{
	isWalking = false;
	isAttacking = true;


	if (CGame::GetInstance()->IsKeyDown(DIK_UP) && curSupWeapon != WeaponType::NONE)
	{
		isUsingSupWeapon = true;
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

//void CSimon::SetWeapon(Weapon* weapon)
//{
//	if (isCollisionItem)
//	{
//		switch () // gan itemstate = subweapon
//					{
//					// XU LY SAU
//					case ItemType::ITEM_BIG_HEART:
//						DebugOut(L"Dung vao tim bu");
//						break;
//					case ItemType::ITEM_SMALL_HEART:
//						break;
//					// default weaponType::NONE
//					case ItemType::ITEM_UPGRADE_WHIP:
//						SetState(SIMON_STATE_CHANGE_COLOR);
//						CWhip::GetInstance()->UpgradeWhip();
//						break;
//					case ItemType::ITEM_DAGGER:
//						curSupWeapon = WeaponType::DAGGER;
//						break;
//					case ItemType::ITEM_AXE:
//						curSupWeapon = WeaponType::AXE;
//						break;
//					case ItemType::ITEM_STOP_WATCH:
//						curSupWeapon = WeaponType::STOP_WATCH;
//						break;
//					case ItemType::ITEM_HOLLY_WATER:
//						curSupWeapon = WeaponType::HOLLY_WATER;
//						break;
//					}
//					coObjects->at(i)->SetState(ITEM_STATE_DISABLE);
//	}
//}

bool CSimon::isCollisionItem(Item* item)
{
	return this->CheckAABBwithObject(item);
}
