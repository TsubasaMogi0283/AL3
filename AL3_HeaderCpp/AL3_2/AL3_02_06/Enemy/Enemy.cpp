#include <cassert>

#include <AL3_HeaderCpp/AL3_2/AL3_02_06/Enemy/Enemy.h>

void Enemy::Initialize(Model* model,const Vector3& position,const Vector3& velocity) {

	//assertも
	assert(model);

	//モデルも忘れずに
	model_ = model;


	//テクスチャ読み込み
	textureHandle_ = TextureManager::Load("AL3_Resources\AL3_2\AL3_2_6\Enemy\Enemy.png");

	//ワールドトランスフォームの初期化
	worldTransform_->Initialize();

	//初期座標・速度の設定を行う
	worldTransform_->translation_ = position;
	velocity_ = velocity;

}

void Enemy::Update() {

	//移動
	worldTransform_->translation_ = Add(worldTransform_->translation_, velocity_);

	//行列の更新
	worldTransform_->UpdateMatrix();

}

void Enemy::Draw(const ViewProjection& viewProjection) { 
	
	model_->Draw(viewProjection);

}
