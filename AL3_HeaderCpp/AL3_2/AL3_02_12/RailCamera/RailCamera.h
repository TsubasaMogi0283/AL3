﻿#pragma once
#include <WorldTransform.h>
#include <ViewProjection.h>

class RailCamera {
public:

	//初期化
	void Initialize(Vector3 worldCoodinate,Vector3 rotateRadian);

	//更新
	void Update();

	//カメラなので基本Draw関数は作らない

private:
	
	//ワールドトランスフォーム
	WorldTransform worldTransform_;
	
	//ビュープロジェクション
	ViewProjection viewProjection_;

};