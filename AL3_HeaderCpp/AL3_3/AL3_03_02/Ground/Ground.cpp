#include "Ground.h"
#include <AL3_HeaderCpp/AL3_3/AL3_03_02/MatrixCalculation/MatrixCalculation.h>


void Ground::Initialize(Model* model,uint32_t textureHandle) {
	this->model_ = model; 
	this->textureHandle_ = textureHandle;
	worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	//ワールド変数の初期化
	worldTransform_.Initialize();
}

void Ground::Update() {
	//行列を定数バッファに転送
	worldTransform_.TransferMatrix(); 

	

	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	worldTransform_.UpdateMatrix();
}

void Ground::Draw(ViewProjection& viewProjection) { 
	model_->Draw(worldTransform_, viewProjection); 
}

