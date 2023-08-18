#pragma once
#include<Model.h>
#include<WorldTransform.h>
#include<Vector3.h>
#include<Input.h>
#include "CalculationFunction/CalculationFunction.h"
#include "Player/Bullet/PlayerBullet.h"

#include "Collider/Collider.h"
#include "Collider/ColliderConfig.h"


#include <list>
//#incude"MatrixTrans.h"

class Player:public Collider {
public:
	Player();
	~Player();

	void Initialize();

	void Update();

	void Draw(ViewProjection ViewProjection_);

	Vector3 GetWorldPosition()override;

	void OnCollision()override;

	const std::list<PlayerBullet*>& GetBullets() const { return bullets_; }

private:

	void Attack(Vector3 &position);

	Vector3 position_;
	uint32_t modeltexHandle;
	Model* model_;

	WorldTransform worldTransform_;
	


	Input* input_ = nullptr;
	
	std::list<PlayerBullet*> bullets_;

	int bulletCoolTimer = 0;


};

