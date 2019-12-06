#include "ScenePlayer.h"
#include "CTileMap.h"
#include "Game.h"
#include "Scenes.h"
#include "Dog.h"
#include "BottomStair.h"
#include "TopStair.h"

vector <LPGAMEOBJECT> listCandle;
vector <LPGAMEOBJECT> listItem;
vector <LPGAMEOBJECT> listBrick;
vector <LPGAMEOBJECT> listHiddenObj;
vector <LPGAMEOBJECT> listEnemy;
vector <LPGAMEOBJECT> listDoor;
vector <LPGAMEOBJECT> listStair;
vector <LPGAMEOBJECT> listZombie;


vector <LPGAMEOBJECT>coObject1;		// bao gom: Simon, brick
vector <LPGAMEOBJECT>coObject2;		// bao gom: Candle, HiddenObj, Door, Stair

vector <LPGAMEOBJECT>SimonItem;		// bao gom: Simon, Item
vector <LPGAMEOBJECT>SimonEnemy;	// bao gom: Simon, enemy
vector <LPGAMEOBJECT>WeaponObject;	// bao gom: weapon, whip, enemy, candle



wchar_t* ConvertToWideChar(char* p) // covert string -> wchar_t*
{
	wchar_t* r;
	r = new wchar_t[strlen(p) + 1];

	char* tempsour = p;
	wchar_t* tempdest = r;
	while (*tempdest++ = *tempsour++);

	return r;
}

ScenePlayer::ScenePlayer()
{
	this->stage = 2; //default
}

void ScenePlayer::LoadResources()
{
#pragma region	LOADFILE
	ReadFile();
	CTileMaps::GetInstance()->AddMap(1000, 9, L"map\\sprites1.txt", L"map\\map1.txt");
	CTileMaps::GetInstance()->AddMap(2000, 10, L"map\\sprites2.txt", L"map\\map2.txt");
	CTileMaps::GetInstance()->AddMap(3000, 11, L"map\\sprites3.txt", L"map\\map3.txt");
	CSimon::GetInstance()->SetPosition(0, 300);
#pragma endregion	LOADFILE

	// DO SIMON KHONG THAY DOI
	SimonItem.push_back(CSimon::GetInstance());
	SimonEnemy.push_back(CSimon::GetInstance());

	subWeapon = new Weapon();
	WeaponObject.push_back(subWeapon);


#pragma region LOAD_OBJECT_STAGE_1
	if (stage == 1)
	{
		/*===========CANDLE========= */
		for (int i = 0; i < 5; i++)
		{
			candle = new CCandle();
			candle->SetState(CANDLE_STATE_ABLE);
			candle->SetAniCandle(CandleType::BIG_CANDLE);
			candle->SetPosition(150 + i * 250, 305);
			candle->SetId(i);
			listCandle.push_back(candle);
		}
		/*===========BRICK========= */
		CBrick* brick = new CBrick();
		brick->SetPosition(0 , 370); // set vi tri du 1 vien gach an o dau map de simon k bi rot
		brick->SetWidthHeigth(CTileMaps::GetInstance()->GetMap(MAP_1)->GetMapWidth(), BRICK_BBOX_WIDTH);
		listBrick.push_back(brick);

		//DOOR AN DE QUA MAN2
		HiddenObject* hidden_obj = new HiddenObject(1,16,30);
		hidden_obj->SetPosition(1300.0f, 305);
		listHiddenObj.push_back(hidden_obj);

	}
#pragma endregion LOAD_OBJECT_STAGE_1

#pragma region	LOAD_OBJECT_STAGE_2
	else if (stage == 2)
	{	
		/*===========BRICK========= */
		// TAO GROUND
		brick = new CBrick();
		brick->SetPosition(0, 400); 
		brick->SetWidthHeigth(CTileMaps::GetInstance()->GetMap(MAP_2)->GetMapWidth(), BRICK_BBOX_WIDTH);
		listBrick.push_back(brick);

		for (int i = 0; i < 1; i++)	// tuong o cuoi map 2
		{
			brick = new CBrick();
			brick->SetPosition(3050 + i *500, 300);
			brick->SetWidthHeigth(BRICK_BBOX_WIDTH,100);
			listBrick.push_back(brick);
		}
		for (int i = 0; i < 1; i++) // them 1
		{
			brick = new CBrick();
			brick->SetPosition(1370.0f + i *1, FLOOR_2);
			brick->SetWidthHeigth(100, BRICK_BBOX_WIDTH);
			listBrick.push_back(brick);
		}
		for (int i = 0; i < 1; i++) // them 2
		{
			brick = new CBrick();
			brick->SetPosition(1500.0f , 210.0f);
			brick->SetWidthHeigth(345, BRICK_BBOX_WIDTH);
			listBrick.push_back(brick);
		}
		for (int i = 0; i < 1; i++) // them 3
		{
			brick = new CBrick();
			brick->SetPosition(1850.0f, FLOOR_2);
			brick->SetWidthHeigth(200, BRICK_BBOX_WIDTH);
			listBrick.push_back(brick);
		}
		//for (int i = 0; i < 1; i++) // them cau thang 1
		//{
		//	CBrick* brick = new CBrick();
		//	brick->SetPosition(2780.0f, 210.0f);
		//	brick->SetWidthHeigth(600, BRICK_BBOX_WIDTH);
		//	listBrick.push_back(brick);
		//}
		//for (int i = 0; i < 1; i++)	// tuong o cuoi map -> de xuong tang ham
		//{
		//	CBrick* brick = new CBrick();
		//	brick->SetPosition(3610.0f, 400.0f);
		//	brick->SetWidthHeigth( BRICK_BBOX_WIDTH, 100 );
		//	listBrick.push_back(brick);
		//}
		//for (int i = 0; i < 3; i++)
		//{
		//	CBrick* brick = new CBrick();
		//	brick->SetPosition(3720.0f + i * 16.0f, 240.0f);
		//	listBrick.push_back(brick);
		//}
		//for (int i = 0; i < 26; i++) // them cau thang 1
		//{
		//	CBrick* brick = new CBrick();
		//	brick->SetPosition(3900.0f + i * 16.0f, 210.0f);
		//	listBrick.push_back(brick);
		//}
		//for (int i = 0; i < 1; i++)
		//{
		//	CBrick* brick = new CBrick();
		//	brick->SetPosition(3330.0f + i * 450.0f, 280.0f);
		//	brick->SetWidthHeigth(72, BRICK_BBOX_WIDTH);
		//	listBrick.push_back(brick);
		//}

		/*===========CANDLE========= */
		
		for (int i = 0; i < 5; i++)
		{
			candle = new CCandle();
			candle->SetState(CANDLE_STATE_ABLE);
			candle->SetAniCandle(CandleType::SMALL_CANDLE);
			candle->SetPosition(190 + i * 250, FLOOR_2);
			listCandle.push_back(candle);
		}
		for (int i = 0; i < 5; i++)
		{
			candle = new CCandle();
			candle->SetState(CANDLE_STATE_ABLE);
			candle->SetAniCandle(CandleType::SMALL_CANDLE);
			candle->SetPosition(60 + i * 250, FLOOR_1);
			listCandle.push_back(candle);
		}
		for (int i = 0; i < 2; i++)
		{
			candle = new CCandle();
			candle->SetState(CANDLE_STATE_ABLE);
			candle->SetAniCandle(CandleType::SMALL_CANDLE);
			candle->SetPosition(1480.0f + i * 350, FLOOR_1);
			listCandle.push_back(candle);
		}
		for (int i = 0; i < 3; i++)
		{
			candle = new CCandle();
			candle->SetState(CANDLE_STATE_ABLE);
			candle->SetAniCandle(CandleType::SMALL_CANDLE);
			candle->SetPosition(1400.0f + i * 300, 150);
			listCandle.push_back(candle);
		}
		for (int i = 0; i < 4; i++)
		{
			candle = new CCandle();
			candle->SetState(CANDLE_STATE_ABLE);
			candle->SetAniCandle(CandleType::SMALL_CANDLE);
			candle->SetPosition(2100.0f + i * 130, FLOOR_1);
			listCandle.push_back(candle);
		}
		
		/*===========TOP STAIR ========= */
		
			listStair.push_back(new BottomStair(1, 1230, 370, 30, 30));
			listStair.push_back(new BottomStair(1, 1350, 200, 30, 30));
		

		
			/*bottomstair = new BottomStair(3, 30, 30);
			bottomstair->SetPosition(1750.0f, 180);
			listStair.push_back(bottomstair);
		
			topStair = new TopStair(4, 30, 30);
			topStair->SetPosition(1500, 150);
			listStair.push_back(topStair);*/
		

		///*===========ENEMY========= */
		// Dog thu nhat tren cau thang
		for (int i = 0; i < 2; i++)
		{
			CDog* dog = new CDog();
			dog->SetPosition(1400.0f + i * 500, 250);
			dog->SetState(ENEMY_STATE_WALKING);
			listEnemy.push_back(dog);
		}
		// Dog thu 2 tren cau thang
		CDog* dog = new CDog();
		dog->SetPosition(1750.0f,180);
		dog->SetState(ENEMY_STATE_WALKING);
		listEnemy.push_back(dog);

		for (int i = 0; i < 3; i++)
		{
			CZombie *zombie = new CZombie();
			zombie->SetPosition(400 + i * 100, 300);
			listZombie.push_back(zombie);
			objects.push_back(zombie);

		}
		//HiddenObject* hidden_obj = new HiddenObject(16,30);
		//hidden_obj->SetPosition(1250.0f, 330.0f );
		//objects.push_back(hidden_obj);

		// BAT HAVE SOME BUGS
		//CBat *bat = new CBat();
		//bat->SetPosition(200, 305);
		//bat->SetState(ENEMY_STATE_WALKING);
		//objects.push_back(bat);

		/*PUSH VO DANH SACH X*/
	}
#pragma endregion	LOAD_OBJECT_STAGE_2

#pragma region LOAD_OBJECT_STAGE_3
	else if (stage == 3)
	{
		//CFishman *fishman = new CFishMan();
		//fishman->SetPosition(300, 305);
		//fishman->SetState(ENEMY_STATE_WALKING);
		//objects.push_back(fishman);
		// xet sau
	}
#pragma endregion LOAD_OBJECT_STAGE_3

}

void ScenePlayer::Update(float dt)
{

	CSimon::GetInstance()->Update(dt,&coObject1);
	for (int i = 0; i < listZombie.size(); i++)
	{
		listZombie[i]->Update(dt, &coObject1);
	}

#pragma region	COOBJECT 1
	coObject1.push_back(CSimon::GetInstance());
	for (int i = 0; i < listItem.size(); i++)
	{
		if (listItem[i]->isAble)
			coObject1.push_back(listItem[i]);
	}
	for (int i = 0; i < listBrick.size(); i++)
	{
		coObject1.push_back(listBrick[i]);
	}
#pragma endregion SIMON, BRICK, ITEM


#pragma region	COOBJECT 2
	for (int i = 0; i < listCandle.size(); i++)
	{
		if(listCandle[i]->isAble)
			coObject2.push_back(listCandle[i]);
		listCandle[i]->Update(dt);
	}
	for (int i = 0; i < listEnemy.size(); i++)
	{
		if (listEnemy[i]->isAble)
			coObject2.push_back(listEnemy[i]);
		listEnemy[i]->Update(dt);
	}
	for (int i = 0; i < listHiddenObj.size(); i++)
	{
		coObject2.push_back(listHiddenObj[i]);
	}
	for (int i = 0; i < listStair.size(); i++)
	{
		coObject2.push_back(listStair[i]);
	}
#pragma endregion CANDLE, DOOR, HIDDENOBJ, STAIR, ENEMY


#pragma region	WEAPONOBJECT
	WeaponObject.push_back(CWhip::GetInstance());
	for (int i = 0; i < listCandle.size(); i++)
	{
		if (listCandle[i]->isAble)
			WeaponObject.push_back(listCandle[i]);
	}
	for (int i = 0; i < listEnemy.size(); i++)
	{
		if (listEnemy[i]->isAble)
			WeaponObject.push_back(listEnemy[i]);

	}
	CWhip::GetInstance()->WhipCollisionObject(WeaponObject);
	subWeapon->WeaponCollisionObject(WeaponObject);

#pragma endregion	WEAPON, WHIP, ENEMY, CANDLE
	
	
	CheckCollision_SimonAndDoor();


	 //UPDATE NEW ITEM WHEN COLLISION VS WEAPON
	//for (int i = 0; i < listCandle.size(); i++)
	//{
	//	if (listCandle[i]->GetAble() == false) // dieu kien Candle bi roi danh
	//	{
	//		float x, y;
	//		Item* item = new Item();
	//		item->SetState(ITEM_STATE_SHOW);
	//		switch (i)
	//		{
	//		case 0:
	//			item->SetItemState(ItemType::ITEM_BIG_HEART);
	//			break;
	//		case 1:
	//			item->SetItemState(ItemType::ITEM_SMALL_HEART);
	//			break;
	//		case 2:
	//			item->SetItemState(ItemType::ITEM_UPGRADE_WHIP);
	//			break;
	//		case 3:
	//			item->SetItemState(ItemType::ITEM_UPGRADE_WHIP);
	//			break;
	//		case 4:
	//			item->SetItemState(ItemType::ITEM_DAGGER);
	//			break;
	//		}
	//		listCandle[i]->GetPosition(x, y);	
	//		item->SetPosition(x, y);
	//		listItem.push_back(item);
	//		listCandle.erase(listCandle.begin() + i);// xoa candle tai vi tri thu i
	//	}
	//}

	//for (int i = 0; i < objects.size(); i++)
	//{
	//	//if (objects[i]->isAble) //cac obj ton tai thi cho vao list obj co kha nang va cham
	//	//	coObjects.push_back(objects[i]);
	//	if (dynamic_cast<CCandle*>(listCandle.at(i)) || dynamic_cast<CDoor*>(listDoor.at(i))
	//		|| dynamic_cast<HiddenObject*>(listHiddenObj.at(i)) || dynamic_cast<CEnemy*>(listEnemy.at(i))
	//		|| dynamic_cast<Weapon*>(objects.at(i)) || dynamic_cast<CWhip*>(objects.at(i)))
	//	{
	//		coObject2.push_back(objects[i]);
	//	}
	//}
	//for (int i = 0; i < objects.size(); i++)
	//{
	//	if (dynamic_cast<CCandle*>(listCandle.at(i)) || dynamic_cast<CDoor*>(objects.at(i))
	//		|| dynamic_cast<HiddenObject*>(objects.at(i)) || dynamic_cast<CEnemy*>(objects.at(i))
	//		|| dynamic_cast<Weapon*>(objects.at(i)) || dynamic_cast<CWhip*>(objects.at(i)))
	//	{
	//		objects[i]->Update(dt, &coObject2);
	//	}
	//}


#pragma region CAMERA
	//HAM UPDATE CAMERA THEO SIMON THEO MAP 1
	//if (stage == 1)
	//{
	//	int mapWidth = CTileMaps::GetInstance()->GetMap(MAP_1)->GetMapWidth();
	//	float cx, cy;
	//	CSimon::GetInstance()->GetPosition(cx, cy);
	//	cx = cx - SCREEN_WIDTH / 2 + 30; // vi tri cam luon de Simon o giua man hinh
	//	//cy -= SCREEN_HEIGHT / 2;

	//	if (cx < 0) //TH: Simon o dau map
	//		cx = 0;

	//	else if (cx + SCREEN_WIDTH > mapWidth) // TH: Simon di qua 1/2 cuoi map
	//		return;

	//	CGame::GetInstance()->SetCamPos(cx, 0.0f);
	//}

	if (stage == 2)
	{
		int mapWidth = CTileMaps::GetInstance()->GetMap(MAP_2)->GetMapWidth();
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
#pragma endregion CAMERA


}


void ScenePlayer::Render()
{
	if (stage == 1)
	{
		CTileMaps::GetInstance()->GetMap(MAP_1)->RenderMap();
		for (int i = 0; i < listCandle.size(); i++)
		{
			listCandle[i]->Render();
		}
		for (int i = 0; i < listBrick.size(); i++)
		{
			listBrick[i]->Render();
		}
		for (int i = 0; i < listHiddenObj.size(); i++)
		{
			listHiddenObj[i]->Render();
		}
		CSimon::GetInstance()->Render(); // Simon ve cuoi
	}

	else if (stage == 2)
	{
		CTileMaps::GetInstance()->GetMap(MAP_2)->RenderMap();
		for (int i = 0; i < listBrick.size(); i++)
		{
			listBrick[i]->Render();
		}
		for (int i = 0; i < objects.size(); i++)
		{
			objects[i]->Render();
		}
		for (int i = 0; i < listEnemy.size(); i++)
		{
			listEnemy[i]->Render();
		}
		for (int i = 0; i < listCandle.size(); i++)
		{
			listCandle[i]->Render();
		}
		for (int i = 0; i < listHiddenObj.size(); i++)
		{
			listHiddenObj[i]->Render();
		}
		for (int i = 0; i < listStair.size(); i++)
		{
			listStair[i]->Render();
		}

		CSimon::GetInstance()->Render(); // Simon ve cuoi
	}

	else if (stage == 3)
	{
		// xet sau
	}
}

void  ScenePlayer::ReadFile()
{
#pragma region DECLARE
	CSprites* sprites = CSprites::GetInstance();
	CAnimations* animations = CAnimations::GetInstance();
	CTextures* textures = CTextures::GetInstance();

	LPANIMATION ani;
#pragma endregion DECLARE

#pragma region READ TEXTURE
	ifstream inp(L"textures\\Resources.txt", ios::in);
	if (inp.fail())
	{
		DebugOut(L"[ERROR] Load file failed!");
		inp.close();
	}

	while (!inp.eof())
	{
		string link;
		int id, r, g, b;
		inp >> id >> r >> g >> b >> link;
		textures->Add(id, D3DCOLOR_XRGB(r, g, b), ConvertToWideChar((char*)link.c_str()));
	}

	LPDIRECT3DTEXTURE9 tex;
#pragma endregion READ TEXTURE

#pragma region READ SPRITE + ANIMATION

	TiXmlDocument doc("textures\\Textures.xml");

	if (!doc.LoadFile())
	{
		DebugOut(L"Can't read XML file");
		MessageBox(NULL, L"Can't Read XML File", L"Error", MB_OK);
		return;
	}
	else
	{
		DebugOut(L"[INFO]Read XML success\n");
	}

	// get info root
	TiXmlElement* root = doc.RootElement();
	TiXmlElement* sprite = nullptr;
	TiXmlElement* animation = nullptr;
	TiXmlElement* texture = nullptr;
	// gameObjectId = 0 -- Simon

	for (texture = root->FirstChildElement(); texture != NULL; texture = texture->NextSiblingElement())
	{
		int textureId;
		int gameObjectId;
		texture->QueryIntAttribute("textureId", &textureId);
		texture->QueryIntAttribute("gameObjectId", &gameObjectId);

		tex = textures->Get(textureId);

		for (animation = texture->FirstChildElement(); animation != NULL; animation = animation->NextSiblingElement())
		{
			int aniId, frameTime;
			animation->QueryIntAttribute("frameTime", &frameTime);
			LPANIMATION ani;

			ani = new CAnimation(frameTime);
			for (sprite = animation->FirstChildElement(); sprite != NULL; sprite = sprite->NextSiblingElement())
			{
				int left, top, right, bottom, id;
				sprite->QueryIntAttribute("id", &id);
				sprite->QueryIntAttribute("top", &top);
				sprite->QueryIntAttribute("left", &left);
				sprite->QueryIntAttribute("right", &right);
				sprite->QueryIntAttribute("bottom", &bottom);
				sprites->Add(id, left, top, right, bottom, tex);
				ani->Add(id);
			}
			animation->QueryIntAttribute("aniId", &aniId);
			animations->Add(aniId, ani);
		};
	}
#pragma endregion READ SPRITE + ANIMATION

}

void ScenePlayer::CheckCollision_SimonAndEnemy()
{

}

void ScenePlayer::CheckCollision_SimonAndDoor()
{
	for (int i = 0; i < listHiddenObj.size(); i++)
	{
		if (CSimon::GetInstance()->CheckAABBwithObject(listHiddenObj[i]))
		{
			DebugOut(L"cham cua");
			this->stage = 2;
			listBrick.clear();
			listCandle.clear();
			listHiddenObj.clear();
			coObject1.clear();
			LoadResources();
		}
	}
}



void ScenePlayer::CheckCollision_SimonAndItem()
{
	/*for (int i = 0; i < coObject1.size(); i++) {
		if (dynamic_cast<Item*>(coObject1[i])) {
				if (CSimon::GetInstance()->isCollisionWithItem(dynamic_cast<Item*>(coObject1[i]))) {
				}
			}

		}
	}*/
}
//void ScenePlayer::CheckCollision_SimonAndItem()
//{
//
//}