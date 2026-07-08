#pragma once
#include<DxLib.h>
#include <cmath>
#include "../lib/Input/input.h"
#include"../lib/common/common.h"
#include"../Effect/effekseer.h"



class EnemyA {
private:
	CInput m_input;				//ボタン

	//軸
	int		m_EnemyID;			//ID			
	int		m_Type;				//移動タイプ	０：停止　１：移動
	bool	m_isActive;         //生存フラグ

	//個体
	int		Condition_ID;		//エネミーの状態
	int		m_hndl;				//ハンドル
	VECTOR	m_Pos;				//位置
	float	m_radius;           //半径	
	VECTOR	m_rot;				//向き
	float	m_rotationY;		//Y軸用
	int		m_Dhndl;			//復活ハンドル




	//ルート
	int		m_rootHndl;			//ルートハンドル
	int		m_rootID;			//ルートID
	int		m_RootNum;			//ルートの個数
	//------------------------------------------------

	//
	VECTOR m_Dir;				//向いている方向
	//------------------------------------------------


	//カウント
	int m_StanTime;
	int m_RePatrol;
	int m_SaveTimer;
	int m_AttackCoolTime;
	//-----------------------------------------------


	//追いかけるPos保存
	VECTOR m_SaveTraget;
	int m_SaveID;
	//-----------------------------------------------


	//視界用
	float	m_Range;			//視界距離
	float	m_Angle;			//視野角
	//-----------------------------------------------



	void MoveRoot(VECTOR P_pos);
	void TargetPlayer(VECTOR P_pos);
	void ReMove();


	//bool IsNearTarget(VECTOR playerPos, float radius);
	void DrawEye();

	bool BehindAttack(VECTOR P_Pos);

public:
	// コンストラクタ・デストラクタ
	EnemyA();
	~EnemyA();

	// 初期化
	void Init();
	// モデルデータのロード
	void Load(int Ahndl, int DanagerHndl, int RootHndl);
	// 終了時のデータ破棄など
	void Exit();
	// 全行動を処理する
	void Step(VECTOR P_pos, int level, VECTOR D_pos);
	// 更新処理
	// すべての行動が終わったらDxLibに情報を渡す
	void Update();
	// 描画処理
	void Draw();



	bool Request(const VECTOR& pos);


	// 生存情報取得・設定
	bool GetIsActive() { return m_isActive; }
	int  GetCondition() { return Condition_ID; }

	// 座標取得
	VECTOR GetPosition() { return m_Pos; }
	VECTOR GetCenter();
	// 座標を指定
	void SetPosition(VECTOR POS) { m_Pos = POS; }
	void SetSaveTargetPos(VECTOR POS) { m_Pos = POS; }
	//向き
	void SetRot(VECTOR rot) { m_rot = rot; }
	void SetRotationY(float rotY) { m_rotationY = rotY; }

	//移動タイプ
	void SetType(int type) { m_Type = type; }
	int GetType() { return m_Type; }
	//ルート個数
	void SetRootNum(int num) { m_RootNum = num; }

	float GetRange() { return m_Range; }
	float GetAngle() { return m_Angle; }

	// ヒット後の処理
	void HitCale();
	bool Attack(CEffekseerCtrl& ef, int effectID);


	//void HitEye();
	//void HitEyeDecoy();
	//void HitDecoy();
	//void HitRelease();

	void SetEnemyID(int id) { m_EnemyID = id; }
	int  GetEnemyID() { return m_EnemyID; }

	VECTOR GetDir() {

		m_Dir.x = -sinf(m_rotationY);
		m_Dir.y = 0.0f;
		m_Dir.z = -cosf(m_rotationY);

		m_Dir = VNorm(m_Dir);

		return m_Dir;
	}



	


	void SetCondition(int id) { Condition_ID = id; }



	// 当たり判定の半径サイズを取得
	float GetRadius() { return m_radius; }
	//


	//進行方向を向く
	float GetRotationY(VECTOR TargetDirection);

};