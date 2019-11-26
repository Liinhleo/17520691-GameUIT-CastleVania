//#include "Scenes.h"
//
//Scenes* Scenes::__instance = NULL;
//Scenes* Scenes::GetInstance()
//{
//	if (__instance == NULL) __instance = new Scenes();
//	return __instance;
//}
//void Scenes::AddScene(int SceneID)
//{
//	LPSCENE stage = new Scene(SceneID);
//	scenes[SceneID] = stage;
//}
//LPSCENE Scenes::GetScene(int SceneID)
//{
//	return scenes[SceneID];
//}
//
//Scene::Scene(int SceneID)
//{
//	this->SceneID = SceneID;
//
//	//LoadResources();
//	//Render();
//}
//
//void Scene::LoadResources()
//{
//	//CTileMaps::GetInstance()->LoadResource(MAP_1);
//
//	CSimon::GetInstance()->SetPosition(0.0f, 0);
//	objects_stage_1.push_back(CSimon::GetInstance());
//	objects_stage_1.push_back(CWhip::GetInstance());
//	/*===========CANDLE========= */
//	for (int i = 0; i < 5; i++)
//	{
//		candle = new CCandle();
//		candle->SetState(CANDLE_STATE_ABLE);
//		candle->SetPosition(150 + i * 250, 305);
//
//		switch (i)
//		{
//		case 0:
//			candle->SetItemState(0);
//			break;
//		case 1:
//			candle->SetItemState(1);
//			break;
//
//		case 2:
//			candle->SetItemState(2);
//			break;
//
//		case 3:
//			candle->SetItemState(2);
//			break;
//		case 4:
//			candle->SetItemState(3);
//			break;
//
//		}
//
//		objects_stage_1.push_back(candle);
//	}
//
//
//	/*===========BRICK========= */
//	for (int i = 0; i < 100; i++) //			map_width / brick_width = 96 -> lay 100 vien gach
//	{
//		brick = new CBrick();
//		brick->SetPosition(0 + i * 16.0f, 370); // set vi tri du 1 vien gach an o dau map de simon k bi rot
//		objects_stage_1.push_back(brick);
//	}
//
//	for (int i = 0; i < 10; i++) // wall invisible cuoi map de simon k di ra khoi map
//	{
//		brick = new CBrick();
//		brick->AddAnimation(601);
//		brick->SetPosition(CTileMaps::GetInstance()->GetMap(1000)->GetMapWidth() - 30.0f, 350.0f - i * BRICK_BBOX_WIDTH);
//		objects_stage_1.push_back(brick);
//	}
//
//	for (int i = 0; i < 3; i++) //  visible door of castle
//	{
//		brick = new CBrick();
//		brick->AddAnimation(601);
//		brick->SetPosition(CTileMaps::GetInstance()->GetMap(1000)->GetMapWidth() - 150.0f, 350.0f - i * BRICK_BBOX_WIDTH);
//		objects_stage_1.push_back(brick);
//	}
//
//
//}
//void Scene::Update(float dt)
//{
//
//	vector<LPGAMEOBJECT> coObjects_stage_1;
//	for (int i = 1; i < objects_stage_1.size(); i++)
//	{
//		if (objects_stage_1[i]->isAble) //cac obj ton tai thi cho vao list obj co kha nang va cham
//			coObjects_stage_1.push_back(objects_stage_1[i]);
//	}
//	for (int i = 0; i < objects_stage_1.size(); i++)
//	{
//		objects_stage_1[i]->Update(dt, &coObjects_stage_1);
//	}
//
//
//	//int mapWidth = CTileMaps::GetInstance()->GetMap(MAP_1)->GetMapWidth(); // lay do dai map 
//	//float cx, cy;
//	//CSimon::GetInstance()->GetPosition(cx, cy);
//
//	//cx = cx - SCREEN_WIDTH / 2 + 30; // vi tri cam luon de Simon o giua man hinh
//	////cy -= SCREEN_HEIGHT / 2;
//
//	//if (cx < 0) //TH: Simon o dau map
//	//	cx = 0;
//
//	//else if (cx + SCREEN_WIDTH > mapWidth) // TH: Simon di qua 1/2 cuoi map
//	//	return;
//
//	//CGame::GetInstance()->SetCamPos(cx, 0.0f);
//}
//void Scene::Render()
//{
//	//CTileMaps::GetInstance()->GetMap(MAP_1)->RenderMap();
//
//	for (int i = 1; i < objects_stage_1.size(); i++)
//	{
//		if (objects_stage_1[i]->isAble) //ktra trang thai obj -> neu ton tai thi render
//			objects_stage_1[i]->Render();
//	}
//	objects_stage_1[0]->Render();
//}
