#pragma once
#include <ViewProjection.h>
#include <WorldTransform.h>
#include <Model.h>
#include <AL3_HeaderCpp/AL3_2/AL3_02_08/EnemyBullet/EnemyBullet.h>

//前方宣言で
class Player {

};



class Enemy {
public:
	~Enemy();

	//Initialize(mode,position,velocity)
	void Initialize(Model* model,const Vector3& position,const Vector3& velocity);

	void Fire();

	void Update();

	//ビュープロジェクション
	void Draw(const ViewProjection& viewProjection);

	Vector3 GetEnemyPosition() { 
		return enemyPosition_;
	}
	Vector3 GetEnemyVelocity() { 
		return enemyVelocity_;
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



public:
	//静的メンバ変数
	static const int kFireInterval = 60;




};
