#pragma once
#include <ViewProjection.h>
#include <WorldTransform.h>
#include <Model.h>

class PlayerBullet {
public:

	//Initialize(mode,position,velocity)
	void Initialize(Model* model,const Vector3& position,const Vector3& velocity);

	//Getter
	//このような関数は「インライン関数」と呼ばれる
	bool IsDead() const { 
		return isDead_;
	}

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
	static const int32_t kLifeTime = 60 * 5;
	//デスタイマー
	int32_t deathTimer_ = kLifeTime;
	//デスフラグ
	bool isDead_ = false;



};
