#pragma once
#include <Model.h>
#include <WorldTransform.h>

class Player {
public:
	//初期化
	void Initialize();

	//更新
	void UpDate();

	//描画
	void Draw();


	
private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャファイル
	uint32_t textureHandle_ = 0u; 

	//c++では以下のようにしよう！
	//unsigned int → unint32_t
	//		   int → int32_t
	//
};