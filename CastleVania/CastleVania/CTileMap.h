#include <Windows.h>

#include "define.h"
#include "Textures.h"
#include "Sprites.h"

#define MAX_SCENE 3
#define TILE_SIZE	64
#define BEGIN_DRAW_Y	80

class CTileMap
{
	int mapWidth; //chieu dai map
	int ID_MAP;		// id map (map1,2,3)
	int num_col;
	int num_row;
	int num_tiles; //so luong tile trong tileSet (sprite trong ~texture)
	
	int col_begin; //tile bat dau ve
	int col_end ;
	vector<vector<int>> tileMap;	 //  ma tran tiles 

public:
	int idTex;

	CTileMap() {}
	CTileMap(int ID_MAP = MAP_1);

	int GetMapWidth(); // lay chieu dai cua map -> de set cam

	wchar_t* ConvertToWideChar(char* p); // chuyen LWSTR -> char
	void LoadTileSet(); // load texture TILEs (hinh)
	void GetTile(); // get tung tile 
	//void LoadResource(int ID, LPCWSTR path); // load duong link map

	void LoadMap();	//Load cac id vao ma tran map 
	void RenderMap();

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
	CTileMaps() {}
	void LoadResource(int ID_MAP);
	LPTILEMAP GetMap(int ID_MAP) { return tilemaps[MAP_1]; }
	static CTileMaps* GetInstance();

};