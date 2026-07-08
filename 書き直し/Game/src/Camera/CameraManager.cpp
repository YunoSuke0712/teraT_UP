#include"CameraManager.h"





//----------------------
// コンストラクタ
//----------------------
CameraManager::CameraManager()
{
	// 初期カメラはプレイカメラ
	m_id = ID_PLAY;
}

//----------------------
// 初期化
//----------------------
void CameraManager::Init()
{
	// それぞれのカメラを初期化
	m_Play.Init();
	m_debug.Init();
	m_event.Init();

	m_NowEvent = false;

	SetCameraNearFar(Near, Far);
}

//----------------------
// カメラの座標計算
//----------------------
void CameraManager::Step(VECTOR forcus, float rotY)
{
	//if (CheckHitKey(KEY_INPUT_C))
	//{
	//	m_id = ID_DEBUG;
	//}
	if (CheckHitKey(KEY_INPUT_1))
	{
		m_id = ID_PLAY;
	}
	if (CheckHitKey(KEY_INPUT_2))
	{
		m_id = ID_DEBUG;
	}
	if (CheckHitKey(KEY_INPUT_3))
	{
		m_NowEvent = ID_EVENT;
	}

	//if (button == true)
	//{
	//	SetEventID(EVENT_BUTTON);		
	//}

	if (m_NowEvent == true)//EVENTになりつづけている
	{
		m_id = ID_EVENT;
	}
	else
	{
		m_id = ID_PLAY;
	}

	switch (m_id)
	{
	// ゲーム中のメインカメラ
	case ID_PLAY:
		m_Play.Step(forcus, rotY);
		m_event.Step();
		break;
	// デバッグ用のカメラ
	case ID_DEBUG:
		m_debug.Step();
		break;
		// デバッグ用のカメラ
	case ID_EVENT:
		m_event.Step();
		break;
	}
}

//----------------------
//	カメラの更新
//----------------------
void CameraManager::Update()
{
	switch (m_id)
	{
		// ゲーム中のメインカメラ
	case ID_PLAY:
		m_Play.Update();
		break;
		// デバッグ用のカメラ
	case ID_DEBUG:
		m_debug.Update();
		break;
	case ID_EVENT:
		m_event.Update();
		break;
	}

}

void CameraManager::Draw()
{
	m_Play.Draw();
	m_event.Draw();
}

VECTOR CameraManager::GetForward()
{
	VECTOR camPos = GetCameraPosition();
	VECTOR camTarget = GetCameraTarget();

	// カメラ → 注視点 の方向
	VECTOR forward = VSub(camTarget, camPos);

	// 正規化（長さ1にする）
	forward = VNorm(forward);

	return forward;
}