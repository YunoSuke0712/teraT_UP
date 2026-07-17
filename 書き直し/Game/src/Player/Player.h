#pragma once
#include<DxLib.h>
#include"../lib/Input/input.h"
#include"../lib/Input/PadInput.h"
#include"../lib/Common/common.h"
#include"../lib/Effect/effekseer.h"

//アニメーション===
static const float	ANIM_SPD = F1;					//アニメーション速度
static const int THROW_COUNT = 30;					//投げるアニメーション時間
static const int DEATH_COUNT = 120;
//=================



class Player {
private:
	CInput m_input;

	enum tagPlayerState {
		PLSTATE_NORMAL,		//待機・移動状態
		PLSTATE_WALK,		//歩く
		PLSTATE_THROW,		//使う
		PLSTATE_DEATH,		//捕まる
		PLSTATE_HITBACK,	//吹っ飛ぶ
		

		PLSTATE_NUM       // 状態の総数
	};


	VECTOR m_Pos;            // 座標
	VECTOR m_RotModel;		  // モデルの見た目回転
	VECTOR m_Speed;           // 移動速度
	
	float m_movespeed;
	VECTOR m_Rot;            // 回転角度


	//アニメーション===========================
	tagPlayerState m_pState; //状態
	//float m_AnimTime;
	int m_AnimIndex;
	int m_NowAnim;
	bool m_walk;
	bool m_throw;
	int m_throwcount;
	int m_DeathCount;
	//========================================
	


	float m_radius;           // 半径
	bool m_isActive;          // 生存フラグ
	bool m_DeathFlag;		  // 死亡フラグ
	bool m_isGoal;
	int m_hndl;
	int m_Hp;
	
	int m_score;


	float m_jumppower;		//ジャンプ力ぅですかねぇ
	bool m_jumpNow;
	int	m_jumpCoolTime;

	int  m_DashStamina;
	int m_Stamina_Cool;

	float wariaiX, wariaiY;
	float sabunX, sabunY;
	int mouseXn, mouseYn;
	float moveX, moveY;
	bool m_shot;



	//アイテム変数＝＝
	int m_effect_speed_up;
	int m_effect_speed_Sup;
	VECTOR m_item3_re;
	int m_Sp_cool;
	int m_F_hndl;//フラッグ




	VECTOR Move(VECTOR rot);
	void Anim();
	void Throw();
	void Death(bool deas);
	void Gravity();

public:
	// コンストラクタ・デストラクタ
	Player();
	~Player();

	// 初期化
	void Init();
	// モデルデータのロード
	void Load();
	// 終了時のデータ破棄など
	void Exit();

	// 全行動を処理する
	void Step(VECTOR rot);
	// 更新処理
	// すべての行動が終わったらDxLibに情報を渡す
	void Update();
	// 描画処理
	void Draw();


	// ヒット後の処理
	void HitEnemyCale();
	void HitGoal();

	//ジャンプ情報取得・設定
	void SetJumpNow(bool Jump) { m_jumpNow = Jump; }
	bool GetJumpNow() { return m_jumpNow; }

	// 生存情報取得・設定
	bool IsActive() { return m_isActive; }
	void SetActive(bool active) { m_isActive = active; }

	//ゴール情報取得・設定
	bool IsGoal() { return m_isGoal; }
	void SetGoal(bool active) { m_isGoal = active; }

	// 当たり判定の半径サイズを取得
	float GetRadius() { return m_radius; }
	// プレイヤーの中心を取得
	VECTOR GetCenter();


	// プレイヤーの座標を取得
	VECTOR GetPosition() { return m_Pos; }
	// プレイヤーの座標を指定
	void SetPosition(VECTOR POS) { m_Pos = POS; }

	// カメラの回転角度（Y軸）を取得 //カメラ用
	float GetRotationY() { return m_Rot.y; }
	//モデルの回転角度Y
	float GetNEWRotationY() { return m_RotModel.y; }

	//プレイヤーのアニメーションを取得
	int GetPlayerAnim() { return m_pState; }
	void SetPpayerAnim_Throw() { m_pState = PLSTATE_THROW; m_throwcount = THROW_COUNT; }


};