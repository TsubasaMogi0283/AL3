#pragma once
#include <WorldTransform.h>
#include <Model.h>

class Skydome {
public:
	//������
	void Initialize();

	//�X�V
	void Update();

	//�`��
	void Draw();


private:

	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	//���f��
	Model* model_ = nullptr;

};

