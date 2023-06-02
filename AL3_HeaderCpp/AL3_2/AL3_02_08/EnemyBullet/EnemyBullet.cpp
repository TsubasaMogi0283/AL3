#include <cassert>
#include <AL3_HeaderCpp/AL3_2/AL3_02_08/EnemyBullet/EnemyBullet.h>
#include <AL3_HeaderCpp/AL3_2/AL3_02_03/Function/Function.h>

void EnemyBullet::Initialize(Model* model, const Vector3& position,const Vector3& velocity) { 
	
	//NULL�`�F�b�N
	assert(model);

	model_ = model;
	//�e�N�X�`���ǂݍ���
	textureHandle_ = TextureManager::Load("AL3_Resources/AL3_2/AL3_2_3/bullet.png");

	//���[���h�g�����X�t�H�[���̏�����
	//���ɂ����
	worldTransform_.Initialize();
	//�����Ŏ󂯎�����������W���Z�b�g
	worldTransform_.translation_ = position;
	velocity_ = velocity;

}



void EnemyBullet::Update() { 

	//���W���ړ�������(1�t���[��������)
	//�x�N�g���̑����Z
	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);

	//���Ԍo�߂Ńf�X
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}


	//���[���h�g�����X�t�H�[���̍X�V
	worldTransform_.UpdateMatrix(); 
}

void EnemyBullet::Draw(const ViewProjection& viewProjection) { 
	//���L�����Ɠ��������Ȃ̂ŏo����Όp�����g���Ƃ�����I
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}