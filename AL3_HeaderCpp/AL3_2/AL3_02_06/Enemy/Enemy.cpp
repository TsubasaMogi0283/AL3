#include <cassert>
#include <AL3_HeaderCpp/AL3_2/AL3_02_06/Enemy/Enemy.h>
#include <AL3_HeaderCpp/AL3_2/AL3_02_03/Function/Function.h>
#include <imgui.h>
#include "AL3_HeaderCpp/AL3_2/AL3_02_03/Player/Player.h"

Enemy::~Enemy() { 
	//弾の解放処理
	//複数出たのでfor文で解放しよう
	for (EnemyBullet* bullet : bullets_) {
		delete bullet;
	}
	delete enemyBullets_;
	delete player_;
	delete model_;
}




void Enemy::ApproachInitialize() {
	//発射タイマーを初期化
	enemyBulletShotTime = kFireInterval;
}

void Enemy::Initialize(Model* model,uint32_t textureHandle, const Vector3& position) { 
	
	//NULLチェック
	assert(model);

	model_ = model;
	//テクスチャ読み込み
	textureHandle_ = textureHandle;

	//ワールドトランスフォームの初期化
	//中にあるよ
	worldTransform_.Initialize();
	//引数で受け取った初期座標をセット

	worldTransform_.translation_ = position;

	//同時に生成
	//Fire();

	//同時生成は止める
	//接近フェーズ初期化
	ApproachInitialize();


}


Vector3 Enemy::GetWorldPosition() { 
	//ワールド座標を取得
	Vector3 worldPos; 
	//ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}


void Enemy::ApproachUpdate() {

	//発射タイマーをデクリメント
	enemyBulletShotTime--;

	//指定時間に達した
	if (enemyBulletShotTime == 0) {
		//弾を発射
		Fire();

		//発射タイマーを初期化
		enemyBulletShotTime = kFireInterval;
	}

	//移動(ベクトルの加算)
	worldTransform_.translation_ = Add(worldTransform_.translation_, enemyVelocity_);
	//規定の位置に到達したら離脱
	if (worldTransform_.translation_.z < 0.0f) {
		phase_ = Phase::Leave;
	}
	
}

void Enemy::LeaveUpdate() {
	//移動(ベクトルを加算)
	worldTransform_.translation_.x += 0.02f;
	worldTransform_.translation_.y += 0.02f;
	worldTransform_.translation_.z += 0.00f;
}

//弾の発射に関する処理
void Enemy::Fire() {
	assert(player_);

	//弾の速度
	//z方向に1.0ずつ進むよ
	const float kBulletSpeed = 1.0f;
	//Vector3 velocity(0, 0, -kBulletSpeed);


	//敵キャラのワールド座標を取得
	Vector3 playerPosition = player_->GetWorldPosition();
	Vector3 enemyPosition = GetWorldPosition();
	//敵と自キャラの差分ベクトル
	Vector3 diffenrence = Subtract(playerPosition,enemyPosition);
	//正規化
	Vector3 velocity = NormalizeVector3(diffenrence);
	//速さに合わせる
	Vector3 afterVelocity = {
	    velocity.x, 
		velocity.y, 
		velocity.z * kBulletSpeed
	};

	
	//速度ベクトルを自機の向きに合わせて回転させる
	afterVelocity = TransformNormal(afterVelocity,worldTransform_.matWorld_ );





	//弾を生成し、初期化
	EnemyBullet* newEnemyBullet = new EnemyBullet();
	newEnemyBullet->Initialize(model_, worldTransform_.translation_,velocity);

	//弾を登録する
	//bullets_に要素を追加
	//bullets_.push_back(newEnemyBullet);
}


//衝突を検出したら呼び出されるコールバック関数
void Enemy::OnCollision() {

}


void Enemy::Update() { 

	switch (phase_) { 
		case Phase::Approach:
	default:
		    ApproachUpdate();
	
		break;
	
		case Phase::Leave:
		LeaveUpdate();
		break;
	
	}

	bullets_.remove_if([](EnemyBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	//弾の更新(引っ越し)
	//for (EnemyBullet* bullet : bullets_) {
	//	bullet->Update();
	//}

	//座標を移動させる(1フレーム分足す)
	//ベクトルの足し算
	worldTransform_.translation_ = Add(worldTransform_.translation_, enemyVelocity_);
	enemyVelocity_ = TransformNormal(enemyVelocity_,worldTransform_.matWorld_ );
	
	//ワールドトランスフォームの更新
	worldTransform_.UpdateMatrix(); 

	ImGui::Begin("Enemy");

	ImGui::Text("EnemyBulletTime");
	ImGui::InputInt("Time", &enemyBulletShotTime);
	
	ImGui::End();


	


}

void Enemy::Draw(const ViewProjection& viewProjection) { 
	//自キャラと同じ処理なので出来れば継承を使うといいよ！
	model_->Draw(worldTransform_, viewProjection, textureHandle_);


	//弾の描画(引っ越し)
	//for (EnemyBullet* bullet : bullets_) {
	//	bullet->Draw(viewProjection);
	//}

	
}