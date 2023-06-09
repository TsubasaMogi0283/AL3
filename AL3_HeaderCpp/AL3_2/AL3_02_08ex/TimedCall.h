#pragma once
#include <functional>

#include "AL3_HeaderCpp/AL3_2/AL3_02_06/Enemy/Enemy.h"

class TimedCall {
public:
	//�R���X�g���N�^
	TimedCall((�Ăяo�������֐�std::function), uint32_t, time);

	void Update();

	bool IsFinished() { 
		return isFinish_;
	}


private:
	//�R�[���o�b�N
	//�Ăяo�������֐�std::function

	//�c�莞��
	uint32_t time_;
	//�����t���O
	bool isFinish_ = false;

};