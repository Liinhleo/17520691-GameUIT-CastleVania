#pragma once
//#include <windows.h>
//#include <d3d9.h>
//#include <d3dx9.h>
#include "define.h"
//#include "tinyxml.h"
//#include "CTileMap.h"


class Scene
{	
public:
	Scene() {}

	virtual void LoadResources() = 0 ;
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
};
typedef Scene* LPSCENE;



class Scenes
{
private:

	static Scenes* __instance; // trong game chi co 1 scene
	unordered_map<int, LPSCENE> scenes;

public:
	Scenes() {}
	void AddScene(int id, LPSCENE scene);
	LPSCENE GetScene(int id);
	static Scenes* GetInstance();
};

