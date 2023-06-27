#include <cassert>
#include <AL3_HeaderCpp/AL3_2/AL3_02_06/Enemy/Enemy.h>
#include <AL3_HeaderCpp/AL3_2/AL3_02_03/Function/Function.h>


#pragma comment(lib, "dxguid.lib")

Enemy::Enemy() {
	//Enemy enemy;
	state_ = new EnemyStateApproach();
}

BaseEnemyState::BaseEnemyState() {

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







//接近
void EnemyStateApproach::Update(Enemy* enemy) {
	//速度
	//enemy_->SetVelocity(enemyVelocity);
	
	enemy->SetVelocity({0.0f, 0.0f, -0.2f});

	enemy->SetTranslation(Add(enemy->GetTranslation(), enemy->GetVelocity()));

	//ここが原因
	//enemy_->SetTranslation();
	//worldTransform_.translation_ = Add(worldTransform_.translation_, enemyVelocity_);
	

	//enemy_->worldTransform_.translation_ = Add(enemy_->worldTransform_.translation_, enemy_->enemyVelocity_);
	//enemy_->enemyVelocity_ = TransformNormal(enemy_->enemyVelocity_,enemy_->worldTransform_.matWorld_ );


	//規定の位置に到達したら離脱
	if (enemy->GetTranslation().z < 0.0f) {
		enemy->ChangeState(new EnemyStateLeave());
	}
	
}

void EnemyStateLeave::Update(Enemy* enemy) {
	//移動(ベクトルを加算)
	//enemy_->SetWorldTranslate(
	//    {enemy_->GetEnemyTranslate().x + 0.2f, 
	//	enemy_->GetEnemyTranslate().y + 0.02f,
	//     enemy_->GetEnemyTranslate().z});

	//worldTransform_.translation_.x += 0.2f,
	//worldTransform_.translation_.y += 0.02f)
	
	enemy->SetVelocity({0.3f, 0.3f, -0.2f});

}

void BaseEnemyState::Update(Enemy* enemy) {
	//enemy_->ChangeState(new EnemyStateApproach);
}


void Enemy::Update() { 
	

	//メンバ関数ポインタに入っている関数を呼び出す
	//ここではAppriachUpdate
	//(this->*spFuncTable[static_cast<size_t>(phase_)])();
	


	//state_->Update();
	//メンバ関数ポインタに入っている関数を呼び出す
	//ここではAppriachUpdate
	//(this->*spFuncTable[static_cast<size_t>(phase_)])();

	
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

void Enemy::ChangeState(BaseEnemyState* newState) { 
	delete state_; 
	this->state_ = newState;
}




