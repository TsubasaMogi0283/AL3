#include "AL3_HeaderCpp/AL3_2/AL3_02_08ex/TimedCall.h"

TimedCall::TimedCall(std::function<int32_t(void)> f, uint32_t time) {
	f_ = f;
	time_ = time;
}

void TimedCall::ShotAndReset() {

}

void TimedCall::Update() { 
	if (isFinish_) {
		return;
	}
	time_--;
	if (time_ <= 0) {
		isFinish_ = true;
		//コールバック関数呼び出し
		//呼び出したい関数のstd::function()
		f_();
	}




}