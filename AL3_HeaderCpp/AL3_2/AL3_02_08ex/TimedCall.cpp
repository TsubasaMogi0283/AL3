#include "AL3_HeaderCpp/AL3_2/AL3_02_08ex/TimedCall.h"

TimedCall::TimedCall(enemy_->, int32_t, time) {

}

void TimedCall::Update() { 
	if (isFinish_) {
		return;
	}
	time_--;
	if (time_ <= 0) {
		isFinish_ = true;
		//�R�[���o�b�N�֐��Ăяo��
		//�Ăяo�������֐���std::function()
	}




}