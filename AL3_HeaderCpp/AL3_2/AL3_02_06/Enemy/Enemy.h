#pragma once
#include <ViewProjection.h>
#include <WorldTransform.h>
#include <Model.h>
#include <AL3_HeaderCpp/AL3_2/AL3_02_08/EnemyBullet/EnemyBullet.h>

//前方宣言で
class Player;

class GameScene;

class Enemy {
public:
	~Enemy();

	//Initialize(mode,position,velocity)
	void Initialize(Model* model,uint32_t textureHandle ,const Vector3& position);

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

	void Update();

	//ビュープロジェクション
	void Draw(const ViewProjection& viewProjection);

	Vector3 GetEnemyPosition() { 
		return enemyPosition_;
	}
	Vector3 GetEnemyVelocity() { 
		return enemyVelocity_;
	}
	void SetGameScene(GameScene* gameScene) { 
		gameScene_ = gameScene;
	}

	bool IsDead() { 
		return isDead_;
	}

	//敵キャラに自キャラのアドレスを渡す
	//GameSceneからPlayerを借りる
	void SetPlayer(Player* player) { 
		player_ = player;
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
	std::list<EnemyBullet*> bullets_;

	//発射タイマー
	int32_t enemyBulletShotTime = 0;



	//自キャラ
	Player* player_ = nullptr;

	GameScene* gameScene_ = nullptr;
	bool isDead_ = false;

public:
	//静的メンバ変数
	static const int kFireInterval = 60*2;




};
