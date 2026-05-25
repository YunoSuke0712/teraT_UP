#pragma once
#include"EnemyA.h"

#include <list>
#include <vector>

using namespace std;

// 最大数
static const int ENEMYA_MAX_NUM = 20;
static const int ENEMYB_MAX_NUM = 20;

// 弾全体を管理する
class EnemyManager
{
private:

	struct ReadPosData {
		float m_Pos_X;
		float m_Pos_Y;
		float m_Pos_Z;
	};
	ReadPosData ReadData;

	list <ReadPosData> m_InfoList;

	vector<EnemyA*> m_EneA_List;


	EnemyA m_EnemyA[ENEMYA_MAX_NUM];

	float m_SoundCage;
	int m_SoundCool;

	void EnemyAData(int mapID);

public:
	// コンストラクタ
	EnemyManager();

	// 初期化
	void Init();
	// モデルデータのロード
	void Load(int mapID);
	// 終了時のデータ破棄など
	void Exit();

	// 全行動を処理する
	void Step(VECTOR P_pos, int level, VECTOR D_pos);
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
	EnemyA& GetEnemyA(int id) { return m_EnemyA[id]; }

	void SetSoundCage(float num) { m_SoundCage += num; }
	float  GetSoundCage() { return m_SoundCage; }


	EnemyA* GetOneEnemyA(int ID) { return m_EneA_List[ID]; }
	int GetEnemyANum() { return m_EneA_List.size(); }




};


