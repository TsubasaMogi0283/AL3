#include <AL3_HeaderCpp/AL3_2/AL3_02_01/Player/Player.h>

#include <cassert>

void Player::Initialize(Model* model,uint32_t textureHandle) {
	//NULL�|�C���^�`�F�b�N
	assert(model);

	//�����Ƃ��Ď󂯎�����f�[�^�������o�ϐ��ɋL�^����

	//���[���h�ϐ��̏�����
	worldTransform_.Initialize();
}

void Player::UpDate() {
}

void Player::Draw() {
}
