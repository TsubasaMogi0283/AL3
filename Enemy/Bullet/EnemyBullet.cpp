#include <cassert>
#include "EnemyBullet.h"
#include "math/Calculation/Calculation.h"
#include "Player/Player.h"

void EnemyBullet::Initialize(Model* model, const Vector3& position,const Vector3& velocity) { 
	
	//NULLチェック
	assert(model);

	model_ = model;
	//テクスチャ読み込み
	textureHandle_ = TextureManager::Load("white1x1.png");

	//ワールドトランスフォームの初期化
	//中にあるよ
	worldTransform_.Initialize();
	//引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;
	//velocity_ = velocity;

	//Z方向に伸びた形状
	worldTransform_.scale_.x = 0.5f;
	worldTransform_.scale_.y = 0.5f;
	worldTransform_.scale_.z = 3.0f;

	
	newVelocity_ = velocity;







}



void EnemyBullet::Update() { 

	//Playerまでの距離を求める
	Vector3 toPlayer = Subtract(player_->GetWorldPosition(), worldTransform_.translation_);

	//正規化
	Vector3 normalizeToPlayer = NormalizeVector3(toPlayer);
	Vector3 normalizeVelocity = NormalizeVector3(newVelocity_);

	
	newVelocity_ = Slerp(normalizeVelocity, normalizeToPlayer, 0.05f);

	Vector3 velocity = newVelocity_;

	float velocityXZ = sqrt(velocity.x * velocity.x + velocity.z * velocity.z);
	
	float height = -velocity.y;


	worldTransform_.rotation_.y = std::atan2(velocity.x,velocity.z);
	
	

	//X軸周り角度
	worldTransform_.rotation_.x = std::atan2(height, velocityXZ);
	
	
	


	//座標を移動させる(1フレーム分足す)
	//ベクトルの足し算
	worldTransform_.translation_ = Add(worldTransform_.translation_, newVelocity_);

	//時間経過でデス
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}


	//ワールドトランスフォームの更新
	worldTransform_.UpdateMatrix(); 
}

void EnemyBullet::Draw(const ViewProjection& viewProjection) { 
	//自キャラと同じ処理なので出来れば継承を使うといいよ！
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}