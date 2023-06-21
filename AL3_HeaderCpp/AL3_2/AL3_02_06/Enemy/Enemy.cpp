#include <cassert>
#include <AL3_HeaderCpp/AL3_2/AL3_02_06/Enemy/Enemy.h>
#include <AL3_HeaderCpp/AL3_2/AL3_02_03/Function/Function.h>
#include <imgui.h>


Enemy::~Enemy() { 
	//弾の解放処理
	//複数出たのでfor文で解放しよう
	for (EnemyBullet* bullet : bullets_) {
		delete bullet;
	}


	//timedCall_の解放
	for (TimedCall* timedCall : timedCalls_) {
		delete timedCall;
	}
}


void Enemy::ApproachInitialize() {
	//発射タイマーを初期化
	//enemyBulletShotTime = kFireInterval;
	
	//発射タイマーをセットする
	FireAndReset();
	
}

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

	//同時に生成
	//Fire();

	//同時生成は止める
	//接近フェーズ初期化
	ApproachInitialize();

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


//発射してリセットする関数
void Enemy::FireAndReset() { 
	//弾を発射
	Fire(); 

	//発射タイマーをセットする
	timedCalls_.push_back(
		new TimedCall(std::bind(&Enemy::FireAndReset, this), kFireInterval));

	#pragma region 上のを分解するとこうなるよ
	//メンバ関数と呼び出し元をbindしてstd::functionに代入
	//std::function<void(void)> callBack = std::bind(&Enemy::FireAndReset, this);

	//時限発動イベントを生成
	//TimedCall* timedCall = new TimedCall(callBack, kFireInterval);

	//時限発動イベントを時限発動イベントリストに追加
	//timedCalls_.push_back(timedCall);

	#pragma endregion

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


	//終了したタイマーを削除
	//リストを削除するなら「remove_if」だよ！
	timedCalls_.remove_if([](TimedCall* timedCall) {
        if (timedCall->IsFinished()) {
            delete timedCall;
            return true;
        }
        return false;
    });

	//範囲forでリストの全要素について回す
	for (TimedCall* timedCall : timedCalls_) {
		timedCall->Update();
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


	#pragma region ImGui

	ImGui::Begin("Enemy");

	ImGui::Text("EnemyBulletTime");
	ImGui::InputInt("Time", &enemyBulletShotTime);
	ImGui::End();

	#pragma endregion

}


void Enemy::Draw(const ViewProjection& viewProjection) { 
	//自キャラと同じ処理なので出来れば継承を使うといいよ！
	model_->Draw(worldTransform_, viewProjection, textureHandle_);


	//弾の描画
	for (EnemyBullet* bullet : bullets_) {
		bullet->Draw(viewProjection);
	}

	

	//ImGui::SliderF
}