#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

#include <GameScene.h>

#include <imgui.h>

#include "AxisIndicator.h"
GameScene::GameScene() {}

GameScene::~GameScene() { 
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	worldTransform_.Initialize();
	//ビュープロジェクション
	viewProjection_.Initialize();

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
	skydomeModel_.reset(Model::CreateFromOBJ("CelestialSphere", true));

	//テクスチャ読み込み
	skydomeTextureHandle_ = TextureManager::Load("CelestialSphere/uvChecker.png");

	//天球の初期化
	skydome_->Initialize(skydomeModel_.get(), skydomeTextureHandle_);



	#pragma endregion

	//AxisIndicator::GetInstance()->SetVisible(true);
	//AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());

	
}

void GameScene::Update() { 
	player_->Update();

	//#ifdef _DEBUG
	//if (input_->TriggerKey(DIK_C)) {
	//	isDebugCameraActive_ = true;
	//}
	//
	//
	//#endif

	//if (isDebugCameraActive_) {
	//	//デバッグカメラの更新
	//	debugCamera_->Update();
	//	
	//	//ビュー行列(逆行列)
	//	viewProjection_.matView = debugCamera_->GetViewProjection().matView;
	//	//プロジェクション行列(射影行列)
	//	viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
	//	
	//	
	//
	//	//ビュープロジェクション行列の転送
	//	viewProjection_.TransferMatrix();
	//
	//} else {
	//	//ビュープロジェクション行列の更新と転送
	//	viewProjection_.UpdateMatrix();
	//}


	//忘れていたのでここに書いておく
	//ImGuiはUpdateで！！！！！！！！
	//ImGui::Begin("Camera");
	//ImGui::Text("Key C To DeBugCameraIsActive!!");
	//ImGui::InputFloat3("CameraTranslation", &viewProjection_.translation_.x);
	//ImGui::SliderFloat3("CameraTranslationSlide", &viewProjection_.translation_.x, 1000.0f,1000.0f);
	//
	//ImGui::End();

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
