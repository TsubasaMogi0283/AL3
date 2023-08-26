#pragma once

class GameScene;

class IGameSceneState {
public:
	IGameSceneState();

	virtual void Update(GameScene* gameScene)=0;

	IGameSceneState();

private:


};