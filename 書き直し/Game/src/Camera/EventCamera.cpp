#include"EventCamera.h"
#include"../lib/Common/common.h"
#include<math.h>

static const float ROT_SPEED = 0.1f;   // カメラの回転速度
static const float MOVE_SPEED = 1.0f;

//----------------------
// コンストラクタ
//----------------------
EventCamera::EventCamera()
{
	m_Pos = ZERO;
	m_Rot = ZERO;

	m_EvStartPos =	ZERO;
	m_EvEndPos   =	ZERO;
	m_EvStartRot =	ZERO;
	m_EvEndRot   =	ZERO;
}

//----------------------
// 初期化
//----------------------
void EventCamera::Init()
{
	m_Pos = ZERO;
	m_Rot = ZERO;

	moveX = 0;
	moveY = 0;
	mouseXn = (1280 / 2);
	mouseYn = (720 / 2);

	m_id = 0;
	m_count = 0;
	m_inEvent = false;

	m_EvStartPos = ZERO;
	m_EvEndPos = ZERO;
	m_EvStartRot = ZERO;
	m_EvEndRot = ZERO;
}

//------------------------
// カメラの座標計算
//------------------------
void EventCamera::Step()
{
	// カメラの回転処理========================
	// 上下回転

	//GetMousePoint(&mouseXn, &mouseYn);
	////横回転
	//sabunX = mouseXn - (WINDOW_SIZE_X /2);
	//wariaiX = 1.0 / (WINDOW_SIZE_X/2);
	//moveX = 2.0943951024 * wariaiX * sabunX;//640どっとで180度回転
	//m_Rot.y+=moveX;//Y軸
	////縦回転
	//sabunY = mouseYn - (WINDOW_SIZE_Y / 2);
	//wariaiY = 1.0 / (WINDOW_SIZE_Y/2);
	//moveY = 1.745329252 * wariaiY * sabunY;//640どっとで180度回転
	//m_Rot.x += moveY;//X軸

	
	// カメラの移動処理========================
	// 前進
	//if (CheckHitKey(KEY_INPUT_W))
	//{
	//	// カメラの角度がオール0度の時に進む速度
	//	VECTOR defaultDir = { 0.0f,0.0f,MOVE_SPEED };
	//	// 上記を行列に変換
	//	MATRIX dir = MGetTranslate(defaultDir);
	//	// X軸回転行列
	//	MATRIX rotX = MGetRotX(m_Rot.x);
	//	// Y軸回転行列
	//	MATRIX rotY = MGetRotY(m_Rot.y);
	//	// 各行列を合成していく
	//	MATRIX res = MMult(dir, rotX);
	//	res = MMult(res, rotY);

	//	// 行列から移動情報だけを取り出す
	//	VECTOR move;
	//	move.x = res.m[3][0];
	//	move.y = res.m[3][1];
	//	move.z = res.m[3][2];
	//	// 計算結果をカメラの現在の座標に足す
	//	m_Pos = VAdd(m_Pos, move);

	//	//=========================================
	//}
	//if (CheckHitKey(KEY_INPUT_A))
	//{
	//	// カメラの角度がオール0度の時に進む速度
	//	VECTOR defaultDir = { -MOVE_SPEED,0.0f,0.0f };
	//	// 上記を行列に変換
	//	MATRIX dir = MGetTranslate(defaultDir);
	//	// X軸回転行列
	//	MATRIX rotX = MGetRotX(m_Rot.x);
	//	// Y軸回転行列
	//	MATRIX rotY = MGetRotY(m_Rot.y);
	//	// 各行列を合成していく
	//	MATRIX res = MMult(dir, rotX);
	//	res = MMult(res, rotY);

	//	// 行列から移動情報だけを取り出す
	//	VECTOR move;
	//	move.x = res.m[3][0];
	//	move.y = res.m[3][1];
	//	move.z = res.m[3][2];
	//	// 計算結果をカメラの現在の座標に足す
	//	m_Pos = VAdd(m_Pos, move);

	//	//=========================================
	//}
	//if (CheckHitKey(KEY_INPUT_S))
	//{
	//	// カメラの角度がオール0度の時に進む速度
	//	VECTOR defaultDir = { 0.0f,0.0f,-MOVE_SPEED };
	//	// 上記を行列に変換
	//	MATRIX dir = MGetTranslate(defaultDir);
	//	// X軸回転行列
	//	MATRIX rotX = MGetRotX(m_Rot.x);
	//	// Y軸回転行列
	//	MATRIX rotY = MGetRotY(m_Rot.y);
	//	// 各行列を合成していく
	//	MATRIX res = MMult(dir, rotX);
	//	res = MMult(res, rotY);

	//	// 行列から移動情報だけを取り出す
	//	VECTOR move;
	//	move.x = res.m[3][0];
	//	move.y = res.m[3][1];
	//	move.z = res.m[3][2];
	//	// 計算結果をカメラの現在の座標に足す
	//	m_Pos = VAdd(m_Pos, move);

	//	//=========================================
	//}
	//if (CheckHitKey(KEY_INPUT_D))
	//{
	//	// カメラの角度がオール0度の時に進む速度
	//	VECTOR defaultDir = { MOVE_SPEED,0.0f,0.0f };
	//	// 上記を行列に変換
	//	MATRIX dir = MGetTranslate(defaultDir);
	//	// X軸回転行列
	//	MATRIX rotX = MGetRotX(m_Rot.x);
	//	// Y軸回転行列
	//	MATRIX rotY = MGetRotY(m_Rot.y);
	//	// 各行列を合成していく
	//	MATRIX res = MMult(dir, rotX);
	//	res = MMult(res, rotY);

	//	// 行列から移動情報だけを取り出す
	//	VECTOR move;
	//	move.x = res.m[3][0];
	//	move.y = res.m[3][1];
	//	move.z = res.m[3][2];
	//	// 計算結果をカメラの現在の座標に足す
	//	m_Pos = VAdd(m_Pos, move);

	//	//=========================================
	//}

	if (m_inEvent == true)
	{
		//一周だけ
		m_inEvent = false;
		switch (m_id)
		{
		case EVENT_NOT:
			m_count = -1;
			m_id = EVENT_NOT;
			break;

		case EVENT_KEY:
			m_count = m_FastTime =180;
			m_Pos ={ 330.0f,83.0f,292.0f };
			m_Rot = { DegToRad(14.6),DegToRad(-10.8),ZERO.z};

			m_EvStartPos = { m_Pos };
			m_EvEndPos = { 336.0f,96.0f,246.0f };
			m_EvStartRot = { m_Rot };
			m_EvEndRot = { DegToRad(14.6),DegToRad(-10.8),ZERO.z };
			break;

		case EVENT_BUTTON:
			m_count = m_FastTime = 180;
			m_Pos = { 222.0f,133.0f,192.0f };
			m_Rot = { DegToRad(25.8),DegToRad(290.3),ZERO.z };

			m_EvStartPos = { m_Pos };
			m_EvEndPos = { m_Pos };
			m_EvStartRot = { m_Rot };
			m_EvEndRot = { m_Rot };
			break;
		}
	}

	if (m_count > 0)
	{
		switch (m_id)
		{
		case EVENT_KEY:
			m_Pos = VecAdd(m_Pos, Pos_Start_End());
			m_Rot = VecAdd(m_Rot, Rot_Start_End());
			
			if(m_count == 120)
			
			break;

		case EVENT_BUTTON:
			m_Pos = VecAdd(m_Pos, Pos_Start_End());
			m_Rot = VecAdd(m_Rot, Rot_Start_End());

			if (m_count == 120)
			break;
		}


		m_count--;
		if(m_count <= 0)
		m_id = EVENT_NOT;
	}



	SetMousePoint(WINDOW_SIZE_X /2, WINDOW_SIZE_Y / 2);
}

//------------------------
// カメラの更新
//------------------------
void EventCamera::Update()
{
	SetCameraPositionAndAngle(m_Pos, m_Rot.x, m_Rot.y,m_Rot.z);

}

//------------------------
// カメラの更新
//------------------------
void EventCamera::Draw()
{
////プレイヤーの位置
//DrawFormatString(1200, 450, GetColor(25, 200, 200), "EVCposX:%f", m_Pos.x);
//DrawFormatString(1200, 500, GetColor(25, 200, 200), "EVCposY:%f", m_Pos.y);
//DrawFormatString(1200, 550, GetColor(25, 200, 200), "EVCposZ:%f", m_Pos.z);
//
//DrawFormatString(1200, 600, GetColor(25, 200, 200), "x%.1f;y%.1f;z%.1f;", RadToDeg(m_Rot.x), RadToDeg(m_Rot.y), RadToDeg(m_Rot.z));

//DrawFormatString(1000, 600, GetColor(25, 200, 200), "EVCrot XYZ:%f,%f,%f", 
//	RadToDeg(m_Rot.x),RadToDeg(m_Rot.y), RadToDeg(m_Rot.z));

}

VECTOR EventCamera::Pos_Start_End()
{

	VECTOR E_S = VecSubtract(m_EvEndPos, m_EvStartPos);	//EからSまでの距離
	VECTOR FRAME = { m_FastTime,m_FastTime,m_FastTime };							//演算する時間
	VECTOR move = VecDivisiontract(E_S, FRAME);			//1フレの移動距離
	return move;

}

VECTOR EventCamera::Rot_Start_End()
{

	VECTOR E_S = VecSubtract(m_EvEndRot, m_EvStartRot);	//EからSまでの距離
	VECTOR FRAME = { m_FastTime,m_FastTime,m_FastTime };							//演算する時間
	VECTOR move = VecDivisiontract(E_S, FRAME);			//1フレの移動距離
	return move;

}