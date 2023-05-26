
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

	Vector3 GetEnemyPosition() { 
		return enemyPosition_;
	}
	Vector3 GetEnemyVelocity() { 
		return enemyVelocity_;
	}

	void ApproachUpdate();

	void LeaveUpdate();


	//StatePattern
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


	//statepattern
	BaseEnemyState* state_;

};



class BaseEnemyState {
public:
	virtual void Update();


protected:
	Enemy* enemy_;


};

class EnemyStateApproach :public BaseEnemyState{
public:
	void Update() override;
};

class EnemyStateLeave :public BaseEnemyState{
public:
	void Update() override;
};