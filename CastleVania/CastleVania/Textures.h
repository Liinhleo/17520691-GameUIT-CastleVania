#pragma once
#include <unordered_map>
#include <d3dx9.h>

using namespace std;

/*
	Manage texture database
*/
class CTextures
{
	// extend
	//int id;
	//LPCWSTR filePath;

	static CTextures * __instance;

	unordered_map<int, LPDIRECT3DTEXTURE9> textures;

public: 
	CTextures();
	void Add(int id, D3DCOLOR transparentColor, LPCWSTR filePath);
	LPDIRECT3DTEXTURE9 Get(unsigned int i);

	static CTextures * GetInstance();
};
typedef CTextures* LPTEXTURES;