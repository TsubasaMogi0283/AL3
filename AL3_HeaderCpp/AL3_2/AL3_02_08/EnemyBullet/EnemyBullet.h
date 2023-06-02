#pragma once
#include <ViewProjection.h>
#include <WorldTransform.h>
#include <Model.h>

class EnemyBullet {
public:

	//Initialize(mode,position,velocity)
	void Initialize(Model* model,const Vector3& position,const Vector3& velocity);

	//Getter
	//���̂悤�Ȋ֐��́u�C�����C���֐��v�ƌĂ΂��
	bool IsDead() const { 
		return isDead_;
	}

	void Update();



	//�r���[�v���W�F�N�V����
	void Draw(const ViewProjection& viewProjection);



private:

	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	//���f���̃|�C���^
	Model* model_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

	//���x
	Vector3 velocity_ ;

	//����
	static const int32_t kLifeTime = 60 * 5;
	//�f�X�^�C�}�[
	int32_t deathTimer_ = kLifeTime;
	//�f�X�t���O
	bool isDead_ = false;








};