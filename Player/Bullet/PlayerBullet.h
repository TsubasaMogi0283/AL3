#pragma once
#include <ViewProjection.h>
#include <WorldTransform.h>
#include <Model.h>

#include "Collider/Collider.h"

#include "CalculationFunction/CalculationFunction.h"
#include "Collider/Collider.h"
#include "Collider/ColliderConfig.h"


//class PlayerBullet : public Collider {
//public:
//
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
//	float_t GetRadius() { 
//		return radius_;
//	}
//
//	//衝突を検出したら呼び出されるコールバック関数
//	void OnCollision() override;
//
//	void Update();
//
//	//ビュープロジェクション
//	void Draw(const ViewProjection& viewProjection);
//
//
//
//private:
//
//	//ワールド変換データ
//	WorldTransform worldTransform_;
//	//モデルのポインタ
//	Model* model_ = nullptr;
//	//テクスチャハンドル
//	uint32_t textureHandle_ = 0u;
//
//	//速度
//	Vector3 velocity_ ;
//
//	
//
//	//寿命
//	static const int32_t kLifeTime = 60 * 2;
//	//デスタイマー
//	int32_t deathTimer_ = kLifeTime;
//	//デスフラグ
//	bool isDead_ = false;
//
//
//	//半径
//	const float_t radius_ = 1.0f;
//
//
//};


class PlayerBullet :public Collider{
public:
	PlayerBullet();
	~PlayerBullet();

	/// <summary>
	/// 
	/// </summary>
	/// <param name="model"></param>
	/// <param name="position"></param>
	void Initialize(Model* model,const Vector3& position,const Vector3& velocity);

	/// <summary>
	/// 
	/// </summary>
	void Update();
	
	/// <summary>
	///
	/// </summary>
	/// <param name="viewProjection"></param>
	void Draw(const ViewProjection& viewProjection);

	// BulletLimitTime
	static const int32_t kLifeTime = 60 * 5;

	Vector3 GetWorldPosition() override;

	void OnCollision() override;



    //Getter
	//このような関数は「インライン関数」と呼ばれる
	bool IsDead() const { return isDead_; }

	WorldTransform GetWorldTransform() { return worldTransform_; }


private:



	uint32_t textureHandle_;
	Model * model_;
	WorldTransform worldTransform_;

	Vector3 velocity_;

	// BulletLimitTime
	
	int32_t deathTimer_ = kLifeTime;
	
	bool isDead_ = false;
};