#include "AL3_HeaderCpp/AL3_2/AL3_02_07a/EnemyStateApproach/EnemyStateApproach.h"
#include <AL3_HeaderCpp/AL3_2/AL3_02_03/Function/Function.h>

void EnemyStateApproach::Update() {
	worldTransform_.translation_ = Add(worldTransform_.translation_, enemy_->GetEnemyVelocity());
	//規定の位置に到達したら離脱
	if (worldTransform_.translation_.z < 0.0f) {
		phase_ = Phase::Leave;
	}
}