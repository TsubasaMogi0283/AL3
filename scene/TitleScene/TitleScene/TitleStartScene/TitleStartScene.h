#pragma once
#include "scene/TitleScene/TitleSceneInterface.h"

#include <Sprite.h>

class TitleScene;

class TitleStartScene :public ITitleScene {
public:
	TitleStartScene();

	void Initialize(TitleScene* titleScene) override;

	void Update(TitleScene* titleScene) override;

	void Draw(TitleScene* titleScene) override;

	~TitleStartScene();


private:
	

	//スプライト
	Sprite* sprite_ = nullptr;


};
