#include "EnemyLeave.h"
#include "Enemy/Enemy.h"

void EnemyLeave::Update(Enemy* enemy) {
	//Approachとは別の方向に移動
	enemy->SetVelocity({0.3f, 0.3f, -0.2f});

}