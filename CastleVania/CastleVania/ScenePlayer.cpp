#include "ScenePlayer.h"
#include "CTileMap.h"
#include "Game.h"
#include "Scenes.h"
#include "Dog.h"

vector <LPGAMEOBJECT> listCandle;
vector <LPGAMEOBJECT> listItem;
vector <LPGAMEOBJECT> listBrick;
vector <LPGAMEOBJECT> listHiddenObj;
vector <LPGAMEOBJECT> listEnemy;
vector <LPGAMEOBJECT> listDoor;


vector <LPGAMEOBJECT>coObject1;	// ~ coObject 1
vector <LPGAMEOBJECT>coObject2;

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
	ReadFile();
	CTileMaps::GetInstance()->AddMap(1000, 9, L"map\\sprites1.txt", L"map\\map1.txt");
	CTileMaps::GetInstance()->AddMap(2000, 10, L"map\\sprites2.txt", L"map\\map2.txt");
	CTileMaps::GetInstance()->AddMap(3000, 11, L"map\\sprites3.txt", L"map\\map3.txt");
	
	CSimon::GetInstance()->SetPosition(0, 300);

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
		CDoor* door = new CDoor();
		door->SetPosition(1350.0f, 305);
		listDoor.push_back(door);
	}

	else if (stage == 2)
	{	
		/*===========BRICK========= */
		// TAO GROUND
		CBrick* brick = new CBrick();
		brick->SetPosition(0, 400); 
		brick->SetWidthHeigth(CTileMaps::GetInstance()->GetMap(MAP_2)->GetMapWidth(), BRICK_BBOX_WIDTH);
		listBrick.push_back(brick);

		for (int i = 0; i < 1; i++)	// tuong o cuoi map 2
		{
			CBrick* brick = new CBrick();
			brick->SetPosition(3050 + i *500, 300);
			brick->SetWidthHeigth(BRICK_BBOX_WIDTH,100);
			listBrick.push_back(brick);
		}
		for (int i = 0; i < 1; i++) // them 1
		{
			CBrick* brick = new CBrick();
			brick->SetPosition(1370.0f + i *1, FLOOR_2);
			brick->SetWidthHeigth(100, BRICK_BBOX_WIDTH);
			listBrick.push_back(brick);
		}
		for (int i = 0; i < 1; i++) // them 2
		{
			CBrick* brick = new CBrick();
			brick->SetPosition(1500.0f , 210.0f);
			brick->SetWidthHeigth(345, BRICK_BBOX_WIDTH);
			listBrick.push_back(brick);
		}
		for (int i = 0; i < 1; i++) // them 3
		{
			CBrick* brick = new CBrick();
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
			candle->SetId(i);
			listCandle.push_back(candle);
		}
		for (int i = 0; i < 5; i++)
		{
			candle = new CCandle();
			candle->SetState(CANDLE_STATE_ABLE);
			candle->SetAniCandle(CandleType::SMALL_CANDLE);
			candle->SetPosition(60 + i * 250, FLOOR_1);
			candle->SetId(i);
			listCandle.push_back(candle);
		}
		for (int i = 0; i < 2; i++)
		{
			candle = new CCandle();
			candle->SetState(CANDLE_STATE_ABLE);
			candle->SetAniCandle(CandleType::SMALL_CANDLE);
			candle->SetPosition(1480.0f + i * 350, FLOOR_1);
			candle->SetId(i);
			listCandle.push_back(candle);
		}
		for (int i = 0; i < 3; i++)
		{
			candle = new CCandle();
			candle->SetState(CANDLE_STATE_ABLE);
			candle->SetAniCandle(CandleType::SMALL_CANDLE);
			candle->SetPosition(1400.0f + i * 300, 150);
			candle->SetId(i);
			listCandle.push_back(candle);
		}
		for (int i = 0; i < 4; i++)
		{
			candle = new CCandle();
			candle->SetState(CANDLE_STATE_ABLE);
			candle->SetAniCandle(CandleType::SMALL_CANDLE);
			candle->SetPosition(2100.0f + i * 130, FLOOR_1);
			candle->SetId(i);
			listCandle.push_back(candle);
		}
		
		/*===========HIDDEN_OJECT========= */
		for (int i = 0; i < 3; i++)
		{
			hiddenOject = new HiddenObject(i, 30, 30);
			hiddenOject->SetPosition(190 + i * 520, 370);
			listHiddenObj.push_back(hiddenOject);
		}


		///*===========ZOMBIE========= */
		/*for (int i = 0; i < 3; i++)
		{
			CZombie* zombie = new CZombie();
			zombie->SetPosition(400 + i * 32.0f , 320);
			zombie->SetState(ENEMY_STATE_WALKING);
			listEnemy.push_back(zombie);
		}*/
		

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

		

		//HiddenObject* hidden_obj = new HiddenObject(16,30);
		//hidden_obj->SetPosition(1250.0f, 330.0f );
		//objects.push_back(hidden_obj);

		// BAT HAVE SOME BUGS
		//CBat *bat = new CBat();
		//bat->SetPosition(200, 305);
		//bat->SetState(ENEMY_STATE_WALKING);
		//objects.push_back(bat);
	}

	else if (stage == 3)
	{
		//CFishman *fishman = new CFishMan();
		//fishman->SetPosition(300, 305);
		//fishman->SetState(ENEMY_STATE_WALKING);
		//objects.push_back(fishman);
		// xet sau
	}
}

void ScenePlayer::Update(float dt)
{
	UpdateStage();
	CSimon::GetInstance()->Update(dt,&coObject1);
	
	/*=== DANH SACH LIST OBJECT O COOBJECT 1 ===*/
	for (int i = 0; i < listBrick.size(); i++)
	{
		coObject1.push_back(listBrick[i]);
		listBrick[i]->Update(dt,&coObject1);
	}
	for (int i = 0; i < listItem.size(); i++)
	{
		coObject1.push_back(listItem[i]);
		listItem[i]->Update(dt);
	}

	/*==== DANH SACH LIST OBJECT O COOBJECT 2 ====*/
	for (int i = 0; i < listCandle.size(); i++)
	{
		if(listCandle[i]->isAble)
			coObject2.push_back(listCandle[i]);
		listCandle[i]->Update(dt);
	}
	for (int i = 0; i < listDoor.size(); i++)
	{
		coObject2.push_back(listDoor[i]);
		listDoor[i]->Update(dt);
	}


	// UPDATE NEW ITEM WHEN COLLISION VS WEAPON
	for (int i = 0; i < listCandle.size(); i++)
	{
		listCandle[i]->Update(dt, &coObject2);
		if (listCandle[i]->GetAble() == false) // dieu kien Candle bi roi danh
		{
			float x, y;
			Item* item = new Item();
			item->SetState(ITEM_STATE_SHOW);
			switch (i)
			{
			case 0:
				item->SetItemState(ItemType::ITEM_BIG_HEART);
				break;
			case 1:
				item->SetItemState(ItemType::ITEM_SMALL_HEART);
				break;
			case 2:
				item->SetItemState(ItemType::ITEM_UPGRADE_WHIP);
				break;
			case 3:
				item->SetItemState(ItemType::ITEM_UPGRADE_WHIP);
				break;
			case 4:
				item->SetItemState(ItemType::ITEM_DAGGER);
				break;
			}
			listCandle[i]->GetPosition(x, y);	
			item->SetPosition(x, y);
			objects.push_back(item);
			listCandle.erase(listCandle.begin() + i);// xoa candle tai vi tri thu i
		}
	}

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


	//HAM UPDATE CAMERA THEO SIMON THEO MAP 1
	if (stage == 1)
	{
		int mapWidth = CTileMaps::GetInstance()->GetMap(MAP_1)->GetMapWidth();
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
		for (int i = 0; i < listDoor.size(); i++)
		{
			listDoor[i]->Render();
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
		CSimon::GetInstance()->Render(); // Simon ve cuoi
	}

	else if (stage == 3)
	{
		// xet sau
	}
}


void ScenePlayer::UpdateStage()
{
	switch (GetStage())
	{
	case 1:
		if (CSimon::GetInstance()->isCollisionDoor)
		{
			Scenes::GetInstance()->GetScene(2)->SetStage(2);
			LoadResources();
		}
		break;
		/*case 2:
			if (CSimon::GetInstance()->isCollisionDoor)
			{
				Scenes::GetInstance()->GetScene(3)->SetStage(3);
				LoadResources();
			}
			break;*/
	default:
		break;
	}
}

void  ScenePlayer::ReadFile()
{
	/*===========DECLARE========= */
	CSprites* sprites = CSprites::GetInstance();
	CAnimations* animations = CAnimations::GetInstance();
	CTextures* textures = CTextures::GetInstance();

	LPANIMATION ani;

	/*===========READ TEXTURE FROM FILE TXT========= */
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


	/*===========ADD SPRITE + ADD ANIMATION ========= */

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
}