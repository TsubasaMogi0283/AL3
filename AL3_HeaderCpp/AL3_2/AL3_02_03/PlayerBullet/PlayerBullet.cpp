#include <cassert>
#include <AL3_HeaderCpp/AL3_2/AL3_02_03/PlayerBullet/PlayerBullet.h>

void PlayerBullet::Initialize(Model* model, const Vector3 position) { 
	
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


}

//void PlayerBullet::Update() { 
//	//ワールドトランスフォームの更新
//	worldTransform_.UpdateMatrix(); 
//}

//void PlayerBullet::Draw(const ViewProjection& viewProjection) { 
//	//自キャラと同じ処理なので出来れば継承を使うといいよ！
//	model_->Draw(worldTransform_, viewProjection, textureHandle_);
//}