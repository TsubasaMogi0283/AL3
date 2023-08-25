#include "TitleScene.h"
#include "TitleStartScene/TitleStartScene.h"

TitleScene::TitleScene() { 
	//�ŏ��̓^�C�g����ʂ̕\��
	state_ = new TitleStartScene(); 
}


void TitleScene::Initialize() { 


	


	worldTransform_.Initialize(); 
}


//�V�[���̐؂�ւ�
void TitleScene::ChangeTitleState(ITitleScene* newState) { 
	delete state_; 
	this->state_ = newState;
}


void TitleScene::Update() {

	//ITitleState��Update�ŕω������
	state_->Update(this);


	worldTransform_.UpdateMatrix();
}


void TitleScene::Draw() {

}

TitleScene::~TitleScene() {

}



