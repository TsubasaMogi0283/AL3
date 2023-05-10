#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

#include <GameScene.h>


GameScene::GameScene() {}

GameScene::~GameScene() { 
	delete playerModel_; 
	delete player_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	//テクスチャ読み込み
	playerTextureHandle_ = TextureManager::Load("AL3_Resources/AL3_2/AL3_02_01/Player/Player1.png");

	//3Dモデルの生成
	//CreateはnewとInitializeの呼び出しをまとめた関数
	playerModel_= Model::Create();

	//ビュープロジェクション
	viewProjection_.Initialize();

	//自キャラの生成
	player_ = new Player();
	
	//自キャラの初期化
	player_->Initialize(playerModel_,playerTextureHandle_);


}

void GameScene::Update() { 
	player_->UpDate();


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
