#include "ScenePlayer.h"
#include "CTileMap.h"
#include "Whip.h"
#include "Brick.h"
#include "Door.h"
#include "Simon.h"
#include "Candle.h"
#include "HiddenObject.h"
#include "Zombie.h"



ScenePlayer::ScenePlayer()
{

}

void ScenePlayer::LoadResources()
{

	//LOAD MAP
	CTileMaps::GetInstance()->AddMap(1000, 9, L"map\\sprites1.txt", L"map\\map1.txt");
	CTileMaps::GetInstance()->AddMap(2000, 10, L"map\\sprites2.txt", L"map\\map2.txt");
	CTileMaps::GetInstance()->AddMap(3000, 11, L"map\\sprites3.txt", L"map\\map3.txt");

	CSimon::GetInstance()->SetPosition(0, 300);

	objects.push_back(CSimon::GetInstance()); //SIMON LA VI TRI 0

	// OBJECT SCENE 1
	/*===========CANDLE========= */
	for (int i = 0; i < 5; i++)
	{
		CCandle* candle = new CCandle();
		candle->SetState(CANDLE_STATE_ABLE);
		candle->SetPosition(150 + i * 250, 305);

		switch (i)
		{
		case 0:
			candle->SetItemState(ItemType::ITEM_BIG_HEART);
			break;
		case 1:
			candle->SetItemState(ItemType::ITEM_SMALL_HEART);
			break;

		case 2:
			candle->SetItemState(ItemType::ITEM_UPGRADE_WHIP);
			break;

		case 3:
			candle->SetItemState(ItemType::ITEM_UPGRADE_WHIP);
			break;
		case 4:
			candle->SetItemState(ItemType::ITEM_DAGGER);
			break;
		}
		objects.push_back(candle);
	}


	/*===========BRICK========= */
	for (int i = 0; i < 100; i++) //			map_width / brick_width = 96 -> lay 100 vien gach
	{
		CBrick* brick = new CBrick();
		brick->SetPosition(0 + i * 16.0f, 370); // set vi tri du 1 vien gach an o dau map de simon k bi rot
		objects.push_back(brick);
	}

	for (int i = 0; i < 10; i++) // wall invisible cuoi map de simon k di ra khoi map
	{
		CBrick* brick = new CBrick();
		brick->SetPosition(CTileMaps::GetInstance()->GetMap(1000)->GetMapWidth() - 30.0f, 350.0f - i * BRICK_BBOX_WIDTH);
		objects.push_back(brick);
	}

	////DOOR AN DE QUA MAN2

	for (int i = 0; i < 3; i++) //  door of castle
	{
		CDoor* door = new CDoor();
		door->SetPosition(CTileMaps::GetInstance()->GetMap(1000)->GetMapWidth() - 150.0f, 350.0f - i * BRICK_BBOX_WIDTH);
		objects.push_back(door);
	}


	//HiddenObject* hidden_obj = new HiddenObject();
	//hidden_obj->SetPosition(1250.0f, 330.0f );
	//objects.push_back(hidden_obj);

	///*===========ZOMBIE========= */
	

	//CZombie* zombie = new CZombie();
	//zombie->SetPosition(100, 305);
	//zombie->SetState(ENEMY_STATE_WALKING);
	//objects.push_back(zombie);

	//CFishman *fishman = new CFishMan();
	//fishman->SetPosition(300, 305);
	//fishman->SetState(ENEMY_STATE_WALKING);
	//objects.push_back(fishman);

	//CDog *dog = new CDog();
	//dog->SetPosition(200, 305);
	//dog->SetState(ENEMY_STATE_WALKING);
	//objects.push_back(dog);

	// BAT HAVE SOME BUGS
	//CBat *bat = new CBat();
	//bat->SetPosition(200, 305);
	//bat->SetState(ENEMY_STATE_WALKING);
	//objects.push_back(bat);
}


void ScenePlayer::Update(float dt)
{
	
	vector<LPGAMEOBJECT> coObjects; // mang chua cac obj co kha nang va cham
	for (int i = 1; i < objects.size(); i++)
	{
		if (objects[i]->isAble) //cac obj ton tai thi cho vao list obj co kha nang va cham
			coObjects.push_back(objects[i]);
	}
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}

	int mapWidth = CTileMaps::GetInstance()->GetMap(1000)->GetMapWidth();
	float cx, cy;
	CSimon::GetInstance()->GetPosition(cx, cy);

	cx = cx - SCREEN_WIDTH / 2 + 30; // vi tri cam luon de Simon o giua man hinh
	//cy -= SCREEN_HEIGHT / 2;

	if (cx < 0) //TH: Simon o dau map
		cx = 0;

	else if (cx + SCREEN_WIDTH > mapWidth) // TH: Simon di qua 1/2 cuoi map
		return;

	CGame::GetInstance()->SetCamPos(cx, 0.0f);
}



void ScenePlayer::Render()
{
	CTileMaps::GetInstance()->GetMap(1000)->RenderMap();  //MapID 1 : 1000

	for (int i = 1; i < objects.size(); i++)
	{
		//if (objects[i]->isAble) //ktra trang thai obj -> neu ton tai thi render
		objects[i]->Render();
	}
	objects[0]->Render(); // SIMON -> ve cuoi cung
}