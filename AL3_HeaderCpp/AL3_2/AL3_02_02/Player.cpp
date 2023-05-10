#include <AL3_HeaderCpp/AL3_2/AL3_02_02/Player.h>

#include <cassert>

void Player::Initialize(Model* model,uint32_t textureHandle) {
	
	assert(model);

	//引数として受け取ったデータをメンバ変数に記録する
	this->model_ = model;
	this->textureHandle_ = textureHandle;

	//ワールド変数の初期化
	worldTransform_.Initialize();

	input_ = Input::GetInstance();
}

void Player::UpDate() {
	//行列を定数バッファに転送
	worldTransform_.TransferMatrix(); 
}

//描画
void Player::Draw(ViewProjection viewProjection) { 
	model_->Draw(
		this->worldTransform_, 
		viewProjection, 
		this->textureHandle_);
}

