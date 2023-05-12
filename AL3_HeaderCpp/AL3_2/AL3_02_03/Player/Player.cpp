#include <AL3_HeaderCpp/AL3_2/AL3_02_03/Player/Player.h>

void Player::Initialize() { 
	input_ = Input::GetInstance(); 
}






void Player::Rotate() { 
	//回転の速さ(ラジアン/frame)
	const float ROT_SPEED = 0.02f;

	//押した方向で移動ベクトルを変更
	if (input_->PushKey(DIK_A)) {
		worldTransform_.rotation_.y = -ROT_SPEED;
	} 
	else if (input_->PushKey(DIK_A)) {
		worldTransform_.rotation_.y = ROT_SPEED;
	}



}

void Player::Update() { 
	//Updateから呼び出す
	Rotate();




}