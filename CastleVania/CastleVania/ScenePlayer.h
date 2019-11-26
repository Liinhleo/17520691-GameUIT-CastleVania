//#pragma once
//#include "Scenes.h"
//#include "define.h"
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
