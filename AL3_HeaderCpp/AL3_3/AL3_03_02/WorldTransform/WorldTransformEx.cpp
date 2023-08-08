#include "WorldTransform.h"
#include <AL3_HeaderCpp/AL3_3/AL3_03_02/MatrixCalculation/MatrixCalculation.h>




void WorldTransform::UpdateMatrix() {
	//SRT合成
	matWorld_ = MakeAffineMatrix(scale_, rotation_, translation_);

	//定数バッファに転送
	TransferMatrix();


}
