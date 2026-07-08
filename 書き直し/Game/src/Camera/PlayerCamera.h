#pragma once
#include<DxLib.h>

class PlayCamera {
private:
	VECTOR m_camPos;      // 視点
	VECTOR m_camRot;
	VECTOR m_targetPos;   // 注視点
	VECTOR m_UpVec;       // カメラの上方向

	float wariaiX, wariaiY;
	float sabunX, sabunY;
	int mouseXn;
	int mouseYn;
	float moveX, moveY;



public:
	// コンストラクタ
	PlayCamera();

	// 初期化
	void Init();
	// ニアーファー設定
	void SetNearFar(float n, float f);

	// カメラの座標計算
	// @forcus : プレイヤーの座標
	//@rotY    : プレイヤーの角度
	void Step(VECTOR forcus, float rotY);


	void Draw();
	// カメラの更新
	void Update();


	VECTOR GetRot() { return m_camRot; }
	VECTOR GetPos() { return m_camPos; }

};