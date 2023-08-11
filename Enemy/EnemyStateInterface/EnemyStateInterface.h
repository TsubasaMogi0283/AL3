#pragma once


//BaseEnemyStateをここにする
//指摘された通りにBaseではなくInterfaceのIを先頭につける
//EnemyStateInterface

//前方宣言
class Enemy;

class IEnemyState {
public:

	IEnemyState();


	virtual void Update(Enemy* enemy)=0;


	~IEnemyState();




private:

	




};