#pragma once
#include <functional>
#include <stdio.h>
#include <stdint.h>

#include "AL3_HeaderCpp/AL3_2/AL3_02_06/Enemy/Enemy.h"

class TimedCall {
public:
	//コンストラクタ
	TimedCall(std::function<int32_t(void)> f, uint32_t time);

	//発射してリセットする関数
	void ShotAndReset();

	//更新
	void Update();

	

	//完了ならtrueを返す
	bool IsFinished() { 
		return isFinish_;
	}


private:
	//コールバック
	//呼び出したい関数std::function
	std::function<int32_t(void)> f_;


	//残り時間
	int32_t time_;
	//完了フラグ
	bool isFinish_ = false;

	Enemy* enemy_= nullptr;

	//時限発動のリスト
	std::list<TimedCall*> timeCalls_;


};