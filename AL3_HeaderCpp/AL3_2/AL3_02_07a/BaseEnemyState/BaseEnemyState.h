#pragma once
#include "AL3_HeaderCpp/AL3_2/AL3_02_06/Enemy/Enemy.h"

//継承するよ
class BaseEnemyState {
public:
	void Update();



protected:
	Enemy* enemy_;



};

