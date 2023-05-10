#include <AL3_HeaderCpp/AL3_2/AL3_02_01/Player/Player.h>

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
void Player::UpDate() {

}

//描画
void Player::Draw() {

}