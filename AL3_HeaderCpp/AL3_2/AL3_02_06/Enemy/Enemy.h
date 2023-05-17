#pragma once
#include <ViewProjection.h>
#include <WorldTransform.h>
#include <Model.h>

class Enemy {
public:


	//Initialize(mode,position,velocity)
	void Initialize(Model* model,const Vector3& position,const Vector3& velocity);

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

	Vector3 enemyPosition_;

	//速度
	Vector3 velocity_;
	Vector3 leaveVelocity_;

	//enum宣言
	enum class Phase {
		Approach,	//接近
		Leave,		//離脱
	};

	Phase phase_ = Phase();

};
