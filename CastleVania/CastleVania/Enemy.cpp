#include "Enemy.h"

CEnemy::CEnemy()
{
	type = ObjectType::ENEMY;

	AddAnimation(260);	//DOG_RIGHT
	AddAnimation(261);  //DOG_LEFT
	AddAnimation(262);	//FISHMAN_RIGHT
	AddAnimation(263);	//FISHMAN_LEFT
	AddAnimation(264);	//ZOMBIE_RIGHT
	AddAnimation(265);	//ZOMBIE_LEFT
	AddAnimation(266);	//BAT_HANG_OUT
	AddAnimation(267);	//BAT_RIGHT
	AddAnimation(268);	//BAT_LEFT
	AddAnimation(269);	//BOSS_HANGOUT
	AddAnimation(270);	//BOSS_ATTACK
	AddAnimation(271);	//DOG_SIT
	AddAnimation(252); // FIRE

}


