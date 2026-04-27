#include"CollisionManager.h"
#include"../lib/Collision/collision.h"
#include"../lib/input/input.h"
#include"../lib/input/PadInput.h"
#include "../lib/Common/common.h"

static const float ENEMY_EYE_SIZE = { 35.0f };//敵の視界サイズ
static const float ENEMY_DECOY_SIZE = { 25.0f };//敵の視界サイズ
static const float ENEMY_EYE_RELEASE = { 100.0f };//敵が見失う距離
static const float ENEMYB_EYE_SIZE = { 75.0f };
static const float ENEMY_WALL_SIZE = { 100.0f };



void CollisionManager::CheckHitFieldToPlayer(Field& fi, Player& pl)
{
    const int ITERATION = 3; // 繰り返し回数

    float p_radius = pl.GetRadius();
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


