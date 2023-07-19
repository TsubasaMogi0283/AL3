#pragma once
#include <ViewProjection.h>
#include <WorldTransform.h>
#include <Model.h>
#include <AL3_HeaderCpp/AL3_2/AL3_02_08/EnemyBullet/EnemyBullet.h>

//前方宣言で
class Player;

//GameSceneの前方宣言
class GameScene;

class Enemy {
public:
	~Enemy();

	//Initialize(mode,position,velocity)
	void Initialize(Model* model,const Vector3& position,const Vector3& velocity);

	void Fire();

	//弾リストを取得
	const std::list<EnemyBullet*>& GetBullets() const { 
		return bullets_;
	}

	const float_t GetRadius() { 
		return radius_; 
	};

	//衝突を検出したら呼び出されるコールバック関数
	void OnCollision();

	//更新
	void Update();

	//ビュープロジェクション
	void Draw(const ViewProjection& viewProjection);


	#pragma region アクセッサ
	Vector3 GetEnemyPosition() { 
		return enemyPosition_;
	}
	Vector3 GetEnemyVelocity() { 
		return enemyVelocity_;
	}
	#pragma endregion

	//敵キャラに自キャラのアドレスを渡す
	//GameSceneからPlayerを借りる
	void SetPlayer(Player* player) { 
		player_ = player;
	}

	//ゲームシーン追加
	void SetGameScene(GameScene* gameScene) { 
		gameScene_ = gameScene;
	}

	//ワールド座標を取得
	Vector3 GetWorldPosition();

	void ApproachInitialize();

	void ApproachUpdate();

	void LeaveUpdate();


private:

	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデルのポインタ
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	//速度
	const float kEnemySpeed_ = -0.05f;
	Vector3 enemyPosition_ = {0.0f, 3.0f, 20.0f};
	Vector3 enemyVelocity_ = {0.0f, 0.0f, kEnemySpeed_};
	
	float_t radius_=1.0f;

	
	
	//enum宣言
	enum class Phase {
		Approach,	//接近
		Leave,		//離脱
	};

	Phase phase_ = Phase();




	EnemyBullet* enemyBullets_ = nullptr;
	//これをゲームシーンへ
	std::list<EnemyBullet*> bullets_;

	//発射タイマー
	int32_t enemyBulletShotTime = 0;



	//自キャラ
	Player* player_ = nullptr;


	//ゲームシーン
	GameScene* gameScene_ = nullptr;

public:
	//静的メンバ変数
	static const int kFireInterval = 60;




};
