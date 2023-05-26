#pragma once
#include <ViewProjection.h>
#include <WorldTransform.h>
#include <Model.h>
#include <AL3_HeaderCpp/AL3_2/AL3_02_07a/BaseEnemyState/BaseEnemyState.h>

class Enemy {
public:

	//Initialize(mode,position,velocity)
	void Initialize(Model* model,const Vector3& position,const Vector3& velocity);

	void Update();

	//ビュープロジェクション
	void Draw(const ViewProjection& viewProjection);

	Vector3 GetEnemyPosition() { 
		return enemyPosition_;
	}
	Vector3 GetEnemyVelocity() { 
		return enemyVelocity_;
	}


	Vector3 GetEnemyTranslate() { 
		return worldTransform_.translation_;
	}


	void ChangeState(BaseEnemyState*);

private:

	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデルのポインタ
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	//速度
	const float kEnemySpeed_ = -0.2f;
	Vector3 enemyPosition_ = {0.0f, 3.0f, 20.0f};
	Vector3 enemyVelocity_ = {0.0f, 0.0f, kEnemySpeed_};
	
	
	
	//enum宣言
	enum class Phase {
		Approach,	//接近
		Leave,		//離脱
	};

	Phase phase_ = Phase();

	

	//メンバ関数ポインタのテーブル
	static void (Enemy::*spFuncTable[])();



	//State Pattern
	BaseEnemyState* state_;

	


};
