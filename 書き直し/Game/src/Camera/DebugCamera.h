#pragma once
#include<DxLib.h>

class DebugCamera {
private:
	VECTOR m_Pos;      // カメラの視点
	VECTOR m_Rot;      // カメラの回転角度
	VECTOR m_mouse_fix;

	float wariaiX, wariaiY;
	float sabunX, sabunY;
	int mouseXn,mouseYn;
	float moveX, moveY;

public:
	// コンストラクタ
	DebugCamera();

	// 初期化
	void Init();

	// カメラの座標計算
	void Step();

	// カメラの更新
	void Update();
};