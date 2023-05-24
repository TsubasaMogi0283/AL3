#include "AL3_HeaderCpp/AL3_2/AL3_02_07a/EnemyStateLeave/EnemyStateLeave.h"

void EnemyStateLeave::Update() {
	//移動(ベクトルを加算)
	worldTransform_.translation_.x += 0.2f;
	worldTransform_.translation_.y += 0.02f;

}