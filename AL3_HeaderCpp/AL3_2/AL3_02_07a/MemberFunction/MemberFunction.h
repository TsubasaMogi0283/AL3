#pragma once

class MemberFunction {
public:
	//自作メンバ関数
	void TestFunc();

private:
	

	//メンバ関数ポインタ
	void (MemberFunction::*pFunc)();
	
	//使い方の参考
	//メンバ関数ポインタに関数のアドレスを代入する
	//pFunc = &MemberFunction::TestFunc;

	//呼び出し
	//(this->pFunc)();


};

