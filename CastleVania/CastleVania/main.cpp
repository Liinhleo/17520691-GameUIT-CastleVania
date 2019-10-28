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

#include "Mario.h"
#include "Brick.h"
#include "Simon.h"
#include "Goomba.h"
#include "CTiles.h"
#include "tinyxml.h"

#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"04 - Collision"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(255, 255, 255)
#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 480

#define MAX_FRAME_RATE 60

#define ID_TEX_MISC 1
#define ID_TEX_SIMON 2
#define ID_TEX_ENEMY 4

#define ID_MAP1 100000

#define ID_TEX_MAP1 100000

CGame *game;
CSimon* simon;
CGoomba* goomba;
CBrick* brick;


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
	if (simon->GetState() == SIMON_STATE_DIE) 
		return;

	if (game->IsKeyDown(DIK_RIGHT))
		simon->SetState(SIMON_STATE_WALKING_RIGHT);

	else if (game->IsKeyDown(DIK_LEFT))
		simon->SetState(SIMON_STATE_WALKING_LEFT);

	else if (game->IsKeyDown(DIK_DOWN))
		simon->SetState(SIMON_STATE_SIT);

	else if (game->IsKeyDown(DIK_SPACE))
		simon->SetState(SIMON_STATE_JUMP);

	else if (game->IsKeyDown(DIK_F))
		simon->SetState(SIMON_STATE_ATTACK);
	
	else
	{
		if (simon->isSitting) simon->SetState(SIMON_STATE_STAND_UP);
		simon->SetState(SIMON_STATE_IDLE);

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
	/*===========DECLARE========= */
	CSprites* sprites = CSprites::GetInstance();
	CAnimations* animations = CAnimations::GetInstance();
	CTextures* textures = CTextures::GetInstance();
	

	LPANIMATION ani;

	simon = new CSimon();

	/*===========READ FILE MAP========= */

	string tileSet;
	CMaps::GetInstance()->Add(L"textures\\scene1-map.txt", L"textures\\scene1.png", 1000, MAP_1_WITDH, MAP_1_HEIGHT);



	/*===========READ FILE TXT========= */
	ifstream inp(L"textures\\Resources.txt", ios::in);
	if (inp.fail())
	{
		DebugOut(L"[ERROR] Load file failed!");
		inp.close();
	}

	string line;
	while (!inp.eof()) 
	{
		string link;
		int id, r, g, b;
		inp >> id >> r >> g >> b >>link;
		textures->Add(id,D3DCOLOR_XRGB(r, g, b), ConvertToWideChar((char*)link.c_str()));
	}


	/*===========ADD SPRITE + ADD ANIMATION ========= */// Init 
	LPDIRECT3DTEXTURE9 tex;
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
			if (gameObjectId == 0)
			{
				simon->AddAnimation(aniId);
			}
		};
	}
	
	simon->SetPosition(0.0f, 0);
	objects.push_back(simon);

	

	/*===========BRICK========= */
	LPDIRECT3DTEXTURE9 texMisc = textures->Get(2);
	sprites->Add(20001, 408, 225, 424, 241, texMisc);

	ani = new CAnimation(100);		// brick
	ani->Add(20001);
	animations->Add(601, ani);

	for (int i = 0; i < 200; i++)
	{
		brick = new CBrick();
		brick->AddAnimation(601);
		brick->SetPosition(0 + i * 16.0f, 370);
		objects.push_back(brick);
	}

	/*====== GOOMBA==========*/

	//LPDIRECT3DTEXTURE9 texEnemy = textures->Get(ID_TEX_ENEMY);
	//sprites->Add(30001, 5, 14, 21, 29, texEnemy);
	//sprites->Add(30002, 25, 14, 41, 29, texEnemy);

	//sprites->Add(30003, 45, 21, 61, 29, texEnemy); // die sprite
	//
	//ani = new CAnimation(300);		// Goomba walk
	//ani->Add(30001);
	//ani->Add(30002);
	//animations->Add(701, ani);

	//ani = new CAnimation(1000);		// Goomba dead
	//ani->Add(30003);
	//animations->Add(702, ani);
	//for (int i = 0; i < 4; i++)
	//{
	//	goomba = new CGoomba();
	//	goomba->AddAnimation(701);
	//	goomba->AddAnimation(702);
	//	goomba->SetPosition(200 + i * 60, 170);
	//	goomba->SetState(GOOMBA_STATE_WALKING);
	//	objects.push_back(goomba);
	//}

}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	vector<LPGAMEOBJECT> coObjects;
	for (int i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt,&coObjects);
	}


	// Update camera to follow mario
	float cx, cy;
	simon->GetPosition(cx, cy);

	cx -= SCREEN_WIDTH / 2;
	cy -= SCREEN_HEIGHT / 2;

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

		CMaps::GetInstance()->Get(SCENE_1)->Draw(CGame::GetInstance()->getCamPos());

		for (int i = 0; i < objects.size(); i++)
			objects[i]->Render();

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

	game = CGame::GetInstance();
	game->Init(hWnd);

	keyHandler = new CSampleKeyHander();
	game->InitKeyboard(keyHandler);


	LoadResources();

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}