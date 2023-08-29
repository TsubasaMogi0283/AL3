#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include <ImGuiManager.h>
#include <AxisIndicator.h>

#include <fstream>


#include "TitleScene/TitleScene/TitleStartScene/TitleStartScene.h"

GameScene::GameScene() {

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
	Vector3 playerPosition = {0.0f, 0.0f, 20.0f};

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
	skydomeModel_ = Model::CreateFromOBJ("CelestialSphere", true);

	//テクスチャ読み込み
	skydomeTextureHandle_ = TextureManager::Load("CelestialSphere/SpaceSphere.png");

	//天球の初期化
	skydome_->Initialize(skydomeModel_,skydomeTextureHandle_);

#pragma endregion

#pragma region レールカメラ


	//初期化

	railCamera_ = new RailCamera();

	railCamera_->Initialize(player_->GetWorldPosition(), {0.0f,0.0f,0.0f});

	player_->SetParent(&railCamera_->GetWorldTransform());
	
#pragma endregion


	//当たり判定
	collisionManager_ = new CollisionManager;


	//タイトル画面

	//タイトルのテクスチャ切り替え
	titleTextureNumber_ = 1;

	
	
	//タイトル
	titleLogoTexture = TextureManager::Load("Title/Logo/TitleLogo.png");
	//説明
	explanationTexture[0] =TextureManager::Load("Title/Explanation/Explanation1/Explanation1.png");
	explanationTexture[1] =TextureManager::Load("Title/Explanation/Explanation2/Explanation2.png");

	// スプライトの生成
	titleLogoSprite_ = Sprite::Create(titleLogoTexture, {0, 0});


	 explanationSprite[0] = Sprite::Create(explanationTexture[0], {0, 0});
	 explanationSprite[1] = Sprite::Create(explanationTexture[1], {0, 0});





	 //カウントダウン
	 countDownTexture[3] = TextureManager::Load("Ready/CountDown/CountDown3.png");
	 countDownTexture[2] = TextureManager::Load("Ready/CountDown/CountDown2.png");
	 countDownTexture[1] = TextureManager::Load("Ready/CountDown/CountDown1.png");
	 countDownTexture[0] = TextureManager::Load("Ready/CountDown/CountDownStart.png");

	 countDownSprite[3]=Sprite::Create( countDownTexture[3], {0, 0});
	 countDownSprite[2]=Sprite::Create( countDownTexture[2], {0, 0});
	 countDownSprite[1]=Sprite::Create( countDownTexture[1], {0, 0});
	 countDownSprite[0]=Sprite::Create( countDownTexture[0], {0, 0});

	 countDownTextureNumber_ = 3;
	 countDownTimer_ = SECOND_ * 3;



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



#pragma region Update用

void GameScene::TitleScene() {


	//基本SPACEで進む
	if (input_->TriggerKey(DIK_SPACE)) {
		titleTextureNumber_ += 1;
		if (titleTextureNumber_ == 3) {
			//カウントダウンへ
			scene_ = Scene::Ready;
			drawSpriteScene_ = DrawSpriteScene::Ready;
		}

	}


	#ifdef _DEBUG

	ImGui::Begin("TitleTexture");
	ImGui::InputInt("TextureNumber", &titleTextureNumber_);
	ImGui::End();



	#endif
}


void GameScene::ReadyScene() { 
	countDownTimer_ -= 1;

	if (countDownTimer_ < SECOND_ * 3) {
		if (countDownTimer_ < SECOND_ * 3 && countDownTimer_ >= SECOND_ * 2) {
			countDownTextureNumber_ = 3;
		}
		if (countDownTimer_ < SECOND_ * 2 && countDownTimer_ >= SECOND_ * 1) {
			countDownTextureNumber_ = 2;
		}
		if (countDownTimer_ < SECOND_ * 1 && countDownTimer_ >= SECOND_ * 0) {
			countDownTextureNumber_ = 1;
		}
		if (countDownTimer_ < SECOND_ * 0 && countDownTimer_ >= SECOND_ * ( - 1)) {
			countDownTextureNumber_ = 0;
		}
		if (countDownTimer_ < SECOND_ * (-1)) {
			countDownTextureNumber_ = -1;
			scene_ = Scene::Game;
		}


	}


	#ifdef _DEBUG

	ImGui::Begin("TitleTexture");
	ImGui::InputInt("CountDown", &countDownTimer_);
	ImGui::InputInt("TextureNumber", &countDownTextureNumber_);

	ImGui::End();



	#endif


}

void GameScene::GamePlayScene() {
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


	
}

void GameScene::ResultScene() {

}

#pragma endregion

#pragma region Draw用

void GameScene::TitleDrawSpriteScene() { 

	if (titleTextureNumber_ == 1) {
		titleLogoSprite_->Draw(); 
	} 
	else if (titleTextureNumber_ == 2) {
		explanationSprite[0]->Draw();
	}
	else if (titleTextureNumber_ == 3) {
		explanationSprite[1]->Draw();
	}
	

	
	

}

void GameScene::ReadyDrawSpriteScene() {

	if (countDownTextureNumber_ == 3) {
		countDownSprite[3]->Draw();
	}
	if (countDownTextureNumber_ == 2) {
		countDownSprite[2]->Draw();
	}
	if (countDownTextureNumber_ == 1) {
		countDownSprite[1]->Draw();
	}
	if (countDownTextureNumber_ == 0) {
		countDownSprite[0]->Draw();
	}

	player_->DrawUI();
}

void GameScene::GamePlayDrawSpriteScene() {
	player_->DrawUI();
}

void GameScene::ResultDrawSpriteScene() {

}

#pragma endregion



//3DObject
void GameScene::TitleDraw3DObjectScene() {

}

void GameScene::ReadyDraw3DObjectScene() {
	
}

void GameScene::GamePlayDraw3DObjectScene() {
	
	

	//2.敵弾リスト描画
	for (EnemyBullet* enemyBullet : enemyBullets_) {
		enemyBullet->Draw(viewProjection_);
	}
	
	for (Enemy* enemy : enemyes_) {
		enemy->Draw(viewProjection_);
		
		
	}
}

void GameScene::ResultDraw3DObjectScene() {

}




void GameScene::Update() {


	switch (scene_) { 
		case Scene::Title:
	default:
		TitleScene();

		break;


		case Scene::Ready:
		ReadyScene();
		break;

		case Scene::Game:
		GamePlayScene();
		break;

		case Scene::Result:
		ResultScene();
		break;

	}


	skydome_->Update();




	player_->Update(viewProjection_);
	
	railCamera_->Update();




	


	
	


	#ifdef _DEBUG
	if (input_->PushKey(DIK_C)) {
		isDebugCameraActive_ = true;
	}
	

	

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

	#endif

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


	//恒常の描画
	skydome_->Draw(viewProjection_);

	player_->Draw(viewProjection_);

	



	switch (draw3DObjectScene_) { 
		case Draw3DObjectScene::Title:
	default:
		TitleDraw3DObjectScene();
		break;


		case Draw3DObjectScene::Ready:
		ReadyDraw3DObjectScene();
		break;

		case Draw3DObjectScene::Game:
		GamePlayDraw3DObjectScene();
		break;

		case Draw3DObjectScene::Result:
		ResultDraw3DObjectScene();
		break;

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

	



	switch (drawSpriteScene_) { 
		case DrawSpriteScene::Title:
	default:
		TitleDrawSpriteScene();

		break;


		case DrawSpriteScene::Ready:
		ReadyDrawSpriteScene();
		break;

		case DrawSpriteScene::Game:
		GamePlayDrawSpriteScene();
		break;

		case DrawSpriteScene::Result:
		ResultDrawSpriteScene();
		break;

	}

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}