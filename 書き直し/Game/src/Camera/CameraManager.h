#pragma once
#include"PlayerCamera.h"
#include"DebugCamera.h"
#include"EventCamera.h"

// 複数のカメラを管理する
class CameraManager {
public:
	// カメラのタイプ
	enum tagCAMERA_ID
	{
		ID_PLAY,    // ゲームのメインカメラ
		ID_DEBUG,   // デバッグ用のカメラ
		ID_EVENT,

		ID_NUM
	};

private:
	PlayCamera m_Play;    // メインとなるカメラ
	tagCAMERA_ID m_id;    // 今どのカメラを使っているか
	DebugCamera m_debug;
	EventCamera m_event;

	bool m_NowEvent;

public:
	// コンストラクタ
	CameraManager();

	// 初期化
	void Init();

	// カメラの座標計算
	// @forcus : プレイヤーの座標
	//@rotY    : プレイヤーの角度
	void Step(VECTOR forcus, float rotY);

	// カメラの更新
	void Update();
	void Draw();

	// カメラのタイプ切り替え
	void ChangeCamera(tagCAMERA_ID id) { m_id = id; }
	// カメラのタイプ取得
	tagCAMERA_ID GetID() { return m_id; }

	VECTOR GetForward();

	void SetEventID(int id)
	{ 
		m_event.SetEventID(id);
		m_NowEvent = true; 
	}
	void SetEventNow() { m_NowEvent = false; }
	VECTOR GetRot() { return m_Play.GetRot(); }


	//int SetEventTime(int time) { return time; }
	//bool SetEventCamera(bool event) { return event; }
};