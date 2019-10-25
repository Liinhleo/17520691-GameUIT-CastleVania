#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <vector>
#include <fstream>

#include "debug.h"
#include "Game.h"
#include "Textures.h"


class CTile {
	int left;
	int top;
	int right;
	int bottom;

	LPDIRECT3DTEXTURE9 texture;
public:
	CTile(int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);
	void Draw(int x, int y);
	~CTile() {};
};
typedef CTile* LPTILE;

/*
	Manage sprite database
*/
class CTiles
{
	int frameWidth, frameHeight;

	int ColumnTileSet, RowTileSet;
	int ColumnMap, RowMap;

	int DrawPositionX, DrawPositionY;

	int HeightBoard; // c.cao board
	int TileMap[500][500];

	LPDIRECT3DTEXTURE9 tex;
	D3DXIMAGE_INFO info;
	vector<LPTILE> tiles;
public:

	CTiles(int texId, LPCWSTR filePath, D3DCOLOR color);

	void ReadMapTXT(LPCWSTR filePath);

	void LoadTile();

	void SetMapPosition(int offsetX, int offsetY);

	void Render();

};

typedef CTiles* LPTILES;

