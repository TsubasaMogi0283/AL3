#pragma once

class TitleScene;

class ITitleScene {
public:
	

	ITitleScene();

	virtual void Initialize(TitleScene* titleScene) = 0;

	virtual void Update(TitleScene* titleScene) = 0;

	virtual void Draw(TitleScene* titleScene) = 0;

	~ITitleScene();


private:







};