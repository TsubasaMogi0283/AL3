#pragma once
#include "scene/TitleScene/TitleSceneInterface.h"

#include <Sprite.h>

class TitleScene;

class TitleStartScene :public ITitleScene {
public:
	TitleStartScene();

	void Initialize() override;

	void Update(TitleScene* titleScene) override;

	void Draw() override;

	~TitleStartScene();


private:
	

	//スプライト
	Sprite* sprite_ = nullptr;


};
