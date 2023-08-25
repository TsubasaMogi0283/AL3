#pragma once
#include "scene/TitleScene/TitleSceneInterface.h"

class TitleScene;

class TitleStartScene :public ITitleScene {
public:
	TitleStartScene();

	void Update(TitleScene* titleScene) override;

	void Draw(TitleScene* titleScene) override;

	~TitleStartScene();


private:
	


};
