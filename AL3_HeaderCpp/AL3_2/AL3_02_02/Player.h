#pragma once
#include <input/Input.h>

class Player {
public:
	void Initialize();

	void UpDate();


	void Draw();


private:
	
	Input* input_ = nullptr;

};

