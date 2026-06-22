#include"Player.h"
#include<math.h>


//Start
static const VECTOR PLAYER_STARTPOS{ 1100.0f, 50.0f, 300.0f };		//開始位置
static const VECTOR PLAYER_STARROT{ 0.0f, 1.55f, 0.0f };			//開始角度
//Model
static const char PLAYER_MODEL_PATH[] = "data/model/player/NewPlayerB.mv1";	//プレイヤーのモデルのパス
static const VECTOR PlayerScalse{ 0.02f,0.02f,0.02f };						//playerのサイズ
//status
static const float MOVE_SPEED = 0.8f;								//プレイヤーの進む速度
static const int   STAMINA_COOL = 120;								//スタミナ回復速度
static const float PLAYER_RADIUS = 4.5f;							//当たり判定
static const float JUMP_POWER = 6.0f;								//ジャンプ力
static const int   JUMP_COOL = 5;									//ジャンプクールタイム
static const float DASH_SPEED_UP = 1.0f;							//ダッシュ



//----------------------
// コンストラクタ
//----------------------
Player::Player()
{
	Init();

}

//----------------------
// デストラクタ
//----------------------
Player::~Player()
{
	Exit();
}

//----------------------
// 初期化
//----------------------
void Player::Init()
{
	m_Pos = PLAYER_STARTPOS;
	m_Rot = PLAYER_STARROT;
	m_RotModel = PLAYER_STARROT;
	m_RotModel.y += DX_PI_F;


	m_pState = PLSTATE_NORMAL;
	
	m_isActive = true;
	m_DeathFlag = false;
	m_isGoal = false;
	m_radius = PLAYER_RADIUS;
	m_hndl = HNDL_INIT;
	m_jumppower = ZERO_F;
	m_jumpNow = false;

	m_Speed = ZERO;
	m_movespeed = ZERO_F;

	m_DashStamina = DASH_STAMINA;
	m_Stamina_Cool = 0;

	//アニメーション
	m_NowAnim = PLSTATE_NORMAL;
	m_AnimIndex = -1;
	m_walk = false;
	m_throw = false;
	m_throwcount = ZERO_I;
	m_DeathCount = ZERO_I;
	//m_AnimTime = 0;


	//アイテム初期化
	m_effect_speed_up = ZERO_I;
	m_effect_speed_Sup = ZERO_I;
	m_shot = false;
	m_F_hndl = -1;
	m_Sp_cool = 0;


}

//--------------------------
// モデルデータのロード
//--------------------------
void Player::Load()
{
	// ロードされていなければする
	if (m_hndl == -1)
	{
		m_hndl = MV1LoadModel(PLAYER_MODEL_PATH);
	}

	if (m_F_hndl == -1)
	{
		m_F_hndl = MV1LoadModel("data/model/item/flag.mv1");
	}
	if (m_AnimIndex == -1)
	{
		m_AnimIndex = MV1AttachAnim(m_hndl, m_pState);

	}

	for (int i = 0; i < MV1GetAnimNum(m_hndl); i++)
	{
		printfDx(
			"Anim[%d] Total=%f\n",
			i,
			MV1GetAnimTotalTime(m_hndl, i)
		);
	}
}

//--------------------------
// 終了時の破棄
//--------------------------
void Player::Exit()
{
	if (m_hndl != -1)
	{
		MV1DeleteModel(m_hndl);
		m_hndl = -1;
	}

	if (m_F_hndl != -1)
	{
		MV1DeleteModel(m_F_hndl);
		m_F_hndl = -1;
	}
}

//------------------------
// カメラの座標計算
//------------------------
void Player::Step(VECTOR rot)
{
	Gravity();

	switch (m_pState)
	{
	case PLSTATE_DEATH:		//死
		if (m_DeathCount > 0)
		{
			m_DeathCount--;
			m_pState = PLSTATE_DEATH;
		}
		if (m_DeathCount == 0)
		{
			m_isActive = false;
		}
		break;
	case PLSTATE_NORMAL:	//生
		//break;
	case PLSTATE_WALK:		//歩く
		//移動
		m_Pos = VAdd(m_Pos, Move(rot));
		m_Speed = { 0.0f,0.0f,0.0f };

		Throw();
		break;
	case PLSTATE_THROW:		//使う
		//投げる処理優先
		if (m_throwcount > 0)
		{
			m_throwcount--;
		}
		if (m_throwcount == 0)
			m_pState = PLSTATE_NORMAL;

		break;
	}


	Anim();
}

//------------------------
// カメラの更新
//------------------------
void Player::Update()
{
	// 座標回転角度を設定する
	//m_RotModel = m_Rot;
	//m_RotModel.y += DX_PI_F;
	MV1SetRotationXYZ(m_hndl, m_RotModel);
	MV1SetPosition(m_hndl, m_Pos);
	MV1SetScale(m_hndl, PlayerScalse);

	if (m_Sp_cool >= 0)m_Sp_cool--;					//クールカウントー


	MV1SetRotationXYZ(m_F_hndl, m_RotModel);
	MV1SetPosition(m_F_hndl, m_item3_re);
	MV1SetScale(m_F_hndl, PlayerScalse);
	
	//スピードリセット
	m_movespeed = MOVE_SPEED;

	//現在のアニメーションを記録
	m_walk = false;
	if (m_throwcount < 0)m_walk = false;
	if(m_Stamina_Cool > 0)m_Stamina_Cool--;
}

//------------------------
// 描画
//------------------------
void Player::Draw()
{
	MV1DrawModel(m_hndl);

	//DrawSphere3D(GetCenter(), m_radius, 16, GetColor(255, 0, 255), GetColor(255, 0, 255), true);
	DrawFormatString(10, 10, GetColor(155, 0, 0),"%f",m_Pos.z);


	//プレイヤーの位置
	DrawFormatString(1200, 300, GetColor(25, 200, 100), "pposX:%f", m_Pos.x);
	DrawFormatString(1200, 350, GetColor(25, 200, 100), "pposY:%f", m_Pos.y);
	DrawFormatString(1200, 400, GetColor(25, 200, 100), "pposZ:%f", m_Pos.z);
	//DrawFormatString(1200, 450, GetColor(25, 200, 100), "dasy:%d", m_DashStamina);
	//DrawFormatString(1200, 500, GetColor(25, 200, 100), "dassyucool:%d", m_Stamina_Cool);

	//DrawFormatString(10, 160, GetColor(0, 0, 0), "SCORE：%d", m_score);

	//アイテム効果
	
	if (m_effect_speed_Sup > 0)
	{
		MV1DrawModel(m_F_hndl);
	}

	DrawFormatString(
    10, 100,
    GetColor(255,255,255),
    "State:%d Anim:%d",
    m_pState,
    m_AnimIndex
);


	DrawFormatString(
		10,
		130,
		GetColor(255, 255, 255),
		"AnimNum=%d",
		MV1GetAnimNum(m_hndl)
	);
	
	////寺戸先生のスペシャル授業＝＝＝＝＝＝
	//VECTOR END = VGet(0.0f,0.0f,0.0f);


	//END.x = sinf(m_RotModel.y) * 300;
	//END.z = cosf(m_RotModel.y) * 300;

	//DrawLine3D(m_Pos, VAdd(m_Pos,END), GetColor(255, 255, 0));

}

// 当たり判定の座標系
VECTOR Player::GetCenter()
{
	// 基本は物体の座標の位置
	VECTOR res = m_Pos;
	// posが足元のため、高さだけ足元から球の半径分上げる
	
	res.y += m_radius;

	return res;
}

void Player::HitEnemyCale()
{
	if (!m_DeathFlag)
	{
		Death(true);
	}
}

void Player::HitGoal()
{
	m_isGoal = true;
}





void Player::Anim()
{
	// アニメ処理-----------------------------------------------
	if (!m_walk && m_pState == PLSTATE_WALK)m_pState = PLSTATE_NORMAL;


	//ダウンが最優先
	//ここにダウンのアニメ

	//ここまでにm_pStateを変更
	if (m_NowAnim != m_pState)
	{
		if (m_AnimIndex != -1)
		{
			//アニメーション外す
			MV1DetachAnim(m_hndl, m_AnimIndex);
		}
		//アニメーション付ける
		m_AnimIndex = MV1AttachAnim(m_hndl, m_pState);
		
		//再生位置設定
		MV1SetAttachAnimTime(m_hndl, m_AnimIndex, 0.0f);

		//アニメーション番号切り替わり確認用
		//printfDx("Change Anim %d -> %d\n", m_NowAnim, m_pState);


	}

	if (m_AnimIndex == -1){return;}
	float	animTime = MV1GetAttachAnimTime(m_hndl, m_AnimIndex);

	animTime += ANIM_SPD * 2;
	if (animTime >= MV1GetAttachAnimTotalTime(m_hndl, m_AnimIndex))
	{
		animTime = 0.0f;
	}
	MV1SetAttachAnimTime(m_hndl, m_AnimIndex, animTime);
	//----------------------------------------------------------

	m_NowAnim = m_pState;

}

void Player::Throw()
{
	if (m_input.IsInputTrg(KEY_RCLICK)
		||CGamePad::IsPadPush(DX_INPUT_PAD1, BUTTON_B))
	{
		m_throwcount = THROW_COUNT;
		m_pState = PLSTATE_THROW;
	}
}

void Player::Death(bool deas)
{	
	m_DeathFlag = true;
	m_DeathCount = DEATH_COUNT;
	m_pState = PLSTATE_DEATH;
	
}




VECTOR Player::Move(VECTOR rot)
{
	m_jumpNow = false;
	m_Rot.y = rot.y;

	//PAD視野操作関連＝＝＝＝＝＝
	if (CGamePad::Stick(STICK_RX_POS) != 0)m_Rot.y += 0.5;
	if (CGamePad::Stick(STICK_RX_NEG) != 0)m_Rot.y += -0.5;


	//ダッシュ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	if (m_input.IsInputRel(KEY_DASH) || CGamePad::IsPadRelease(DX_INPUT_PAD1, BUTTON_RB))
	{
		m_Stamina_Cool = STAMINA_COOL;
	}
	if ((m_input.IsInputRep(KEY_DASH) || CGamePad::IsPadKeep(DX_INPUT_PAD1, BUTTON_RB)) && m_DashStamina > 0)
	{
		m_movespeed += DASH_SPEED_UP;
		m_DashStamina--;
		m_Stamina_Cool = STAMINA_COOL;
	}
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝


	else if ((!m_input.IsInputRep(KEY_DASH) || CGamePad::IsPadKeep(DX_INPUT_PAD1, BUTTON_RB)) && m_Stamina_Cool <= 0)
	{
		m_DashStamina += 2;
		if (m_DashStamina >= 300)
			m_DashStamina = 300;
	}
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	//ジャンプ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	if ((m_input.IsInputTrg(KEY_JUMP) || CGamePad::IsPadPush(DX_INPUT_PAD1, BUTTON_A)) && m_jumpNow == false && m_jumpCoolTime <= 0)
	{
		m_jumpNow = true;
		m_jumppower = JUMP_POWER;
		//m_movespeed += 5;
		m_jumpCoolTime = JUMP_COOL;

	}

	if (m_jumpCoolTime > 0)
	{
		m_jumpCoolTime--;
		m_jumpNow = true;
	}



	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	//移動＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	float lx = 0.0f;
	float ly = 0.0f;

	// キーボード入力
	if (m_input.IsInputRep(KEY_RIGHT))
	{
		lx -= 1.0f;
		m_RotModel.y = rot.y - DX_PI_F / 2;
	}
	if (m_input.IsInputRep(KEY_LEFT))
	{
		lx += 1.0f;
		m_RotModel.y = rot.y + DX_PI_F / 2;
	}
	if (m_input.IsInputRep(KEY_DOWN))
	{
		ly += 1.0f;
		m_RotModel.y = rot.y;
	}
	if (m_input.IsInputRep(KEY_UP))
	{
		ly -= 1.0f;
		m_RotModel.y = rot.y - DX_PI_F;
	}

	// スティック入力
	if (CGamePad::Stick(STICK_LX_POS))
	{
		lx -= 1.0f;
		m_RotModel.y = rot.y - DX_PI_F / 2;
	}
	if (CGamePad::Stick(STICK_LX_NEG))
	{
		lx += 1.0f;
		m_RotModel.y = rot.y + DX_PI_F / 2;

	}
	if (CGamePad::Stick(STICK_LY_POS))
	{
		ly += 1.0f;
		m_RotModel.y = rot.y;

	}
	if (CGamePad::Stick(STICK_LY_NEG))
	{
		ly -= 1.0f;
		m_RotModel.y = rot.y - DX_PI_F;

	}

	VECTOR move = { 0.0f, 0.0f, 0.0f };

	float len = sqrtf(lx * lx + ly * ly);
	if (len > 0.0f)
	{
		// 正規化
		lx /= len;
		ly /= len;

		//向き
		m_RotModel.y = rot.y + atan2f(lx, ly);

		// ワールド座標に変換
		move.x = (sinf(m_Rot.y) * ly + sinf(m_Rot.y + DX_PI_F / 2) * lx) * m_movespeed;
		move.y = 0.0f;
		move.z = (cosf(m_Rot.y) * ly + cosf(m_Rot.y + DX_PI_F / 2) * lx) * m_movespeed;

		// 状態変更
		m_pState = PLSTATE_WALK;
		m_walk = true;
	}
	else
	{
		// 移動なし
		m_walk = false;
	}
	m_Speed = move;
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	return move;
}


void Player::Gravity()
{
	m_Pos.y += m_jumppower;

	m_jumppower -= GRAVITY;

	if (m_jumppower <= -4) {
		m_jumppower = -4.0f;
	}

}