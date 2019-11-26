//#pragma once
//#include <windows.h>
//#include <d3d9.h>
//#include <d3dx9.h>
//
//#include "define.h"
//#include "Game.h"
//#include "Textures.h"
//#include "Whip.h"
//#include "Brick.h"
//#include "Simon.h"
//#include "Candle.h"
//#include "CTileMap.h"
//#include "tinyxml.h"
//
//class Scene
//{
//
//public:
//	
//	int MapID;
//	int SceneID;
//
//	CGame* game = CGame::GetInstance();
//	CBrick* brick;
//	CCandle* candle;
//
//	vector<LPGAMEOBJECT> objects_stage_1;
//	vector<LPGAMEOBJECT> objects_stage_2;
//	vector<LPGAMEOBJECT> objects_stage_3;
//
//	vector<int>stage;	//danh sach stage -> 3 stage -> get theo ID
//
//	Scene() {};
//
//	Scene(int SceneID = SCENE_1);
//
//	void LoadResources();
//	void Update(float dt);
//	void Render();
///*
//	void OnKeyDown(int keyCode);		
//	void OnKeyUp(int keyCode);*/	
//};
//typedef Scene* LPSCENE;
//
//class Scenes
//{
//private:
//	static Scenes* __instance; // trong game chi co 1 player
//	unordered_map<int, LPSCENE> scenes;
//
//public:
//	void AddScene(int SceneID);
//	LPSCENE GetScene(int SceneID);
//	static Scenes* GetInstance();
//};
//
