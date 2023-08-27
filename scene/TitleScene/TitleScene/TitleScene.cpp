#include "TitleScene.h"
#include "TitleStartScene/TitleStartScene.h"

TitleScene::TitleScene() { 
	//最初はタイトル画面の表示
	state_ = new TitleStartScene(); 
}


void TitleScene::Initialize() { 


	


	worldTransform_.Initialize(); 
}


//シーンの切り替え
void TitleScene::ChangeTitleState(ITitleScene* newState) { 
	delete state_; 
	this->state_ = newState;
}


void TitleScene::Update() {

	//ITitleStateのUpdateで変化するよ
	state_->Update(this);


	worldTransform_.UpdateMatrix();
}


void TitleScene::Draw() {

}

TitleScene::~TitleScene() {

}



