#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"

#include <AL3_HeaderCpp/AL3_2/AL3_02_06/Function/Function.h>

class Enemy {
public:

	void Initialize(Model* model,const Vector3& position,const Vector3& velocity_);

	void Update();

	void Draw(const ViewProjection& viewProjection);


private:
	
	//ワールドトランスフォーム
	WorldTransform* worldTransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャ
	uint32_t textureHandle_ = 0u;

	//速度
	Vector3 velocity_;

};