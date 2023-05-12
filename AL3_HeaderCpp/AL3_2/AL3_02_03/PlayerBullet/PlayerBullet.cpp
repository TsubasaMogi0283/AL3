#include <cassert>
#include <AL3_HeaderCpp/AL3_2/AL3_02_03/PlayerBullet/PlayerBullet.h>

void PlayerBullet::Initialize(Model* model, const Vector3 position) { 
	
	//NULL�`�F�b�N
	assert(model);

	model_ = model;
	//�e�N�X�`���ǂݍ���
	textureHandle_ = TextureManager::Load("white.png");

	//���[���h�g�����X�t�H�[���̏�����
	//���ɂ����
	worldTransform_.Initialize();
	//�����Ŏ󂯎�����������W���Z�b�g
	worldTransform_.translation_ = position;


}