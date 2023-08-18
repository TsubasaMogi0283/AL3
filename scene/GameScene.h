#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

#include "Player/Player.h"
#include "Enemy/Enemy.h"
#include "Collider/Collider.h"
#include <DebugCamera.h>

#include <imgui.h>

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
	/// 衝突判定と応答
	/// </summary>
	void CheckAllCollision();

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
	/// 
	
	 
	 ///テクスチャハンドル
	uint32_t playerTextureHandle_ = 0;

	//3Dモデル
	Model* playerModel_=nullptr;
	
	//ワールドトランスフォーム
	WorldTransform worldTransform_;
	
	//ビュープロジェクション
	ViewProjection viewProjection_;
	 
	//自キャラ
	Player* player_ = nullptr;


	//敵キャラ
	Model* enemyModel_ = nullptr;
	Enemy* enemy_ = nullptr;


	//デバッグカメラの切り替え
	bool isDebugCameraActive_ = false;




	//デバッグカメラ
	DebugCamera* debugCamera_ = nullptr;



private:
	//GameSceneのにで使うよ!!
	//コライダー２つの衝突判定と応答
	void CheckCollisionPair(Collider* colliderA, Collider* colliderB);

};