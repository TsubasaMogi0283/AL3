#include "Skydome.h"
#include <AL3_HeaderCpp/AL3_2/AL3_02_03/Function/Function.h>

//初期化
void Skydome::Initialize(Model* model,uint32_t textureHandle) { 
	this->model_ = model; 
	this->textureHandle_ = textureHandle;

	//ワールド変数の初期化
	worldTransform_.Initialize();
}

//更新
void Skydome::Update() {

	//行列を定数バッファに転送
	worldTransform_.TransferMatrix(); 

	worldTransform_.translation_ = {0.0f, 0.0f, 0.3f};
	//小さすぎたかも・・
	const float_t SCALE = 200.0f;
	worldTransform_.scale_ = {SCALE, SCALE, SCALE};

	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	//更新処理
	worldTransform_.UpdateMatrix();

}

//描画
void Skydome::Draw(ViewProjection viewProjection) {
	model_->Draw(
		worldTransform_, 
		viewProjection);
}