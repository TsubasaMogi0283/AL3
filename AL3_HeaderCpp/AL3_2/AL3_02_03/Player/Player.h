#pragma once
#include <Input.h>
#include <WorldTransform.h>]

class Player {
public:

	void Initialize();

	void Update();

	void Rotate();

	void Draw();


private:

	Input* input_ = nullptr;

	WorldTransform worldTransform_;

};
