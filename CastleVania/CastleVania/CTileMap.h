#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <Windows.h>
#include <iostream>
#include <vector>

//#include "Camera.h"
#include "debug.h"
#include "Textures.h"
#include "Sprites.h"

#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 480
#define MAX_SCENE 3

class CTileMap
{

	int ID_MAP = 1000;		// id map (map1,2,3)
	int num_col;
	int num_row;
	int num_tiles; //so luong tile trong tileSet (sprite trong ~texture)
	
	int cell_begin; //tile bat dau ve
	int cell_end;
	//vector<vector<LPSPRITE>> tileMap;


	int** tileMap; //  ma tran tiles 

public:
	int idTex; 
	CTileMap(){}
	CTileMap(int ID_MAP = 1000);

	wchar_t* ConvertToWideChar(char* p); // chuyen LWSTR -> char

	void LoadTileSet(); // load texture TILEs (hinh)
	void GetTile(); // get tung tile 
	//void GetFileMap(string path); // lay file map theo ID_MAP 
	void LoadMap();	//Load cac id vao ma tran map 
	void DrawMap();
	//void UpdateMap(D3DXVECTOR3 camPosition); //ve map theo camera

};
typedef CTileMap* LPTILEMAP;


/*
	Class manage Tilemap
*/
class CTileMaps
{
	static CTileMaps* __instance;	// co 1 map dc khoi tao
	unordered_map<int, LPTILEMAP> tilemaps;
public:
	CTileMaps() {};
	void LoadResource(int ID_MAP);
	LPTILEMAP GetMap(int ID_MAP) { return tilemaps[ID_MAP]; }
	static CTileMaps* GetInstance();

};