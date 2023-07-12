#pragma once
#include <list>

#include <input/Input.h>
#include <Model.h>
#include <WorldTransform.h>
#include <AL3_HeaderCpp/AL3_2/AL3_02_03/Function/Function.h>
#include <AL3_HeaderCpp/AL3_2/AL3_02_03/PlayerBullet/PlayerBullet.h>
#include "AL3_HeaderCpp/AL3_2/AL3_02_10_ex1/Collider/Collider.h"


class Player : public Collider{
public:
	// デストラクタ
	~Player();

	// 初期化
	void Initialize(Model* model, uint32_t textureHandle);

	// ワールド座標を取得
	Vector3 GetWorldPosition() override;


	// 回転
	void Rotate();
	// 攻撃
	void Attack();

	//弾リストを取得
	const std::list<PlayerBullet*>& GetBullets() const { 
		return bullets_;
	};

	const float_t GetRadius() { return radius_; };

	//衝突を検出したら呼び出されるコールバック関数
	//オーバーライドするよ!!
	void OnCollision() override;

	// 更新
	void UpDate();

	// 描画
	void Draw(ViewProjection viewProjection);

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	// 自キャラ
	Player* player_ = nullptr;

	Input* input_ = nullptr;

	const float_t radius_ = 2.0f;

	int32_t count_ = 0;

	// 弾
	// メンバ「変数」なのでprivate
	PlayerBullet* bullet_ = nullptr;

	// STL(Standard Template
	// Library)...「データの出し入れ、整理する」ための便利な仕組みを提供するlib
	//
	// list(双方向リスト)の導入
	// とりあえず弾を沢山出したい時に使うのがおすすめらしい。ただどの順番で消えるか分からない
	// 複数形だからsつけるの忘れないでね
	std::list<PlayerBullet*> bullets_;
};


