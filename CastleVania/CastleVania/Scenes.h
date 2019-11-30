#pragma once
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "define.h"
#include "tinyxml.h"


class Scene
{

public:
	int MapID;
	int SceneID = SCENE_1;

	vector<LPGAMEOBJECT> objects;



	vector<LPGAMEOBJECT> objects_stage_2;
	vector<LPGAMEOBJECT> objects_stage_3;

	vector<int>stage;	//danh sach stage -> 3 stage -> get theo ID

	Scene();

	void LoadResources();
	void Update(float dt);
	void Render();
/*
	void OnKeyDown(int keyCode);		
	void OnKeyUp(int keyCode);*/	
};
typedef Scene* LPSCENE;



class Scenes
{
private:
	LPSCENE curScene;	// pointer quan ly scene hien tai

	static Scenes* __instance; // trong game chi co 1 scene
	unordered_map<int, LPSCENE> scenes;

public:
	void AddScene(int SceneID);
	LPSCENE GetCurScene(int SceneID);
	void ChangeScene(LPSCENE scene);
	static Scenes* GetInstance();
};

