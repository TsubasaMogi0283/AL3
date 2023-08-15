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
	velocity_ = velocity;

	//Z方向に伸びた形状
	worldTransform_.scale_.x = 0.5f;
	worldTransform_.scale_.y = 0.5f;
	worldTransform_.scale_.z = 3.0f;

	
	 
	
	//ロール・ピッチ・ヨー
	// MTでやったやつだけど一応もう一回復習として
	//ロール...Z軸に回転
	//ピッチ...X軸に回転(仰角)
	//ヨー...Y軸に回転(方位角)

	#pragma region 解法1
	//atan2...ArcTangent
	//底辺と高さから角度を求める
	//atan2(高さ,底辺)
	//Y軸回りの角度
	worldTransform_.rotation_.y = std::atan2(velocity_.x,velocity_.z);
	//Y軸周りに-θy回す回転行列を計算
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(-worldTransform_.rotation_.y);
	//velocity_に回転行列を掛け算してvelocityZを求める
	Vector3 velocityZ = TransformNormal(velocity_, rotateYMatrix);
	
	//X軸周り角度
	worldTransform_.rotation_.x = std::atan2(velocity_.y, velocity_.z);
	
	#pragma endregion











}



void EnemyBullet::Update() { 

	//Playerまでの距離を求める
	Vector3 toPlayer = Subtract(player_->GetWorldPosition(), worldTransform_.translation_);

	//正規化
	Vector3 normalizeToPlayer = NormalizeVector3(toPlayer);
	Vector3 normalizeVelocity = NormalizeVector3(velocity_);

	
	velocity_.x = Slerp(normalizeVelocity, normalizeToPlayer, 0.1f).x * 0.1f;
	velocity_.y = Slerp(normalizeVelocity, normalizeToPlayer, 0.1f).y * 0.1f;
	velocity_.z = Slerp(normalizeVelocity, normalizeToPlayer, 0.1f).z * 0.1f;


	float velocityXZ = sqrt(velocity_.x * velocity_.x + velocity_.z * velocity_.z);



	worldTransform_.rotation_.y = std::atan2(velocity_.x,velocity_.z);
	
	float height = -velocity_.y;

	//X軸周り角度
	worldTransform_.rotation_.x = std::atan2(height, velocityXZ);
	
	
	


	//座標を移動させる(1フレーム分足す)
	//ベクトルの足し算
	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);

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