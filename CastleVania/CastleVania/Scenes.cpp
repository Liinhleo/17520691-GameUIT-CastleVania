#include "Scenes.h"

Scenes* Scenes::__instance = NULL;
Scenes* Scenes::GetInstance()
{
	if (__instance == NULL) __instance = new Scenes();
	return __instance;
}

void Scenes::AddScene(int SceneID, LPSCENE scene)
{
	scenes[SceneID] = scene; // Gan curScene vao scenes[SceneID]
}

LPSCENE Scenes::GetScene(int SceneID)
{
	return scenes[SceneID];
}



