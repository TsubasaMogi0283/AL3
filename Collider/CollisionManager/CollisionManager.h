#pragma once

#include <list>
#include <Collider/Collider.h>


//当たり判定関係は全部こっちに持ってくるよ
class CollisionManager {
public:

	//GameSceneであった関数
	void CheckAllCollisions();

	void CheckCollisionPair(Collider* colliderA, Collider* colliderB);

	bool CheckBallCollosion(Vector3 v1, float v1Radious, Vector3 v2, float v2Radious);

	//新規追加
	//コライダーリストに追加する関数
	void AddToColliderList(Collider* collider);
	//コライダーリストをクリアする関数
	void ClearColliderList();



private:
	//コライダーリスト
	std::list<Collider*> colliders_;



};