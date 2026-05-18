#pragma once
#include<DxLib.h>
#include <cmath>
#include "../Player/Player.h"
#include "../lib/Input/input.h"


static const int WarpMaxNum = 2;

class Warp {
private:
	CInput m_input;

	bool	m_isActive[WarpMaxNum];			//生存フラグ
	int		m_hndl[WarpMaxNum];				//ハンドル
	VECTOR	m_Pos[WarpMaxNum];				//位置
	float	m_radius[WarpMaxNum];           // 半径	
	float   m_rotationY[WarpMaxNum];		//常に回転させるためだけ

	int		m_WarpID;			//ID

	bool	m_warpActive;
	

public:
	// コンストラクタ・デストラクタ
	Warp();
	~Warp();

	// 初期化
	void Init();
	// モデルデータのロード
	void Load(int Ahndl,int Bhnd);
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


	//// 生存情報取得・設定
	//bool GetIsActiveA() { return m_isActive; }
	// 座標取得
	VECTOR GetPositionA() { return m_Pos[0]; }
	VECTOR GetPositionB() { return m_Pos[1]; }

	VECTOR GetCenterA();
	VECTOR GetCenterB();

	//// 座標を指定
	void SetPositionA(VECTOR POSA) { m_Pos[0] = POSA; }
	void SetPositionB(VECTOR POSB) { m_Pos[1] = POSB; }

	void SetID(int id) { m_WarpID = id; }


};