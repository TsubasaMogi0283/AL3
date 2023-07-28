#include "Ground.h"
#include <AL3_HeaderCpp/AL3_3/AL3_03_02/MatrixCalculation/MatrixCalculation.h>


void Ground::Initialize(Model* model,uint32_t textureHandle) {
	this->model_ = model; 
	this->textureHandle_ = textureHandle;
	worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	//���[���h�ϐ��̏�����
	worldTransform_.Initialize();
}

void Ground::Update() {
	//�s���萔�o�b�t�@�ɓ]��
	worldTransform_.TransferMatrix(); 

	

	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
}

void Ground::Draw(ViewProjection& viewProjection) { 
	model_->Draw(worldTransform_, viewProjection); 
}

