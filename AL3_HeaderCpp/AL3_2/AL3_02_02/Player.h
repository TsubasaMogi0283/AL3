#pragma once
#include <input/Input.h>
#include <Model.h>
#include <WorldTransform.h>
#include <AL3_HeaderCpp/AL3_2/AL3_02_02/Function/Function.h>

class Player {
public:
	//初期化
	void Initialize(Model* model,uint32_t textureHandle);

	//更新
	void UpDate();

	//描画
	void Draw(ViewProjection viewProjection);
private:
		
	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	//自キャラ
	Player* player_ = nullptr;

	Input* input_ = nullptr;

};

