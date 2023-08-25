#pragma once
#include <WorldTransform.h>
#include <cstdint>

class ITitleScene;
class TitleStartScene;

class TitleScene {
public:
	
	TitleScene();

	void Initialize();

	void Update();

	void ChangeTitleState(ITitleScene* newState);

	void Draw();


	~TitleScene();


private:
	ITitleScene* state_ = nullptr;

	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

};