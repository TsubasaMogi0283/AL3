#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "sstream"

#define _USE_MATH_DEFINES
#include <math.h>


#include <AL3_HeaderCpp/AL3_2/AL3_02_03/Player/Player.h>
#include <AL3_HeaderCpp/AL3_2/AL3_02_06/Enemy/Enemy.h>
#include <DebugCamera.h>

#include <imgui.h>
#include <AL3_HeaderCpp/AL3_2/AL3_02_11/Skydome/Skydome.h>
#include <AL3_HeaderCpp/AL3_2/AL3_02_12/RailCamera/RailCamera.h>

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


	//敵発生用関数
	void GenerateEnemy(Vector3 position);

	/// <summary>
	/// 衝突判定と応答
	/// </summary>
	void CheckAllCollision();

	/// 敵弾を追加
	void AddEnemyBullet(EnemyBullet* enemyBullet);

	//敵発生データの読み込み
	void LoadEnemyPopData();

	//敵発生コマンドの更新
	void UpdateEnemyPopCommands();


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
	
	
#pragma region プレイヤーのメンバ変数
	 ///テクスチャハンドル
	uint32_t playerTextureHandle_ = 0;

	//3Dモデル
	Model* playerModel_=nullptr;
	
	//自キャラ
	Player* player_ = nullptr;
#pragma endregion

#pragma region 敵弾
	EnemyBullet* enemyBullet_ = nullptr;

	//引っ越し
	//1.敵弾リストを敵からゲームシーンに引っ越す
	std::list<EnemyBullet*> enemyBullets_;

	//モデルのポインタ
	Model* enemyBodel_ = nullptr;
	//テクスチャハンドル
	
#pragma endregion

#pragma region 敵のメンバ変数

	//敵キャラ

	uint32_t enemyTexture_ =  TextureManager::Load("AL3_Resources/AL3_2/AL3_2_6/Enemy/Enemy.png");;

	Model* enemyModel_ = nullptr;
	Enemy* enemy_ = nullptr;


	std::list<Enemy*> enemyes_;

	//敵発生コマンド
	std::stringstream enemyPopCommands_;


	//待機中フラグ
	bool isWait_ ;
	//待機タイマー
	int32_t waitingTimer_ = 0;

#pragma endregion

	#pragma region 天球のメンバ変数
	//テクスチャハンドル
	uint32_t skydomeTextureHandle_ = 0u;

	//3Dモデル
	Model* skydomeModel_ = nullptr;

	//天球ポインタ
	Skydome* skydome_ = nullptr;

#pragma endregion

	RailCamera* railCamera_ = nullptr;

	//ワールドトランスフォーム
	WorldTransform worldTransform_;
	
	//ビュープロジェクション
	ViewProjection viewProjection_;

	#pragma region カメラのメンバ変数

	//デバッグカメラの切り替え
	bool isDebugCameraActive_ = false;

	//RailCamera
	bool isDebugRailCameraActive_ = false;

	//デバッグカメラ
	DebugCamera* debugCamera_ = nullptr;
	#pragma endregion


};