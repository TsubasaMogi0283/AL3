#pragma once

class TitleScene;

class ITitleScene {
public:
	

	ITitleScene();

	virtual void Initialize() = 0;

	virtual void Update(TitleScene* titleScene) = 0;

	virtual void Draw() = 0;

	~ITitleScene();


private:







};