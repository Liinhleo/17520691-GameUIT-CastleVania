#include "CTileMap.h"
#include "Game.h"


CTileMap::CTileMap(int _ID_MAP, int _ID_TEX, LPCWSTR _Sprite_path, LPCWSTR _Matrix_path)
{
	this->ID_MAP = _ID_MAP;
	this->ID_TEX = _ID_TEX;
	this->Sprite_path = _Sprite_path;
	this->Matrix_path = _Matrix_path;

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


void CTileMap::LoadTile() // ~load sprite
{
	CTextures* textures = CTextures::GetInstance();
	CSprites* sprites = CSprites::GetInstance();
	LPDIRECT3DTEXTURE9 tex = textures->Get(ID_TEX);	// lay id Texture (TileSet)


	int ID_Tile, left_tile, top_tile, right_tile, bottom_tile;
	ifstream inp(Sprite_path, ios::in);
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


void CTileMap::LoadMap() // DOC FILE MA TRAN CUA MAP THEO ID MAP
{
	ifstream inp(Matrix_path, ios::in);
	if (inp.fail())
	{
		DebugOut(L"[ERROR] Load map failed!");
		inp.close();
		return;
	}
	inp >> mapWidth >> mapHeight; // doc gia tri hang 1 (chieu dai, chieu rong)

	num_col = mapWidth / TILE_SIZE;
	num_row = mapHeight / TILE_SIZE;
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
		col_begin = CGame::GetInstance()->GetCam_x() / TILE_SIZE;
		col_end = col_begin + SCREEN_WIDTH / TILE_SIZE + 1;					// cot ket thuc -> lay du 1 cot 
		// cot bd (lam tron xuong)

	for (int i = 0; i < num_row; i++)
	{
		for (int j = col_begin; j < col_end; j++)
		{
			int x = TILE_SIZE * (j - col_begin) - (int)CGame::GetInstance()->GetCam_x() % TILE_SIZE + CGame::GetInstance()->GetCam_x();
			int y = TILE_SIZE * i + BEGIN_DRAW_Y;

			CSprites::GetInstance()->Get(ID_MAP + tileMap[i][j])->Draw(x, y, 255); // ID SPRITE = ID_MAP + tileMap[i][j]
		}

	}
}

CTileMaps* CTileMaps::__instance = NULL;
CTileMaps* CTileMaps::GetInstance()
{
	if (__instance == NULL) __instance = new CTileMaps();
	return __instance;
}
LPTILEMAP CTileMaps::GetMap(int ID_MAP)
{
	return tilemaps[ID_MAP];
}
void CTileMaps::AddMap(int ID_MAP, int ID_TEX, LPCWSTR Sprite_path, LPCWSTR Matrix_path)
{
	LPTILEMAP map = new CTileMap(ID_MAP, ID_TEX, Sprite_path, Matrix_path);
	tilemaps[ID_MAP] = map;
}

