#include"EnemyB.h"
#include<math.h>
#include"../lib/MyMath/MyMath.h"

static const VECTOR ROOT_POS = { 500.0f, -15.0f, 300.0f };		//ルートの位置
static const VECTOR Scale{ 0.03f,0.03f,0.03f };					//敵のサイズ
static const float ENEMY_SIZE = 5.0f;							//敵の当たり判定
static const float ENEMY_ROTATIONY = 0.0f;						//回転Y

// 視界距離
static const float ENEMY_RANGE = 200.0f;
// 視野角
static const float ENEMY_ANGLE = DegToRad(25.0f);

static const float ENEMY_SPEED = 1.0f;							//敵の移動速度
static const float ENEMY_P_SPEED = 1.5f;						//敵の追跡速度

static const int   ENEMY_RE_COOL = 180;							//パトロールに戻る



//----------------------
// コンストラクタ
//----------------------
EnemyB::EnemyB()
{
	Init();
}

//----------------------
// デストラクタ
//----------------------
EnemyB::~EnemyB()
{
	Exit();  // 念のためモデルデータを破棄
}

//----------------------
// 初期化
//----------------------
void EnemyB::Init()
{
	m_radius = ENEMY_SIZE;	//敵の当たり判定
	m_isActive = true;
	m_hndl = HNDL_INIT;
	m_Dhndl = HNDL_INIT;
	Condition_ID = WAIT;
	m_rotationY = ENEMY_ROTATIONY;
	m_rootHndl = HNDL_INIT;
	m_RePatrol = ZERO_I;
	m_StanTime = ZERO_I;


	m_SaveTimer = ZERO_I;
	m_SaveID = 0;



	// 0番目のルートに配置したので、次の目的地は1
	//
	m_rootID = 1;

}

//--------------------------
// モデルデータのロード
//--------------------------
void EnemyB::Load(int Ahndl, int danagerHndl)
{
	// ロードされていなければする
	if (m_hndl == HNDL_INIT)
	{
		m_hndl = MV1DuplicateModel(Ahndl);
	}
	if (m_Dhndl == HNDL_INIT)
	{
		m_Dhndl = MV1DuplicateModel(danagerHndl);
	}
	if (m_rootHndl == HNDL_INIT)
	{
		m_rootHndl = MV1LoadModel("data/model/field/Map01/Map01_EnemyBRoot_01.mv1");
	}
}

//--------------------------
// 終了時の破棄
//--------------------------
void EnemyB::Exit()
{
	// データをロードしているときだけ削除
	if (m_hndl != -1)
	{
		MV1DeleteModel(m_hndl);
		m_hndl = -1;
	}
	if (m_Dhndl != -1)
	{
		MV1DeleteModel(m_Dhndl);
		m_Dhndl = -1;
	}
	if (m_rootHndl != -1)
	{
		MV1DeleteModel(m_rootHndl);
		m_rootHndl = -1;
	}
}

//------------------------
// 毎フレーム更新
//------------------------
void EnemyB::Step(VECTOR P_pos, int level, VECTOR D_pos)
{
	MV1SetPosition(m_rootHndl, ROOT_POS);

	MV1SetScale(m_rootHndl, VGet(0.8f, 1.0f, 0.8f));
	MV1SetupCollInfo(m_rootHndl);

	m_Pos.y -= GRAVITY;

	switch (Condition_ID)
	{
	case WAIT:
		break;

	case TRACKING_P:
		TargetPlayer(P_pos);
		break;
	case STAN:
		if (m_StanTime < 180) m_StanTime++;
		if (m_StanTime >= 180)
		{
			m_StanTime = 0;
			Condition_ID = PATROL;
			m_isActive = false;
		}
		break;
	}

	if (BehindAttack(P_pos))Condition_ID = STAN;

}

//------------------------
// 更新
//------------------------
void EnemyB::Update()
{
	// 座標回転角度を設定する
	MV1SetPosition(m_hndl, m_Pos);


	VECTOR rot = { 0.0f,m_rotationY,0.0f };

	MV1SetRotationXYZ(m_hndl, rot);
	MV1SetScale(m_hndl, Scale);

	//MV1SetPosition(m_Dhndl, { m_remove_pos.x,m_remove_pos.y + 15,m_remove_pos.z });
	MV1SetRotationXYZ(m_Dhndl, rot);
	MV1SetScale(m_Dhndl, { 0.05f,0.05f,0.05f });
}

//------------------------
// 描画
//------------------------
void EnemyB::Draw()
{
	if (!m_isActive) return;

	MV1DrawModel(m_hndl);

	//DrawFormatString(1200, 500, GetColor(25, 200, 100), "EposX:%f", m_Pos.x);
	//DrawFormatString(1200, 650, GetColor(25, 200, 100), "EposY:%f", m_Pos.y);
	//DrawFormatString(1200, 600, GetColor(25, 200, 100), "EposZ:%f", m_Pos.z);
	//DrawFormatString(1200, 700, GetColor(25, 200, 100), ":%d", m_rootID);

	MV1DrawModel(m_rootHndl);
	DrawSphere3D(GetCenter(), m_radius, 16, GetColor(255, 0, 255), GetColor(255, 0, 255), true);

	////DrawFormatString(1200, 800, GetColor(25, 200, 100), "x:%f",m_remove_pos.x);
	////DrawFormatString(1200, 900, GetColor(25, 200, 100), "z:%f", m_remove_pos.z);

	DrawEye();
}

//------------------------
// 敵をリクエスト
//------------------------
bool EnemyB::Request(const VECTOR& pos)
{
	// すでに発射されている弾は生成失敗
	if (m_isActive)return false;

	// 必要な情報を渡していく
	m_isActive = true;
	m_Pos = pos;
	//m_Speed = speed;

	return true;
}

// 当たり判定の座標系
VECTOR EnemyB::GetCenter()
{
	// 基本は物体の座標の位置
	VECTOR res = m_Pos;
	// 高さだけ足元から球の半径分上げる
	res.y += m_radius;

	return res;
}

//------------------------
// ヒット後の処理
//------------------------
void EnemyB::HitCale()
{
	// 生存フラグを消す
	Condition_ID = STAN;

}

//プレイヤーを追いかける
void EnemyB::TargetPlayer(VECTOR P_pos)
{
	VECTOR targetPos = P_pos;

	if (m_SaveTimer <= 0)
	{
		m_SaveTimer = 300;
		m_SaveTraget = P_pos;
	}
	m_SaveTimer--;


	// 自分の座標取得
	VECTOR pos = GetPosition();
	// 目的地へのベクトル取得
	VECTOR p_dir = VSub(targetPos, pos);
	// 目的地までの距離を取得
	float p_len = VSize(p_dir);

	// Saveへのベクトル取得
	VECTOR s_dir = VSub(m_SaveTraget, pos);
	// Saveまでの距離を取得
	float s_len = VSize(s_dir);


	if (s_len < 5.0f)
	{
		m_SaveTimer = 0;
	}

	if (p_len < 4.0f)
	{
	}
	// 目的地までの距離が一定範囲内なら
	else if (p_len < 25.0f)
	{
		// いったん正規化して
		p_dir.y = 0.0f;
		p_dir = VNorm(p_dir);
		// 実際の移動速度に変更
		p_dir = VScale(p_dir, ENEMY_SPEED);
		// 速度を加算してキャラクターにセット
		pos = VAdd(pos, p_dir);
		SetPosition(pos);

		// 進行方向を向かせる(これは便利なので関数化しておいてもいいかも)
		float rot = atan2f(-p_dir.x, -p_dir.z);
		SetRot(VGet(0.0f, rot, 0.0f));
		m_rotationY = rot;
	}
	else if(p_len < 300.0f)
	{
		// いったん正規化して
		s_dir.y = 0.0f;
		s_dir = VNorm(s_dir);
		// 実際の移動速度に変更
		s_dir = VScale(s_dir, ENEMY_SPEED);
		// 速度を加算してキャラクターにセット
		pos = VAdd(pos, s_dir);
		SetPosition(pos);

		// 進行方向を向かせる(これは便利なので関数化しておいてもいいかも)
		float rot = atan2f(-s_dir.x, -s_dir.z);
		SetRot(VGet(0.0f, rot, 0.0f));
		m_rotationY = rot;
	}
	else
	{
		Condition_ID = PATROL_RE;
		m_RePatrol = ENEMY_RE_COOL;
		m_SaveTimer = 0;
	}
}





void EnemyB::DrawEye()
{
	//=====================================
// 視界表示
//=====================================

// 敵の位置
	VECTOR pos = m_Pos;

	// 敵の向き
	VECTOR dir;

	// rotationYから向きを作る
	dir.x = -sinf(m_rotationY);
	dir.y = 0.0f;
	dir.z = -cosf(m_rotationY);

	// 正規化
	dir = VNorm(dir);

	// 視界距離
	float range = ENEMY_RANGE;

	// 視野角
	float angle = ENEMY_ANGLE;
	//--------------------------------
	// 左方向
	//--------------------------------
	VECTOR leftDir;

	leftDir.x = dir.x * cosf(angle) - dir.z * sinf(angle);
	leftDir.y = 0.0f;
	leftDir.z = dir.x * sinf(angle) + dir.z * cosf(angle);

	//--------------------------------
	// 右方向
	//--------------------------------
	VECTOR rightDir;

	rightDir.x = dir.x * cosf(-angle) - dir.z * sinf(-angle);
	rightDir.y = 0.0f;
	rightDir.z = dir.x * sinf(-angle) + dir.z * cosf(-angle);

	//--------------------------------
	// 線の終点
	//--------------------------------
	VECTOR centerEnd =
	{
		pos.x + dir.x * range,
		pos.y + 10.0f,
		pos.z + dir.z * range
	};

	VECTOR leftEnd =
	{
		pos.x + leftDir.x * range,
		pos.y + 10.0f,
		pos.z + leftDir.z * range
	};

	VECTOR rightEnd =
	{
		pos.x + rightDir.x * range,
		pos.y + 10.0f,
		pos.z + rightDir.z * range
	};

	//--------------------------------
	// 視界描画
	//--------------------------------

	// 真ん中
	DrawLine3D(
		VGet(pos.x, pos.y + 10.0f, pos.z),
		centerEnd,
		GetColor(0, 0, 0)
	);

	// 左
	DrawLine3D(
		VGet(pos.x, pos.y + 10.0f, pos.z),
		leftEnd,
		GetColor(255, 0, 0)
	);

	// 右
	DrawLine3D(
		VGet(pos.x, pos.y + 10.0f, pos.z),
		rightEnd,
		GetColor(255, 0, 0)
	);


////--------------------------------
//// GetDir() の確認用
////--------------------------------
//	VECTOR testDir = GetDir();
//
//	testDir = VNorm(testDir);
//
//	VECTOR testEnd =
//	{
//		pos.x + testDir.x * 60.0f,
//		pos.y + 15.0f,
//		pos.z + testDir.z * 60.0f
//	};
//
//	// 黄色線
//	DrawLine3D(
//		VGet(pos.x, pos.y + 15.0f, pos.z),
//		testEnd,
//		GetColor(0, 0, 255)
//	);
}



bool EnemyB::BehindAttack(VECTOR P_Pos)
{
	//--------------------------------
	// 敵の前方向
	//--------------------------------
	VECTOR dir;

	dir.x = -sinf(m_rotationY);
	dir.y = 0.0f;
	dir.z = -cosf(m_rotationY);

	dir = VNorm(dir);

	//--------------------------------
	// 敵→プレイヤー方向
	//--------------------------------
	VECTOR toPlayer = VSub(P_Pos, m_Pos);

	toPlayer.y = 0.0f;

	//--------------------------------
	// 距離
	//--------------------------------
	float len = VSize(toPlayer);

	// 25m以上なら失敗
	if (len > 25.0f)
	{
		return false;
	}

	//--------------------------------
	// 正規化
	//--------------------------------
	toPlayer = VNorm(toPlayer);

	//--------------------------------
	// 内積
	//--------------------------------
	float dot = VDot(dir, toPlayer);

	//--------------------------------
	// 背後60度判定
	//--------------------------------
	float angle = DegToRad(45.0f);

	if (dot < -cosf(angle))
	{
		if(m_input.IsInputTrg(KEY_RCLICK)) return true;
	}

	return false;
}
