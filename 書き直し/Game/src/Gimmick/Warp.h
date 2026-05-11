#pragma once
#include<DxLib.h>
#include <cmath>

static const int WarpMaxNum = 2;

class Warp {
private:

	bool	m_isActive[WarpMaxNum];			//生存フラグ
	int		m_hndl[WarpMaxNum];				//ハンドル
	VECTOR	m_Pos[WarpMaxNum];				//位置
	float	m_radius[WarpMaxNum];           // 半径	
	float   m_rotationY[WarpMaxNum];		//常に回転させるためだけ

	int		m_WarpID;			//ID			
	

public:
	// コンストラクタ・デストラクタ
	Warp();
	~Warp();

	// 初期化
	void Init();
	// モデルデータのロード
	void Load(int Ahndl,int BHnd);
	// 終了時のデータ破棄など
	void Exit();

	// 全行動を処理する
	void Step(VECTOR P_pos);
	// 更新処理
	// すべての行動が終わったらDxLibに情報を渡す
	void Update();
	// 描画処理
	void Draw();

	bool Request(const VECTOR& pos);


	//// 生存情報取得・設定
	//bool GetIsActiveA() { return m_isActive; }
	//// 座標取得
	//VECTOR GetPosition() { return m_Pos; }
	VECTOR GetCenterA();
	VECTOR GetCenterB();

	void SetWarpID(int id) { m_WarpID = id; }

	//// 座標を指定
	void SetPositionA(VECTOR POSA) { m_Pos[0] = POSA; }
	void SetPositionB(VECTOR POSB) { m_Pos[1] = POSB; }


	//// ヒット後の処理
	//void HitCale();


	//void SetWarpID(int id) { m_WarpID = id; }
	//
	//// 当たり判定の半径サイズを取得
	//float GetRadius() { return m_radius; }
};