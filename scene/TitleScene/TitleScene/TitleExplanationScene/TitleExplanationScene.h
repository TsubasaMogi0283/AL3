#pragma once
#include "scene/TitleScene/TitleSceneInterface.h"
#include <cstdint>

class TitleScene;

class TitleExplanationScene  :public ITitleScene{
public:
	
	TitleExplanationScene();

	void Initialize(TitleScene* titleScene) override;

	void Update(TitleScene* titleScene) override;

	void Draw(TitleScene* titleScene) override;
	
	~TitleExplanationScene();

private:




	//�e�N�X�`���̐ݒ�
	uint32_t textureHandle_ = 0u;

	//2���p�ӂ���
	uint32_t explanation[2] = {0u};


	//�t���O�I�Ȃ��
	int32_t explantionTextureNumber_ = 0;



};