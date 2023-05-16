#pragma once
#include "Model.h"
#include "WorldTransform.h"

class Enemy {
public:

	void Initialize();

	void Update();

	void Draw();


private:
	
	//ワールドトランスフォーム
	WorldTransform* worldTransform_;
	//モデル
	Model* model_=nullptr;
	//テクスチャ
	uint32_t textureHandle_ = 0u;



};