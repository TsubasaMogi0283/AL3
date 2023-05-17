#include <cassert>

#include <AL3_HeaderCpp/AL3_2/AL3_02_06/Enemy/Enemy.h>

void Enemy::Initialize(Model* model,const Vector3& position,const Vector3& velocity) {

	//assert��
	assert(model);

	//���f�����Y�ꂸ��
	model_ = model;


	//�e�N�X�`���ǂݍ���
	textureHandle_ = TextureManager::Load("AL3_Resources\AL3_2\AL3_2_6\Enemy\Enemy.png");

	//���[���h�g�����X�t�H�[���̏�����
	worldTransform_->Initialize();

	//�������W�E���x�̐ݒ���s��
	worldTransform_->translation_ = position;
	velocity_ = velocity;

}

void Enemy::Update() {

	//�ړ�
	worldTransform_->translation_ = Add(worldTransform_->translation_, velocity_);

	//�s��̍X�V
	worldTransform_->UpdateMatrix();

}

void Enemy::Draw(const ViewProjection& viewProjection) { 
	
	model_->Draw(viewProjection);

}
