#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"

#include <AL3_HeaderCpp/AL3_2/AL3_02_06/Function/Function.h>

class Enemy {
public:

	void Initialize(Model* model,const Vector3& position,const Vector3& velocity_);

	void Update();

	void Draw(const ViewProjection& viewProjection);


private:
	
	//���[���h�g�����X�t�H�[��
	WorldTransform* worldTransform_;
	//���f��
	Model* model_ = nullptr;
	//�e�N�X�`��
	uint32_t textureHandle_ = 0u;

	//���x
	Vector3 velocity_;

};