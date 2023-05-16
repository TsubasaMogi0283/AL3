#pragma once
#include <ViewProjection.h>
#include <WorldTransform.h>
#include <Model.h>

class PlayerBullet {
public:

	void Initialize(Model* model,const Vector3 position);

	void Update();

	//ビュープロジェクション
	void Draw(const ViewProjection& viewProjection);



private:

	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデルのポインタ
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;
};
