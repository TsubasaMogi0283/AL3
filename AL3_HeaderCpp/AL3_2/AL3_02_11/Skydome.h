#pragma once
#include <WorldTransform.h>
#include <Model.h>

class Skydome {
public:
	//初期化
	void Initialize();

	//更新
	void Update();

	//描画
	void Draw();


private:

	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;

};

