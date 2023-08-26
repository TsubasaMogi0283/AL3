#include "TitleExplanationScene.h"


#include "TitleScene/TitleScene/TitleScene.h"


TitleExplanationScene::TitleExplanationScene() {

}

void TitleExplanationScene::Initialize() {
	input_ = Input::GetInstance();


	explanation[0] = 0;
	explanation[1] = 0;


	//�ŏ��͂P���ڂ̉摜
	explantionTextureNumber_ = 1;

	textureHandle_ = explanation[0];

	//���Ԃ��Ă݂��璆�S�_�����Ă���݂���
	sprite_ = Sprite::Create(textureHandle_, {100.0f, 50.0f});
}

void TitleExplanationScene::Update(TitleScene* titleScene) {

	//2���ڂ̐����ɐi��
	if (input_->TriggerKey(DIK_SPACE) != 0 && explantionTextureNumber_ == 1) {
		explantionTextureNumber_ = 2;
	}


	//�J�E���g�_�E����
	if (input_->TriggerKey(DIK_SPACE) != 0 && explantionTextureNumber_ == 2) {
		//titleScene->ChangeTitleState(new )
	}

}

void TitleExplanationScene::Draw() { 
	if (explantionTextureNumber_ == 1) {
		textureHandle_ = explanation[0];
	}
	if (explantionTextureNumber_ == 2) {
		textureHandle_ = explanation[1];
	}


	sprite_->Draw();


}


TitleExplanationScene::~TitleExplanationScene() {


}

