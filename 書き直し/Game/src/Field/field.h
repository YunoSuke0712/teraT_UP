#pragma once
#include <DxLib.h>
//#include "../Plyaer/Player.h


static const int GIMMICK_MAX = 5;

class Field
{
private:
	VECTOR m_vPos;            // 座標

	int m_hndl;			//フィールド
	int m_skyhndll;		//すかい

	int m_Gimmick_hndl[GIMMICK_MAX];
	float SkyRotY;
	bool m_isHitFlag;
	
	bool m_Gimmick_active[GIMMICK_MAX];
	//０：P鍵	１：スイッチ　２：檻　

public:
	Field();
	~Field();

	void Init();
	// モデルデータのロード
	void Load();
	// 終了時のデータ破棄など
	void Exit();
	// 描画処理
	void Draw();
	//　ステップ
	void Step();

	//アップデート
	void Updata();
	


	int GetFieldHndl() { return m_hndl; }
	//void HitCheck(Player& player);
	//void HitCheckDoor(Player& player,ItemSlot& item);
	//void HitCheckA(EnemyManager& enemy);
	//bool HitCheckEnemyA_Button(EnemyManager& enemy);
	//void HitCheckB(EnemyManager& enemy);

	//int GetModelHandle() const { return m_hndl; }

	//void SetGimmickActive(int ID, bool active) { m_Gimmick_active[ID] = active; }

	//int GetClearGimick()
	//{
	//	int clear = 0;
	//	for (int i = 0; i < GIMMICK_MAX; i++)
	//	{
	//		if (m_Gimmick_active[i] == false)
	//		{
	//			clear++;
	//		}
	//	}
	//	return clear;
	//}
	//bool CheckHitWall(const VECTOR& pos, float radius);
	//void ResolveCollision(VECTOR& pos, float height, float radius);
};