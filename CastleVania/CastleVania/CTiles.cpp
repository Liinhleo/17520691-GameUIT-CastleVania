//#include "CTiles.h"
//#include"Textures.h"
//#include <iostream>
//
//#define OBJECT_SCENE_1 -999
//
//CMaps* CMaps::_instance = NULL;
//
//CMaps* CMaps::GetInstance()
//{
//	if (_instance == NULL) _instance = new CMaps();
//	return _instance;
//}
//
//CMap::CMap(int ID, LPCWSTR filePath_tex, LPCWSTR filePath_data, int map_width, int map_height)
//{
//	this->ID = ID;
//
//	this->filePath_tex = filePath_tex;
//	this->filePath_data = filePath_data;
//
//	this->map_Width = map_width;
//	this->map_Height = map_height;
//
//	nums_row = map_Height / TILE_HEIGHT;
//	nums_col = map_Width / TILE_WIDTH;
//
//	LoadResources();
//	LoadMap();
//}
//
//void CMap::LoadResources()
//{
//	CSprites * sprites = CSprites::GetInstance();
//	CTextures* texture = CTextures::GetInstance();
//
//	texture->Add(ID, TILEMAP_TRANSPARENT_COLOR, filePath_tex);
//
//	LPDIRECT3DTEXTURE9 texTileMap = texture->Get(ID);
//
//	// lay size texture luu trong texture (tileset)
//	D3DSURFACE_DESC surfaceDesc;
//	int level = 0;
//	texTileMap->GetLevelDesc(level, &surfaceDesc);
//
//	// tính toán s? hàng, s? c?t c?n thi?t ?? ??c các ô tile from file
//	int nums_rowToRead = surfaceDesc.Height / TILE_HEIGHT;
//	int nums_colToRead = surfaceDesc.Width / TILE_WIDTH;
//
//	// Luu list tile tiles theo id_sprite
//	int id_sprite = 1;
//
//	for (UINT i = 0; i < nums_rowToRead; i++)
//	{
//		for (UINT j = 0; j < nums_colToRead; j++)
//		{
//			int idTile = ID * 1000 + id_sprite;
//			sprites->Add(idTile, TILE_WIDTH * j, TILE_HEIGHT * i, TILE_WIDTH * (j + 1), TILE_HEIGHT * (i + 1), texTileMap);
//			id_sprite = id_sprite + 1;
//		}
//	}
//}
//
//void CMap::LoadMap()
//{
//	CSprites* sprites = CSprites::GetInstance();
//
//	fstream inp;
//	inp.open(filePath_data, ios::in);
//
//	if (inp.fail())
//	{
//		DebugOut(L"[ERROR] Load map failed!");
//		inp.close();
//		return;
//	}
//
//	string line;
//
//	while (!inp.eof())
//	{
//		getline(inp, line);
//
//		// luu sprite tile vào vector tilemap
//		vector<LPSPRITE> spriteline;
//		stringstream ss(line);
//		int n;
//
//		while (ss >> n)
//		{
//			int idTile = ID * 1000 + n;
//			spriteline.push_back(sprites->Get(idTile));
//		}
//
//		tilemap.push_back(spriteline);
//	}
//
//	inp.close();
//}
//
//void CMap::Draw(D3DXVECTOR3 camPosition)
//{
//	int start_col_to_draw = (int)camPosition.x / 32;
//	int end_col_to_draw = start_col_to_draw + SCREEN_WIDTH / 32;
//
//	for (UINT i = 0; i < nums_row; i++)
//	{
//		for (UINT j = start_col_to_draw; j <= end_col_to_draw; j++)
//		{
//			// +camPosition.x ?? luôn gi? camera ? chính gi?a, vì trong hàm Game::Draw() có tr? cho camPosition.x làm các object ??u di chuy?n theo
//			// +(int)camPosition.x % 32 la lay vi tri left cua tile map khi bd ve
//			float x = TILE_WIDTH * (j - start_col_to_draw) + camPosition.x - (int)camPosition.x % 32; 
//			float y = TILE_HEIGHT * i + 80;
//
//			tilemap[i][j]->Draw(x, y, D3DCOLOR_ARGB(255, 255, 255, 255));
//		}
//	}
//}
//
//void CMaps::Add(LPCWSTR filePath_data, LPCWSTR filePath_tex, int ID, int map_width, int map_height)
//{
//	LPTILEMAP tilemap = new CMap(ID, filePath_tex, filePath_data, map_width, map_height);
//	tilemaps[ID] = tilemap;
//}
//
//
