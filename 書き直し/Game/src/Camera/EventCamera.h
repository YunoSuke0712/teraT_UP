#pragma once
#include<DxLib.h>
#include "../lib/MyMath/MyMath.h"


class EventCamera {
private:
	VECTOR m_Pos;      // カメラの視点
	VECTOR m_Rot;      // カメラの回転角度
	VECTOR m_mouse_fix;

	float wariaiX, wariaiY;
	float sabunX, sabunY;
	int mouseXn,mouseYn;
	float moveX, moveY;

	//イベント管理
	int m_id;		//イベントID
	int m_count;	//経過時間
	int m_FastTime; //設定時間
	bool m_inEvent;	//イベント開始時一回だけ

	//イベント中のカメラ位置用
	VECTOR m_EvStartPos;
	VECTOR m_EvEndPos;
	VECTOR m_EvStartRot;
	VECTOR m_EvEndRot;



public:
	// コンストラクタ
	EventCamera();

	// 初期化
	void Init();

	// カメラの座標計算
	void Step();

	// カメラの更新
	void Update();

	//イベントID
	void SetEventID(int id) 
	{
		m_id = id; 
		m_inEvent = true;	
	}



	//ドr－
	void Draw();

	VECTOR Pos_Start_End();

	VECTOR Rot_Start_End();





};