#include <cassert>
#include "PlayerBullet.h"
#include "CalculationFunction/CalculationFunction.h"
#include <imgui.h>
#include "Collider/ColliderConfig.h"

PlayerBullet::PlayerBullet() {

}


void PlayerBullet::Initialize(Model* model, const Vector3& position,const Vector3& velocity) { 
	
	//NULLチェック
	assert(model);

	model_ = model;
	//テクスチャ読み込み
	textureHandle_ =  TextureManager::Load("AL3_Resources/AL3_2/AL3_2_3/bullet.png");

	//ワールドトランスフォームの初期化
	//中にあるよ
	worldTransform_.Initialize();
	//引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;
	velocity_ = velocity;

	SetCollosionAttribute(kCollisionAttributePlayer);
	SetCollisionMask(kCollisionAttributeEnemy);
}



// ワールド座標を取得
Vector3 PlayerBullet::GetWorldPosition() {
	Vector3 worldPos; 

	//ワールド行列の「平行移動成分」を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}



//衝突を検出したら呼び出されるコールバック関数
void PlayerBullet::OnCollision() { 
	isDead_ = true;
}



void PlayerBullet::Update() { 

	//座標を移動させる(1フレーム分足す)
	//ベクトルの足し算
	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);

	//時間経過でデス
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}

	ImGui::Begin("PlayerBullet");

	ImGui::InputFloat3("PlayerBulletPosition", &worldTransform_.translation_.x);
	

	//ImGui::SliderFloat3()
	ImGui::End();

	//ワールドトランスフォームの更新
	worldTransform_.UpdateMatrix(); 

}


void PlayerBullet::Draw(const ViewProjection& viewProjection) { 
	//自キャラと同じ処理なので出来れば継承を使うといいよ！
	if (isDead_ == false) {
		model_->Draw(worldTransform_, viewProjection, textureHandle_);
	}
	
}



PlayerBullet::~PlayerBullet() {

}