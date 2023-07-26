#include "AL3_HeaderCpp/AL3_3/AL3_03_01/Player/Player.h"
#include <cassert>

//初期化
void Player::Initialize(Model* model,uint32_t textureHandle) { 
	

	assert(model);

	//引数として受け取ったデータをメンバ変数に記録する
	this->model_ = model;
	this->textureHandle_ = textureHandle;

	//ワールド変数の初期化
	worldTransform_.Initialize();
}

//更新
void Player::Update() { 
	//行列を定数バッファに転送
	worldTransform_.TransferMatrix(); 
}

//描画
void Player::Draw(ViewProjection& viewProjection) { 
	model_->Draw(
		this->worldTransform_, 
		viewProjection, 
		this->textureHandle_);
}

