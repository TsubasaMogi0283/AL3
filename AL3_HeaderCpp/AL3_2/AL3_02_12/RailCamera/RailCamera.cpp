

#include "RailCamera.h"
#include <AL3_HeaderCpp/AL3_2/AL3_02_03/Function/Function.h>
#include <imgui.h>


void RailCamera::Initialize(Vector3 worldPosition,Vector3 radian) {
	worldTransform_.Initialize();

	worldTransform_.translation_.x = worldPosition.x;
	worldTransform_.translation_.y = worldPosition.y;
	worldTransform_.translation_.z = worldPosition.z;

	cameraSpeed_ = {0.0f, 0.0f, 0.0f};

	worldTransform_.rotation_ = radian;


	viewProjection_.Initialize();
	viewProjection_.farZ = 1200.0f;

}




void RailCamera::Update() {

	worldTransform_.translation_ = Add(worldTransform_.translation_, cameraSpeed_);
	worldTransform_.rotation_ = Add(worldTransform_.rotation_, {0.0f, 0.0f, 0.0f});

	worldTransform_.UpdateMatrix();

	viewProjection_.matView = Inverse(worldTransform_.matWorld_);


	#ifdef _DEBUG

	ImGui::Begin("Camera");
	ImGui::SliderFloat3("translation", &worldTransform_.translation_.x, -10.0f, 10.0f);
	ImGui::SliderFloat3("rotation", &worldTransform_.rotation_.x, -10.0f, 10.0f);
	ImGui::End();

	#endif
}
