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

	//同次に生成
	Fire();



}

void Enemy::ApproachUpdate() {
	//移動(ベクトルの加算)
		
		worldTransform_.translation_ = Add(worldTransform_.translation_, enemyVelocity_);
		//規定の位置に到達したら離脱
		if (worldTransform_.translation_.z < 0.0f) {
			phase_ = Phase::Leave;
		}
	
}

void Enemy::LeaveUpdate() {
	//移動(ベクトルを加算)
		worldTransform_.translation_.x += 0.2f;
		worldTransform_.translation_.y += 0.02f;
}



//弾の発射に関する処理
void Enemy::Fire() {
	//弾の速度
	//z方向に+1.0ずつ進むよ
	const float kBulletSpeed = 1.0f;
	Vector3 velocity(0, 0, -kBulletSpeed);

	//速度ベクトルを自機の向きに合わせて回転させる
	velocity = TransformNormal(velocity,worldTransform_.matWorld_ );

	//弾を生成し、初期化
	EnemyBullet* newEnemyBullet = new EnemyBullet();
	newEnemyBullet->Initialize(model_, worldTransform_.translation_,velocity);

	//弾を登録する
	//bullets_に要素を追加
	bullets_.push_back(newEnemyBullet);
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

	//弾の更新
	for (EnemyBullet* bullet : bullets_) {
		bullet->Update();
	}

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


	//弾の描画
	for (EnemyBullet* bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}