//#pragma once
//#include "Scenes.h"
//
//#define ID_MAP_1 1000
//#define ID_MAP_2 2000
//#define ID_MAP_3 3000
//
//class ScenePlayer : public Scene
//{
//	static ScenePlayer* __instance; // trong game chi co 1 player
//
//public:
//	ScenePlayer()
//	{
//		SceneID = 1; //default
//	}
//
//
//	CGame* game = CGame::GetInstance();
//	CBrick* brick;
//	CCandle* candle;
//	vector<LPGAMEOBJECT> objects;
//	vector<LPDIRECT3DTEXTURE9> textures;
//
//
//	//void SetStage(int a) { this->stage = a; }
//	//int GetStage() { return this->stage; }
//
//	wchar_t* ConvertToWideChar(char* p);
//	void LoadResources();
//	void Update(DWORD dt);
//	void Render();
//
//	static ScenePlayer* GetInstance();
//	~ScenePlayer() {};
//};
//
