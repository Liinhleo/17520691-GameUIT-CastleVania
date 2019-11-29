#include "Scenes.h"
#include "CTileMap.h"
#include "Whip.h"
#include "Brick.h"
#include "Door.h"
#include "Simon.h"
#include "Candle.h"
#include "Game.h"


Scenes* Scenes::__instance = NULL;
Scenes* Scenes::GetInstance()
{
	if (__instance == NULL) __instance = new Scenes();
	return __instance;
}

void Scenes::AddScene(int SceneID)
{
	curScene = new Scene();
	scenes[SceneID] = curScene; // Gan curScene vao scenes[SceneID]
}

LPSCENE Scenes::GetCurScene(int SceneID)
{
	return scenes[SceneID];
}


Scene::Scene()
{
	this->SceneID = SCENE_1;
}

void Scene::LoadResources()
{
	//LOAD MAP
	CTileMaps::GetInstance()->LoadResource(MAP_1);	
	CSimon::GetInstance()->SetPosition(0, 300);

	//NEED TO RETHINKING
	objects_stage_1.push_back(CSimon::GetInstance()); //SIMON LA VI TRI 0

	// OBJECT SCENE 1
	/*===========CANDLE========= */
	for (int i = 0; i < 5; i++)
	{
		CCandle *candle = new CCandle();
		candle->SetState(CANDLE_STATE_ABLE);
		candle->SetPosition(150 + i * 250, 305);

		switch (i)
		{
		case 0:
			candle->SetItemState(0);
			break;
		case 1:
			candle->SetItemState(1);
			break;

		case 2:
			candle->SetItemState(2);
			break;

		case 3:
			candle->SetItemState(2);
			break;
		case 4:
			candle->SetItemState(3);
			break;

		}

		objects_stage_1.push_back(candle);
	}


	/*===========BRICK========= */
	for (int i = 0; i < 100; i++) //			map_width / brick_width = 96 -> lay 100 vien gach
	{
		CBrick *brick = new CBrick();
		brick->SetPosition(0 + i * 16.0f, 370); // set vi tri du 1 vien gach an o dau map de simon k bi rot
		objects_stage_1.push_back(brick);
	}

	for (int i = 0; i < 10; i++) // wall invisible cuoi map de simon k di ra khoi map
	{
		CBrick *brick = new CBrick();
		brick->SetPosition(CTileMaps::GetInstance()->GetMap(MAP_1)->GetMapWidth() - 30.0f, 350.0f - i * BRICK_BBOX_WIDTH);
		objects_stage_1.push_back(brick);
	}

	for (int i = 0; i < 3; i++) //  door of castle
	{
		CDoor *door = new CDoor();
		door->SetPosition(CTileMaps::GetInstance()->GetMap(MAP_1)->GetMapWidth() - 150.0f, 350.0f - i * BRICK_BBOX_WIDTH);
		objects_stage_1.push_back(door);
	}


	

	

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


void Scene::Update(float dt)
{
	vector<LPGAMEOBJECT> coObjects; // mang chua cac obj co kha nang va cham
	for (int i = 1; i < objects_stage_1.size(); i++)
	{
		if (objects_stage_1[i]->isAble) //cac obj ton tai thi cho vao list obj co kha nang va cham
			coObjects.push_back(objects_stage_1[i]);
	}
	for (int i = 0; i < objects_stage_1.size(); i++)
	{
		objects_stage_1[i]->Update(dt, &coObjects);
	}

}
void Scene::Render()
{
	for (int i = 1; i < objects_stage_1.size(); i++)
	{
		//if (objects[i]->isAble) //ktra trang thai obj -> neu ton tai thi render
		objects_stage_1[i]->Render();
	}
	objects_stage_1[0]->Render(); // SIMON
}
