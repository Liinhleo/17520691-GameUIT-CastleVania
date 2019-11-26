/* =============================================================
	INTRODUCTION TO GAME PROGRAMMING SE102
	
	SAMPLE 04 - COLLISION

	This sample illustrates how to:

		1/ Implement SweptAABB algorithm between moving objects
		2/ Implement a simple (yet effective) collision frame work

	Key functions: 
		CGame::SweptAABB
		CGameObject::SweptAABBEx
		CGameObject::CalcPotentialCollisions
		CGameObject::FilterCollision

		CGameObject::GetBoundingBox
		
================================================================ */

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <fstream>
#include <string>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"

#include "Whip.h"
#include "Brick.h"
#include "Simon.h"
#include "define.h"

#include "tinyxml.h"
#include <iostream>
#include "Candle.h"
#include "Weapon.h"
#include "CTileMap.h"
#include "Scenes.h"
#include "ScenePlayer.h"
#include "Zombie.h"

#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"04 - Collision"


CGame *game	= CGame::GetInstance();
CBrick* brick;
CCandle* candle;
//Scenes * scenes = Scenes::GetInstance();
//ScenePlayer* scenePlayer = ScenePlayer::GetInstance();
//Weapon* weapon;
CZombie* zombie;

vector<LPGAMEOBJECT> objects;
vector<LPDIRECT3DTEXTURE9> textures;

class CSampleKeyHander: public CKeyEventHandler
{
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

CSampleKeyHander * keyHandler; 

void CSampleKeyHander::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CSimon* simon = CSimon::GetInstance();

	switch (KeyCode)
	{
	case DIK_SPACE:
		simon->SetState(SIMON_STATE_JUMP);
		break;
	case DIK_Q: // reset
		simon->SetState(SIMON_STATE_IDLE);
		simon->SetPosition(0.0f, 0.0f);
		simon->SetSpeed(0, 0);
		break;

	case DIK_F:		//attack				
		if (game->IsKeyDown(DIK_DOWN))	// ktra co nhan phim down hay k
			simon->SetState(SIMON_STATE_SIT_ATTACK);
		simon->SetState(SIMON_STATE_ATTACK); // else chi danh 
		break;

	case DIK_DOWN:		//sit
		simon->SetState(SIMON_STATE_SIT);
		break;
	}
}

void CSampleKeyHander::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}

void CSampleKeyHander::KeyState(BYTE *states)
{
	// disable control key when Simon die 
	if (CSimon::GetInstance()->GetState() == SIMON_STATE_DIE) 
		return;

	if (game->IsKeyDown(DIK_RIGHT))
		CSimon::GetInstance()->SetState(SIMON_STATE_WALKING_RIGHT);

	else if (game->IsKeyDown(DIK_LEFT))
		CSimon::GetInstance()->SetState(SIMON_STATE_WALKING_LEFT);

	else if (game->IsKeyDown(DIK_DOWN))
		CSimon::GetInstance()->SetState(SIMON_STATE_SIT);
	else
	{
		if (CSimon::GetInstance()->isSitting) 
			CSimon::GetInstance()->SetState(SIMON_STATE_STAND_UP);
		CSimon::GetInstance()->SetState(SIMON_STATE_IDLE);

	}

}

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

/*
	Load all game resources 
	In this example: load textures, sprites, animations and mario object

	TO-DO: Improve this function by loading texture,sprite,animation,object from file
*/

wchar_t* ConvertToWideChar(char* p) // covert string -> wchar_t*
{
	wchar_t* r;
	r = new wchar_t[strlen(p) + 1];

	char* tempsour = p;
	wchar_t* tempdest = r;
	while (*tempdest++ = *tempsour++);

	return r;
}

void LoadResources()
{
	/*scenes->Get(1)->LoadResources();*/

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
		inp >> id >> r >> g >> b >>link;
		textures->Add(id,D3DCOLOR_XRGB(r, g, b), ConvertToWideChar((char*)link.c_str()));
	}

	LPDIRECT3DTEXTURE9 tex;
	/*===========READ FILE MAP========= */

	//string tileSet;
	CTileMaps::GetInstance()->LoadResource(MAP_1);

	/*===========ADD SPRITE + ADD ANIMATION ========= */

	TiXmlDocument doc("Textures.xml");

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

	CSimon::GetInstance()->SetPosition(0.0f, 0);
	objects.push_back(CSimon::GetInstance());
	objects.push_back(CWhip::GetInstance());


	/*===========CANDLE========= */
	for (int i = 0; i < 5; i++)
	{ 
		candle = new CCandle();
		candle->SetState(CANDLE_STATE_ABLE);
		candle->SetPosition(150 + i*250 , 305);

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
			
		objects.push_back(candle);
	}


	/*===========BRICK========= */
	for (int i = 0; i < 100; i++) //			map_width / brick_width = 96 -> lay 100 vien gach
	{
		brick = new CBrick();
		brick->SetPosition( 0 + i * 16.0f, 370); // set vi tri du 1 vien gach an o dau map de simon k bi rot
		objects.push_back(brick);	
	}
	
	for (int i = 0; i < 10; i++) // wall invisible cuoi map de simon k di ra khoi map
	{
		brick = new CBrick();
		brick->AddAnimation(601);
		brick->SetPosition(CTileMaps::GetInstance()->GetMap(1000)->GetMapWidth() - 30.0f, 350.0f - i * BRICK_BBOX_WIDTH);
		objects.push_back(brick);
	}

	for (int i = 0; i < 3; i++) //  visible door of castle
	{
		brick = new CBrick();
		brick->AddAnimation(601);
		brick->SetPosition(CTileMaps::GetInstance()->GetMap(1000)->GetMapWidth() - 150.0f, 350.0f - i * BRICK_BBOX_WIDTH);
		objects.push_back(brick);
	}

	/*===========ZOMBIE========= */
	/*zombie = new CZombie();
	zombie->SetPosition(100, 305);
	zombie->SetState(ZOMBIE_STATE_WALKING);
	objects.push_back(zombie);*/
}



/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	/*scenes->Get(1)->Update(dt);*/

	//// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	//// TO-DO: This is a "dirty" way, need a more organized way 

	vector<LPGAMEOBJECT> coObjects;
	for (int i = 1; i < objects.size(); i++)
	{
		if (objects[i]->isAble) //cac obj ton tai thi cho vao list obj co kha nang va cham
			coObjects.push_back(objects[i]); 
	}
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt,&coObjects);
	}
	

	// Update camera to follow mario
	int mapWidth = CTileMaps::GetInstance()->GetMap(1000)->GetMapWidth(); // lay do dai map 
	float cx, cy;
	CSimon::GetInstance()->GetPosition(cx, cy);

	cx = cx - SCREEN_WIDTH / 2 + 30 ; // vi tri cam luon de Simon o giua man hinh
	//cy -= SCREEN_HEIGHT / 2;

	if (cx < 0) //TH: Simon o dau map
		cx = 0;

	else if (cx + SCREEN_WIDTH > mapWidth) // TH: Simon di qua 1/2 cuoi map
		return;

	CGame::GetInstance()->SetCamPos(cx, 0.0f);
}

/*
	Render a frame 
*/
void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();
	
	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		CTileMaps::GetInstance()->GetMap(MAP_1)->RenderMap();
		//scenes->Get(1)->Render();

		for (int i = 1; i < objects.size(); i++)
		{
			if (objects[i]->isAble) //ktra trang thai obj -> neu ton tai thi render
				objects[i]->Render();
		}
		objects[0]->Render();

		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd) 
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;

			game->ProcessKeyboard();
			
			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);	
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	//scenes->Add(1, scenePlayer);
	game->Init(hWnd);

	keyHandler = new CSampleKeyHander();
	game->InitKeyboard(keyHandler);


	LoadResources();

	/*SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);
	AllocConsole();
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);*/

	Run();

	return 0;
}