
#include "Enemy.h"
#include "CalculationFunction/CalculationFunction.h"

Enemy::Enemy() {}

Enemy::~Enemy() 
{
	model_->~Model();

	for (EnemyBullet* bullet : bullets_) {
		delete bullet;
	}
}



void Enemy::Initialize() {

	phase_ = Phase::Approach;
	PhaseInitialize();

	worldTransform_.Initialize();
	worldTransform_.translation_ = {0.0f, 5.0f, 30.0f};
	model_ = Model::Create();
	modeltexHandle = TextureManager::Load("AL3_Resources/AL3_2/AL3_2_6/Enemy/Enemy.png");
	
	SetCollosionAttribute(kCollisionAttributeEnemy);
	SetCollisionMask(kCollisionAttributePlayer);


}

void Enemy::Update() {

	
	
	

	//const float kCharacterSpeed = 0.2f;

	bullets_.remove_if([](EnemyBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});



	switch (phase_) 
	{

		case Phase::Approach:
			
	        worldTransform_.translation_.z += -0.05f;
		   
			if (worldTransform_.translation_.z<0.0f) {
			    phase_ = Phase::Leave;
			}

			FireTimer--;
		    if (FireTimer<=0) {
			    Fire();
			    FireTimer = kFireInterval;
			
			}
			
			break;

		case Phase::Leave:
		    worldTransform_.translation_.x -= 0.1f;
		    worldTransform_.translation_.z -= 0.1f;
		   
			
			break;

	default:
		break;
	}

	for (EnemyBullet* bullet : bullets_) {
		bullet->Update();
	}	 
	//worldTransform_.translation_ = Add(worldTransform_.translation_, move);

	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	worldTransform_.TransferMatrix();
}

void Enemy::Draw(ViewProjection ViewProjection_) {

	model_->Draw(worldTransform_, ViewProjection_, modeltexHandle);

	for (EnemyBullet* bullet : bullets_) {

		bullet->Draw(ViewProjection_);
	}
}

void Enemy::PhaseInitialize() 
{
	FireTimer = kFireInterval;

}

void Enemy::OnCollision() {}

Vector3 Enemy::GetWorldPosition() {
	Vector3 worldPos;

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;


}

Vector3 Enemy::LerpFanc(Vector3 v1, Vector3 v2) 
{ 
	Vector3 result;


	result.x = v2.x - v1.x;
	result.y = v2.y - v1.y;
	result.z = v2.z - v1.z;

	return result;

}

void Enemy::Fire()
{

	
	//ホーミング処理
	Vector3 PlayerPos=player_->GetWorldPosition();
	Vector3 EnemyPos = GetWorldPosition();

	Vector3 PiEnLerp = LerpFanc(EnemyPos, PlayerPos);

	Vector3 PiEnNormalize = NormalizeVector3(PiEnLerp);



	PiEnNormalize= TransformNormal(PiEnNormalize, worldTransform_.matWorld_);

	// intealize
	EnemyBullet* newBullet = new EnemyBullet();

	newBullet->Initialize(model_, worldTransform_.translation_, PiEnNormalize);

	bullets_.push_back(newBullet);
}