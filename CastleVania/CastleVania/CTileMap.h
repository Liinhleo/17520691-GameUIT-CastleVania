#include "define.h"
#include "Textures.h"
#include "Sprites.h"

#define MAX_SCENE 3
#define TILE_SIZE	32
#define BEGIN_DRAW_Y	80
#define DATAPATH  L"map\\MapResource.txt"

class CTileMap
{
	int ID_MAP;		// id map (map1,2,3)
	int ID_TEX;

	LPCWSTR Sprite_path;
	LPCWSTR Matrix_path;


	int mapWidth; //chieu dai map
	int mapHeight; //chieu rong map
	int num_col;
	int num_row;
	int num_tiles; //so luong tile trong tileSet (sprite trong ~texture)

	int col_begin; //tile bat dau ve
	int col_end;
	vector<vector<int>> tileMap;	 //  ma tran tiles 

public:


	//CTileMap(int ID_MAP, int ID_TEX, LPCWSTR Sprite_path, LPCWSTR Matrix_path);
	CTileMap(int ID_MAP, int ID_TEX, LPCWSTR Sprite_path, LPCWSTR Matrix_path);
	int GetMapWidth(); // lay chieu dai cua map -> de set cam

	wchar_t* ConvertToWideChar(char* p); // chuyen LWSTR -> char
	

	void LoadTile(); // load file sprite tile 
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

	void AddMap(int ID_MAP, int ID_TEX, LPCWSTR Sprite_path, LPCWSTR Matrix_path);
	LPTILEMAP GetMap(int ID_MAP);
	static CTileMaps* GetInstance();

};