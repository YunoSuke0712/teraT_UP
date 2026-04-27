#include"DebugCamera.h"
#include<math.h>
#include "../lib/common/common.h"

static const float ROT_SPEED = 0.1f;   // カメラの回転速度
static const float MOVE_SPEED = 1.0f;

//----------------------
// コンストラクタ
//----------------------
DebugCamera::DebugCamera()
{
	m_Pos = ZERO;
	m_Rot = ZERO;
}

//----------------------
// 初期化
//----------------------
void DebugCamera::Init()
{
	m_Pos = ZERO;
	m_Rot = ZERO;

	moveX = 0;
	moveY = 0;
	mouseXn = (1280 / 2);
	mouseYn = (720 / 2);
}

//------------------------
// カメラの座標計算
//------------------------
void DebugCamera::Step()
{
	// カメラの回転処理========================
	// 上下回転

	GetMousePoint(&mouseXn, &mouseYn);
	//横回転
	sabunX = mouseXn - (WINDOW_SIZE_X /2);
	wariaiX = 1.0 / (WINDOW_SIZE_X /2);
	moveX = 2.0943951024 * wariaiX * sabunX;//640どっとで180度回転
	m_Rot.y+=moveX;//Y軸
	//縦回転
	sabunY = mouseYn - (WINDOW_SIZE_Y / 2);
	wariaiY = 1.0 / (WINDOW_SIZE_Y/2);
	moveY = 1.745329252 * wariaiY * sabunY;//640どっとで180度回転
	m_Rot.x += moveY;//X軸

	
	// カメラの移動処理========================
	// 前進
	if (CheckHitKey(KEY_INPUT_W))
	{
		// カメラの角度がオール0度の時に進む速度
		VECTOR defaultDir = { 0.0f,0.0f,MOVE_SPEED };
		// 上記を行列に変換
		MATRIX dir = MGetTranslate(defaultDir);
		// X軸回転行列
		MATRIX rotX = MGetRotX(m_Rot.x);
		// Y軸回転行列
		MATRIX rotY = MGetRotY(m_Rot.y);
		// 各行列を合成していく
		MATRIX res = MMult(dir, rotX);
		res = MMult(res, rotY);

		// 行列から移動情報だけを取り出す
		VECTOR move;
		move.x = res.m[3][0];
		move.y = res.m[3][1];
		move.z = res.m[3][2];
		// 計算結果をカメラの現在の座標に足す
		m_Pos = VAdd(m_Pos, move);

		//=========================================
	}
	if (CheckHitKey(KEY_INPUT_A))
	{
		// カメラの角度がオール0度の時に進む速度
		VECTOR defaultDir = { -MOVE_SPEED,0.0f,0.0f };
		// 上記を行列に変換
		MATRIX dir = MGetTranslate(defaultDir);
		// X軸回転行列
		MATRIX rotX = MGetRotX(m_Rot.x);
		// Y軸回転行列
		MATRIX rotY = MGetRotY(m_Rot.y);
		// 各行列を合成していく
		MATRIX res = MMult(dir, rotX);
		res = MMult(res, rotY);

		// 行列から移動情報だけを取り出す
		VECTOR move;
		move.x = res.m[3][0];
		move.y = res.m[3][1];
		move.z = res.m[3][2];
		// 計算結果をカメラの現在の座標に足す
		m_Pos = VAdd(m_Pos, move);

		//=========================================
	}
	if (CheckHitKey(KEY_INPUT_S))
	{
		// カメラの角度がオール0度の時に進む速度
		VECTOR defaultDir = { 0.0f,0.0f,-MOVE_SPEED };
		// 上記を行列に変換
		MATRIX dir = MGetTranslate(defaultDir);
		// X軸回転行列
		MATRIX rotX = MGetRotX(m_Rot.x);
		// Y軸回転行列
		MATRIX rotY = MGetRotY(m_Rot.y);
		// 各行列を合成していく
		MATRIX res = MMult(dir, rotX);
		res = MMult(res, rotY);

		// 行列から移動情報だけを取り出す
		VECTOR move;
		move.x = res.m[3][0];
		move.y = res.m[3][1];
		move.z = res.m[3][2];
		// 計算結果をカメラの現在の座標に足す
		m_Pos = VAdd(m_Pos, move);

		//=========================================
	}
	if (CheckHitKey(KEY_INPUT_D))
	{
		// カメラの角度がオール0度の時に進む速度
		VECTOR defaultDir = { MOVE_SPEED,0.0f,0.0f };
		// 上記を行列に変換
		MATRIX dir = MGetTranslate(defaultDir);
		// X軸回転行列
		MATRIX rotX = MGetRotX(m_Rot.x);
		// Y軸回転行列
		MATRIX rotY = MGetRotY(m_Rot.y);
		// 各行列を合成していく
		MATRIX res = MMult(dir, rotX);
		res = MMult(res, rotY);

		// 行列から移動情報だけを取り出す
		VECTOR move;
		move.x = res.m[3][0];
		move.y = res.m[3][1];
		move.z = res.m[3][2];
		// 計算結果をカメラの現在の座標に足す
		m_Pos = VAdd(m_Pos, move);

		//=========================================
	}

	SetMousePoint(1280/2, 720 / 2);
}

//------------------------
// カメラの更新
//------------------------
void DebugCamera::Update()
{
	SetCameraPositionAndAngle(m_Pos, m_Rot.x, m_Rot.y,m_Rot.z);
}