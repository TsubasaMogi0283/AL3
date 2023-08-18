#pragma once
#include <ViewProjection.h>
#include <WorldTransform.h>
#include <Model.h>
#include "Collider/Collider.h"
#include "CalculationFunction/CalculationFunction.h"
#include "Collider/ColliderConfig.h"


//class EnemyBullet : public Collider {
//public:
//
//	//Initialize(mode,position,velocity)
//	void Initialize(Model* model,const Vector3& position,const Vector3& velocity);
//
//	//Getter
//	//このような関数は「インライン関数」と呼ばれる
//	bool IsDead() const { 
//		return isDead_;
//	}
//
//	// ワールド座標を取得
//	Vector3 GetWorldPosition() override;
//
//
//	float_t GetRadius() { 
//		return radius_;
//	}
//
//	//衝突を検出したら呼び出されるコールバック関数
//	void OnCollision() override;
//
//	void Update();
//
//
//
//	//ビュープロジェクション
//	void Draw(const ViewProjection& viewProjection);
//
//

class EnemyBullet : public Collider{
public:
	EnemyBullet();

	void Initialize(Model* model,const Vector3& position, const Vector3& velocity);

	//衝突を検出したら呼び出されるコールバック関数
	void OnCollision()override;

	//Getter
	//このような関数は「インライン関数」と呼ばれる
	Vector3 GetWorldPosition() override;


	WorldTransform GetWorldTransform() { 
		return worldTransform_; 
	}

	bool IsDead() const { 
		return isDead_; 
	}

	void Update();

	void Draw(const ViewProjection& viewProjection);

	
	~EnemyBullet();

private:

	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデルのポインタ
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	//速度
	Vector3 velocity_ ;

	const float_t radius_=1.0f;

	//寿命
	static const int32_t kLifeTime = 60 * 5;
	//デスタイマー
	int32_t deathTimer_ = kLifeTime;
	//デスフラグ
	bool isDead_ = false;



	// BulletLimitTime
	bool bulletDrawFlag = false;

};