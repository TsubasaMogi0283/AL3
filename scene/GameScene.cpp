#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

#include <GameScene.h>


GameScene::GameScene() {}

GameScene::~GameScene() { 
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	#pragma region 自キャラの生成
	//newの代わり
	player_ = std::make_unique<Player>();

	//テクスチャ読み込み
	playerTextureHandle_ = TextureManager::Load("AL3_Resources/AL3_2/AL3_02_01/Player/Player1.png");

	//3Dモデルの生成
	//CreateはnewとInitializeの呼び出しをまとめた関数
	playerModel_.reset(Model::Create());

	//自キャラの初期化
	player_->Initialize(playerModel_.get(), playerTextureHandle_);

	#pragma endregion



	#pragma region 天球の生成
	skydome_ = std::make_unique<Skydome>();

	//フォルダの名前を指定してね
	//読み込むファイルと同じフォルダ名にしないと✕
	playerModel_.reset(Model::CreateFromOBJ("CelestialSphere", true));

	//テクスチャ読み込み
	skydomeTextureHandle_ = TextureManager::Load("CelestialSphere/uvChecker.png");

	//天球の初期化
	skydome_->Initialize(skydomeModel_.get(), skydomeTextureHandle_);



	#pragma endregion



	//ビュープロジェクション
	viewProjection_.Initialize();
}

void GameScene::Update() { 
	player_->Update();


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
