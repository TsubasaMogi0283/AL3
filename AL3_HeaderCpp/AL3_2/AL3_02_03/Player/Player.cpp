#include <AL3_HeaderCpp/AL3_2/AL3_02_03/Player/Player.h>

#include <ImGuiManager.h>
#include <cassert>

#include <AL3_HeaderCpp/AL3_2/AL3_02_03/Player/Player.h>

#include <ImGuiManager.h>
#include <cassert>

Player::~Player() { 
	//弾の解放処理
	//複数出たのでfor文で解放しよう
	for (PlayerBullet* bullet : bullets_) {
		delete bullet;
	}
}



void Player::Initialize(Model* model,uint32_t textureHandle) {
	
	assert(model);

	//引数として受け取ったデータをメンバ変数に記録する
	this->model_ = model;
	this->textureHandle_ = textureHandle;

	//ワールド変数の初期化
	worldTransform_.Initialize();

	input_ = Input::GetInstance();
}


Vector3 Player::GetWorldPosition() { 
	Vector3 worldPos; 

	//ワールド行列の「平行移動成分」を取得(ワールド座標)
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;

}



//旋回
void Player::Rotate() {
	//回転の速さ「ラジアン/frame」
	const float kRotSpeed = 0.02f;

	//押した方向で移動ベクトルを変更
	if (input_->PushKey(DIK_A)) {
		worldTransform_.rotation_.y -= kRotSpeed;
	}
	else if (input_->PushKey(DIK_D)) {
		worldTransform_.rotation_.y += kRotSpeed;
	}


}

//攻撃
void Player::Attack() { 
	//SPACEキーで発射
	if (input_->TriggerKey(DIK_SPACE)) {
		count_ += 1;
		//弾の速度
		//z方向に+1.0ずつ進むよ
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0, 0, kBulletSpeed);

		//速度ベクトルを自機の向きに合わせて回転させる
		velocity = TransformNormal(velocity,worldTransform_.matWorld_ );

		//弾を生成し、初期化
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(model_, worldTransform_.translation_,velocity);

		//弾を登録する
		//bullets_に要素を追加
		bullets_.push_back(newBullet);
	
	}
}


//衝突を検出したら呼び出されるコールバック関数
void Player::OnCollision() {

}



void Player::UpDate() {

	//旋回処理
	Rotate();


	//デスフラグの経った弾を削除
	//remove ifは条件に当てはまる要素をリストから排除する関数
	//trueを返すとlistから取り除かれる
	bullets_.remove_if([](PlayerBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	#pragma region 移動処理

	//行列を定数バッファに転送
	worldTransform_.TransferMatrix(); 

	//キャラクターも異動ベクトル
	Vector3 move = {0.0f, 0.0f, 0.0f};
	
	//キャラクターの移動の速さ
	const float kCharacterSpeed = 0.2f;
	


	#pragma region キーボード入力による移動処理
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
	#pragma endregion
	
	#pragma region 移動の限界
	const float MOVE_LIMITX = 30.0f;
	const float MOVE_LIMITY = 18.0f;

	//超えない処理
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -MOVE_LIMITX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, MOVE_LIMITX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -MOVE_LIMITY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, MOVE_LIMITY);

	#pragma endregion

	
	//行列更新
	//座標移動(ベクトルの加算)
	worldTransform_.translation_= Add(worldTransform_.translation_, move);
	
	


	////平行移動行列
	
	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	//更新処理書き直し
	worldTransform_.UpdateMatrix();

	#pragma endregion

	//攻撃処理
	Attack();

	//弾の更新
	for (PlayerBullet* bullet : bullets_) {
		bullet->Update();
	}


	#pragma region デバッグテキスト

	ImGui::Begin("Player");

	ImGui::Text("Space To BulletShot");
	ImGui::InputFloat3("PlayerPosition", &worldTransform_.translation_.x);
	ImGui::SliderFloat3("PlayerSlide", &worldTransform_.translation_.x, -20.0f,30.0f);
	ImGui::InputInt("count", &count_);

	//ImGui::SliderFloat3()
	ImGui::End();

	#pragma endregion

}

//描画
void Player::Draw(ViewProjection viewProjection) { 
	model_->Draw(
		this->worldTransform_, 
		viewProjection, 
		this->textureHandle_);

	//弾の描画
	for (PlayerBullet* bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
	

}
