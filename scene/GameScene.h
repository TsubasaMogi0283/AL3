#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

#define _USE_MATH_DEFINES
#include <math.h>


#include <AL3_HeaderCpp/AL3_2/AL3_02_03/Player/Player.h>
#include <AL3_HeaderCpp/AL3_2/AL3_02_06/Enemy/Enemy.h>
#include <DebugCamera.h>

#include <imgui.h>
#include <AL3_HeaderCpp/AL3_2/AL3_02_11/Skydome/Skydome.h>
#include <AL3_HeaderCpp/AL3_2/AL3_02_12/RailCamera/RailCamera.h>

#include "sstream"
#include <Collider/Collider.h>
#include <Collider/ColliderManager/CollisionManager.h>



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

	void LoadEnemyPopData();
	void UpdateEnemyPopCommands();

	//敵発生用関数
	void GenerateEnemy(Vector3 position);





	//登録用の関数
	void AddEnemyBullet(EnemyBullet* enemyBullet);

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





	//Update用
	void TitleScene();

	void ReadyScene();

	void GamePlayScene();

	void ResultScene();

	void WinScene();

	void LoseScene();


	//Sprite描画よう
	void TitleDrawSpriteScene();

	void ReadyDrawSpriteScene();

	void GamePlayDrawSpriteScene();

	void ResultDrawSpriteScene();

	void WinDrawSpriteScene();

	void LoseDrawSpriteScene();


	//3DObject
	void TitleDraw3DObjectScene();

	void ReadyDraw3DObjectScene();

	void GamePlayDraw3DObjectScene();

	void ResultDraw3DObjectScene();

	void WinDraw3DObjectScene();

	void LoseDraw3DObjectScene();


private:

	//当たり判定
	void CheckCollisionPair(Collider* colliderA, Collider* colliderB);
	
	void CheckAllCollisions();

	 CollisionManager* collisionManager_ = nullptr;

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	/// 
	
#pragma region プレイヤーのメンバ変数
	 ///テクスチャハンドル
	uint32_t playerTextureHandle_ = 0;

	//3Dモデル
	Model* playerModel_=nullptr;
	
	//自キャラ
	Player* player_ = nullptr;

	uint32_t reticleHandle_ = 0;

#pragma endregion

#pragma region 自弾
	PlayerBullet* playerBullet_ = nullptr;

	//引っ越し
	//1.敵弾リストを敵からゲームシーンに引っ越す
	std::list<PlayerBullet*> playerBullets_;

	//モデルのポインタ
	Model* playerBulletModel_ = nullptr;
	//テクスチャハンドル
	uint32_t playerBulletTexture_ = 0;


#pragma endregion


#pragma region 敵弾
	EnemyBullet* enemyBullet_ = nullptr;

	///テクスチャハンドル
	uint32_t enemyTextureHandle_ = 0;

	//引っ越し
	//1.敵弾リストを敵からゲームシーンに引っ越す
	std::list<EnemyBullet*> enemyBullets_;

	//モデルのポインタ
	Model* enemyBulletModel_ = nullptr;
	//テクスチャハンドル
	uint32_t enemyBulletTexture_ = 0;


#pragma endregion

#pragma region 敵のメンバ変数

	//敵キャラ

	uint32_t enemyTexture_ =  0;

	Model* enemyModel_ = nullptr;
	Enemy* enemy_ = nullptr;


	//さっさと引っ越し！
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




	//シーン管理をStatePatternでやろうと思ったけど時間かかりそう
	//余裕があるときにやってみる
	//なんやかんやでswitchが一番使いやすい。偉大だよこれ
	enum class Scene {
		//タイトル
		Title,
		
		//カウントダウン
		Ready,

		//ゲーム
		Game,

		//結果
		Result,

		//勝ち
		Win,

		//負け
		Lose,

	};

	Scene scene_ = Scene();


	enum class DrawSpriteScene {
		//タイトル
		Title,
		
		//カウントダウン
		Ready,

		//ゲーム
		Game,

		//結果
		Result,

		//勝ち
		Win,

		//負け
		Lose,
	};

	DrawSpriteScene drawSpriteScene_ = DrawSpriteScene();




	enum class Draw3DObjectScene {
		//タイトル
		Title,
		
		//カウントダウン
		Ready,

		//ゲーム
		Game,

		//結果
		Result,

		//勝ち
		Win,

		//負け
		Lose,
	};

	Draw3DObjectScene draw3DObjectScene_ = Draw3DObjectScene();


	
	


	//フラグ的な奴
	int32_t titleTextureNumber_ = 0;
	
	
	
	//タイトル
	Sprite* titleLogoSprite_ = nullptr;
	uint32_t titleLogoTexture = 0u;
	//説明
	Sprite* explanationSprite[2] = {nullptr};
	uint32_t explanationTexture[2] = {0u};
	



	//フラグ的な奴
	int32_t countDownTextureNumber_ = 0;

	//カウントダウン
	const int32_t SECOND_ = 60;
	int32_t countDownTimer_ = SECOND_ * 3;

	Sprite* countDownSprite[4] = {nullptr};
	uint32_t countDownTexture[4] = {0u};








	          
	//制限時間
	int32_t gameLimitTime_ = SECOND_* 30;



	//リザルト
	Sprite* winSprite_ = nullptr;
	uint32_t winTexture_ = 0u;

	Sprite* loseSprite_ = nullptr;
	uint32_t loseTexture_ = 0u;

	bool isWin_;




};