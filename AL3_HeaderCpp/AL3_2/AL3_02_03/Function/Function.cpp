﻿#include <AL3_HeaderCpp/AL3_2/AL3_02_03/Function/Function.h>
#include <cassert>
#include <cmath>


Vector3 Add(const Vector3 v1, const Vector3 v2) {
	Vector3 result = {};
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;

	return result;
}

Vector3 Subtract(const Vector3 v1, const Vector3 v2) {
	Vector3 result;
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return result;
}



//Scale
Matrix4x4 MakeScaleMatrix(const Vector3 scale) {
	Matrix4x4 result = {};
	result.m[0][0] = scale.x;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = scale.y;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = scale.z;
	result.m[2][3] = 0.0f;


	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;


	return result;
}

//Rotate
Matrix4x4 MakeRotateXMatrix(float radian) {
	Matrix4x4 result = {};

	result.m[0][0] = 1.0f;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = std::cos(radian);
	result.m[1][2] = std::sin(radian);
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = -(std::sin(radian));
	result.m[2][2] = std::cos(radian);
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

	return result;
}

Matrix4x4 MakeRotateYMatrix(float radian) {
	Matrix4x4 result = {};

	result.m[0][0] = std::cos(radian);
	result.m[0][1] = 0.0f;
	result.m[0][2] = -(std::sin(radian));
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = 1.0f;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = std::sin(radian);
	result.m[2][1] = 0.0f;
	result.m[2][2] = std::cos(radian);
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

	return result;
}

Matrix4x4 MakeRotateZMatrix(float radian) {
	Matrix4x4 result = {};

	result.m[0][0] = std::cos(radian);
	result.m[0][1] = std::sin(radian);
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = -(std::sin(radian));
	result.m[1][1] = std::cos(radian);
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = 1.0f;
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

	return result;
}


Matrix4x4 Multiply(const Matrix4x4 m1, const Matrix4x4 m2) {
	Matrix4x4 result = {};
	result.m[0][0] = (m1.m[0][0] * m2.m[0][0]) + (m1.m[0][1] * m2.m[1][0]) + (m1.m[0][2] * m2.m[2][0]) + (m1.m[0][3] * m2.m[3][0]);
	result.m[0][1] = (m1.m[0][0] * m2.m[0][1]) + (m1.m[0][1] * m2.m[1][1]) + (m1.m[0][2] * m2.m[2][1]) + (m1.m[0][3] * m2.m[3][1]);
	result.m[0][2] = (m1.m[0][0] * m2.m[0][2]) + (m1.m[0][1] * m2.m[1][2]) + (m1.m[0][2] * m2.m[2][2]) + (m1.m[0][3] * m2.m[3][2]);
	result.m[0][3] = (m1.m[0][0] * m2.m[0][3]) + (m1.m[0][1] * m2.m[1][3]) + (m1.m[0][2] * m2.m[2][3]) + (m1.m[0][3] * m2.m[3][3]);

	result.m[1][0] = (m1.m[1][0] * m2.m[0][0]) + (m1.m[1][1] * m2.m[1][0]) + (m1.m[1][2] * m2.m[2][0]) + (m1.m[1][3] * m2.m[3][0]);
	result.m[1][1] = (m1.m[1][0] * m2.m[0][1]) + (m1.m[1][1] * m2.m[1][1]) + (m1.m[1][2] * m2.m[2][1]) + (m1.m[1][3] * m2.m[3][1]);
	result.m[1][2] = (m1.m[1][0] * m2.m[0][2]) + (m1.m[1][1] * m2.m[1][2]) + (m1.m[1][2] * m2.m[2][2]) + (m1.m[1][3] * m2.m[3][2]);
	result.m[1][3] = (m1.m[1][0] * m2.m[0][3]) + (m1.m[1][1] * m2.m[1][3]) + (m1.m[1][2] * m2.m[2][3]) + (m1.m[1][3] * m2.m[3][3]);

	result.m[2][0] = (m1.m[2][0] * m2.m[0][0]) + (m1.m[2][1] * m2.m[1][0]) + (m1.m[2][2] * m2.m[2][0]) + (m1.m[2][3] * m2.m[3][0]);
	result.m[2][1] = (m1.m[2][0] * m2.m[0][1]) + (m1.m[2][1] * m2.m[1][1]) + (m1.m[2][2] * m2.m[2][1]) + (m1.m[2][3] * m2.m[3][1]);
	result.m[2][2] = (m1.m[2][0] * m2.m[0][2]) + (m1.m[2][1] * m2.m[1][2]) + (m1.m[2][2] * m2.m[2][2]) + (m1.m[2][3] * m2.m[3][2]);
	result.m[2][3] = (m1.m[2][0] * m2.m[0][3]) + (m1.m[2][1] * m2.m[1][3]) + (m1.m[2][2] * m2.m[2][3]) + (m1.m[2][3] * m2.m[3][3]);

	result.m[3][0] = (m1.m[3][0] * m2.m[0][0]) + (m1.m[3][1] * m2.m[1][0]) + (m1.m[3][2] * m2.m[2][0]) + (m1.m[3][3] * m2.m[3][0]);
	result.m[3][1] = (m1.m[3][0] * m2.m[0][1]) + (m1.m[3][1] * m2.m[1][1]) + (m1.m[3][2] * m2.m[2][1]) + (m1.m[3][3] * m2.m[3][1]);
	result.m[3][2] = (m1.m[3][0] * m2.m[0][2]) + (m1.m[3][1] * m2.m[1][2]) + (m1.m[3][2] * m2.m[2][2]) + (m1.m[3][3] * m2.m[3][2]);
	result.m[3][3] = (m1.m[3][0] * m2.m[0][3]) + (m1.m[3][1] * m2.m[1][3]) + (m1.m[3][2] * m2.m[2][3]) + (m1.m[3][3] * m2.m[3][3]);


	return result;


}


//AllRotate
Matrix4x4 MakeRotateXYZMatrix(float radianX, float radianY, float radianZ) {
	Matrix4x4 result;
	
	Matrix4x4 rotateMatrixX = MakeRotateXMatrix(radianX);
	Matrix4x4 rotateMatrixY = MakeRotateYMatrix(radianY);
	Matrix4x4 rotateMatrixZ = MakeRotateZMatrix(radianZ);



	result = Multiply(rotateMatrixX, Multiply(rotateMatrixY, rotateMatrixZ));

	return result;

}

//Translate
Matrix4x4 MakeTranslateMatrix(Vector3 translate) {
	Matrix4x4 result = {};
	result.m[0][0] = 1.0f;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = 1.0f;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = 1.0f;
	result.m[2][3] = 0.0f;


	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;
	result.m[3][3] = 1.0f;


	return result;
}


Vector3 Transform(const Vector3 vector, const Matrix4x4 matrix) {
	Vector3 result = {};

	result.x = (vector.x * matrix.m[0][0]) + (vector.y * matrix.m[1][0]) + (vector.z * matrix.m[2][0]) + (1.0f * matrix.m[3][0]);
	result.y = (vector.x * matrix.m[0][1]) + (vector.y * matrix.m[1][1]) + (vector.z * matrix.m[2][1]) + (1.0f * matrix.m[3][1]);
	result.z = (vector.x * matrix.m[0][2]) + (vector.y * matrix.m[1][2]) + (vector.z * matrix.m[2][2]) + (1.0f * matrix.m[3][2]);

	float w = (vector.x * matrix.m[0][3]) + (vector.y * matrix.m[1][3]) + (vector.z * matrix.m[2][3]) + (1.0f * matrix.m[3][3]);


	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;

	return result;


}


//AffineMatrix
Matrix4x4 MakeAffineMatrix(const Vector3 scale, const Vector3 rotate, const Vector3 translate) {
	Matrix4x4 result;

	//S
	Matrix4x4 scaleMatrix;
	scaleMatrix = MakeScaleMatrix(scale);

	//R
	Matrix4x4 rotateMatrix;
	rotateMatrix = MakeRotateXYZMatrix(rotate.x, rotate.y, rotate.z);

	Matrix4x4 translateMatrix;
	translateMatrix = MakeTranslateMatrix(translate);


	result = Multiply(scaleMatrix, Multiply(rotateMatrix, translateMatrix));

	return result;
}

//ビュー行列
Matrix4x4 Inverse(const Matrix4x4 m) {
	float MatrixFormula;
	MatrixFormula =
		+(m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3])
		+ (m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1])
		+ (m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2])

		- (m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1])
		- (m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3])
		- (m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2])

		- (m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3])
		- (m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1])
		- (m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2])

		+ (m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1])
		+ (m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3])
		+ (m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2])

		+ (m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3])
		+ (m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1])
		+ (m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2])


		- (m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1])
		- (m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3])
		- (m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2])

		- (m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0])
		- (m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0])
		- (m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0])

		+ (m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0])
		+ (m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0])
		+ (m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0]);

	Matrix4x4 result = {};



	result.m[0][0] = (1 / MatrixFormula) * (
		+(m.m[1][1] * m.m[2][2] * m.m[3][3])
		+ (m.m[1][2] * m.m[2][3] * m.m[3][1])
		+ (m.m[1][3] * m.m[2][1] * m.m[3][2])
		- (m.m[1][3] * m.m[2][2] * m.m[3][1])
		- (m.m[1][2] * m.m[2][1] * m.m[3][3])
		- (m.m[1][1] * m.m[2][3] * m.m[3][2]));

	result.m[0][1] = (1 / MatrixFormula) * (
		-(m.m[0][2] * m.m[2][3] * m.m[3][3])
		- (m.m[0][2] * m.m[2][3] * m.m[3][1])
		- (m.m[0][3] * m.m[2][1] * m.m[3][2])
		+ (m.m[0][3] * m.m[2][2] * m.m[0][2])
		+ (m.m[0][2] * m.m[2][1] * m.m[3][3])
		+ (m.m[0][1] * m.m[2][3] * m.m[3][2]));


	result.m[0][2] = (1 / MatrixFormula) * (
		+(m.m[0][1] * m.m[1][2] * m.m[3][3])
		+ (m.m[0][2] * m.m[1][3] * m.m[3][1])
		+ (m.m[0][3] * m.m[1][1] * m.m[3][2])
		- (m.m[0][3] * m.m[1][2] * m.m[3][1])
		- (m.m[0][2] * m.m[1][1] * m.m[3][3])
		- (m.m[0][1] * m.m[1][3] * m.m[3][2]));

	result.m[0][3] = (1 / MatrixFormula) * (
		-(m.m[0][1] * m.m[1][2] * m.m[2][3])
		- (m.m[0][2] * m.m[1][3] * m.m[2][1])
		- (m.m[0][3] * m.m[1][1] * m.m[2][2])
		+ (m.m[0][3] * m.m[1][2] * m.m[2][1])
		+ (m.m[0][2] * m.m[1][1] * m.m[2][3])
		+ (m.m[0][1] * m.m[1][3] * m.m[2][2]));



	result.m[1][0] = (1 / MatrixFormula) * (
		-(m.m[1][0] * m.m[2][2] * m.m[3][3])
		- (m.m[1][2] * m.m[2][3] * m.m[3][0])
		- (m.m[1][3] * m.m[2][0] * m.m[3][2])
		+ (m.m[1][3] * m.m[2][2] * m.m[3][0])
		+ (m.m[1][2] * m.m[2][0] * m.m[3][3])
		+ (m.m[1][0] * m.m[2][3] * m.m[3][2]));

	result.m[1][1] = (1 / MatrixFormula) * (
		+(m.m[0][0] * m.m[2][2] * m.m[3][3])
		+ (m.m[0][2] * m.m[2][3] * m.m[3][0])
		+ (m.m[0][3] * m.m[2][0] * m.m[3][2])
		- (m.m[0][3] * m.m[2][2] * m.m[3][0])
		- (m.m[0][2] * m.m[2][0] * m.m[3][3])
		- (m.m[0][0] * m.m[2][3] * m.m[3][2]));

	result.m[1][2] = (1 / MatrixFormula) * (
		-(m.m[0][0] * m.m[1][2] * m.m[3][3])
		- (m.m[0][2] * m.m[1][3] * m.m[3][0])
		- (m.m[0][3] * m.m[1][0] * m.m[3][2])
		+ (m.m[0][3] * m.m[1][2] * m.m[3][0])
		+ (m.m[0][2] * m.m[1][0] * m.m[3][3])
		+ (m.m[0][0] * m.m[1][3] * m.m[3][2]));

	result.m[1][3] = (1 / MatrixFormula) * (
		+(m.m[0][0] * m.m[1][2] * m.m[2][3])
		+ (m.m[0][2] * m.m[1][3] * m.m[2][0])
		+ (m.m[0][3] * m.m[1][0] * m.m[2][2])
		- (m.m[0][3] * m.m[1][2] * m.m[2][0])
		- (m.m[0][2] * m.m[1][0] * m.m[2][3])
		- (m.m[0][0] * m.m[1][3] * m.m[2][2]));



	result.m[2][0] = (1 / MatrixFormula) * (
		+(m.m[1][0] * m.m[2][1] * m.m[3][3])
		+ (m.m[1][1] * m.m[2][3] * m.m[3][0])
		+ (m.m[1][3] * m.m[2][0] * m.m[3][1])
		- (m.m[1][3] * m.m[2][1] * m.m[3][0])
		- (m.m[1][1] * m.m[2][0] * m.m[3][3])
		- (m.m[1][0] * m.m[2][3] * m.m[3][1]));

	result.m[2][1] = (1 / MatrixFormula) * (
		-(m.m[0][0] * m.m[2][1] * m.m[3][3])
		- (m.m[0][1] * m.m[2][3] * m.m[3][0])
		- (m.m[0][3] * m.m[2][0] * m.m[3][1])
		+ (m.m[0][3] * m.m[2][1] * m.m[3][0])
		+ (m.m[0][1] * m.m[2][0] * m.m[3][3])
		+ (m.m[0][0] * m.m[2][3] * m.m[3][1]));

	result.m[2][2] = (1 / MatrixFormula) * (
		+(m.m[0][0] * m.m[1][1] * m.m[3][3])
		+ (m.m[0][1] * m.m[1][3] * m.m[3][0])
		+ (m.m[0][3] * m.m[1][0] * m.m[3][1])
		- (m.m[0][3] * m.m[1][1] * m.m[3][0])
		- (m.m[0][1] * m.m[1][0] * m.m[3][3])
		- (m.m[0][0] * m.m[1][3] * m.m[3][1]));

	result.m[2][3] = (1 / MatrixFormula) * (
		-(m.m[0][0] * m.m[1][1] * m.m[2][3])
		- (m.m[0][1] * m.m[1][3] * m.m[2][0])
		- (m.m[0][3] * m.m[1][0] * m.m[2][1])
		+ (m.m[0][3] * m.m[1][1] * m.m[2][0])
		+ (m.m[0][1] * m.m[1][0] * m.m[2][3])
		+ (m.m[0][0] * m.m[1][3] * m.m[2][1]));


	result.m[3][0] = (1 / MatrixFormula) * (
		-(m.m[1][0] * m.m[2][1] * m.m[3][2])
		- (m.m[1][1] * m.m[2][2] * m.m[3][0])
		- (m.m[1][2] * m.m[2][0] * m.m[3][1])
		+ (m.m[1][2] * m.m[2][1] * m.m[3][0])
		+ (m.m[1][1] * m.m[2][0] * m.m[3][2])
		+ (m.m[1][0] * m.m[2][2] * m.m[3][1]));


	result.m[3][1] = (1 / MatrixFormula) * (
		+(m.m[0][0] * m.m[2][1] * m.m[3][2])
		+ (m.m[0][1] * m.m[2][2] * m.m[3][0])
		+ (m.m[0][2] * m.m[2][0] * m.m[3][1])
		- (m.m[0][2] * m.m[2][1] * m.m[3][0])
		- (m.m[0][1] * m.m[2][0] * m.m[3][2])
		- (m.m[0][0] * m.m[2][2] * m.m[3][1]));

	result.m[3][2] = (1 / MatrixFormula) * (
		-(m.m[0][0] * m.m[1][1] * m.m[3][2])
		- (m.m[0][1] * m.m[1][2] * m.m[3][0])
		- (m.m[0][2] * m.m[1][0] * m.m[3][1])
		+ (m.m[0][2] * m.m[1][1] * m.m[3][0])
		+ (m.m[0][1] * m.m[1][0] * m.m[3][2])
		+ (m.m[0][0] * m.m[1][2] * m.m[3][1]));

	result.m[3][3] = (1 / MatrixFormula) * (
		+(m.m[0][0] * m.m[1][1] * m.m[2][2])
		+ (m.m[0][1] * m.m[1][2] * m.m[2][0])
		+ (m.m[0][2] * m.m[1][0] * m.m[2][1])
		- (m.m[0][2] * m.m[1][1] * m.m[2][0])
		- (m.m[0][1] * m.m[1][0] * m.m[2][2])
		- (m.m[0][0] * m.m[1][2] * m.m[2][1]));


	return result;
}

Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float neaCrlip, float farClip) {
	Matrix4x4 result = {};
	result.m[0][0] = 2.0f /( right - left);
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;

	result.m[1][0] = 0;
	result.m[1][1] = 2.0f /( top - bottom);
	result.m[1][2] = 0;
	result.m[1][3] = 0;

	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = (1 / farClip - neaCrlip);
	result.m[2][3] = 0;

	result.m[3][0] = (left + right) / (left - right);
	result.m[3][1] = (top + bottom) / (bottom - top);
	result.m[3][2] = neaCrlip / (neaCrlip - farClip);
	result.m[3][3] = 1;

	return result;
}

float Cot(float theta) {
	return (1.0f / tan(theta));
}

float Dot(Vector3 V1, Vector3 V2) {
	return V1.x * V2.x + V1.y * V2.y;
}

Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip) {
	Matrix4x4 result = {};
	float theta = fovY / 2.0f;

	result.m[0][0] = (1.0f / aspectRatio) * Cot(theta);
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;

	result.m[1][0] = 0;
	result.m[1][1] = Cot(theta);
	result.m[1][2] = 0;
	result.m[1][3] = 0;

	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = farClip/ (farClip- nearClip);
	result.m[2][3] = 1;

	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = ( - nearClip * farClip) / (farClip - nearClip);
	result.m[3][3] = 0;

	return result;
}

Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth) {
	Matrix4x4 result = {};
	result.m[0][0] = width / 2;
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;

	result.m[1][0] = 0;
	result.m[1][1] = -(height / 2);
	result.m[1][2] = 0;
	result.m[1][3] = 0;

	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = maxDepth - minDepth;
	result.m[2][3] = 0;

	result.m[3][0] = left + (width / 2);
	result.m[3][1] = top + (height / 2);
	result.m[3][2] = minDepth;
	result.m[3][3] = 1;

	return result;
}

//ベクトルの回転
Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m) {
	Vector3 result{
	    v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0],
	    v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1],
	    v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2],
	};
	return result;
}

float Length(const Vector3 v) {
	float result;
	result = sqrtf(v.x*v.x+ v.y* v.y + v.z * v.z);
	return result;
}

Vector3 NormalizeVector3(const Vector3& v1) { 
	Vector3 result = {};
	
	float length = Length(v1);

	result.x = v1.x;
	result.y = v1.y;
	result.z = v1.z;


	if (length != 0.0f) {
		result.x = v1.x / length;
		result.y = v1.y / length;
		result.z = v1.z / length;


	}

	return result;


}

//線形補間
Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t) { 
	Vector3 result = {};

	//高校の時にやったない分するベクトルから求める
	//P=s*v1+t*v2
	//	   t+s	
	//t+s=1→s=1-t


	//result.x = (1.0f - t) * v1.x + t * v2.x;
	//result.y = (1.0f - t) * v1.y + t * v2.y;
	//result.z = (1.0f - t) * v1.z + t * v2.z;

	//さらに変形するとこうなる
	//個人的には上の方が好き
	result.x = v1.x + t * (v2.x-v1.x);
	result.y = v1.y + t * (v2.y-v1.y);
	result.z = v1.z + t * (v2.z-v1.z);


	

	return result;

}

//球面線形補間
Vector3 Slerp(const Vector3& v1, const Vector3& v2, float t) {
	
          
	//            |
	//     sin(θ)|----Start
	//            |
	//sin(θ(1-t))|- - - - - -t
	//            |
	//            |
	//            |-----------End---

	//Start側
	//sinθ:sin(θ(1-t))=1:Ps(t)
	//Ps(t)=sin(θ(1-t))
	//		sin(θ)





	//        |
	// sin(θ)|----End
	//        |
	//sin(θt)|- - - - - -t
	//        |
	//        |
	//        |-----------Start---

	//End側
	//sinθ:sin(θt)=1:Pe(t)
	//Pe(t)=sin(θt)
	//	    sin(θ)

	//線形補間の位置Iは
	//I=Ps(t)*S+Pe(t)*E

	Vector3 result = {};

	Vector3 NormalizeLengthV1 = NormalizeVector3(v1);
	Vector3 NormalizeLengthV2 = NormalizeVector3(v2);

	//角度を求めたい
	float angle=std::acos(Dot(NormalizeLengthV1,NormalizeLengthV2));
	
	float sinThetaT = std::sinf(angle);

	float ps = std::sinf(angle*(1-t));
	float pe = std::sinf(angle*t);

	result = {
		(ps * NormalizeLengthV1.x + pe * NormalizeLengthV2.x) / sinThetaT,
		(ps * NormalizeLengthV1.x + pe * NormalizeLengthV2.x) / sinThetaT,
		(ps * NormalizeLengthV1.x + pe * NormalizeLengthV2.x) / sinThetaT	
	};

	return result;

}
