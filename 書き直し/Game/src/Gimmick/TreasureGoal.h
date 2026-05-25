#pragma once
#include<DxLib.h>
#include <cmath>
#include "../Player/Player.h"
#include "../lib/Input/input.h"
#include "../lib/MyMath/MyMath.h"
#include"../lib/common/common.h"



static const int TreasureGoalMaxNum = 2;

class TreasureGoal {
private:
	CInput m_input;

	bool	m_isActive[TreasureGoalMaxNum];			//生存フラグ
	int		m_hndl[TreasureGoalMaxNum];				//ハンドル
	VECTOR	m_Pos[TreasureGoalMaxNum];				//位置
	float	m_radius[TreasureGoalMaxNum];           // 半径	
	float   m_rotationY[TreasureGoalMaxNum];		//常に回転させるためだけ

	int		m_TreasureGoalID;			//ID

	//
	//


public:
	// コンストラクタ・デストラクタ
	TreasureGoal();
	~TreasureGoal();

	// 初期化
	void Init();
	// モデルデータのロード
	void Load(int Ahndl, int Bhnd);
	// 終了時のデータ破棄など
	void Exit();

	// 全行動を処理する
	void Step(Player& player);
	// 更新処理
	// すべての行動が終わったらDxLibに情報を渡す
	void Update();
	// 描画処理
	void Draw();

	bool Request(const VECTOR& pos);



	// 座標取得
	VECTOR GetPositionA() { return m_Pos[0]; }
	VECTOR GetPositionB() { return m_Pos[1]; }

	VECTOR GetCenterA();
	VECTOR GetCenterB();

	//// 座標を指定
	void SetPositionA(VECTOR POSA) { m_Pos[0] = POSA; }
	void SetPositionB(VECTOR POSB) { m_Pos[1] = POSB; }
	//角度を指定
	void SetRotationA(float rot_y) { m_rotationY[0] = DegToRad(rot_y); }
	void SetRotationB(float rot_y) { m_rotationY[1] = DegToRad(rot_y); }

	//ID
	void SetID(int id) { m_TreasureGoalID = id; }
	//座標取得
	VECTOR GetTreasureGoalPos(VECTOR pos) { return GetCenterB(); }


	bool GetIsActive()
	{
		return m_isActive[0];
	}

	int GetHndl()
	{
		return m_hndl[0];
	}



};