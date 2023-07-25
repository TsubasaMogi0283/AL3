#include "RailCamera.h"


void RailCamera::Initialize(Vector3 worldPosition,Vector3 radian) {
	worldTransform_.translation_ = worldPosition;
	worldTransform_.rotation_ = radian;

	viewProjection_.Initialize();


}




void RailCamera::Update() {

}