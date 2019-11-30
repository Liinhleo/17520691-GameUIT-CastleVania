#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "GameObject.h"
#include "debug.h"


#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0, 0) // background black
#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 480
#define MAX_FRAME_RATE 60


/*MAP_ID*/
#define MAP_1	1000
#define MAP_2	2000
#define MAP_3	3000

/*SCENE_ID*/
#define SCENE_1	1
#define SCENE_2	2
#define SCENE_3	3

#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16

// ENEMY
#define ENEMY_GRAVITY		0.002f

#define ZOMBIE_WALKING_SPEED		0.1f;
#define FISHMAN_WALKING_SPEED		0.05f;
#define FISHMAN_WALKING_SPEED_Y		0.05f;

#define ZOMBIE_BBOX_WIDTH 30
#define ZOMBIE_BBOX_HEIGHT 65
#define FISHMAN_BBOX_WIDTH 30
#define FISHMAN_BBOX_HEIGHT 65
#define DOG_BBOX_WIDTH		0
#define DOG_BBOX_HEIGHT		0
#define BAT_BBOX_WIDTH		0
#define BAT_BBOX_HEIGHT		0


#define ENEMY_STATE_WALKING				0
#define ENEMY_STATE_FIRE				100
#define ENEMY_STATE_FALLING_ITEM		200
#define ENEMY_STATE_DEAD				300

#define DOG_ANI_RIGHT				0
#define DOG_ANI_LEFT				1
#define FISHMAN_ANI_RIGHT			2		
#define FISHMAN_ANI_LEFT			3
#define ZOMBIE_ANI_WALKING_RIGHT	4	
#define ZOMBIE_ANI_WALKING_LEFT		5
#define BAT_ANI_HANGOUT				6
#define BAT_ANI_RIGHT				7
#define BAT_ANI_LEFT				8
#define BOSS_ANI_HANGOUT			9
#define BOSS_ANI_ATTACK				10


/*========ITEM==============*/
#define ITEM_GRAVITY				0.2f
#define SMALL_HEART_GRAVITY			0.02f

// xet bien do roi cua small heart
#define MAX_SPEED					0.1f
#define MIN_SPEED					-0.1f


#define ITEM_ANI_BIG_HEART				3
#define ITEM_ANI_SMALL_HEART			4
#define ITEM_ANI_UPGRADE_WHIP			5
#define ITEM_ANI_DAGGER					6
#define ITEM_ANI_AXE					7
#define ITEM_ANI_STOP_WATCH				8
#define ITEM_ANI_HOLLY_WATER			9

#define BIG_HEART_BBOX					23
#define SMALL_HEART_BBOX				15
#define ITEM_WEAPON_BBOX				32

// TEXTURE ID
/*
#define ID_TEX_BRICK		1
#define ID_TEX_SIMON		2
#define ID_TEX_ENEMY		4
#define ID_TEX_WHIP			5
#define ID_TEX_WEAPON		6
#define ID_TEX_ITEM			7
#define ID_TEX_CANDLE		8
#define ID_TEX_TILEMAP_1	9
#define ID_TEX_TILEMAP_2	10
#define ID_TEX_TILEMAP_3	11
*/




class define
{

};

