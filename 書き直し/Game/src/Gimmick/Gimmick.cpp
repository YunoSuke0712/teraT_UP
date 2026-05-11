#include"Gimmick.h"
#include<math.h>
#include"../lib/common/common.h"
#include "../Field/field.h"
#include "../lib/Input/input.h"

//ルートの番号
static const int ROOT_ID[] = { 1,4,7,10};
//ルートの個数
static const int ROOT_NUM = 4;

// 敵の進む速度
static const float SHOT_SPEED = 1.0f;

static const VECTOR Scale{ 0.03f,0.03f,0.03f };					//敵のサイズ
static const float ENEMY_SIZE = 5.0f;							//敵の当たり判定
static const float ENEMY_SPEED = 1.0f;							//敵の移動速度
static const float ENEMY_P_SPEED = 1.5f;						//敵の移動速度
static const float ENEMY_ROTATIONY = 0.0f;						//回転Y
static const int   ENEMY_RE_COOL = 180;							//パトロールに戻る


//----------------------
// コンストラクタ
//----------------------
Gimmick::Gimmick()
{
	Init();
}

//----------------------
// デストラクタ
//----------------------
Gimmick::~Gimmick()
{
	Exit();  // 念のためモデルデータを破棄
}

//----------------------
// 初期化
//----------------------
void Gimmick::Init()
{
	m_radius = ENEMY_SIZE;	//敵の当たり判定
	m_isActive = true;
	m_hndl = HNDL_INIT;
	m_Dhndl = HNDL_INIT;
	Condition_ID = PATROL;
	m_rotationY = ENEMY_ROTATIONY;
	m_rootHndl = HNDL_INIT;
	m_RePatrol = ZERO_I;

	MV1SetPosition(m_hndl, { 500.0f, -15.0f, 300.0f });

	// 0番目のルートに配置したので、次の目的地は1
	//
	m_rootID = 1;

}

//--------------------------
// モデルデータのロード
//--------------------------
void Gimmick::Load(int Ahndl, int danagerHndl)
{
	// ロードされていなければする
	if (m_hndl == -1)
	{
		m_hndl = MV1DuplicateModel(Ahndl);
	}
	if (m_Dhndl == -1)
	{
		m_Dhndl = MV1DuplicateModel(danagerHndl);
	}
	if (m_rootHndl == -1)
	{
		m_rootHndl = MV1LoadModel("data/field/Map01/Map01_GimmickRoot_01.mv1");
	}
}

//--------------------------
// 終了時の破棄
//--------------------------
void Gimmick::Exit()
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
void Gimmick::Step(VECTOR P_pos, int level, VECTOR D_pos)
{
	MV1SetPosition(m_rootHndl, { 500.0f, -15.0f, 300.0f });
	MV1SetScale(m_rootHndl, VGet(0.8f, 1.0f, 0.8f));

}

//------------------------
// 更新
//------------------------
void Gimmick::Update()
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
void Gimmick::Draw()
{
	if (!m_isActive) return;

	MV1DrawModel(m_hndl);

	DrawFormatString(1200, 500, GetColor(25, 200, 100), "EposX:%f", m_Pos.x);
	DrawFormatString(1200, 650, GetColor(25, 200, 100), "EposY:%f", m_Pos.y);
	DrawFormatString(1200, 600, GetColor(25, 200, 100), "EposZ:%f", m_Pos.z);
	DrawFormatString(1200, 700, GetColor(25, 200, 100), ":%d", m_rootID);

	MV1DrawModel(m_rootHndl);
	DrawSphere3D(GetCenter(), m_radius, 16, GetColor(255, 0, 255), GetColor(255, 0, 255), true);

	////DrawFormatString(1200, 800, GetColor(25, 200, 100), "x:%f",m_remove_pos.x);
	////DrawFormatString(1200, 900, GetColor(25, 200, 100), "z:%f", m_remove_pos.z);

	DrawEye();
}

//------------------------
// 敵をリクエスト
//------------------------
bool Gimmick::Request(const VECTOR& pos)
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
VECTOR Gimmick::GetCenter()
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
void Gimmick::HitCale()
{
	// 生存フラグを消す
	Condition_ID = STAN;

}




