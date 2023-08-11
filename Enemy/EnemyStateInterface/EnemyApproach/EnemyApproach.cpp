#include "EnemyApproach.h"
#include "AL3_HeaderCpp/AL3_2/AL3_02_06/Enemy/Enemy.h"
#include <AL3_HeaderCpp/AL3_2/AL3_02_03/Function/Function.h>
#include "Enemy/EnemyStateInterface/EnemyLeave/EnemyLeave.h"


void EnemyApproach::Update(Enemy* enemy) {

	//速度と位置の設定
	enemy->SetVelocity({0.0f, 0.0f, -0.2f});
	enemy->SetTranslation(Add(enemy->GetTranslation(), enemy->GetVelocity()));


	//規定の位置に到達したら離脱
	//今まではswitchだったけどStatePatternですっきり見やすくなった！
	if (enemy->GetTranslation().z < 0.0f) {
		enemy->ChangeState(new EnemyLeave());
	}
}