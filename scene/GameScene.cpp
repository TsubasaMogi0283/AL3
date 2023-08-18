#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include <ImGuiManager.h>
#include <AxisIndicator.h>
#include "CalculationFunction/CalculationFunction.h"

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete debugCamera_;
	delete enemy_;
	//delete player_;
	delete playerModel_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();


	//テクスチャ読み込み
	playerTextureHandle_ = TextureManager::Load("AL3_Resources/AL3_2/AL3_2_3/Player1.png");

	//3Dモデルの生成
	//CreateはnewとInitializeの呼び出しをまとめた関数
	playerModel_= Model::Create();

	//ビュープロジェクション
	viewProjection_.Initialize();

	//自キャラの生成
	player_ = new Player();
	
	//自キャラの初期化
	player_->Initialize(playerModel_,playerTextureHandle_);

	//敵の生成
	
	

	//敵の速度
	enemyModel_ = Model::Create();
	enemy_ = new Enemy();

	enemy_->Initialize(enemyModel_, enemy_->GetEnemyPosition(),enemy_->GetEnemyVelocity());
	

	//敵キャラに自キャラのアドレスを渡す
	enemy_->SetPlayer(player_);


	//デバッグカメラの設定
	debugCamera_ = new DebugCamera(1280, 720);

	//軸方向表示の障子を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	//軸方向表示が参照するビュープロジェクションを指定する
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
	

}


void GameScene::CheckAllCollision() { 
	//判定対象AとBの座標
	//Vector3 posA, posB; 
	////自弾
	//Vector3 posC;
	//Vector3 posD;
	//自弾リストの取得
	const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();
	//敵弾リストの取得
	const std::list<EnemyBullet*>& enemyBullets = enemy_->GetBullets();

	//コライダー
	std::list<Collider*> colliders_;
	//コライダーをリストに登録
	colliders_.push_back(player_);
	colliders_.push_back(enemy_);
	for (PlayerBullet* playerBullet : playerBullets) {
		colliders_.push_back(playerBullet);
	}
	for (EnemyBullet* enemyBullet : enemyBullets) {
		colliders_.push_back(enemyBullet);
	}

	
	//リスト内のペアを総当たり
	std::list<Collider*>::iterator itrA = colliders_.begin();
	for (; itrA != colliders_.end(); ++itrA) {
		Collider* colliderA = *itrA;

		//イテレータBはイテレータAの次の要素から回す(重複判定を回避)
		std::list<Collider*>::iterator itrB = itrA;
		itrB++;

		for (; itrB != colliders_.end(); ++itrB) {
			Collider* colliderB = *itrB;

			//ペアの当たり判定
			CheckCollisionPair(colliderA, colliderB);

		}

	}



}


//コライダー２つの衝突判定と応答
void GameScene::CheckCollisionPair(Collider* colliderA, Collider* colliderB) {
	

	//一応通っている
	float debug = 0.1f;
	ImGui::Begin("a");
	ImGui::DragFloat("distance", &debug, 0.01f);
	ImGui::End();

	//それぞれの座標を取得
	Vector3 worldPositionA = colliderA->GetWorldPosition();
	Vector3 worldPositionB = colliderB->GetWorldPosition();

	float collisionDistance = Length(Subtract(worldPositionA, worldPositionB));

	//衝突フィルタリング
	if ((colliderA->GetCollosionAttribute()&colliderB->GetCollisionMask())==0||
	    (colliderB->GetCollosionAttribute() & colliderA->GetCollisionMask()) == 0)
	{
		return;
	}

	//球と球の交差判定
	if (collisionDistance < colliderA->GetCollisionRadius() + colliderB->GetCollisionRadius()) {
		//ステップインで確認
		//コライダーAの衝突判定時コールバックを呼び出す
		colliderA->OnCollision();
		
		//コライダーBの衝突判定時コールバックを呼び出す
		colliderB->OnCollision();
	}



	


	
}


void GameScene::Update() {
	player_->UpDate();
	enemy_->Update();

	CheckAllCollision();



	


	
	


	#ifdef _DEBUG
	if (input_->TriggerKey(DIK_C)) {
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
		


		//ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();

	} else {
		//ビュープロジェクション行列の更新と転送
		viewProjection_.UpdateMatrix();
	}


	//忘れていたのでここに書いておく
	//ImGuiはUpdateで！！！！！！！！
	ImGui::Begin("Camera");
	ImGui::Text("Key C To DeBugCameraIsActive!!");
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