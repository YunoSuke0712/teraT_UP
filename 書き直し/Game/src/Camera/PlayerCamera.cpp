#include"PlayerCamera.h"
#include<math.h>
#include "../lib/MyMath/MyMath.h"
#include"../lib/Common/common.h"
#include"../lib/input/PadInput.h"
//#include "../plyaer/Player.h"

// カメラとプレイヤーの距離
static const float CAMERA_LENGTH = 60.0f;
// カメラの高さ（今回は固定）
static const float CAMERA_OFFSET_Y = 15.0f;
// カメラの注視点の高さ（今回は固定）
static const float TARGET_OFFSET_Y = 15.0f;

//Player g_pl;

//----------------------
// コンストラクタ
//----------------------
PlayCamera::PlayCamera()
{
	m_camPos = ZERO;
	m_camRot = ZERO;
	m_targetPos = ZERO;
	m_UpVec = ZERO;
	
}

//----------------------
// 初期化
//----------------------
void PlayCamera::Init()
{
	m_camPos = ZERO;
	m_camRot = { 0.0f, DX_PI_F / 2 ,0.0f};
	m_targetPos = ZERO;
	m_UpVec = { 0.0f,1.0f,0.0f };
	SetMousePoint(WINDOW_SIZE_X / 2, WINDOW_SIZE_Y/ 2);
}

//----------------------
//	ニアーファー設定
//----------------------
void PlayCamera::SetNearFar(float n,float f)
{
	SetCameraNearFar(n, f);
}

//------------------------
// カメラの座標計算
//------------------------
void PlayCamera::Step(VECTOR forcus, float rotY)
{
	int MouseX, MouseY;
	MouseX = MouseY = 0;
	GetMousePoint(&MouseX, &MouseY);
	//横回転
	float x, y;
	x = y = 0.0f;
	x = (WINDOW_SIZE_X / 2)- MouseX;
	y= (WINDOW_SIZE_Y / 2) - MouseY;
	if (x <= 0)x *= -1;
	if (y <= 0)y *= -1;
	VECTOR MousePos = VGet((float)MouseX, (float)MouseY, 0.0f );

	float SpeedY = y / (WINDOW_SIZE_Y / 2);

	SpeedY *= 70;

	//
	if (MousePos.y <= WINDOW_SIZE_Y / 2) 
	{
		float Rad = (60 * DX_PI_F) / 180;//カメラの上限
		//
		if (m_camRot.x < Rad)
		{
			m_camRot.x += (SpeedY * DX_PI_F) / 180;	
		}
		else
		{
			m_camRot.x = Rad; //上限以上だったらそれ以上行かないようにする
		}
		if (m_camRot.x > 2.0f * DX_PI_F)m_camRot.x -= 2.0f;
	}

	//マウスの高さが画面の半分より大きかったら
	if (MousePos.y > WINDOW_SIZE_Y / 2)
	{
		float Rad = (-50 * DX_PI_F) / 180;//カメラの下限
		//
		if (m_camRot.x > Rad)
		{
			m_camRot.x -= (SpeedY * DX_PI_F) / 180;	
		}
		else
		{
			m_camRot.x = Rad; //上限以上だったらそれ以上行かないようにする
		}
		if (m_camRot.x < -2.0f)m_camRot.x += 2.0f;
	}

	float SpeedX = x / (WINDOW_SIZE_X / 2);
	SpeedX *= 70;

	if (MousePos.x < WINDOW_SIZE_X / 2) {
		m_camRot.y -= (SpeedX * DX_PI_F) / 180;
	}
	if (MousePos.x > WINDOW_SIZE_X / 2) {
		m_camRot.y += (SpeedX * DX_PI_F) / 180;
	}

	//VECTOR v;
	//v.x = sinf(rotY) * CAMERA_LENGTH;
	//v.y = CAMERA_OFFSET_Y;
	//v.z = cosf(rotY) * CAMERA_LENGTH;
	//m_camPos = VAdd(forcus, v);   // 視点はプレイヤー


		//PAD視野操作関連＝＝＝＝＝＝
	if (CGamePad::Stick(STICK_RX_POS) != 0)m_camRot.y += 0.04;
	if (CGamePad::Stick(STICK_RX_NEG) != 0)m_camRot.y += -0.04;

	if (CGamePad::Stick(STICK_RY_POS) != 0)m_camRot.x += -0.04;
	if (CGamePad::Stick(STICK_RY_NEG) != 0)m_camRot.x += 0.04;

	// 上下角度制限
	float maxRad = (60.0f * DX_PI_F) / 180.0f;
	float minRad = (-50.0f * DX_PI_F) / 180.0f;

	if (m_camRot.x > maxRad)
	{
		m_camRot.x = maxRad;
	}

	if (m_camRot.x < minRad)
	{
		m_camRot.x = minRad;
	}

	m_targetPos = forcus;         // 注視点はプレイヤー
	m_targetPos.y += TARGET_OFFSET_Y;


	// 注視点を原点に平行移動する行列を作成
	MATRIX OriginMove = GetTranslateMatrix_float(-forcus.x, -forcus.y + TARGET_OFFSET_Y, -forcus.z);

	//カメラを注視点より手前に移動させる平行移動行列を作成
	MATRIX OriginFront = GetTranslateMatrix_float(0.0f, TARGET_OFFSET_Y, CAMERA_LENGTH);

	//カメラのX軸回転行列を作成
	MATRIX X_Rot = GetPitchMatrix(m_camRot.x);

	//カメラのY軸回転行列を作成
	MATRIX Y_Rot = GetYawMatrix(m_camRot.y);

	// 注視点を元の位置に平行移動する行列を作成
	MATRIX OriginBack = GetTranslateMatrix_float(forcus.x, forcus.y+ TARGET_OFFSET_Y, forcus.z);

	//各行列を合成（掛け算の順番に注意！！）
	MATRIX Mix = MatMult(OriginBack, Y_Rot);
	Mix = MatMult(Mix, X_Rot);
	Mix = MatMult(Mix, OriginFront);
	Mix = MatMult(Mix, OriginMove);

	m_targetPos = VGet(forcus.x, forcus.y + TARGET_OFFSET_Y, forcus.z);

	m_camPos = MatTransform(Mix, forcus);

	
	SetMousePoint(WINDOW_SIZE_X / 2, WINDOW_SIZE_Y / 2);



}

//------------------------
// カメラの更新
//------------------------
void PlayCamera::Update()
{
	SetCameraPositionAndTargetAndUpVec(m_camPos, m_targetPos, m_UpVec);
}

void PlayCamera::Draw()
{

	//DrawFormatString(500, 590, GetColor(255, 30, 30), "kameraraX:%f",m_camPos.x);
	//DrawFormatString(500, 620, GetColor(255, 30, 30), "kameraraY:%f", m_camPos.y);
	//DrawFormatString(500, 640, GetColor(255, 30, 30), "kameraraZ:%f", m_camPos.z);


}

