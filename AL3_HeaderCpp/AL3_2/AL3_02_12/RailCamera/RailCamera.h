#pragma once
#include <WorldTransform.h>
#include <ViewProjection.h>

class RailCamera {
public:

	//初期化
	void Initialize(Vector3 worldCoodinate,Vector3 rotateRadian);

	//更新
	void Update();

	WorldTransform &GetWorldTransform(){ 
		return worldTransform_;
	}

	Vector3 GetCameraSpeed() { 
		return cameraSpeed_;
	}
	void  SetCameraSpeed(Vector3 speed) { 
		cameraSpeed_ = speed;
	}

	ViewProjection GetViewProjection() { 
		return viewProjection_;
	}


	//カメラなので基本Draw関数は作らない

private:
	
	//ワールドトランスフォーム
	WorldTransform worldTransform_;
	
	//ビュープロジェクション
	ViewProjection viewProjection_;

	Vector3 cameraSpeed_ = {};

};