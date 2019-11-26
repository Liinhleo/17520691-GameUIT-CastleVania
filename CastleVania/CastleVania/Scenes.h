//#pragma once
//#include <windows.h>
//#include <d3d9.h>
//#include <d3dx9.h>

//#include "tinyxml.h"

//#include "Game.h"
//#include "Textures.h"
//#include "Whip.h"
//#include "Brick.h"
//#include "Simon.h"
//#include "Candle.h"
//#include "CTileMap.h"
//
//class Scene
//{
//
//public:
//	
//	//int MapID;
//	int SceneID;
//
//	virtual void LoadResources() = 0;
//	virtual void Update(float dt) = 0;
//	virtual void Render() = 0;
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
//	void Add(int SceneID, LPSCENE scene);
//	LPSCENE Get(int SceneID);
//	static Scenes* GetInstance();
//};
//
