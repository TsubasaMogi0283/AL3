#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

#include "AL3_HeaderCpp/AL3_3/AL3_03_01/Player/Player.h"


#include <memory>

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	
	
	//ワールドトランスフォーム
	WorldTransform worldTransform_;
	
	//ビュープロジェクション
	ViewProjection viewProjection_;
	 


	///テクスチャハンドル
	uint32_t playerTextureHandle_ = 0;

	//3Dモデル
	std::unique_ptr<Model> playerModel_;
	
	//自キャラ
	//Player* player_ = nullptr;

	//自キャラ
	std::unique_ptr<Player> player_;



};
