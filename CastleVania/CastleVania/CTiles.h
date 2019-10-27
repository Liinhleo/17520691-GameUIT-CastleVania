#pragma once

#include <Windows.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>

#include "Sprites.h"
#include "Debug.h"
#include "Textures.h"

#define SCREEN_WIDTH 320

#define TILEMAP_TRANSPARENT_COLOR		D3DCOLOR_XRGB(5,5,5)

#define MAP_1_WITDH			1536
#define MAP_1_HEIGHT		320

#define MAP_2_WITDH			5632
#define MAP_2_HEIGHT		352

#define TILE_WIDTH		32
#define TILE_HEIGHT		32

#define MAP_MIN_COL	0
#define MAP_1_MAX_COL	47
#define MAP_2_MAX_COL	177

// Scene
#define SCENE_1			1000
#define SCENE_2			2000
using namespace std;

class CMap
{
	CSprites* sprites = CSprites::GetInstance();
	vector<vector<LPSPRITE>> tilemap;

	int map_Width;					// crong map
	int map_Height;					// ccao c?a map

	int nums_row;					// so hang map
	int nums_col;					// so cot map

	LPCWSTR filePath_tex;			// filepath texture 
	LPCWSTR filePath_data;			// filepath data 

	int ID;							// ID tile map

public:

	CMap() {}
	CMap(int ID, LPCWSTR filePath_tex, LPCWSTR filePath_data, int map_width, int map_height);

	void LoadResources();			// load tile vao sprite
	void LoadMap();					// load map (ma tran)
	void Draw(D3DXVECTOR3 camPosition);	// ve tile trong cam

	int GetMapWidth() { return map_Width; }
};

typedef CMap* LPTILEMAP;

/*
	Class manage Tilemap
*/
class CMaps
{
	static CMaps* _instance;
	unordered_map<int, LPTILEMAP> tilemaps;

public:
	void Add(LPCWSTR filePath_data, LPCWSTR filePath_tex, int ID, int map_width, int map_height);
	LPTILEMAP Get(int ID) { return tilemaps[ID]; }

	static CMaps* GetInstance();
};
