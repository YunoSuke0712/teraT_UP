#pragma once
#include<DxLib.h>



class EnemyA {
private:

	bool	m_isActive;         //生存フラグ
	int		m_hndl;				//ハンドル
	VECTOR	m_Pos;				//位置
	float	m_radius;           // 半径	
	VECTOR	m_rot;
	
	int		m_EnemyID;			//ID			
	int		m_Dhndl;			//復活ハンドル
	
	int		m_rootHndl;
	int		m_rootID;

	float m_rotationY;			//常に回転させるためだけ


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
	bool IsNearTarget(VECTOR playerPos, float radius);
	void TargetPlayer(VECTOR P_pos);


public:
	// コンストラクタ・デストラクタ
	EnemyA();
	~EnemyA();

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
	void HitEye();
	void HitEyeDecoy();
	void HitDecoy();

	void HitRelease();

	void SetEnemyID(int id) { m_EnemyID = id; }







	
	// 当たり判定の半径サイズを取得
	float GetRadius() { return m_radius; }







	
};