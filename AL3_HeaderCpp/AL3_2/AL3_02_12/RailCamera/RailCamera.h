#pragma once
#include <WorldTransform.h>
#include <ViewProjection.h>

class RailCamera {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Vector3 worldPsition,Vector3 radian);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	WorldTransform &GetWorldTransform() {
		return worldTransform_; 
	};

	ViewProjection GetViewProjection() { 
		return viewProjection_;
	};

private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//ビュープロジェクション
	ViewProjection viewProjection_;

};