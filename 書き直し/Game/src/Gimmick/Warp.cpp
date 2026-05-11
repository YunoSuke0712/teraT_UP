#include"Warp.h"
#include<math.h>
#include"../lib/common/common.h"
#include "../Field/field.h"
#include "../lib/Input/input.h"

static const VECTOR Scale{ 0.03f,0.03f,0.03f };					//敵のサイズ
static const float WARP_SIZE = 5.0f;							//敵の当たり判定


//----------------------
// コンストラクタ
//----------------------
Warp::Warp()
{
	Init();
}

//----------------------
// デストラクタ
//----------------------
Warp::~Warp()
{
	Exit();  // 念のためモデルデータを破棄
}

//----------------------
// 初期化
//----------------------
void Warp::Init()
{
	for (int i = 0;i < WarpMaxNum;i++)
	{
		m_radius[i] = WARP_SIZE;	//敵の当たり判定
		m_isActive[i] = true;
		m_hndl[i] = HNDL_INIT;
		m_rotationY[i] = ZERO_F;
	}

}

//--------------------------
// モデルデータのロード
//--------------------------
void Warp::Load(int Ahndl, int BHndl)
{
	for (int i = 0;i < WarpMaxNum;i++)
	{
		// ロードされていなければする
		if (m_hndl[i] == -1)
		{
			m_hndl[i] = MV1DuplicateModel(Ahndl);
		}
	}
}

//--------------------------
// 終了時の破棄
//--------------------------
void Warp::Exit()
{
	for (int i = 0;i < WarpMaxNum;i++)
	{
		// データをロードしているときだけ削除
		if (m_hndl[i] != -1)
		{
			MV1DeleteModel(m_hndl[i]);
			m_hndl[i] = -1;
		}
	}
}

//------------------------
// 毎フレーム更新
//------------------------
void Warp::Step(VECTOR P_pos)
{
	//MV1SetPosition(m_rootHndl, { 500.0f, -15.0f, 300.0f });
	//MV1SetScale(m_rootHndl, VGet(0.8f, 1.0f, 0.8f));

}

//------------------------
// 更新
//------------------------
void Warp::Update()
{


}

//------------------------
// 描画
//------------------------
void Warp::Draw()
{
	if (!m_isActive[0]) return;
	if (!m_isActive[1]) return;

	for (int i = 0;i < WarpMaxNum;i++)
	{
		MV1DrawModel(m_hndl[i]);
	}

	//DrawFormatString(1200, 500, GetColor(25, 200, 100), "EposX:%f", m_Pos.x);
	//DrawFormatString(1200, 650, GetColor(25, 200, 100), "EposY:%f", m_Pos.y);
	//DrawFormatString(1200, 600, GetColor(25, 200, 100), "EposZ:%f", m_Pos.z);

	DrawSphere3D(GetCenterA(), m_radius[0], 16, GetColor(255, 0, 255), GetColor(255, 0, 255), true);
	DrawSphere3D(GetCenterB(), m_radius[1], 16, GetColor(255, 0, 255), GetColor(255, 0, 255), true);


}

//------------------------
// 敵をリクエスト
//------------------------
bool Warp::Request(const VECTOR& pos)
{
	// すでに発射されている弾は生成失敗
	if (m_isActive[0])return false;
	if (m_isActive[1])return false;


	// 必要な情報を渡していく
	m_isActive[0] = true;
	m_Pos[0] = pos;
	//m_Speed = speed;

	return true;
}

// 当たり判定の座標系
VECTOR Warp::GetCenterA()
{
	// 基本は物体の座標の位置
	VECTOR res = m_Pos[0];
	// 高さだけ足元から球の半径分上げる
	res.y += m_radius[0];

	return res;
}

// 当たり判定の座標系
VECTOR Warp::GetCenterB()
{
	// 基本は物体の座標の位置
	VECTOR res = m_Pos[1];
	// 高さだけ足元から球の半径分上げる
	res.y += m_radius[1];

	return res;
}

//y




