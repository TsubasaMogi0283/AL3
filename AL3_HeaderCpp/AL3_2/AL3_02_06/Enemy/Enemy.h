#pragma once
#include "Model.h"
#include "WorldTransform.h"

class Enemy {
public:

	void Initialize();

	void Update();

	void Draw();


private:
	
	//���[���h�g�����X�t�H�[��
	WorldTransform* worldTransform_;
	//���f��
	Model* model_=nullptr;
	//�e�N�X�`��
	uint32_t textureHandle_ = 0u;



};