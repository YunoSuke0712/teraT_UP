#pragma once
#include<DxLib.h>
#include <cmath>
#include "../Player/Player.h"
#include "../lib/Input/input.h"
#include "../lib/MyMath/MyMath.h"
#include "../Effect/effekseer.h"

static const int OriMaxNum = 2;

class Ori {
private:
	CInput m_input;

	bool	m_isActive[OriMaxNum];			//生存フラグ
	int		m_hndl[OriMaxNum];				//ハンドル
	VECTOR	m_Pos[OriMaxNum];				//位置
	float	m_radius[OriMaxNum];           // 半径	
	float   m_rotationY[OriMaxNum];		//常に回転させるためだけ

	int		m_OriID;			//ID

	//
	VECTOR m_InitPos;
	bool m_OriActive;
	//


public:
	// コンストラクタ・デストラクタ
	Ori();
	~Ori();

	// 初期化
	void Init();
	// モデルデータのロード
	void Load(int Ahndl,int Bhnd);
	// 終了時のデータ破棄など
	void Exit();

	// 全行動を処理する
	void Step(Player& player, CEffekseerCtrl& effect);
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

	//おりの状態を指定
	void SetOriActive(bool active) { m_OriActive = active; }

	//ID
	void SetID(int id) { m_OriID = id; }
	//座標取得
	VECTOR GetOriPos(VECTOR pos) { return GetCenterB(); }
	void GetInitPosA(VECTOR pos) { m_InitPos = pos; }


	bool GetIsActive()
	{
		return m_isActive[0];
	}

	int GetHndl()
	{
		return m_hndl[0];
	}



};