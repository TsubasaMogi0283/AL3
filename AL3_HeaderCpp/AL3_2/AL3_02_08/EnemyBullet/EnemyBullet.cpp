#include <cassert>
#include <AL3_HeaderCpp/AL3_2/AL3_02_08/EnemyBullet/EnemyBullet.h>
#include <AL3_HeaderCpp/AL3_2/AL3_02_03/Function/Function.h>

void EnemyBullet::Initialize(Model* model, const Vector3& position,const Vector3& velocity) { 
	
	//NULLチェック
	assert(model);

	model_ = model;
	//テクスチャ読み込み
	textureHandle_ = TextureManager::Load("AL3_Resources/AL3_2/AL3_2_3/bullet.png");

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
	worldTransform_.rotation_.y = std::atan2(velocity_.z,velocity_.x);
	//Y軸周りに-θy回す回転行列を計算
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(worldTransform_.rotation_.y);
	//velocity_に回転行列を掛け算してvelocityZを求める
	Vector3 velocityZ = TransformNormal(velocity_, rotateYMatrix);
	
	//X軸周り角度
	worldTransform_.rotation_.x = std::atan2(velocity_.y, velocity_.z);
	
	#pragma endregion


	#pragma region 解法2
	//Y軸周り角度(θy)
	//worldTransform_.rotation_.y = std::atan2();



	#pragma endregion

}



void EnemyBullet::Update() { 

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