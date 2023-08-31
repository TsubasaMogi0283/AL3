#include <AL3_HeaderCpp/AL3_2/AL3_02_03/Player/Player.h>

#include <ImGuiManager.h>
#include <cassert>

#include <AL3_HeaderCpp/AL3_2/AL3_02_03/Player/Player.h>

#include <ImGuiManager.h>
#include <cassert>

#include "GameScene.h"

Player::~Player() { 
	//弾の解放処理
	//複数出たのでfor文で解放しよう
	for (PlayerBullet* bullet : bullets_) {
		delete bullet;
	}

	delete sprite2DReticle_;
}

Vector3 Player::GetWorldPosition() { 
	Vector3 worldPos; 

	//ワールド行列の「平行移動成分」を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;

}

Vector3 Player::Get3DReticleWorldPosition() {
	Vector3 worldPos; 

	//ワールド行列の「平行移動成分」を取得(ワールド座標)
	worldPos.x = worldTransform3DReticle_.matWorld_.m[3][0];
	worldPos.y = worldTransform3DReticle_.matWorld_.m[3][1];
	worldPos.z = worldTransform3DReticle_.matWorld_.m[3][2];

	return worldPos;
}


void Player::Initialize(Model* model,uint32_t textureHandle,Vector3 position) {
	
	assert(model);

	//引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	textureHandle_ = textureHandle;

	//ワールド変数の初期化
	worldTransform_.Initialize();
	//3Dレティクル
	worldTransform3DReticle_.Initialize();
	worldTransform3DReticle_.translation_ = position;
	worldTransform_.translation_ = position;

	isAlive_ = true;

	//レティクル用
	uint32_t textureReticle_ = TextureManager::Load("AL3_Resources/AL3_2/AL3_2_14/3DReticle/Sign.png");
	sprite2DReticle_ = Sprite::Create(
	    textureReticle_, {1.0f, 100.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f,0.5f});

	input_ = Input::GetInstance();
}




//親となるワールドトランスフォームをセット
void Player::SetParent(const WorldTransform* parent) { 
	worldTransform_.parent_ = parent;
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
	
	XINPUT_STATE joyState;
	
	if (!Input::GetInstance()->GetJoystickState(0, joyState)) {
		return;
	}

	//SPACEキーで発射
	if ( (joyState.Gamepad.wButtons&XINPUT_GAMEPAD_RIGHT_SHOULDER)) {
		count_ += 1;
		//弾の速度
		//z方向に+1.0ずつ進むよ
   		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0, 0, kBulletSpeed);


		//自機から照準オブジェクトへのベクトル
		velocity = Subtract(Get3DReticleWorldPosition(), GetWorldPosition());

		velocity.x = NormalizeVector3(velocity).x * kBulletSpeed;
		velocity.y = NormalizeVector3(velocity).y * kBulletSpeed;
		velocity.z = NormalizeVector3(velocity).z * kBulletSpeed;

		//速度ベクトルを自機の向きに合わせて回転させる
		velocity = TransformNormal(velocity,worldTransform_.matWorld_ );




		//弾を生成し、初期化
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(model_, GetWorldPosition(), velocity);

		//弾を登録する
		//bullets_に要素を追加
		//gameScene_->AddPlayerBullet(newBullet);
		bullets_.push_back(newBullet);
		
	}




}


//衝突を検出したら呼び出されるコールバック関数
void Player::OnCollision() { isAlive_ = false; }



void Player::Update(ViewProjection viewProjection) {



	#pragma region 修正後

	//行列を定数バッファに転送
	worldTransform_.TransferMatrix(); 

	//キャラクターも異動ベクトル
	Vector3 move = {0.0f,0.0f,0.0f};
	//キャラクターの移動の速さ
    const float kCharacterSpeed = 0.05f;
	
	

	XINPUT_STATE joyState;

	//ゲームパッド状態取得
	//左スティック
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		move.x += (float)joyState.Gamepad.sThumbLX / SHRT_MAX * kCharacterSpeed ;
		move.y += (float)joyState.Gamepad.sThumbLY / SHRT_MAX * kCharacterSpeed ;
		
	}


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

	//行列更新
	//座標移動(ベクトルの加算)
	worldTransform_.translation_ = Add(worldTransform_.translation_ , move);
	

	////平行移動行列
	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	worldTransform_.UpdateMatrix();

	#pragma region 移動の限界
	const float MOVE_LIMITX = 30.0f;
	const float MOVE_LIMITY = 18.0f;

	//超えない処理
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -MOVE_LIMITX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, MOVE_LIMITX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -MOVE_LIMITY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, MOVE_LIMITY);



	//自機のワールド座標から3Dレティクルのワールド座標を計算

	//自機から3Dレティクルへの距離
	const float DISTANCE_PLAYER_TO_3D_RETICLE = 50.0f;

	//自機から3Dレティクルへのオフセット(Z向き)
	Vector3 offset = {0.0f, 0.0f, 1.0f};

	//自機のワールド行列の回復を反映
	offset = TransformNormal(offset, worldTransform_.matWorld_);

	//ベクトルの長さを整える
	offset.x = NormalizeVector3(offset).x * DISTANCE_PLAYER_TO_3D_RETICLE;
	offset.y = NormalizeVector3(offset).y * DISTANCE_PLAYER_TO_3D_RETICLE;
	offset.z = NormalizeVector3(offset).z * DISTANCE_PLAYER_TO_3D_RETICLE;

	
	worldTransform3DReticle_.translation_ = Add(GetWorldPosition(),offset);
	

	worldTransform3DReticle_.UpdateMatrix();
	worldTransform3DReticle_.TransferMatrix();


	//スプライトの現在座標を取得
	//Vector2 spritePosition = sprite2DReticle_->GetPosition();





	//35ページ
	//Vector3 positionReticle = Get3DReticleWorldPosition();

	//Vector2 spritePosition = sprite2DReticle_->GetPosition();
	
	//右スティック
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		spritePosition.x += (float)joyState.Gamepad.sThumbRX / SHRT_MAX * 5.0f;
		spritePosition.y -= (float)joyState.Gamepad.sThumbRY / SHRT_MAX * 5.0f;
		
		//スプライトの座標変更を反映
		sprite2DReticle_->SetPosition(spritePosition);
	
	}




	//3Dレティクルのw－ルド座標から2Dレティクルのスクリーン座標を計算
	//ビューポート
	Matrix4x4 matViewport =
	    MakeViewportMatrix(0, 0, WinApp::kWindowWidth, WinApp::kWindowHeight, 0, 1);

	
	//ビュー行列
	Matrix4x4 matViewProjectionViewport =
	    Multiply(viewProjection.matView, Multiply(viewProjection.matProjection,matViewport));

	//ワールド→スクリーン座標変換(3Dから2Dへ)
	positionReticle = Transform(positionReticle, matViewProjectionViewport);

	//スプライトのレティクルに座標設定
	sprite2DReticle_->SetPosition(Vector2(positionReticle.x, positionReticle.y));







	//マウスカーソルのスクリーン座標からワールド座標を取得して3Dレティクルを配置

	POINT mousePosition;
	//マウス座標(スクリーン座標)を取得
	GetCursorPos(&mousePosition);

	//クライアントエリア座標に変換する
	HWND hwnd = WinApp::GetInstance()->GetHwnd();
	ScreenToClient(hwnd, &mousePosition);


	//マウス座標を2Dレティクルのスプライトに入れる
	sprite2DReticle_->SetPosition(Vector2(float(spritePosition.x), float(spritePosition.y)));


	//合成行列の逆行列
	//ビュープロジェクションビューポート合成行列
	Matrix4x4 matVPV =
	    Multiply(viewProjection.matView, Multiply(viewProjection.matProjection, matViewport));
	//合成行列の逆行列を計算する
	Matrix4x4 matInverseVPV = Inverse(matVPV);

	//2点のワールド行列
	//スクリーン座標
	Vector3 posNear = Vector3(float(spritePosition.x), float(spritePosition.y), 0);
	Vector3 posFar = Vector3(float(spritePosition.x), float(spritePosition.y), 1);

	//スクリーン座標系からワールド座標系へ
	posNear = Transform(posNear, matInverseVPV);
	posFar = Transform(posFar, matInverseVPV);


	//3Dレティクルの座標計算
	//マウスレイの方向
	Vector3 mouseDirection = Subtract(posFar,posNear);
	mouseDirection = NormalizeVector3(mouseDirection);


	//カメラから照準オブジェクトの距離
	const float DISTANCE_TEST_OBJECT = 50.0f;
	worldTransform3DReticle_.translation_.x = posNear.x + mouseDirection.x*DISTANCE_TEST_OBJECT;
	worldTransform3DReticle_.translation_.y = posNear.y + mouseDirection.y*DISTANCE_TEST_OBJECT;
	worldTransform3DReticle_.translation_.z = posNear.z + mouseDirection.z*DISTANCE_TEST_OBJECT;



	worldTransform3DReticle_.UpdateMatrix();
	worldTransform3DReticle_.TransferMatrix();




	#pragma endregion














	////行列を定数バッファに転送
	//worldTransform_.TransferMatrix(); 

	//旋回処理
	Rotate();
	//reticlePosition_ = Get3DReticleWorldPosition();

	

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

	
	
	#pragma region ゲームパッドの状態を得る変数(XINPUT)

	
	
	#pragma endregion
	

	
	#pragma endregion

	



	#pragma region レティクル


	

	#pragma endregion



	#pragma region 2D照準




	#pragma endregion






	//更新処理書き直し
	//worldTransform_.UpdateMatrix();
	//worldTransform3DReticle_.UpdateMatrix();
	


	//攻撃処理
	Attack();

	//弾の更新
	for (PlayerBullet* bullet : bullets_) {
		bullet->Update();
	}




	

	#pragma region デバッグテキスト



	ImGui::Begin("3D");
	
	
	
	ImGui::InputFloat3("3dPosition", &reticlePosition_.x);
	ImGui::End();

	ImGui::Begin("Player");


	ImGui::Text("Life", isAlive_);

	ImGui::Text("Space To BulletShot");
	ImGui::InputFloat3("PlayerPosition", &worldTransform_.translation_.x);
	ImGui::SliderFloat3("PlayerSlide", &worldTransform_.translation_.x, -20.0f,30.0f);
	ImGui::InputInt("count", &count_);


	ImGui::Text(
	    "2DReticle:(%f,%f)", sprite2DReticle_->GetPosition().x, sprite2DReticle_->GetPosition().y);
	ImGui::Text("Near:(%+.2f,%+.2f,%+.2f)", posNear.x, posNear.y, posNear.z);
	ImGui::Text("Far:(%+.2f,%+.2f,%+.2f)", posFar.x, posFar.y, posFar.z);
	ImGui::Text(
	    "3DReticle(%+.2f,%+.2f,%+.2f)", worldTransform3DReticle_.translation_.x,
	    worldTransform3DReticle_.translation_.y, worldTransform3DReticle_.translation_.z);



	ImGui::End();

	#pragma endregion


	


}

void Player::DrawUI() {
	//3Dレティクル描画
	sprite2DReticle_->Draw();

}

//描画
void Player::Draw(ViewProjection viewProjection) { 


	if (isAlive_==true) {
		
		model_->Draw(
			worldTransform_,
			viewProjection, 
			textureHandle_);
	}

	
	//弾の描画
	for (PlayerBullet* bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
	

}





