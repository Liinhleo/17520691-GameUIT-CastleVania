#ifndef SCENEPLAYER_H
#define SCENEPLAYER_H
#include "tinyxml.h"
#include "Candle.h"
#include "Whip.h"
#include "Brick.h"
#include "Door.h"
#include "Simon.h"
#include "Candle.h"
#include "HiddenObject.h"
#include "Zombie.h"
#pragma once

#include "Scenes.h"

class ScenePlayer :public Scene
{
	


public:
	vector <LPGAMEOBJECT> objects;
	CCandle* candle;
	CDoor* door;
	CBrick* brick;
	HiddenObject* hiddenOject;
	Weapon* subWeapon;

	ScenePlayer();
	void ReadFile();

	void LoadResources();
	void Update(float dt);
	void Render();

	void CreateZombie();	// tao zombie
	void CreateItem();		// tao item ngay tai vi tri object die

	void CheckCollision_SimonAndDoor();
	void CheckCollision_SimonAndEnemy();
	void CheckCollision_SimonAndItem();

};
#endif
