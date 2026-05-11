#pragma once
#include<DxLib.h>
#include <cmath>


class Gimmick {
private:

	bool	m_isActive;         //生存フラグ
	int		m_hndl;				//ハンドル
	VECTOR	m_Pos;				//位置
	float	m_radius;           // 半径	
	VECTOR	m_rot;
	
	int		m_GimmickID;			//ID			
	int		m_Dhndl;			//復活ハンドル
	
	int		m_rootHndl;
	int		m_rootID;

	float m_rotationY;			//常に回転させるためだけ

	//視界
	VECTOR m_Dir;
	bool m_IsFindPlayer;
	int m_RePatrol;


	enum Condition {
		STOP,			 // 停止
		PATROL,			 //巡回
		IN_P,			 //視界にPが入る
		DISCOVERY_P,	 //Pを発見する
		TRACKING_P,		 //Pを追跡する
		TRACKING_D,		 //Pを追跡する
		IN_ITEM,		 //視界にIが入る
		DISCOVERY_ITEM,	 //Iを発見する
		TRACKING_ITEM,	 //Iを追跡する
		PATROL_RE,		 //巡回に戻る
		STAN,			 //気絶
		NOW_MOTION,		 //モーション中
		WAIT,		     //待つ
	};
	Condition Condition_ID;



	void MoveRoot(VECTOR P_pos);
	void TargetPlayer(VECTOR P_pos);
	void ReMove();


	bool IsNearTarget(VECTOR playerPos, float radius);
	void DrawEye();

public:
	// コンストラクタ・デストラクタ
	Gimmick();
	~Gimmick();

	// 初期化
	void Init();
	// モデルデータのロード
	void Load(int Ahndl,int danagerHndl);
	// 終了時のデータ破棄など
	void Exit();

	// 全行動を処理する
	void Step(VECTOR P_pos,int level,VECTOR D_pos);
	// 更新処理
	// すべての行動が終わったらDxLibに情報を渡す
	void Update();
	// 描画処理
	void Draw();

	// 敵をリクエスト
	// @pos : どこから発射するか
	// @speed : どの方向に飛んでいくか
	// @return : 生成成功か失敗か
	bool Request(const VECTOR& pos);


	// 生存情報取得・設定
	bool GetIsActive() { return m_isActive; }
	// 座標取得
	VECTOR GetPosition() { return m_Pos; }
	VECTOR GetCenter();
	// 座標を指定
	void SetPosition(VECTOR POS) { m_Pos = POS; }
	//向き
	void SetRot(VECTOR rot) { m_rot = rot; }



	// ヒット後の処理
	void HitCale();


	void SetGimmickID(int id) { m_GimmickID = id; }


	VECTOR GetDir() {

		m_Dir.x = -sinf(m_rotationY);
		m_Dir.y = 0.0f;
		m_Dir.z = -cosf(m_rotationY);

		m_Dir = VNorm(m_Dir);

		return m_Dir;
	}

	void SetFindPlayer(bool flag) { m_IsFindPlayer = flag; }

	void SetCondition_TRACKING_P() { Condition_ID = TRACKING_P; }


	
	// 当たり判定の半径サイズを取得
	float GetRadius() { return m_radius; }


};