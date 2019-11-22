//#pragma once
//
//#include <Windows.h>
//#include <vector>
//#include <string>
//#include <fstream>
//#include <sstream>
//#include <unordered_map>
//
//#include "Sprites.h"
//#include "Debug.h"
//#include "Textures.h"
//#include "Game.h"
//
//#define SCREEN_WIDTH 512
//
//#define TILEMAP_TRANSPARENT_COLOR		D3DCOLOR_XRGB(255,0,255)
//
//#define MAP_1_WITDH			1536
//#define MAP_1_HEIGHT		320
//
//#define TILE_WIDTH		32
//#define TILE_HEIGHT		32
//
//#define MAP_MIN_COL			0
//#define MAP_1_MAX_COL		47
//#define MAP_1_MAX_ROW		11
//#define MAP_1_MAX_SPRITE	79
//
//#define MAP_1			1
//#define MAP_2			2
//#define MAP_3			3
//
//
//class CMap
//{
//	int** Tilemap;					// ma tran tile map
//	int cell_begin;					// o bat dau ve
//	int cell_end;					// o ket thuc ve
//
//	int nums_row;					// so hang map
//	int nums_col;					// so cot map
//
//	int level;						// level cua map
//
//	//LPCWSTR filePath_tex;			// filepath texture 
//	//LPCWSTR filePath_data;			// filepath data 
//
//	//int ID;							// ID tile map
//
//
//public:
//	CMap(int level);
//	//void LoadMap();
//	void Update();
//	void Render();
//
//	int width;
//	int height;
//};
//typedef CMap* LPTILEMAP;
//
///*
//	Class manage map
//*/
//class CMaps
//{
//	static CMaps* __instance;	// co 1 map dc khoi tao
//	vector<LPTILEMAP> maps;		//ds cac maps
//
//public:
//	void LoadResources();		//load theo level cua map
//	LPTILEMAP GetLevel(int level);
//	static CMaps* GetInstance();
//};