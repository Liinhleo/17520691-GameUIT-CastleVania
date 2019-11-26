//#include "ScenePlayer.h"
//
//
//wchar_t* ScenePlayer::ConvertToWideChar(char* p) // covert string -> wchar_t*
//{
//	wchar_t* r;
//	r = new wchar_t[strlen(p) + 1];
//
//	char* tempsour = p;
//	wchar_t* tempdest = r;
//	while (*tempdest++ = *tempsour++);
//
//	return r;
//}
//
//void ScenePlayer::LoadResources()
//{
//
//	/*===========DECLARE========= */
//	CSprites* sprites = CSprites::GetInstance();
//	CAnimations* animations = CAnimations::GetInstance();
//	CTextures* textures = CTextures::GetInstance();
//
//	LPANIMATION ani;
//	LPDIRECT3DTEXTURE9 tex;
//
//	///*===========READ FILE MAP========= */
//
//	////string tileSet;
//	CTileMaps::GetInstance()->LoadResource(1000);
//	/*===========READ TEXTURE FROM FILE TXT========= */
//	ifstream inp(L"textures\\Resources.txt", ios::in);
//	if (inp.fail())
//	{
//		DebugOut(L"[ERROR] Load file failed!");
//		inp.close();
//	}
//
//	while (!inp.eof())
//	{
//		string link;
//		int id, r, g, b;
//		inp >> id >> r >> g >> b >> link;
//		textures->Add(id, D3DCOLOR_XRGB(r, g, b), ConvertToWideChar((char*)link.c_str()));
//	}
//
//	/*===========ADD SPRITE + ADD ANIMATION ========= */
//
//	TiXmlDocument doc("Textures.xml");
//
//	if (!doc.LoadFile())
//	{
//		DebugOut(L"Can't read XML file");
//		MessageBox(NULL, L"Can't Read XML File", L"Error", MB_OK);
//		return;
//	}
//	else
//	{
//		DebugOut(L"[INFO]Read XML success\n");
//	}
//
//	// get info root
//	TiXmlElement* root = doc.RootElement();
//	TiXmlElement* sprite = nullptr;
//	TiXmlElement* animation = nullptr;
//	TiXmlElement* texture = nullptr;
//	// gameObjectId = 0 -- Simon
//
//	for (texture = root->FirstChildElement(); texture != NULL; texture = texture->NextSiblingElement())
//	{
//		int textureId;
//		int gameObjectId;
//		texture->QueryIntAttribute("textureId", &textureId);
//		texture->QueryIntAttribute("gameObjectId", &gameObjectId);
//
//		tex = textures->Get(textureId);
//
//		for (animation = texture->FirstChildElement(); animation != NULL; animation = animation->NextSiblingElement())
//		{
//			int aniId, frameTime;
//			animation->QueryIntAttribute("frameTime", &frameTime);
//			LPANIMATION ani;
//
//			ani = new CAnimation(frameTime);
//			for (sprite = animation->FirstChildElement(); sprite != NULL; sprite = sprite->NextSiblingElement())
//			{
//				int left, top, right, bottom, id;
//				sprite->QueryIntAttribute("id", &id);
//				sprite->QueryIntAttribute("top", &top);
//				sprite->QueryIntAttribute("left", &left);
//				sprite->QueryIntAttribute("right", &right);
//				sprite->QueryIntAttribute("bottom", &bottom);
//				sprites->Add(id, left, top, right, bottom, tex);
//				ani->Add(id);
//			}
//			animation->QueryIntAttribute("aniId", &aniId);
//			animations->Add(aniId, ani);
//			if (gameObjectId == 0)
//				CSimon::GetInstance()->AddAnimation(aniId);
//			else if (gameObjectId == 1)
//				CWhip::GetInstance()->AddAnimation(aniId);
//		};
//	}
//	CSimon::GetInstance()->SetPosition(0.0f, 0);
//	objects.push_back(CSimon::GetInstance());
//	objects.push_back(CWhip::GetInstance());
//
//}
//
//void ScenePlayer::Update(DWORD dt)
//{
//	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
//	// TO-DO: This is a "dirty" way, need a more organized way 
//
//	vector<LPGAMEOBJECT> coObjects;
//	for (int i = 1; i < objects.size(); i++)
//	{
//		if (objects[i]->isAble) //cac obj ton tai thi cho vao list obj co kha nang va cham
//			coObjects.push_back(objects[i]); 
//	}
//	for (int i = 0; i < objects.size(); i++)
//	{
//		objects[i]->Update(dt,&coObjects);
//	}
//	
//
//	// Update camera to follow mario
//	int mapWidth = CTileMaps::GetInstance()->GetMap(1000)->GetMapWidth(); // lay do dai map 
//	float cx, cy;
//	CSimon::GetInstance()->GetPosition(cx, cy);
//
//	cx = cx - SCREEN_WIDTH / 2 + 30 ; // vi tri cam luon de Simon o giua man hinh
//	//cy -= SCREEN_HEIGHT / 2;
//
//	if (cx < 0) //TH: Simon o dau map
//		cx = 0;
//
//	else if (cx + SCREEN_WIDTH > mapWidth) // TH: Simon di qua 1/2 cuoi map
//		return;
//
//	CGame::GetInstance()->SetCamPos(cx, 0.0f);
//}
//
//
//void ScenePlayer::Render()
//{
//	CTileMaps::GetInstance()->GetMap(1000)->RenderMap();
//	for (int i = 1; i < objects.size(); i++)
//		{
//			if (objects[i]->isAble) //ktra trang thai obj -> neu ton tai thi render
//				objects[i]->Render();
//		}
//		objects[0]->Render();
//}