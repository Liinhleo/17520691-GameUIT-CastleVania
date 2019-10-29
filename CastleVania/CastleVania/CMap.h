#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#include <unordered_map>

#include "Sprites.h"
#include "debug.h"
#include "CTiles.h"

#define ID_MAP_LEVEL1 100000

class CMap
{
	static CMap* __instance;
	unordered_map<int, LPTILES> maps;

public:
	void Add(int mapId, LPCWSTR mapPath, int texId, LPCWSTR filePath, D3DCOLOR color);

	LPTILES Get(int id);

	static CMap* GetInstance();

};