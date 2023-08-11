#pragma once

#include <Matrix4x4.h>
#include <Vector3.h>


//足し算
Vector3 Add(const Vector3 v1, const Vector3 v2);

//Scale
Matrix4x4 MakeScaleMatrix(const Vector3 scale);

//Rotate
Matrix4x4 MakeRotateXMatrix(float radian);
Matrix4x4 MakeRotateYMatrix(float radian);
Matrix4x4 MakeRotateZMatrix(float radian);
//Rotate全部合わせたもの
Matrix4x4 MakeRotateXYZMatrix(float radianX, float radianY, float radianZ);


//掛け算
Matrix4x4 Multiply(const Matrix4x4 m1, const Matrix4x4 m2);

//Translate
Matrix4x4 MakeTranslateMatrix(Vector3 translate);
Vector3 Transform(const Vector3 vector, const Matrix4x4 matrix);

//AffineMatrix
Matrix4x4 MakeAffineMatrix(const Vector3 scale, const Vector3 rotate, const Vector3 translate);

//逆行列
Matrix4x4 Inverse(const Matrix4x4 m);

//投影行列
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);

//コタンジェント
float Cot(float theta);

//Projection
Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float neaClip, float farClip);

//ビューポート
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);

//ベクトルの回転
Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m);