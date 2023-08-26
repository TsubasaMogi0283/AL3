#include "TitleExplanationScene.h"


TitleExplanationScene::TitleExplanationScene() {

}

void TitleExplanationScene::Initialize(TitleScene* titleScene) {
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


	if (input_->TriggerKey(DIK_SPACE) != 0 && explantionTextureNumber_ == 1) {
		explantionTextureNumber_ = 2;
	}


}

void TitleExplanationScene::Draw(TitleScene* titleScene) { 
	sprite_->Draw();


}


TitleExplanationScene::~TitleExplanationScene() {


}

