#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include <ImGuiManager.h>
#include <AxisIndicator.h>

#include <fstream>


#include "TitleScene/TitleScene/TitleStartScene/TitleStartScene.h"

GameScene::GameScene() {
	//最初はタイトル
	//state_ = new TitleStartScene();

}

GameScene::~GameScene() {
	delete debugCamera_;
	//delete enemy_;
	delete playerModel_;
	delete skydomeModel_;
	delete railCamera_;
	delete player_;
	delete enemyBulletModel_;

	for (Enemy* enemy : enemyes_) {
		delete enemy;
	}


	//3.敵弾の解放
	for (EnemyBullet* enemyBullet : enemyBullets_) {
		delete enemyBullet;
	}

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
	
	reticleHandle_=TextureManager::Load("AL3_Resources/AL3_2/AL3_2_3/Player1.png");
	//3Dモデルの生成
	//CreateはnewとInitializeの呼び出しをまとめた関数
	playerModel_= Model::Create();
	//自キャラの初期化
	Vector3 playerPosition = {0.0f, 0.0f, 10.0f};

	//Initializeの引数無くした方がよさそう
	player_->Initialize(playerModel_,playerTextureHandle_,playerPosition);
	

#pragma endregion


#pragma region 敵の生成
	
	

	//敵の速度
	enemyModel_ = Model::Create();

	enemyTextureHandle_ = TextureManager::Load("AL3_Resources/AL3_2/AL3_2_6/Enemy/Enemy.png");


	LoadEnemyPopData();

	isWait_ = false;

#pragma endregion

#pragma region 天球の生成

	//生成
	skydome_ = new Skydome();

	//フォルダの名前を指定してね
	//読み込むファイルと同じフォルダ名にしないと✕
	skydomeModel_ = Model::CreateFromOBJ("SpaceSphere", true);

	//テクスチャ読み込み
	skydomeTextureHandle_ = TextureManager::Load("SpaceSphere/SpaceSphere.png");

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


void GameScene::GenerateEnemy(Vector3 position) {
	//生成
	enemy_ = new Enemy();
	
	enemy_->Initialize(enemyModel_,enemyTextureHandle_,position);
	enemy_->SetPlayer(player_);
	enemy_->SetGameScene(this);

	enemyes_.push_back(enemy_);
}


//敵発生データの読み込み
void GameScene::LoadEnemyPopData() {
	////ファイルを開く
	std::ifstream file;
	
	file.open("Resources/enemyPop.csv");
	assert(file.is_open());

	//ファイルの内容を文字列ストリームにコピー
	enemyPopCommands_ << file.rdbuf();
	
	//ファイルを閉じる
	file.close();
}

//敵発生コマンドの更新
void GameScene::UpdateEnemyPopCommands() {
	
	
	//待機処理
	if (isWait_ == true) {
		waitingTimer_--;
		if (waitingTimer_ <= 0) {
			//待機完了
			isWait_ = false;
		}
	}
	
	
	
	//1行分の文字列を入れる変数
	std::string line;

	//コマンド実行ループ
	while (getline(enemyPopCommands_, line)) {
		//1行分の文字列をストリームに変呼応して解析しやすくする
		std::istringstream line_stream(line);

		std::string word;
		//「,」区切りの先頭文字列を取得
		getline(line_stream, word, ',');


		//"//"から始まる行はコメント
		if (word.find("//") == 0) {
			//コメント行を飛ばす
			continue;
		}

		//POPコマンド
		if (word.find("POP") == 0) {
			//x座標
			getline(line_stream, word, ',');
			float x = (float)std::atof(word.c_str());

			//y座標
			getline(line_stream, word, ',');
			float y = (float)std::atof(word.c_str());

			//z座標
			getline(line_stream, word, ',');
			float z = (float)std::atof(word.c_str());

			//敵を発生させる
			GenerateEnemy({x,y,z});

		} 
		else if (word.find("WAIT") == 0) {
			getline(line_stream, word, ',');

			//待ち時間
			int32_t waitTime = atoi(word.c_str());

			//待機開始
			isWait_ =true;
			//待機タイマー
			waitingTimer_ = waitTime;



			//コマンドループを抜ける
			break;


		}


	}



}


//登録用の関数
void GameScene::AddEnemyBullet(EnemyBullet* enemyBullet) {
	//リストに登録する
	enemyBullets_.push_back(enemyBullet);
	
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
	//const std::list<EnemyBullet*>& enemyBullets = enemy_->GetBullets();


	
	#pragma region 自キャラと敵弾の当たり判定

	//自キャラの座標
	posA = player_->GetWorldPosition();

	

	//自キャラと敵弾全ての当たり判定
	for (EnemyBullet* bullet : enemyBullets_) {
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


	for (Enemy* enemy : enemyes_) {
		//敵キャラの位置
		posC = enemy->GetWorldPosition();

		

		//自キャラと敵弾全ての当たり判定
		for (PlayerBullet* playerBullet : playerBullets) {
			//自弾の座標
			posD = playerBullet->GetWorldPosition();
		

		
			//座標CとDの距離を求める
			float distanceCD = Length(Subtract(posD,posC));
			
			if (distanceCD < enemy->GetRadius() + playerBullet->GetRadius()) {
				//敵キャラの衝突時コールバックを呼び出す
				enemy->OnCollision();
				
		

				//自弾の衝突時コールバックを呼び出す
 				playerBullet->OnCollision();
			
				
				
				
			}
		
			ImGui::Begin("PlayerBulletCondition");
			ImGui::InputFloat3("EnemyPositipn", &posC.x);
			ImGui::InputFloat3("PlayerBulletPosition", &posD.x);
			ImGui::InputFloat("distance", &distanceCD);

			ImGui::End();
		
		}
	}
	

	#pragma endregion

	
	#pragma region 
	//自弾と敵弾全ての当たり判定
	for (PlayerBullet* playerBullet : playerBullets) {
		//自弾の座標
		posD = playerBullet->GetWorldPosition();
	
		for (EnemyBullet* enemyBullet : enemyBullets_) {
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


	switch (Scene)







	player_->Update(viewProjection_);
	//enemy_->Update();
	skydome_->Update();
	railCamera_->Update();

	UpdateEnemyPopCommands();

	for (Enemy* enemy : enemyes_) {
		 enemy->Update();
	}

	for (EnemyBullet* enemyBullet : enemyBullets_) {
		enemyBullet->Update();
	}

	//6.敵のデスフラグが立ったら解放し除外
	//資料ではデスフラグと書いてあるが生存フラグにした。
	enemyBullets_.remove_if([](EnemyBullet* newEnemyBullets) {
		if (newEnemyBullets->IsDead()) {
			delete newEnemyBullets;
			return true;
		}
		return false;
	});

	enemyes_.remove_if([](Enemy* enemy) {
		if (enemy->IsDead()) {
			delete enemy;
			return true;
		}
		return false;
	});



	CheckAllCollision();


	


	
	


	#ifdef _DEBUG
	if (input_->PushKey(DIK_C)) {
		isDebugCameraActive_ = true;
	}
	

	#endif

	if (input_->PushKey(DIK_C)!=0&&isDebugCameraActive_==true) {
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
	//enemy_->Draw(viewProjection_);
	skydome_->Draw(viewProjection_);

	//2.敵弾リスト描画
	for (EnemyBullet* enemyBullet : enemyBullets_) {
		enemyBullet->Draw(viewProjection_);
	}
	
	for (Enemy* enemy : enemyes_) {
		enemy->Draw(viewProjection_);
		
		
	}

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	player_->DrawUI();


	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}