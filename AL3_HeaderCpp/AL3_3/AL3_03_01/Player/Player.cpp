#include "AL3_HeaderCpp/AL3_3/AL3_03_01/Player/Player.h"
#include <cassert>

void Player::Initialize(Model* model, uint32_t textureHandle) { 
	assert(model_);

	this->model_ = model;

	textureHandle_ = textureHandle;

	worldTransform_.Initialize();

}

void Player::Update() { 
	worldTransform_.TransferMatrix(); 
}

void Player::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}


