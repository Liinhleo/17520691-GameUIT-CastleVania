#ifndef SCENEPLAYER_H
#define SCENEPLAYER_H

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
	CWhip* whip;
	CBrick* brick;
	HiddenObject* hiddenOject;
	CZombie* zombie;


public:
	ScenePlayer();
	
	void UpdateStage();
	void LoadResources();
	void Update(float dt);
	void Render();
};
#endif
