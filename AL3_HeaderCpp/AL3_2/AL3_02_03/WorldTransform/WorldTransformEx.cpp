#include <WorldTransform.h>
#include <AL3_HeaderCpp/AL3_2/AL3_02_03/Function/Function.h>




void WorldTransform::UpdateMatrix() {
	//SRT合成
	matWorld_ = MakeAffineMatrix(scale_, rotation_, translation_);

	if (parent_) {
		matWorld_ *= parent_->matWorld_;
	}

	//定数バッファに転送
	TransferMatrix();


}
