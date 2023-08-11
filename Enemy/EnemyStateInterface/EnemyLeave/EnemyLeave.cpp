#include "EnemyLeave.h"
#include "AL3_HeaderCpp/AL3_2/AL3_02_06/Enemy/Enemy.h"

void EnemyLeave::Update(Enemy* enemy) {
	//Approachとは別の方向に移動
	enemy->SetVelocity({0.3f, 0.3f, -0.2f});

}