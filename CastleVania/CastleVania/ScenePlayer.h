#ifndef SCENEPLAYER_H
#define SCENEPLAYER_H
#pragma once

#include "Scenes.h"

class ScenePlayer :public Scene
{
	vector <LPGAMEOBJECT> objects;
	int stage;
public:
	ScenePlayer();

	void LoadResources();
	void Update(float dt);
	void Render();
};
#endif
