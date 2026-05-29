#include "field.h"
#include<math.h>
#include"../lib/common/common.h"

//ブレンダー保存サイズ　0.1

static const VECTOR fieldPos{ 500.0f,-15.0f,300.0f };		//背景の位置
static const VECTOR fieldScale{ 0.8f,1.0f,0.8f };		    //背景のサイズ
static const VECTOR skyScale{ 20.0f,20.0f,20.0f };			//背景のサイズ
static const VECTOR skyPos{ 0.0f,0.0f,0.0f };				//背景の位置
static const float  skyRot{ 0.001f };

Field::Field()
{
	Init();
}

Field::~Field()
{
	Field::Exit();
}

void Field::Init()
{
	m_hndl = HNDL_INIT;
	m_hndl = HNDL_INIT;
	m_skyhndll = HNDL_INIT;
	m_vPos = fieldPos;            // 座標

	SkyRotY = 0;
}


void Field::Load(int mapID)
{

	switch (mapID)
	{
	case 1:
		if (m_hndl == -1)
		{
			m_hndl = MV1LoadModel("data/model/field/Map01/Map_01.mv1");
		}
		break;
	case 2:
		if (m_hndl == -1)
		{
			m_hndl = MV1LoadModel("data/model/field/Map02/Map_02.mv1");
			//子リジョン情報構築
		}
	case 3:
		if (m_hndl == -1)
		{
			m_hndl = MV1LoadModel("data/model/field/Map03/Map_03.mv1");
			//子リジョン情報構築
		}
		break;
	}


	

	if (m_skyhndll == -1)
	{
		m_skyhndll = MV1LoadModel("data/model/sky/sky.mv1");
	}


}



void Field::Step()
{
	SkyRotY += 0.001f;

	//HitCheck(Player & player);
	//HitCheck(EnemyManager & enemy);

}


void Field::Updata()
{
	MV1SetPosition(m_hndl, m_vPos);

	MV1SetScale(m_hndl, fieldScale);
	MV1SetScale(m_skyhndll, skyScale);

	MV1SetupCollInfo(m_hndl);

	VECTOR rot{ 0.0,SkyRotY,0.0f };
	MV1SetRotationXYZ(m_skyhndll, rot);

}



void Field::Exit()
{
	if (m_hndl != -1) {
		m_hndl = -1;
		MV1DeleteModel(m_hndl);
		//念のため不要になったコリジョン情報を削除
		MV1TerminateCollInfo(m_hndl);
		MV1DeleteModel(m_hndl);
		m_hndl = -1;
	}

	if (m_skyhndll != -1) {
		m_skyhndll = -1;
		MV1DeleteModel(m_skyhndll);
	}

}

void Field::Draw()
{
	MV1DrawModel(m_hndl);
	MV1DrawModel(m_skyhndll);
}

////プレイヤーと当たり判定
//void Field::HitCheck(Player& player)
//{
//	VECTOR p_pos = player.GetCenter();
//	float p_radius = player.GetRadius() +3.0f;
//	player.SetJumpNot();
//
//	VECTOR out = { 0.0f };
//	bool m_isHitFlag = false;
//	MV1_COLL_RESULT_POLY_DIM res;	//当たり判定情報が格納される構造体
//	MV1RefreshCollInfo(m_hndl);
//	res = MV1CollCheck_Sphere(m_hndl, -1, p_pos, p_radius);
//	//res[1] = MV1CollCheck_Sphere(m_Pdoor_hndl, -1, p_pos, p_radius);
//
//	if (res.HitNum != 0)
//	{
//		m_isHitFlag = true;
//	
//	}
//	if (m_isHitFlag == true)
//	{	// 最も深く当たっているポリゴンに基づいて押し戻し処理
//		for (int i = 0; i < res.HitNum; ++i)
//		{
//			VECTOR Norm = res.Dim[i].Normal;
//
//			//	ヒットしたポリゴンとヒットした物体のめり込んだ距離を求める
//			VECTOR	sub = VSub(res.Dim[i].HitPosition, p_pos);
//			float	len = VSize(sub);
//			len = p_radius - len;
//			// めり込んだ距離分だけ外に押し出す　押し出す方向は法線の方向
//			VECTOR	line = VScale(Norm, len);
//			out = VAdd(out, line);
//			//out.y += 0.3;
//			if (Norm.y > 0.8)
//			{
//				player.SetJumpNow();
//			}
//		}
//	}
//	player.SetPosition(VAdd(player.GetPosition(), out));
//	//毎回データを削除する
//	MV1CollResultPolyDimTerminate(res);
//}
//
////プレイヤーとギミックオブジェ当たり判定
//void Field::HitCheckDoor(Player& player, ItemSlot& item)
//{
//	for (int GIMMICK_ID = 0;GIMMICK_ID < GIMMICK_MAX;GIMMICK_ID++)
//	{
//		if (!m_Gimmick_active[GIMMICK_ID])return;
//		
//		VECTOR p_pos = player.GetCenter();
//		float p_radius = player.GetRadius();
//		VECTOR out = { 0.0f };
//		bool m_isHitFlag = false;
//		MV1_COLL_RESULT_POLY_DIM res;	//当たり判定情報が格納される構造体
//		res = MV1CollCheck_Sphere(m_Gimmick_hndl[GIMMICK_ID], -1, p_pos, p_radius);
//
//		if (GIMMICK_ID == 1)continue;
//
//
//		if (res.HitNum != 0)
//		{
//			m_isHitFlag = true;
//		}
//		if (m_isHitFlag == true)
//		{	// 最も深く当たっているポリゴンに基づいて押し戻し処理
//			for (int i = 0; i < res.HitNum; ++i)
//			{
//				VECTOR Norm = res.Dim[i].Normal;
//
//
//				//	ヒットしたポリゴンとヒットした物体のめり込んだ距離を求める
//				VECTOR	sub = VSub(res.Dim[i].HitPosition, p_pos);
//				float	len = VSize(sub);
//				len = p_radius - len;
//				// めり込んだ距離分だけ外に押し出す　押し出す方向は法線の方向
//				VECTOR	line = VScale(Norm, len);
//				out = VAdd(out, line);
//			}
//		}
//		player.SetPosition(VAdd(player.GetPosition(), out));
//		//毎回データを削除する
//		MV1CollResultPolyDimTerminate(res);
//
//		switch (GIMMICK_ID)
//		{
//		case 0:
//			if (item.GetUseItemID() == KEY)
//			{
//				//SetGimmickActive(0, false);
//				//m_Gimmick_active[0] = false;
//
//			}
//			break;
//		case 1:
//			break;
//		}
//	}
//}
//
//
////敵Aの壁当たり判定
//void Field::HitCheckA(EnemyManager& enemy)
//{
//	for (int ENEMY_ID = 0; ENEMY_ID < ENEMYA_MAX_NUM; ENEMY_ID++)
//	{
//		VECTOR result = { 0.0f };
//		//当たり判定情報が格納される構造体
//		MV1_COLL_RESULT_POLY_DIM col;
//
//		EnemyA& oneEnemy = enemy.GetEnemyA(ENEMY_ID);
//		VECTOR pos = oneEnemy.GetCenter();
//		float radius = oneEnemy.GetRadius();
//
//		//いったんフラグをオフ
//		bool m_isHitFlag = false;
//		//ポリゴンと弾の当たり判定
//		col = MV1CollCheck_Sphere(m_hndl, -1, pos, radius);
//		//ポリゴンと当たっていた
//		if (col.HitNum != 0)
//		{
//			m_isHitFlag = true;
//			// 最も深く当たっているポリゴンに基づいて押し戻し処理
//			for (int i = 0; i < col.HitNum; ++i)
//			{
//				// プレイヤーの中心から当たった面までのベクトル
//				VECTOR toSurface = VSub(pos, col.Dim[i].HitPosition);
//
//				// 面の法線方向に投影（押し戻すベクトル成分を計算）
//				float penetrationDepth = radius - VDot(toSurface, col.Dim[i].Normal);
//
//				if (penetrationDepth > 0.0f)
//				{
//					// 法線方向に押し戻すベクトル
//					VECTOR pushBack = VScale(col.Dim[i].Normal, penetrationDepth);
//					// プレイヤーを少しだけ押し戻す（複数の面に当たる可能性があるので加算)
//					//pushBack = VAdd(pushBack, pushBack);
//					result = VAdd(result, pushBack);
//					//result = VAdd(result, pushBack);
//				}
//			}
//			//// プレイヤー位置補正
//			oneEnemy.SetPosition(VAdd(oneEnemy.GetPosition(), result));
//		}
//		//毎回データを削除する
//		MV1CollResultPolyDimTerminate(col);
//	}
//}
//
////敵Bの壁当たり判定
//void Field::HitCheckB(EnemyManager& enemy)
//{
//	for (int ENEMY_ID = 0; ENEMY_ID < ENEMYB_MAX_NUM; ENEMY_ID++)
//	{
//
//		//生存確認
//		EnemyB& oneEnemy = enemy.GetEnemyB(ENEMY_ID);
//		if (oneEnemy.GetIsActive() == false)continue;
//
//
//		VECTOR result = { 0.0f };
//		//当たり判定情報が格納される構造体
//		MV1_COLL_RESULT_POLY_DIM col;
//		VECTOR pos = oneEnemy.GetCenter();
//		float radius = oneEnemy.GetRadius();
//
//		//いったんフラグをオフ
//		bool m_isHitFlag = false;
//		//ポリゴンと弾の当たり判定
//		col = MV1CollCheck_Sphere(m_hndl, -1, pos, radius);
//		//ポリゴンと当たっていた
//		if (col.HitNum != 0)
//		{
//			m_isHitFlag = true;
//		
//			// 最も深く当たっているポリゴンに基づいて押し戻し処理
//			for (int i = 0; i < col.HitNum; ++i)
//			{
//				// プレイヤーの中心から当たった面までのベクトル
//				VECTOR toSurface = VSub(pos, col.Dim[i].HitPosition);
//
//				// 面の法線方向に投影（押し戻すベクトル成分を計算）
//				float penetrationDepth = radius - VDot(toSurface, col.Dim[i].Normal);
//
//				if (penetrationDepth > 0.0f)
//				{
//					// 法線方向に押し戻すベクトル
//					VECTOR pushBack = VScale(col.Dim[i].Normal, penetrationDepth);
//					// プレイヤーを少しだけ押し戻す（複数の面に当たる可能性があるので加算)
//					//pushBack = VAdd(pushBack, pushBack);
//					result = VAdd(result, pushBack);
//					//result = VAdd(result, pushBack);
//					if ((pushBack.x > 0.2 || pushBack.x < 0.8 || pushBack.z >0.2 || pushBack.z < 0.8)&&pushBack.y < 0.2)
//					{
//						oneEnemy.SetPosYUp();
//			
//					}
//					if (pushBack.y > 0.8)
//					{
// 						oneEnemy.SetGravity(false);
//					}
//				}
//			}
//
//			//// プレイヤー位置補正
//			oneEnemy.SetPosition(VAdd(oneEnemy.GetPosition(), result));
//		}
//		oneEnemy.SetGravity(true);
//
//		//毎回データを削除する
//		MV1CollResultPolyDimTerminate(col);
//	}
//}
//
////敵Aのぼたんあたり判定
//bool Field::HitCheckEnemyA_Button(EnemyManager& enemy)
//{
//	for (int ENEMY_ID = 0; ENEMY_ID < ENEMYA_MAX_NUM; ENEMY_ID++)
//	{
//		EnemyA& oneEnemy = enemy.GetEnemyA(ENEMY_ID);
//
//
//		VECTOR result = { 0.0f };
//		//当たり判定情報が格納される構造体
//		MV1_COLL_RESULT_POLY_DIM col;
//
//		VECTOR pos = oneEnemy.GetCenter();
//		float radius = oneEnemy.GetRadius();
//
//		//いったんフラグをオフ
//		bool m_isHitFlag = false;
//		//ポリゴンと弾の当たり判定
//		col = MV1CollCheck_Sphere(m_Gimmick_hndl[1], -1, pos, radius);
//		//ポリゴンと当たっていた
//		if (col.HitNum != 0)
//		{
//			m_isHitFlag = true;
//			//m_Gimmick_active[2] = false;
//			return true;
//		}
//
//		//毎回データを削除する
//		MV1CollResultPolyDimTerminate(col);
//	}
//	return false;
//}