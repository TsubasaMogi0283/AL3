#include <cassert>
#include <AL3_HeaderCpp/AL3_2/AL3_02_06/Enemy/Enemy.h>
#include <AL3_HeaderCpp/AL3_2/AL3_02_03/Function/Function.h>


void Enemy::Initialize(Model* model, const Vector3& position,const Vector3& velocity) { 
	
	//NULLチェック
	assert(model);

	model_ = model;
	//テクスチャ読み込み
	textureHandle_ = TextureManager::Load("AL3_Resources/AL3_2/AL3_2_6/Enemy/Enemy.png");


	//ワールドトランスフォームの初期化
	//中にあるよ
	worldTransform_.Initialize();
	//引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;
	enemyVelocity_ = velocity;

}

//void Enemy::ApproachUpdate() {
//	//移動(ベクトルの加算)
//		
//	
//	
//}




//void (Enemy::*Enemy::spFuncTable[])()={
//
//	//0
//	&Enemy::ApproachUpdate,
//	//1
//	&Enemy::LeaveUpdate,
//
//};

void Enemy::Update() { 

	//switch (phase_) { 
	//	case Phase::Approach:
	//default:
	//	    ApproachUpdate();
	//
	//	break;
	//
	//	case Phase::Leave:
	//	LeaveUpdate();
	//	break;
	//
	//}
	
	
	//メンバ関数ポインタに入っている関数を呼び出す
	//ここではAppriachUpdate
	(this->*spFuncTable[static_cast<size_t>(phase_)])();



	//座標を移動させる(1フレーム分足す)
	//ベクトルの足し算
	worldTransform_.translation_ = Add(worldTransform_.translation_, enemyVelocity_);
	enemyVelocity_ = TransformNormal(enemyVelocity_,worldTransform_.matWorld_ );
	
	//ワールドトランスフォームの更新
	worldTransform_.UpdateMatrix(); 


}

void Enemy::Draw(const ViewProjection& viewProjection) { 
	//自キャラと同じ処理なので出来れば継承を使うといいよ！
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}