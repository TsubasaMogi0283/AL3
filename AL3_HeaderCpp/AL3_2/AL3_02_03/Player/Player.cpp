#include <AL3_HeaderCpp/AL3_2/AL3_02_03/Player/Player.h>

#include <ImGuiManager.h>
#include <cassert>

#include <AL3_HeaderCpp/AL3_2/AL3_02_03/Player/Player.h>

#include <ImGuiManager.h>
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

//回転
void Player::Rotate() {
	//回転の速さ「ラジアン/frame」
	const float kRotSpeed = 0.02f;

	//押した方向で移動ベクトルを変更
	if (input_->PushKey(DIK_A)) {
		worldTransform_.translation_.y = -kRotSpeed;
	}
	else if (input_->PushKey(DIK_D)) {
		worldTransform_.translation_.y = kRotSpeed;
	}


}



void Player::UpDate() {
	//行列を定数バッファに転送
	worldTransform_.TransferMatrix(); 

	//キャラクターも異動ベクトル
	Vector3 move = {0.0f, 0.0f, 0.0f};
	
	//キャラクターの移動の速さ
	const float kCharacterSpeed = 0.2f;
	

	


	//キーボード入力による移動処理
	//押した方向で移動
	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	}
	else if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}
	else if(input_->PushKey(DIK_DOWN)) {
		move.y -= kCharacterSpeed;
	}
	else if (input_->PushKey(DIK_UP)) {
		move.y += kCharacterSpeed;
	} 
	else {
		move.x = 0.0f;
		move.y = 0.0f;
	}
	
	//移動の限界
	const float MOVE_LIMITX = 30.0f;
	const float MOVE_LIMITY = 18.0f;

	//超えない処理
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -MOVE_LIMITX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, MOVE_LIMITX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -MOVE_LIMITY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, MOVE_LIMITY);



	
	//行列更新
	//座標移動(ベクトルの加算)
	worldTransform_.translation_= Add(worldTransform_.translation_, move);
	
	


	////平行移動行列
	
	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	worldTransform_.TransferMatrix();


	ImGui::Begin("Player");

	
	ImGui::InputFloat3("PlayerPosition", &worldTransform_.translation_.x);
	ImGui::SliderFloat3("PlayerSlide", &worldTransform_.translation_.x, -20.0f,30.0f);
	
	//ImGui::SliderFloat3()
	ImGui::End();

}

//描画
void Player::Draw(ViewProjection viewProjection) { 
	model_->Draw(
		this->worldTransform_, 
		viewProjection, 
		this->textureHandle_);

	
	

}
