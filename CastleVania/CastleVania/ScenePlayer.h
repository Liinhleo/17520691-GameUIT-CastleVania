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
	
	vector <LPGAMEOBJECT> objects;
	CCandle* candle;
	CDoor* door;
	CBrick* brick;
	HiddenObject* hiddenOject;
	CZombie* zombie;
	Weapon* subWeapon;

public:
	ScenePlayer();
	void ReadFile();

	void UpdateStage();
	void LoadResources();
	void Update(float dt);
	void Render();

	void CheckCollision_SimonAndEnemy();
	void CheckCollision_SimonAndItem();
	
	void CheckCollision_WeaponAndEnemy();
	void CheckCollision_WhipAndEnemy();


};
#endif
