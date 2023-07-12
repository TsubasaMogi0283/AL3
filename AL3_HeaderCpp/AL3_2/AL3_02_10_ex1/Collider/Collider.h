#pragma once
#include <Vector3.h>

//衝突判定オブジェクト
class Collider {
public:

	//衝突時に呼ばれる関数
	virtual void OnCollision();

	//純枠仮想関数(Pure Virtual Function)
	//Virtual関数の後ろに「=0」をつけるだけ
	//https://kaworu.jpn.org/cpp/%E7%B4%94%E7%B2%8B%E4%BB%AE%E6%83%B3%E9%96%A2%E6%95%B0
	//ワールド座標を取得
	virtual Vector3 GetWorldPosition() = 0;


	//アクセッサを宣言・定義
	//Getter
	float GetCollisionRadius() { 
		return radius_;
	}

	//Setter
	void SetCollisionRadius(float radius) { 
		radius_ = radius;
	}




private:
	//当たり判定で使う半径
	float radius_ = 1.0f;





};