#pragma once

#include "Enemy/EnemyStateInterface/EnemyStateInterface.h"
#include <Vector3.h>

//前方宣言
class Enemy;

//接近
class EnemyApproach :public IEnemyState{
public:
	void Update(Enemy* enemy) override;

private:

};