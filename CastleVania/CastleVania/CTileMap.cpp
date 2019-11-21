#include "CTileMap.h"


CTileMap::CTileMap (int ID_MAP)
{ 
	this->ID_MAP = ID_MAP; 

	LoadMap();
	LoadTileSet();
	GetTile();
}


wchar_t* CTileMap::ConvertToWideChar(char* p) // covert LWstring -> wchar_t*
{
	wchar_t* r;
	r = new wchar_t[strlen(p) + 1];

	char* tempsour = p;
	wchar_t* tempdest = r;
	while (*tempdest++ = *tempsour++);

	return r;
}

void CTileMap::LoadTileSet()
{
	CTextures* textures = CTextures::GetInstance();
	ifstream inp(L"map\\TilesetResource.txt", ios::in);
	if (inp.fail())
	{
		DebugOut(L"[ERROR] Load file failed!");
		inp.close();
	}

	while (!inp.eof())
	{
		string link;
		int  r, g, b;
		inp >> idTex >> r >> g >> b >> link;
		textures->Add(idTex, D3DCOLOR_XRGB(r, g, b), ConvertToWideChar((char*)link.c_str()));
	}
}

void CTileMap::GetTile() //lay ra tung tile -> gan id theo ID_MAP
{
	CTextures* textures = CTextures::GetInstance();
	CSprites* sprites = CSprites::GetInstance();
	LPDIRECT3DTEXTURE9 tex = textures->Get(idTex);	// lay id Texture (TileSet)

	int ID_Sprite, left_tile, top_tile, right_tile, bottom_tile;	

	//LAY RA GIA TRI SPRITE CHO TUNG TILE TRONG TEXTURE
	for (int i = 1; i <= num_tiles; i++) // lay tung sprite cua texture
	{
		ID_Sprite = ID_MAP + i;		// gan ID sprite theo ID_MAP
		left_tile = i * 32;
		top_tile = 0;
		right_tile = left_tile + 32;
		bottom_tile = 32;

		sprites->Add(ID_Sprite, left_tile, top_tile, right_tile, bottom_tile, tex);
	}
}
//
//void CTileMap::GetFileMap(string path) // lay file map theo ID_MAP (->ID_SCENE) 
//{
//	// Get link file map1,map2,map3
//	ifstream inp;
//	inp.open(path, ios::in);
//	if (inp.fail())
//	{
//		DebugOut(L"[ERROR] Load file map failed! \n");
//		inp.close();
//	}
//
//	while (!inp.eof())
//	{
//		int SCENE_ID;
//		inp >> SCENE_ID >> ID_MAP;
//
//	}
//	inp.close();
//}

void CTileMap::LoadMap() // DOC FILE MA TRAN CUA MAP THEO ID MAP
{
	CSprites* sprites = CSprites::GetInstance();
	// doc ma tran cua map
	ifstream inp(L"map\\map1.txt", ios::in);

	if (inp.fail())
	{
		DebugOut(L"[ERROR] Load map failed!");
		inp.close();
		return;
	}

	string line; // doc dong dau tien cua file txt
	getline(inp, line);
	stringstream ss(line);
	ss >> num_tiles >> num_col >> num_row; // doc gia tri hang 1 (sl tile trong texture, col, row)

	// Tao ma tran chua gia tri tile cho map 
	//while (!inp.eof())
	//{
	//	stringstream ss(line); 
	//	int num;

	//	while (ss >> num) // doc sl gia tri tren 1 hang
	//	{
	//		for int 
	//		int idTile = ID_MAP + num; // gan idTile theo IDMAP
	//	}
	//}
	
	tileMap = new int* [num_row];
	for (int i = 1; i <= num_row; ++i)
	{
		tileMap[i] = new int[num_col];
		for (int j = 1; j <= num_col; ++j)
		{
			inp >> tileMap[i][j];
		}
	}
	inp.close();

}

void CTileMap::DrawMap()
{
	CSprites* spritetile = CSprites::GetInstance();

	for (int i = 0; i < num_row; i++)
	{
		for (int j = cell_begin; j <= cell_end; j++) // ve tu tile bd den cuoi tile set (update theo vi tri camera)
		{
			CSprites::GetInstance()->Get(ID_MAP + tileMap[i][j]);
			// chua xu ly neu di den cuoi map
		}
	}
}

//void CTileMap::UpdateMap(D3DXVECTOR3 camPosition)
//{
//	cell_begin = (int)camPosition.x/ 32;
//	cell_end = cell_begin + SCREEN_WIDTH / 32;
//}



CTileMaps* CTileMaps::__instance = NULL;
CTileMaps* CTileMaps::GetInstance()
{
	if (__instance == NULL) __instance = new CTileMaps();
	return __instance;
}


void CTileMaps::LoadResource(int ID_MAP) // load map theo ID
{
	LPTILEMAP tilemap = new CTileMap(ID_MAP);
	tilemaps[ID_MAP] = tilemap;
}

