#include "CTileMap.h"
#include "Game.h"


CTileMap::CTileMap (int ID_MAP)
{ 
	this->ID_MAP = ID_MAP; 

	LoadTileSet();
	LoadTile();
	LoadMap();

}

int CTileMap::GetMapWidth()
{
	return mapWidth;
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


void CTileMap::LoadTileSet() // ~load texture
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

void CTileMap::LoadTile() // ~load sprite
{
	CTextures* textures = CTextures::GetInstance();
	CSprites* sprites = CSprites::GetInstance();
	LPDIRECT3DTEXTURE9 tex = textures->Get(idTex);	// lay id Texture (TileSet)

	int ID_Tile, left_tile, top_tile, right_tile, bottom_tile;

	ifstream inp(L"map\\sprites1.txt", ios::in);
	if (inp.fail())
	{
		DebugOut(L"[ERROR] Load file failed!");
		inp.close();
	}

	while (!inp.eof())
	{
		inp >> ID_Tile >> left_tile >> top_tile >> right_tile >> bottom_tile;
		sprites->Add(ID_Tile, left_tile, top_tile, right_tile, bottom_tile, tex);
	}

	////LAY RA GIA TRI SPRITE CHO TUNG TILE TRONG TEXTURE
	//for (int i = 0; i <= num_tiles; i++) // lay tung sprite cua texture
	//{
	//	ID_Sprite = ID_MAP + i + 1;		// gan ID sprite theo ID_MAP
	//	left_tile = i * TILE_SIZE;
	//	top_tile = 0;
	//	right_tile = left_tile + TILE_SIZE;
	//	bottom_tile = TILE_SIZE;
	//	sprites->Add(ID_Sprite, left_tile, top_tile, right_tile, bottom_tile, tex);
	//}
}

//void CTileMap::LoadResource(int ID, LPCWSTR path)	// Lay ID_MAP & LINK -> MA TRAN MAP
//{
//	//CTextures* textures = CTextures::GetInstance();
//	//LPDIRECT3DTEXTURE9 tex = textures->Get(idTex);	// lay id Texture (TileSet)
//
//	ifstream inp(L"map\\id_map.txt", ios::in);
//	if (inp.fail())
//	{
//		DebugOut(L"[ERROR] Load resource for map is failed!");
//		inp.close();
//	}
//	string link;
//	while (!inp.eof())
//	{
//		inp >> ID_MAP >> link;
//		LoadResource(ID_MAP, ConvertToWideChar((char*)link.c_str()));
//	}
//}


void CTileMap::LoadMap() // DOC FILE MA TRAN CUA MAP THEO ID MAP
{
	//CSprites* sprites = CSprites::GetInstance();
	ifstream inp(L"map\\map1.txt", ios::in);
	if (inp.fail())
	{
		DebugOut(L"[ERROR] Load map failed!");
		inp.close();
		return;
	}
	inp >> mapWidth >> mapHeight; // doc gia tri hang 1 (chieu dai, chieu rong)

	num_col = mapWidth / 32;
	num_row = mapHeight / 32;
	int n;	//gia tri trong ma tran

	for (int i = 0; i < num_row; ++i)
	{
		vector<int>line;

		for (int j = 0; j < num_col; ++j)
		{
			inp >> n;
			line.push_back(n);
 		}
		tileMap.push_back(line);
	}
	inp.close();

}

void CTileMap::RenderMap()
{
	col_begin = floor( CGame::GetInstance()->GetCam_x() / TILE_SIZE);	// cot bd (lam tron xuong)
	col_end = col_begin + SCREEN_WIDTH / TILE_SIZE + 1;					// cot ket thuc -> lay du 1 cot 

	for (int i = 0; i < num_row; i++)
	{
		for (int j = col_begin; j < col_end; j++)
		{
			int x = TILE_SIZE * (j - col_begin) - (int)CGame::GetInstance()->GetCam_x() % TILE_SIZE + CGame::GetInstance()->GetCam_x();
			int y = TILE_SIZE * i + BEGIN_DRAW_Y ;

			CSprites::GetInstance()->Get(ID_MAP+tileMap[i][j])->Draw(x, y, 255); // ID SPRITE = ID_MAP + tileMap[i][j]
		}

	}
}

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

