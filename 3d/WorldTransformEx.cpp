#include <WorldTransform.h>
#include "math/MatrixCalculation/MatrixCalculation.h"




void WorldTransform::UpdateMatrix() {
	//SRT合成
	matWorld_ = MakeAffineMatrix(scale_, rotation_, translation_);

	//定数バッファに転送
	TransferMatrix();


}
