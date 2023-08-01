#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include <ImGuiManager.h>
#include <AxisIndicator.h>


GameScene::GameScene() {}

GameScene::~GameScene() {
	delete debugCamera_;
	delete enemy_;
	delete playerModel_;
	delete skydomeModel_;
	delete railCamera_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

#pragma region プレイヤーの生成

	//自キャラの生成
	player_ = new Player();

	//テクスチャ読み込み
	playerTextureHandle_ = TextureManager::Load("AL3_Resources/AL3_2/AL3_2_3/Player1.png");

	//3Dモデルの生成
	//CreateはnewとInitializeの呼び出しをまとめた関数
	playerModel_= Model::Create();
	//自キャラの初期化
	Vector3 playerPosition = {0.0f, 0.0f, 10.0f};
	player_->Initialize(playerModel_,playerTextureHandle_,playerPosition);
	

#pragma endregion


#pragma region 敵の生成
	
	//生成
	enemy_ = new Enemy();

	//敵の速度
	enemyModel_ = Model::Create();

	//初期化
	enemy_->Initialize(enemyModel_, {0.0f,0.0f,100.0f}, enemy_->GetEnemyVelocity());
	
	//敵キャラに自キャラのアドレスを渡す
	enemy_->SetPlayer(player_);

#pragma endregion

#pragma region 天球の生成

	//生成
	skydome_ = new Skydome();

	//フォルダの名前を指定してね
	//読み込むファイルと同じフォルダ名にしないと✕
	skydomeModel_ = Model::CreateFromOBJ("CelestialSphere", true);

	//テクスチャ読み込み
	//skydomeTextureHandle_ = TextureManager::Load("CelestialSphere/uvChecker.png");

	//天球の初期化
	skydome_->Initialize(skydomeModel_,skydomeTextureHandle_);

#pragma endregion

#pragma region レールカメラ


	//初期化

	railCamera_ = new RailCamera();

	railCamera_->Initialize(player_->GetWorldPosition(), {0.0f,0.0f,0.0f});

	player_->SetParent(&railCamera_->GetWorldTransform());
	
#pragma endregion

	//ビュープロジェクション
	//forZを適度に大きい値に変更する
	//大きくしすぎるとZファイティングになるよ
	viewProjection_.farZ = 1200.0f;
	//初期化
	viewProjection_.Initialize();

	//デバッグカメラの設定
	debugCamera_ = new DebugCamera(1280, 720);

	//軸方向表示の障子を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	//軸方向表示が参照するビュープロジェクションを指定する
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
	

}


void GameScene::CheckAllCollision() { 
	//判定対象AとBの座標
	Vector3 posA, posB; 
	//自弾
	Vector3 posC;
	Vector3 posD;
	//自弾リストの取得
	const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();
	//敵弾リストの取得
	const std::list<EnemyBullet*>& enemyBullets = enemy_->GetBullets();


	
	#pragma region 自キャラと敵弾の当たり判定

	//自キャラの座標
	posA = player_->GetWorldPosition();

	

	//自キャラと敵弾全ての当たり判定
	for (EnemyBullet* bullet : enemyBullets) {
		//敵弾の座標
		posB = bullet->GetWorldPosition();


		//座標AとBの距離を求める
		float distanceAB = Length(Subtract(posA, posB));
		
		if (distanceAB < player_->GetRadius() + bullet->GetRadius()) {
			//自キャラの衝突時コールバックを呼び出す
			player_->OnCollision();
			//敵弾の衝突時コールバックを呼び出す
			bullet->OnCollision();

		}
		ImGui::Begin("EnemyBulletCondition");
		ImGui::InputFloat3("PlayerPosition", &posA.x);
		ImGui::InputFloat3("EnemyBulletPosition", &posB.x);
		ImGui::InputFloat("distance", &distanceAB);

		ImGui::End();


	}
	
	#pragma endregion

	#pragma region 自弾と敵キャラの当たり判定

	//敵キャラの位置
	posC = enemy_->GetWorldPosition();

	

	//自キャラと敵弾全ての当たり判定
	for (PlayerBullet* playerBullet : playerBullets) {
		//自弾の座標
		posD = playerBullet->GetWorldPosition();
	

	
		//座標CとDの距離を求める
		float distanceCD = Length(Subtract(posD,posC));
		
		if (distanceCD < enemy_->GetRadius() + playerBullet->GetRadius()) {
			//敵キャラの衝突時コールバックを呼び出す
			enemy_->OnCollision();
			
			//自弾の衝突時コールバックを呼び出す
			playerBullet->OnCollision();
		
			
			
			
		}
	
		ImGui::Begin("PlayerBulletCondition");
		ImGui::InputFloat3("EnemyPositipn", &posC.x);
		ImGui::InputFloat3("PlayerBulletPosition", &posD.x);
		ImGui::InputFloat("distance", &distanceCD);

		ImGui::End();
	
	}

	#pragma endregion

	
	#pragma region 
	//自弾と敵弾全ての当たり判定
	for (PlayerBullet* playerBullet : playerBullets) {
		//自弾の座標
		posD = playerBullet->GetWorldPosition();
	
		for (EnemyBullet* enemyBullet : enemyBullets) {
			//敵弾の座標
			posB = enemyBullet->GetWorldPosition();


			//座標AとBの距離を求める
			float distanceDB = Length(Subtract(posD, posB));
			
			if (distanceDB < player_->GetRadius() + enemyBullet->GetRadius()) {
				//自弾の衝突時コールバックを呼び出す
				playerBullet->OnCollision();
				//敵弾の衝突時コールバックを呼び出す
				enemyBullet->OnCollision();

			}
			

		}
	
	}
	#pragma endregion

}


void GameScene::Update() {
	player_->UpDate();
	enemy_->Update();
	skydome_->Update();
	railCamera_->Update();

	CheckAllCollision();

	Matrix4x4 cameraMatrix = {};
	cameraMatrix.m[0][0] = 1.0f;
	cameraMatrix.m[0][1] = 0.0f;
	cameraMatrix.m[0][2] = 0.0f;
	cameraMatrix.m[0][3] = 0.0f;

	cameraMatrix.m[1][0] = 0.0f;
	cameraMatrix.m[1][1] = 1.0f;
	cameraMatrix.m[1][2] = 0.0f;
	cameraMatrix.m[1][3] = 0.0f;

	cameraMatrix.m[2][0] = 0.0f;
	cameraMatrix.m[2][1] = 0.0f;
	cameraMatrix.m[2][2] = 1.0f;
	cameraMatrix.m[2][3] = 0.0f;

	cameraMatrix.m[2][0] = 1280.0f;
	cameraMatrix.m[2][1] = 720.0f;
	cameraMatrix.m[2][2] = 1.0f;
	cameraMatrix.m[2][3] = 1.0f;



	


	
	


	#ifdef _DEBUG
	if (input_->PushKey(DIK_C)) {
		isDebugCameraActive_ = true;
	}
	

	#endif

	if (isDebugCameraActive_) {
		//デバッグカメラの更新
		debugCamera_->Update();
		
		//ビュー行列(逆行列)
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		//プロジェクション行列(射影行列)
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		
		viewProjection_.TransferMatrix();

		

		

	} 
	
	else {

		
		//ビュー行列(逆行列)
		viewProjection_.matView = railCamera_->GetViewProjection().matView;
		//プロジェクション行列(射影行列)
		viewProjection_.matProjection = railCamera_->GetViewProjection().matProjection;




		//ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();

		
		//ビュープロジェクション行列の更新と転送
		//viewProjection_.UpdateMatrix();

		
	}

	
	

	//忘れていたのでここに書いておく
	//ImGuiはUpdateで！！！！！！！！
	ImGui::Begin("Camera");
	ImGui::Text("Key C To DebugCameraIsActive!!");
	ImGui::Text("Key R To DebugRailCameraIsActive!!");

	ImGui::InputFloat3("CameraTranslation", &viewProjection_.translation_.x);

	ImGui::End();


}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	player_->Draw(viewProjection_);
	enemy_->Draw(viewProjection_);
	skydome_->Draw(viewProjection_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}