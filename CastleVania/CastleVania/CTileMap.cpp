#include "CTileMap.h"


CTileMap::CTileMap (int ID_MAP)
{ 
	this->ID_MAP = ID_MAP; 

	LoadMap();
	LoadTileSet();
	GetTile();
}

int CTileMap::GetMapWidth()
{
	mapWidth = num_col * TILE_SIZE;
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
	//LPDIRECT3DTEXTURE9 tex = textures->Get(idTex);	// lay id Texture (TileSet)
	LPDIRECT3DTEXTURE9 tex = textures->Get(9);	// lay id Texture (TileSet)

	int ID_Sprite, left_tile, top_tile, right_tile, bottom_tile;	

	//LAY RA GIA TRI SPRITE CHO TUNG TILE TRONG TEXTURE
	for (int i = 0; i <= num_tiles; i++) // lay tung sprite cua texture
	{
		ID_Sprite = ID_MAP + i + 1;		// gan ID sprite theo ID_MAP
		left_tile = i * TILE_SIZE;
		top_tile = 0;
		right_tile = left_tile + TILE_SIZE;
		bottom_tile = TILE_SIZE;

		sprites->Add(ID_Sprite, left_tile, top_tile, right_tile, bottom_tile, tex);
	}
}

//
//void CTileMap::LoadResource(LPCWSTR path)
//{
//	ifstream inp(L"map\\id_map.txt", ios::in);
//	if (inp.fail())
//	{
//		DebugOut(L"[ERROR] Load resource for map is failed!");
//		inp.close();
//	}
//	while (!inp.eof())
//	{
//		inp >> ID_MAP >> path;
//	}
//}

void CTileMap::LoadMap() // DOC FILE MA TRAN CUA MAP THEO ID MAP
{
	CSprites* sprites = CSprites::GetInstance();
	//string path;

	ifstream inp(L"map\\map1.txt", ios::in);

	// doc ma tran cua map
	if (inp.fail())
	{
		DebugOut(L"[ERROR] Load map failed!");
		inp.close();
		return;
	}

	inp >> num_tiles >> num_col >> num_row; // doc gia tri hang 1 (sl tile trong texture, col, row)
	int n;

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

void CTileMap::DrawMap()
{
	//D3DXVECTOR3 camPosition;
	CSprites* spritetile = CSprites::GetInstance();
	CTextures* textures = CTextures::GetInstance();


	//col_begin = (int)camPosition.x / 32 - 1; // lay cot bat ve
	//col_end = (int)col_begin + SCREEN_WIDTH / 32 + 1; //lay cot cuoi cua map
	int x = 0, y = 80;
	for (int i = 0; i < num_row; i++)
	{
		x = 0; // vi tri dau cua map
		for (int j = 0; j < num_col; j++) // ve tu tile bd den cuoi tile set (update theo vi tri camera)
		{
			/*int x = 32 * (j - col_begin) + camPosition.x - (int)camPosition.x % 32;
			int y = 32 * i + 80;*/

			CSprites::GetInstance()->Get(ID_MAP + tileMap[i][j]+1)->Draw(x, y, 255); // lay id sprite de draw theo ma tran map			
			x = x + TILE_SIZE;
			// chua xu ly neu di den cuoi map
		}
		y = y + TILE_SIZE;

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

