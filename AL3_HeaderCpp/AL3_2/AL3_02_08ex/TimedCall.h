#pragma once
#include <functional>
#include <stdio.h>
#include <stdint.h>

#include "AL3_HeaderCpp/AL3_2/AL3_02_06/Enemy/Enemy.h"

class TimedCall {
public:
	//�R���X�g���N�^
	TimedCall(std::function<int32_t(void)> f, uint32_t time);

	//���˂��ă��Z�b�g����֐�
	void ShotAndReset();

	//�X�V
	void Update();

	

	//�����Ȃ�true��Ԃ�
	bool IsFinished() { 
		return isFinish_;
	}


private:
	//�R�[���o�b�N
	//�Ăяo�������֐�std::function
	std::function<int32_t(void)> f_;


	//�c�莞��
	int32_t time_;
	//�����t���O
	bool isFinish_ = false;

	Enemy* enemy_= nullptr;

	//���������̃��X�g
	std::list<TimedCall*> timeCalls_;


};