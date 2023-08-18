#include "CollisionManager.h"


void CollisionManager::CheckAllCollisions()
{
	std::list<Collider*>::iterator itrA = colliders_.begin();

	for (; itrA != colliders_.end(); ++itrA) {

		Collider* colliderA = *itrA;

		std::list<Collider*>::iterator itrB = itrA;
		itrB++;
		for (; itrB != colliders_.end(); ++itrB) {
			Collider* colliderB = *itrB;
			//当たり判定処理
			CheckCollisionPair(colliderA, colliderB);
		}
	}
}

bool CollisionManager::CheckBallCollosion(Vector3 v1, float v1Radious, Vector3 v2, float v2Radious) {
	float x = (v2.x - v1.x);
	float y = (v2.y - v1.y);
	float z = (v2.z - v1.z);

	float resultPos = (x * x) + (y * y) + (z * z);

	float resultRadious = v1Radious + v2Radious;

	bool Flag = false;

	if (resultPos <= (resultRadious * resultRadious)) {
		Flag = true;
	}

	return Flag;
}

void CollisionManager::CheckCollisionPair(Collider* colliderA, Collider* colliderB) {
	
	//フィルタリング
	if ((colliderA->GetCollosionAttribute() & colliderB->GetCollisionMask()) == 0 ||
	    (colliderA->GetCollisionMask()&colliderB->GetCollosionAttribute()) == 0) {
		return;
	}

	//当たり判定の計算開始
	Vector3 cApos = colliderA->GetWorldPosition();
	Vector3 cBpos = colliderB->GetWorldPosition();

	float cAradious = colliderA->GetRadious();
	float cBradious = colliderB->GetRadious();

	if (CheckBallCollosion(cApos, cAradious, cBpos, cBradious)) {
		colliderA->OnCollision();
		colliderB->OnCollision();
	}
}



//コライダーリストに追加する関数
void CollisionManager::AddToColliderList(Collider* collider) { 
	colliders_.push_back(collider);
}

//コライダーリストをクリアする関数
void CollisionManager::ClearColliderList() { 
	colliders_.clear();
}

