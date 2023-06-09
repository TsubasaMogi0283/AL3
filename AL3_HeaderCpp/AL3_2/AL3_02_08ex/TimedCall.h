#pragma once
#include <functional>

#include "AL3_HeaderCpp/AL3_2/AL3_02_06/Enemy/Enemy.h"

class TimedCall {
public:
	//コンストラクタ
	TimedCall((呼び出したい関数std::function), uint32_t, time);

	void Update();

	bool IsFinished() { 
		return isFinish_;
	}


private:
	//コールバック
	//呼び出したい関数std::function

	//残り時間
	uint32_t time_;
	//完了フラグ
	bool isFinish_ = false;

};