#pragma once

#include"Warp.h"
#include"Ori.h"
#include"TreasureGoal.h"

#include <list>
#include <vector>

//#include "../Player/Player.h"
//#include "エフェクトのやつ"
//↑消しても大丈夫そう


using namespace std;

// 最大数
static const int GIMMICK_MAX_NUM = 20;

// 弾全体を管理する
class GimmickManager
{
private:

	struct ReadPosData {
		float m_PosA_X;		
		float m_PosA_Y;
		float m_PosA_Z;
		float m_PosB_X;
		float m_PosB_Y;
		float m_PosB_Z;
		float m_RotA_Y;
		float m_RotB_Y;
		bool  m_Active;
	};
	ReadPosData ReadData;
	list <ReadPosData> m_InfoList;

	//==ワープ
	vector<Warp*> m_Warp_List;
	Warp m_Warp[GIMMICK_MAX_NUM];
	//===檻
	vector<Ori*> m_Ori_List;
	Ori m_Ori[GIMMICK_MAX_NUM];
	//===宝ゴール
	vector<TreasureGoal*> m_Tre_Goal_List;
	TreasureGoal m_Tre[GIMMICK_MAX_NUM];
	//===

	void LoadWarp(int mapID);
	void LoadOri(int mapID);
	void LoadTre_Goal(int mapID);


public:
	// コンストラクタ
	GimmickManager();

	// 初期化
	void Init();
	// モデルデータのロード
	void Load(int mapID);
	// 終了時のデータ破棄など
	void Exit();

	// 全行動を処理する
	void Step(Player& player, CEffekseerCtrl& effect);
	// 更新処理
	// すべての行動が終わったらDxLibに情報を渡す
	void Update();
	// 描画処理
	void Draw();

	void Request(VECTOR P_pos);


	// Ori数取得
	int GetGimmickNum() { return m_Ori_List.size(); }
	// Ori取得
	Ori* GetOneOri(int index) { return m_Ori_List[index]; }

};


