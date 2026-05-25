#include"TreasureGoal.h"
#include<math.h>
#include "../Field/field.h"

static const VECTOR GIMMICK_SCALE{ 0.1f,0.1f,0.1f };					//サイズ
static const float WARP_SIZE = 5.0f;									//当たり判定

static const float MaxDownPos = -200;
//----------------------
// コンストラクタ
//----------------------
TreasureGoal::TreasureGoal()
{
	Init();
}

//----------------------
// デストラクタ
//----------------------
TreasureGoal::~TreasureGoal()
{
	Exit();  // 念のためモデルデータを破棄
}

//----------------------
// 初期化
//----------------------
void TreasureGoal::Init()
{
	for (int i = 0;i < TreasureGoalMaxNum;i++)
	{
		m_radius[i] = WARP_SIZE;	//敵の当たり判定
		m_hndl[i] = HNDL_INIT;
		m_rotationY[i] = ZERO_F;

	}

	m_isActive[0] = true;
	m_isActive[1] = false;


}

//--------------------------
// モデルデータのロード
//--------------------------
void TreasureGoal::Load(int Ahndl, int Bhndl)
{
	for (int i = 0;i < TreasureGoalMaxNum;i++)
	{
		// ロードされていなければする
		if (m_hndl[i] == -1)
		{
			m_hndl[i] = MV1DuplicateModel(Ahndl);
		}
	}

	m_hndl[0] = MV1DuplicateModel(Ahndl);
	m_hndl[1] = MV1DuplicateModel(Bhndl);
	MV1SetPosition(m_hndl[0], GetPositionA());
	MV1SetPosition(m_hndl[1], GetPositionB());
	MV1SetScale(m_hndl[0], GIMMICK_SCALE);
	MV1SetScale(m_hndl[1], GIMMICK_SCALE);


}

//--------------------------
// 終了時の破棄
//--------------------------
void TreasureGoal::Exit()
{
	for (int i = 0;i < TreasureGoalMaxNum;i++)
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
void TreasureGoal::Step(Player& player)
{
	bool Active = false;

	if (!Active)
	{
		VECTOR targetPos = player.GetCenter();
		// 自分の座標取得
		VECTOR pos = GetCenterA();
		// 目的地へのベクトル取得
		VECTOR dir = VSub(targetPos, pos);
		// 目的地までの距離を取得
		float len = VSize(dir);
		// 目的地までの距離が一定範囲内なら
		if (len < 15.0f)
		{
			if (Active == false && m_input.IsInputTrg(KEY_CLICK) && m_isActive[0])
			{
				m_isActive[0] = false;
				m_isActive[1] = true;
				
			}
		}
	}

	if (m_isActive[1]) 
	{

		VECTOR targetPos = player.GetCenter();
		// 自分の座標取得
		VECTOR pos = GetCenterB();
		// 目的地へのベクトル取得
		VECTOR dir = VSub(targetPos, pos);
		// 目的地までの距離を取得
		float len = VSize(dir);
		// 目的地までの距離が一定範囲内なら
		if (len < 15.0f)
		{
			if (Active == false && m_input.IsInputTrg(KEY_CLICK))
			{
				player.SetGoal(true);
			}
		}
	}
	


}

//------------------------
// 更新
//------------------------
void TreasureGoal::Update()
{
	MV1SetPosition(m_hndl[0], GetPositionA());
}

//------------------------
// 描画
//------------------------
void TreasureGoal::Draw()
{

	if (m_isActive[0]) MV1DrawModel(m_hndl[0]);
	if (m_isActive[1]) MV1DrawModel(m_hndl[1]);

	//DrawFormatString(1200, 500, GetColor(25, 200, 100), "EposX:%f", m_Pos.x);
	//DrawFormatString(1200, 650, GetColor(25, 200, 100), "EposY:%f", m_Pos.y);
	//DrawFormatString(1200, 600, GetColor(25, 200, 100), "EposZ:%f", m_Pos.z);

	DrawSphere3D(GetCenterA(), m_radius[0], 16, GetColor(255, 0, 255), GetColor(255, 0, 255), true);
	DrawSphere3D(GetCenterB(), m_radius[1], 16, GetColor(255, 255, 255), GetColor(255, 255, 255), true);

	//DrawFormatString(1200, 600, GetColor(25, 200, 100), "A:%f,%f,%f", m_Pos[0].x, m_Pos[0].y, m_Pos[0].z);
	//DrawFormatString(1200, 650, GetColor(25, 200, 100), "B:%f,%f,%f", m_Pos[1].x, m_Pos[1].y, m_Pos[1].z);


}

//------------------------
// 敵をリクエスト//未使用
//------------------------
bool TreasureGoal::Request(const VECTOR& pos)
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
VECTOR TreasureGoal::GetCenterA()
{
	// 基本は物体の座標の位置
	VECTOR res = m_Pos[0];
	// 高さだけ足元から球の半径分上げる
	res.y += m_radius[0];

	return res;
}

// 当たり判定の座標系
VECTOR TreasureGoal::GetCenterB()
{
	// 基本は物体の座標の位置
	VECTOR res = m_Pos[1];
	// 高さだけ足元から球の半径分上げる
	res.y += m_radius[1];

	return res;
}

//y




