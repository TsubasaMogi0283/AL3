
#pragma once
#include <ViewProjection.h>
#include <WorldTransform.h>
#include <Model.h>


class Enemy;
class BaseEnemyState;
class EnemyStateApproach;
class EnemyStateLeave;







class BaseEnemyState {
public:
	BaseEnemyState();

	virtual void Update()=0;


protected:
	Enemy* enemy_=nullptr;

	Vector3 enemyNewTranslate_ = {};

};

class EnemyStateApproach :public BaseEnemyState{
public:
	void Update() override;

};

class EnemyStateLeave :public BaseEnemyState{
public:
	void Update() override;
};





class Enemy {
public:
	Enemy();
	~Enemy();

	//Initialize(mode,position,velocity)
	void Initialize(Model* model,const Vector3& position,const Vector3& velocity);

	void Update();

	//ビュープロジェクション
	void Draw(const ViewProjection& viewProjection);


	Vector3 GetTranslation() { 
		return worldTransform_.translation_;
	}
	Vector3 GetVelocity() { 
		return enemyVelocity_;
	}
	

	void SetTranslation(Vector3 enemyTranslate);
	
	void SetVelocity(Vector3 enemyVelocity);




	void ApproachUpdate();

	void LeaveUpdate();


	//StatePattern
	void ChangeState(BaseEnemyState* newState);

private:

	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデルのポインタ
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;


	//速度
	const float kEnemySpeed_ = -0.2f;
	Vector3 enemyTranslate_ = {0.0f, 3.0f, 20.0f};
	

	Vector3 enemyVelocity_ = {0.0f, 0.0f, kEnemySpeed_};
	


	
	
	//enum宣言
	enum class Phase {
		Approach,	//接近
		Leave,		//離脱
	};

	Phase phase_ = Phase();

	

	//メンバ関数ポインタのテーブル
	static void (Enemy::*spFuncTable[])();


	//StatePattern
	BaseEnemyState* state_=nullptr;

};