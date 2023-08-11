#pragma once
#include "Enemy/EnemyStateInterface/EnemyStateInterface.h"

//前方宣言
class Enemy;

//離脱
class EnemyLeave :public IEnemyState{
public:
	void Update(Enemy* enemy) override;
};
