#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include <ImGuiManager.h>
#include <AxisIndicator.h>
#include "CalculationFunction/CalculationFunction.h"



GameScene::GameScene() {
}

GameScene::~GameScene()
{ 
    player_->~Player();
	enemy_->~Enemy();
	delete collisionManager_;
}

//GameScene::~GameScene() {
//	delete debugCamera_;
//	delete enemy_;
//	//delete player_;
//	delete playerModel_;
//}


void GameScene::Initialize() 
{
	
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	
	enemy_ = new Enemy();

	//player
	player_->Initialize();
	enemy_->Initialize();

	enemy_->SetPlayer(player_);
	collisionManager_ = new CollisionManager;

	// ビュープロジェクション
	viewProjection_.Initialize();
	//でバックカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);
    
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());
}






void GameScene::Update() 
{ 

	player_->Update();
	enemy_->Update();


	CheckAllCollisions();

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





void GameScene::CheckAllCollisions() 
{
	collisionManager_->ClearColliderList();


    const std::list<EnemyBullet*>& enemyBullets = enemy_->GetBullets();
	const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();

	std::list<Collider*> colliders_;

	collisionManager_->AddToColliderList(player_);
	collisionManager_->AddToColliderList(enemy_);

    


	for (PlayerBullet* bullet : playerBullets){
		collisionManager_->AddToColliderList(bullet);
	}
	for (EnemyBullet* bullet : enemyBullets){
		collisionManager_->AddToColliderList(bullet);
	}
	collisionManager_->CheckAllCollisions();

}



//void GameScene::CheckAllCollision() { 
//	//判定対象AとBの座標
//	//Vector3 posA, posB; 
//	////自弾
//	//Vector3 posC;
//	//Vector3 posD;
//	//自弾リストの取得
//	const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();
//	//敵弾リストの取得
//	const std::list<EnemyBullet*>& enemyBullets = enemy_->GetBullets();
//
//	//コライダー
//	std::list<Collider*> colliders_;
//	//コライダーをリストに登録
//	colliders_.push_back(player_);
//	colliders_.push_back(enemy_);
//	for (PlayerBullet* playerBullet : playerBullets) {
//		colliders_.push_back(playerBullet);
//	}
//	for (EnemyBullet* enemyBullet : enemyBullets) {
//		colliders_.push_back(enemyBullet);
//	}
//
//	
//	//リスト内のペアを総当たり
//	std::list<Collider*>::iterator itrA = colliders_.begin();
//	for (; itrA != colliders_.end(); ++itrA) {
//		Collider* colliderA = *itrA;
//
//		//イテレータBはイテレータAの次の要素から回す(重複判定を回避)
//		std::list<Collider*>::iterator itrB = itrA;
//		itrB++;
//
//		for (; itrB != colliders_.end(); ++itrB) {
//			Collider* colliderB = *itrB;
//
//			//ペアの当たり判定
//			CheckCollisionPair(colliderA, colliderB);
//
//		}
//
//	}
//
//
//
//}
//
//



