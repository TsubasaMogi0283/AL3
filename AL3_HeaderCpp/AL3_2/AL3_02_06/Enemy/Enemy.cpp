//#include <cassert>
//
//#include <AL3_HeaderCpp/AL3_2/AL3_02_06/Enemy/Enemy.h>
//#include <AL3_HeaderCpp/AL3_2/AL3_02_03/PlayerBullet/PlayerBullet.h>
//
//void Enemy::Initialize(Model* model,const Vector3& position,const Vector3& velocity) {
//
//	//assertも
//	assert(model);
//
//	//モデルも忘れずに
//	this->model_ = model;
//
//
//	//テクスチャ読み込み
//	textureHandle_ = TextureManager::Load("AL3_Resources\AL3_2\AL3_2_6\Enemy\Enemy.png");
//
//	//ワールドトランスフォームの初期化
//	worldTransform_->Initialize();
//
//	//初期座標・速度の設定を行う
//	worldTransform_->translation_ = position;
//	velocity_ = velocity;
//
//}
//
//void Enemy::Update() {
//
//	//移動
//	worldTransform_->translation_ = Add(worldTransform_->translation_, velocity_);
//
//	//行列の更新
//	worldTransform_->UpdateMatrix();
//
//}
//
//void Enemy::Draw(const ViewProjection& viewProjection) { 
//	model_->Draw(worldTransform_, viewProjection, textureHandle_);
//	//model_->Draw(this->worldTransform_, viewProjection, this->textureHandle_);
//}
//
//void PlayerBullet::Draw(const ViewProjection& viewProjection) { 
//	//自キャラと同じ処理なので出来れば継承を使うといいよ！
//	model_->Draw(worldTransform_, viewProjection, textureHandle_);
//}


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
	enemyVelocity_ = velocity;

}

void Enemy::Update() { 

	//switch (phase_) { 
	//	case Phase::Approach:
	//default:
	//	//移動(ベクトルの加算)
	//	//worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);
	//	//規定の位置に到達したら離脱
	//	if (worldTransform_.translation_.z < 0.0f) {
	//		phase_ = Phase::Leave;
	//	}
	//
	//
	//	break;
	//
	//	case Phase::Leave:
	//		//移動(ベクトルを加算)
	//	
	//
	//	break;
	//
	//}



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