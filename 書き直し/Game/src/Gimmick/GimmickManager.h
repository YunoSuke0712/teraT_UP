#pragma once
#include"Warp.h"

#include <list>
#include <vector>

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
	};
	ReadPosData ReadData;

	list <ReadPosData> m_InfoList;

	vector<Warp*> m_Warp_List;



	Warp m_Warp[GIMMICK_MAX_NUM];

	float m_SoundCage;
	int m_SoundCool;

public:
	// コンストラクタ
	GimmickManager();

	// 初期化
	void Init();
	// モデルデータのロード
	void Load();
	// 終了時のデータ破棄など
	void Exit();

	// 全行動を処理する
	void Step(VECTOR P_pos);
	// 更新処理
	// すべての行動が終わったらDxLibに情報を渡す
	void Update();
	// 描画処理
	void Draw();

	// 弾をリクエスト
	// @pos : どこから発射するか
	// @speed : どの方向に飛んでいくか
	// @return : 生成成功か失敗か
	void Request(VECTOR P_pos);

	// 敵一体分の情報取得
	// @id : 配列番号
	Warp& GetWarp(int id) { return m_Warp[id]; }

	void SetSoundCage(float num) { m_SoundCage += num; }
	float  GetSoundCage() { return m_SoundCage; }


	Warp* GetOneWarp(int ID) { return m_Warp_List[ID]; }
	int GetWarpNum() { return m_Warp_List.size(); }

};


	//void SetSoundCool() { m_SoundCool = SOUND_COOL_TIME; }
	//int GetSoundCool() { return m_SoundCool; }