#ifndef _MYMATH_H_
#define _MYMATH_H_

#include "DxLib.h"


//////ベクトルや行列の計算処理をまとめたクラス
////VECTOR VecCreate(VECTOR PosA, VECTOR PosB);//ベクトル作成
////float VecLong(VECTOR PosA, VECTOR PosB);//ベクトルの長さ
VECTOR VecAdd(VECTOR vecA, VECTOR vecB);//ベクトルの足し算
VECTOR VecSubtract(VECTOR vecA, VECTOR vecB);//ベクトルの引き算
VECTOR VecDivisiontract(VECTOR vecA, VECTOR vecB);//ベクトルの割り算
////VECTOR VecScale(VECTOR vec, float scale);//ベクトルのスカラー倍
////float VecDot(VECTOR vecA, VECTOR vecB);//ベクトルの内積
////VECTOR VecCross(VECTOR vecA, VECTOR vecB);//ベクトルの外積
////VECTOR VecNormalize(VECTOR vec);//ベクトルの正規化
////void Matldentity(MATRIX *mp);//単位行列の取得
////MATRIX MatAdd(MATRIX matA, MATRIX matB);//行列の足し算
////MATRIX MyMatMult(MATRIX matA, MATRIX matB);//行列の掛け算
////MATRIX MatScale(MATRIX mat, float scale);//行列のスカラー倍
////VECTOR Transform(MATRIX mat, VECTOR vec);//ベクトル×行列
////float GetAngleY(VECTOR vec1, VECTOR vec2);//角度を取得(Y軸)
////float GetAngleX(VECTOR vec1, VECTOR vec2);//角度を取得(X軸)
////float GetAngleZ(VECTOR vec1, VECTOR vec2);//角度を取得(Z軸)
////float MyAbsf(float i_fNum);//絶対値の取得

MATRIX GetIdentityMatrix();//単位行列取得　斜めに１
MATRIX GetTranslateMatrix(VECTOR heikouidougyouretu);//↑のやつ引き継いで平行移動行列　右端xyz1
MATRIX GetTranslateMatrix_float(float x,float y ,float z);//↑のやつ引き継いで平行移動行列　右端xyz1
MATRIX GetScaleMatrix(VECTOR sukeeeruchi);//スケール値　ななめxyz1
MATRIX GetPitchMatrix(float raziann);// 回転　ラジアン値をcosf,sinfにぶち込み　X軸回転
MATRIX GetYawMatrix(float raziann);//回転　ラジアン値をcosf,sinfにぶち込み　Y軸回転
MATRIX GetRollMatrix(float rasiann);//回転　ラジアン値をcosf,sinfにぶち込み　Z軸回転
MATRIX MatAdd(MATRIX add1, MATRIX add2);//行列同士の足し算する奴ら
MATRIX MatSub(MATRIX sub1, MATRIX sub2);//行列同士の引き算する奴ら
MATRIX MatScale(MATRIX gyouretu, float scale);//行列のスカラー倍
MATRIX MatMult(MATRIX Mult1, MATRIX Mult2);//行列同士の掛け算
VECTOR MatTransform(MATRIX mat, VECTOR vec);//行列とVECTORの掛け算
MATRIX MatTranspose(MATRIX mat);//行列転置


//自作＝＝

float DegToRad(float deg);   // 度 → ラジアン変換
//使用例　
// DegToRad(30.0f);	ラジアンを度指定で出来る
//m_rot = DegToRad(30.0f) 　で30度のラジアン値が入る

float RadToDeg(float rad);	//ラジアン→度変換
//使用例
// 度＝DegToRad(ラジアン)　になっているため
// m_Rot.y =ラジアン値													↓
//drawFormatString(10,10,GetColor(0,0,0), 　"m_rotY:%.1f 度",　　RedToDeg(m_Rot.y)　　)
//のようにすると度で表示できる
//
float CosDeg(float cos);

float SinDeg(float sin);

#endif