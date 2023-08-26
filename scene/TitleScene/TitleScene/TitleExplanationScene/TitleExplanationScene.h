#pragma once
#include "scene/TitleScene/TitleSceneInterface.h"


#include <cstdint>
#include <Input.h>
#include <Sprite.h>

class TitleScene;

class TitleExplanationScene  :public ITitleScene{
public:
	
	TitleExplanationScene();

	void Initialize() override;

	void Update(TitleScene* titleScene) override;

	void Draw() override;
	
	~TitleExplanationScene();

private:

	Input* input_ = nullptr;


	const float WINDOW_SIZE_WIDTH = 1280.0f;
	const float WINDOW_SIZE_HEIGHT = 720.0f;



#pragma region
	//�e�N�X�`���̐ݒ�
	Sprite* sprite_ = nullptr;

	uint32_t textureHandle_ = 0u;

	//2���p�ӂ���
	uint32_t explanation[2] = {0u};


	//�t���O�I�Ȃ��
	int32_t explantionTextureNumber_ = 0;

#pragma endregion

};