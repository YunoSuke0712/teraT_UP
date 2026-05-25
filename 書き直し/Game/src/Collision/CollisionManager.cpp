#include"CollisionManager.h"
#include"../lib/Collision/collision.h"
#include"../lib/MyMath/MyMath.h"
#include"../lib/input/input.h"
#include"../lib/input/PadInput.h"
#include "../lib/Common/common.h"

static const float ENEMY_EYE_SIZE = { 35.0f };//敵の視界サイズ
static const float ENEMY_DECOY_SIZE = { 25.0f };//敵の視界サイズ
static const float ENEMY_EYE_RELEASE = { 100.0f };//敵が見失う距離
static const float ENEMYB_EYE_SIZE = { 75.0f };
static const float ENEMY_WALL_SIZE = { 100.0f };


//フィールドプレイヤー
void CollisionManager::CheckHitFieldToPlayer(Field& fi, Player& pl)
{
    const int ITERATION = 10; // 繰り返し回数

    float p_radius = pl.GetRadius()+3.0f;
    VECTOR pos = pl.GetPosition();

    for (int iter = 0; iter < ITERATION; ++iter)
    {
        VECTOR p_pos = pl.GetCenter(); // 中心は毎回更新
        MV1_COLL_RESULT_POLY_DIM res;

        MV1RefreshCollInfo(fi.GetFieldHndl());
        res = MV1CollCheck_Sphere(fi.GetFieldHndl(), -1, p_pos, p_radius);

        if (res.HitNum == 0)
        {
            MV1CollResultPolyDimTerminate(res);
            break;
        }

        float maxLen = 0.0f;
        VECTOR bestPush = { 0.0f, 0.0f, 0.0f };

        for (int i = 0; i < res.HitNum; ++i)
        {
            VECTOR Norm = res.Dim[i].Normal;

            VECTOR sub = VSub(res.Dim[i].HitPosition, p_pos);
            float len = VSize(sub);
            len = p_radius - len;

            if (len <= 0.0f) continue;

            // 一番深いものだけ選ぶ
            if (len > maxLen)
            {
                maxLen = len;
                bestPush = VScale(Norm, len);
            }
        }

        // 押し出し
        pos = VAdd(pos, bestPush);
        pl.SetPosition(pos);

        MV1CollResultPolyDimTerminate(res);

        // ほぼ押し出し終わったら終了
        if (maxLen < 0.001f) break;
    }
}

//フィールドエネミー
void CollisionManager::CheckHitFieldToEnemy(Field& fi, EnemyManager& ene)
{
    const int ITERATION = 3; // 繰り返し回数

    for (int i = 0;i < ene.GetEnemyANum();i++)
    {
        EnemyA* OneEnemy = ene.GetOneEnemyA(i);
        if (OneEnemy->GetIsActive() == false) continue;

        float  e_radius = OneEnemy->GetRadius()+1.0f;
        VECTOR pos = OneEnemy->GetPosition();


        for (int iter = 0; iter < ITERATION; ++iter)
        {
            VECTOR e_pos = OneEnemy->GetCenter();
            MV1_COLL_RESULT_POLY_DIM res;

            MV1RefreshCollInfo(fi.GetFieldHndl());
            res = MV1CollCheck_Sphere(fi.GetFieldHndl(), -1, e_pos, e_radius);

            if (res.HitNum == 0)
            {
                MV1CollResultPolyDimTerminate(res);
                break;
            }

            float maxLen = 0.0f;
            VECTOR bestPush = { 0.0f, 0.0f, 0.0f };

            for (int i = 0; i < res.HitNum; ++i)
            {
                VECTOR Norm = res.Dim[i].Normal;

                VECTOR sub = VSub(res.Dim[i].HitPosition, e_pos);
                float len = VSize(sub);
                len = e_radius - len;

                if (len <= 0.0f) continue;

                // 一番深いものだけ選ぶ
                if (len > maxLen)
                {
                    maxLen = len;
                    bestPush = VScale(Norm, len);
                }
            }

            // 押し出し
            pos = VAdd(pos, bestPush);
            OneEnemy->SetPosition(pos);

            MV1CollResultPolyDimTerminate(res);

            // ほぼ押し出し終わったら終了
            if (maxLen < 0.001f) break;
        }
    }
}

////プレイヤーエネミー
//void CollisionManager::CheckHitPlayerToEnemy(Player& pl, EnemyManager& ene)
//{
//
//    for (int i = 0;i < ene.GetEnemyANum();i++)
//    {
//        EnemyA* OneEnemy = ene.GetOneEnemyA(i);
//        if (OneEnemy->GetIsActive() == false) continue;
//
//        float  e_radius = OneEnemy->GetRadius();
//        VECTOR e_pos = OneEnemy->GetPosition();
//        float p_radius = pl.GetRadius();
//        VECTOR p_pos = pl.GetPosition();
//
//        VECTOR e_center = OneEnemy->GetCenter();
//        VECTOR p_center = pl.GetCenter();
//
//
//        // 当たり判定開始
//        bool isHit = Collision::CheckHitSphereToSphere(p_center, p_radius, e_center, e_radius);
//   
//        if (isHit == true)
//        {
//            //// お互い当たった！！
//            pl.HitEnemyCale();
//            
//        }
//    
//    
//    }
//}

//プレイヤーエネミー
void CollisionManager::CheckHitPlayerToEnemy(Player& pl, EnemyManager& ene)
{
    for (int i = 0; i < ene.GetEnemyANum(); i++)
    {
        EnemyA* OneEnemy = ene.GetOneEnemyA(i);

        if (OneEnemy->GetIsActive() == false) continue;
        if (OneEnemy->GetCondition() == STAN) continue;

        //--------------------------------
        // 座標取得
        //--------------------------------
        VECTOR e_pos = OneEnemy->GetCenter();
        VECTOR p_pos = pl.GetCenter();

        //--------------------------------
        // Enemy → Player方向
        //--------------------------------
        VECTOR toPlayer = VSub(p_pos, e_pos);

        //--------------------------------
        // 距離
        //--------------------------------
        float dist = VSize(toPlayer);

        // 視界距離
        const float VIEW_RANGE = 200.0f;

        // 距離外
        if (dist > VIEW_RANGE) continue;

        //--------------------------------
        // 正規化
        //--------------------------------
        toPlayer = VNorm(toPlayer);

        //--------------------------------
        // Enemyの向き
        //--------------------------------
        VECTOR enemyDir = OneEnemy->GetDir();

        enemyDir = VNorm(enemyDir);

        //--------------------------------
        // 内積
        //--------------------------------
        float dot = VDot(enemyDir, toPlayer);

        //--------------------------------
        // 視野角判定
        //--------------------------------
        // 90度視野
        // cos(45°) = 0.707
        //--------------------------------
        if (dot > CosDeg(25.0f))
        {
            //--------------------------------
            // プレイヤー発見
            //--------------------------------

            OneEnemy->SetFindPlayer(true);
            OneEnemy->SetCondition(TRACKING_P);

            //--------------------------------
            // 接触判定
            //--------------------------------
            float e_radius = OneEnemy->GetRadius();
            float p_radius = pl.GetRadius();

            VECTOR e_center = OneEnemy->GetCenter();
            VECTOR p_center = pl.GetCenter();

            bool isHit = Collision::CheckHitSphereToSphere(p_center, p_radius, e_center, e_radius);

            if (isHit == true)
            {
                pl.HitEnemyCale();
            }
        }
        else
        {
            //--------------------------------
            // 見失った
            //--------------------------------
            OneEnemy->SetFindPlayer(false);
        }
    }
}
          

void CollisionManager::CheckHitGimmickToPlayer(
    GimmickManager& gim,
    Player& pl)
{
    const int ITERATION = 10;

    //--------------------------------
    // Ori全取得
    //--------------------------------
    for (int i = 0; i < gim.GetGimmickNum(); i++)
    {
        Ori* oneOri = gim.GetOneOri(i);

        //--------------------------------
        // 非アクティブ
        //--------------------------------
        if (oneOri->GetIsActive() == false)
        {
            continue;
        }

        //--------------------------------
        // プレイヤー情報
        //--------------------------------
        float p_radius = pl.GetRadius();

        VECTOR pos = pl.GetPosition();

        //--------------------------------
        // 押し出し
        //--------------------------------
        for (int iter = 0; iter < ITERATION; iter++)
        {
            VECTOR p_pos = pl.GetCenter();

            //--------------------------------
            // Ori更新
            //--------------------------------
            MV1RefreshCollInfo(
                oneOri->GetHndl()
            );

            //--------------------------------
            // モデル衝突
            //--------------------------------
            MV1_COLL_RESULT_POLY_DIM res =
                MV1CollCheck_Sphere(
                    oneOri->GetHndl(),
                    -1,
                    p_pos,
                    p_radius
                );

            //--------------------------------
            // 当たっていない
            //--------------------------------
            if (res.HitNum == 0)
            {
                MV1CollResultPolyDimTerminate(res);
                break;
            }

            //--------------------------------
            // 最大押し出し
            //--------------------------------
            float maxLen = 0.0f;

            VECTOR bestPush = { 0,0,0 };

            for (int j = 0; j < res.HitNum; j++)
            {
                VECTOR norm =
                    res.Dim[j].Normal;

                VECTOR sub =
                    VSub(
                        res.Dim[j].HitPosition,
                        p_pos
                    );

                float len = VSize(sub);

                len = p_radius - len;

                if (len <= 0.0f)
                {
                    continue;
                }

                //--------------------------------
                // 一番深いもの
                //--------------------------------
                if (len > maxLen)
                {
                    maxLen = len;

                    bestPush =
                        VScale(norm, len);
                }
            }

            //--------------------------------
            // プレイヤー押し出し
            //--------------------------------
            pos = VAdd(pos, bestPush);

            pl.SetPosition(pos);

            //--------------------------------
            // 解放
            //--------------------------------
            MV1CollResultPolyDimTerminate(res);

            //--------------------------------
            // 終了
            //--------------------------------
            if (maxLen < 0.001f)
            {
                break;
            }
        }
    }
}