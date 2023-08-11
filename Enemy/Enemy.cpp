#include <cassert>
#include "Enemy.h"

#include "Enemy/EnemyStateInterface/EnemyStateInterface.h"
#include "Enemy/EnemyStateInterface/EnemyApproach/EnemyApproach.h"
#include "Enemy/EnemyStateInterface/EnemyLeave/EnemyLeave.h"

#include <MatrixCalculation/MatrixCalculation.h>




Enemy::Enemy() {
	state_ = new EnemyApproach();
}



void Enemy::Initialize(Model* model,uint32_t textureHandle) { 
	
	//NULLチェック
	assert(model);

	model_ = model;
	
	textureHandle_ = textureHandle;
	//ワールドトランスフォームの初期化
	//中にあるよ
	worldTransform_.Initialize();

	//Vector3 enemyTranslate = {0.0f, 3.0f, 20.0f};
	this->worldTransform_.translation_ = {0.0f, 3.0f, 20.0f};
	

}


#pragma region Setter
void Enemy::SetTranslation(Vector3 enemyTranslate) {
	worldTransform_.translation_ = enemyTranslate;
}

void Enemy::SetVelocity(Vector3 enemyVelocity) {
	enemyVelocity_ = enemyVelocity;
}

#pragma endregion


void Enemy::ChangeState(IEnemyState* newState) { 
	//一度deleteして新しい状態に変化
	delete state_; 
	this->state_ = newState;
}

void Enemy::Update() { 
	

	
	state_->Update(this);


	//座標を移動させる(1フレーム分足す)
	//ベクトルの足し算
	worldTransform_.translation_ = Add(worldTransform_.translation_, enemyVelocity_);
	enemyVelocity_ = TransformNormal(enemyVelocity_,worldTransform_.matWorld_ );
	
	//ワールドトランスフォームの更新
	worldTransform_.UpdateMatrix(); 
}

void Enemy::Draw(const ViewProjection& viewProjection) { 
	//自キャラと同じ処理なので出来れば継承を使うといいよ！
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}







Enemy::~Enemy() {
	delete state_;
}






