#include "Scenes.h"
#include "CTileMap.h"
#include "Whip.h"
#include "Brick.h"
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

LPSCENE Scenes::GetScene(int SceneID)
{
	return scenes[SceneID];
}

Scene::Scene()
{
	this->SceneID = SCENE_1;

	LoadResources();
	Render();
}

void Scene::LoadResources()
{
	CSimon::GetInstance()->SetPosition(0.0f, 0);
	objects_stage_1.push_back(CSimon::GetInstance());
	objects_stage_1.push_back(CWhip::GetInstance());


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

	for (int i = 0; i < 3; i++) //  visible door of castle
	{
		CBrick *brick = new CBrick();
		brick->SetPosition(CTileMaps::GetInstance()->GetMap(MAP_1)->GetMapWidth() - 150.0f, 350.0f - i * BRICK_BBOX_WIDTH);
		objects_stage_1.push_back(brick);
	}

	// DOOR AN CUOI MAP 1
	//brick = new CBrick();
	//brick->SetPosition(CTileMaps::GetInstance()->GetMap(MAP_1)->GetMapWidth() - TILE_SIZE, 350.0f);
	//brick->AddAnimation(271);
	//objects_stage_1.push_back(brick);



	///*===========ZOMBIE========= */
	
}
void Scene::Update(float dt)
{

}
void Scene::Render()
{
	
}
