#include <cassert>
#include <AL3_HeaderCpp/AL3_2/AL3_02_03/PlayerBullet/PlayerBullet.h>
#include <AL3_HeaderCpp/AL3_2/AL3_02_03/Function/Function.h>
#include <imgui.h>
#include <AL3_HeaderCpp/AL3_2/AL3_02_10_ex1/Collider/ColliderConfig.h>

void PlayerBullet::Initialize(Model* model, const Vector3& position,const Vector3& velocity) { 
	
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

	SetCollosionAttribute(COLLISION_ATTRIBUTE_PLAYER);
	SetCollisionMask(COLLISION_ATTRIBUTE_ENEMY);
}

// ワールド座標を取得
Vector3 PlayerBullet::GetWorldPosition() {
	Vector3 worldPos; 

	//ワールド行列の「平行移動成分」を取得(ワールド座標)
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

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