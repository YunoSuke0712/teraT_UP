#pragma once
#include"../camera/CameraManager.h"
#include"../Player/Player.h"
#include"../Field/field.h"
#include"../Enemy/EnemyManager.h"

// 各種オブジェクトの当たり判定クラス
class CollisionManager {
public:


	static void CheckHitFieldToPlayer(Field& fi,Player& pl);

	static void CheckHitPlayerToEnemy(Player& pl, EnemyManager& ene);















	//======下前データ

	//// ITEMAの弾と敵Aの当たり判定
	//static void CheckHitShotToEnemyA(ShotManager& shot, EnemyManager& enemy, Player& player);
	//// プレイヤーと敵Aの当たり判定
	//static void CheckHitPlayerToEnemyA(Player& player, EnemyManager& enemy);
	//// デコイと敵Aの当たり判定
	//static VECTOR CheckHitDecoyToEnemyA(ShotManager& decoy, EnemyManager& enemy);

	//// ITEMAの弾と敵Bの当たり判定
	//static void CheckHitShotToEnemyB(ShotManager& shot, EnemyManager& enemy, Player& player);
	//// プレイヤーと敵Aの当たり判定
	//static void CheckHitPlayerToEnemyB(Player& player, EnemyManager& enemy);
	//// デコイと敵Bの当たり判定
	//static VECTOR CheckHitDecoyToEnemyB(ShotManager& decoy, EnemyManager& enemy);


	//// プレイヤーとItemの当たり判定
	//static void CheckHitPlayerToItem(Player& player, ItemManager& item,ItemSlot& slot);
	//// プレイヤーとSPItemの当たり判定
	//static void CheckHitPlayerToSPItem(Player& player, ItemManager& item, ItemSlot& slot);
	//// プレイヤーとgoalの当たり判定
	//static void CheckHitPlayerToGoal(Player& player, Goal& goal);

	////壁越し
	//static bool IsEnemyBehindWall(const VECTOR& playerPos, const VECTOR& enemyPos, int mapModelHandle);
	//壁越し修正
	//static bool AIsEnemyBehindWall(Player& playerpos, EnemyManager& enemypos, int mapModelHandle);

	//static bool CheckHitPlayerToEnemyA_Wall(Player& player, EnemyManager& enemy);
	
};



