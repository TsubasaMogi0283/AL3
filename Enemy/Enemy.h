#pragma once

#include <Model.h>
#include <WorldTransform.h>
#include "Enemy/Bullet/EnemyBullet.h"
#include "Player/Player.h"
#include "Collider/Collider.h"
#include "Collider/ColliderConfig.h"

class Player;


class Enemy :public Collider{
public:
	enum class Phase {
		Approach,
		Leave,
	};

	Enemy();
	~Enemy();

	void Initialize();

	void Update();

	void Draw(ViewProjection ViewProjection_);

	void PhaseInitialize();
	
	void SetPlayer(Player* player) { player_ = player; }

	

	void OnCollision() override;

	Vector3 GetWorldPosition()override;

	Vector3 LerpFanc(Vector3 v1, Vector3 v2);

	
	const std::list<EnemyBullet*>& GetBullets() const { return bullets_; }


private:
	

	void Fire();

	uint32_t modeltexHandle;
	Model* model_;
	WorldTransform worldTransform_;


	Phase phase_ = Phase();

	std::list<EnemyBullet*> bullets_;

	static const int kFireInterval = 60;

	int32_t FireTimer = 0;

	Player* player_ = nullptr;

};
