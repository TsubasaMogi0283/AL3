#include <cassert>
#include <AL3_HeaderCpp/AL3_2/AL3_02_06/Enemy/Enemy.h>
#include <AL3_HeaderCpp/AL3_2/AL3_02_03/Function/Function.h>


void Enemy::Initialize(Model* model, const Vector3& position,const Vector3& velocity) { 
	
	//NULLチェック
	assert(model);

	model_ = model;
	//テクスチャ読み込み
	textureHandle_ = TextureManager::Load("AL3_Resources/AL3_2/AL3_2_6/Enemy/Enemy.png");

	//ワールドトランスフォームの初期化
	//中にあるよ
	worldTransform_.Initialize();
	//引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;
	this->enemyVelocity_ = velocity;

}

//void Enemy::ApproachUpdate() {
//	//移動(ベクトルの加算)
//		
//	worldTransform_.translation_ = Add(worldTransform_.translation_, enemyVelocity_);
//	//規定の位置に到達したら離脱
//	if (worldTransform_.translation_.z < 0.0f) {
//		phase_ = Phase::Leave;
//	}
//	
//}
//
//void Enemy::LeaveUpdate() {
//	//移動(ベクトルを加算)
//	worldTransform_.translation_.x += 0.2f;
//	worldTransform_.translation_.y += 0.02f;
//}



void Enemy::SetEnemyTranslate(Vector3 translation) {
	worldTransform_.translation_.x = translation.x;
	worldTransform_.translation_.y = translation.y;
	worldTransform_.translation_.z = translation.z;

}

//void (Enemy::*Enemy::spFuncTable[])()={
//
//	//0
//	&Enemy::ApproachUpdate,
//	//1
//	&Enemy::LeaveUpdate,
//
//};

void Enemy::Update() { 

	//switch (phase_) { 
	//	case Phase::Approach:
	//default:
	//	    ApproachUpdate();
	//
	//	break;
	//
	//	case Phase::Leave:
	//	LeaveUpdate();
	//	break;
	//
	//}
	
	
	//メンバ関数ポインタに入っている関数を呼び出す
	//ここではAppriachUpdate
	//(this->*spFuncTable[static_cast<size_t>(phase_)])();
	
	//Updateが原因
	state_->Update();


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







Enemy::Enemy() {
	//最初はApproach
	state_ = new EnemyStateApproach();
}

Enemy::~Enemy() {
	delete state_;
}

void Enemy::ChangeState(BaseEnemyState* newState) { 
	delete state_; 
	this->state_ = newState;
}


BaseEnemyState::BaseEnemyState(){

}

//接近
void EnemyStateApproach::Update() {
	

	//ここが原因
	//Getterなどで設定しよう！

	//enemyNewTranslate_ = enemy_->GetEnemyTranslate();
	

	enemy_->worldTransform_.translation_ = Add(enemy_->worldTransform_.translation_, enemy_->enemyVelocity_);
	enemy_->enemyVelocity_ = TransformNormal(enemy_->enemyVelocity_,enemy_->worldTransform_.matWorld_ );


	//enemy_->SetEnemyTranslate(enemyNewTranslate_);
	//worldTransform_.translation_ = Add(worldTransform_.translation_, enemyVelocity_);
	
	


	//規定の位置に到達したら離脱
	if (enemy_->worldTransform_.translation_.z < 0.0f) {
		enemy_->ChangeState(new EnemyStateLeave());
		//phase_ = Phase::Leave;
	}
}

void EnemyStateLeave::Update() {
	//移動(ベクトルを加算)
	enemy_->SetEnemyTranslate(
	    {enemy_->worldTransform_.translation_.x + 0.2f, 
		enemy_->worldTransform_.translation_.y + 0.02f,
	     enemy_->worldTransform_.translation_.z});

	//worldTransform_.translation_.x += 0.2f,
	//worldTransform_.translation_.y += 0.02f)
	
}


