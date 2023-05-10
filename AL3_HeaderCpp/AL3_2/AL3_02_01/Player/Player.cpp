#include <AL3_HeaderCpp/AL3_2/AL3_02_01/Player/Player.h>

#include <cassert>

void Player::Initialize(Model* model,uint32_t textureHandle) {
	//NULLポインタチェック
	assert(model);

	//引数として受け取ったデータをメンバ変数に記録する

	//ワールド変数の初期化
	worldTransform_.Initialize();
}

void Player::UpDate() {
}

void Player::Draw() {
}
