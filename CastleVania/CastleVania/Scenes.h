#pragma once
#include "define.h"
#include "GameObject.h"

class Scene
{	
public:
	int stage;		// man choi

	Scene() { stage = 1; }	//default
	void SetStage(int _stage)
	{
		this->stage = _stage;
	}
	int GetStage() { return stage; }
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

