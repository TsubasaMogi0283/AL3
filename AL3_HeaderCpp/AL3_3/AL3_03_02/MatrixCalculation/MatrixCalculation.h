#pragma once

#include <Matrix4x4.h>
#include <Vector3.h>

#include <cassert>
#define _USE_MATH_DEFINES
#include <cmath>
#include  <math.h>


//Scale
Matrix4x4 MakeScaleMatrix(const Vector3 scale);

//Rotate
Matrix4x4 MakeRotateXMatrix(float radian);

Matrix4x4 MakeRotateYMatrix(float radian);

Matrix4x4 MakeRotateZMatrix(float radian);

//AllRotate
Matrix4x4 MakeRotateXYZMatrix(float radianX, float radianY, float radianZ);

Matrix4x4 Multiply(const Matrix4x4 m1, const Matrix4x4 m2);

//Translate
Matrix4x4 MakeTranslateMatrix(Vector3 translate);

//Transform
Vector3 Transform(const Vector3 vector, const Matrix4x4 matrix);

Matrix4x4 Inverse(const Matrix4x4 m);

//AffineMatrix
Matrix4x4 MakeAffineMatrix(const Vector3 scale, const Vector3 rotate, const Vector3 translate);
