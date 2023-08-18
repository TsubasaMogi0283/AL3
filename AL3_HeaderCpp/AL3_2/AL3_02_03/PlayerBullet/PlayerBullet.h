﻿#pragma once
#include <ViewProjection.h>
#include <WorldTransform.h>
#include <Model.h>

#include "AL3_HeaderCpp/AL3_2/AL3_02_10_ex1/Collider/Collider.h"

class PlayerBullet : public Collider {
public:

	//Initialize(mode,position,velocity)
	void Initialize(Model* model,const Vector3& position,const Vector3& velocity);

	//Getter
	//このような関数は「インライン関数」と呼ばれる
	bool IsDead() const { 
		return isDead_;
	}

	// ワールド座標を取得
	Vector3 GetWorldPosition() override;

	float_t GetRadius() { 
		return radius_;
	}

	//衝突を検出したら呼び出されるコールバック関数
	void OnCollision() override;

	void Update();

	//ビュープロジェクション
	void Draw(const ViewProjection& viewProjection);



private:

	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデルのポインタ
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	//速度
	Vector3 velocity_ ;

	

	//寿命
	static const int32_t kLifeTime = 60 * 2;
	//デスタイマー
	int32_t deathTimer_ = kLifeTime;
	//デスフラグ
	bool isDead_ = false;


	//半径
	const float_t radius_ = 1.0f;


};
