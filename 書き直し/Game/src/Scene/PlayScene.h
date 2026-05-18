#pragma once

//=========================================
#include"../Field/field.h"
#include"../Player/Player.h"
#include"../Enemy/EnemyManager.h"
#include"../Gimmick/GimmickManager.h"

//
#include"../Camera/CameraManager.h"
#include "../Collision/CollisionManager.h"

#include "../lib/Fade/Fade.h"

//=========================================

// 複数のカメラを管理する
class PlayScene {
private:
	// ゲームの処理の流れ
	enum tagScene {
		INIT,   // データ初期化
		LOAD,   // データ読み込み
		MAIN,   // ゲーム本編実行
		END ,    // 終了前のデータ破棄
		CLEAR,
	};

	tagScene m_state;         // 現在の状態遷移

	//===============================================
	Field m_field;
	Player m_player;
	EnemyManager m_enemy;
	GimmickManager m_gimmick;

	CameraManager m_camera;   // カメラ
	CollisionManager m_col;
	CFade m_fade;
	//CFade m_fade;
	
	//===============================================

public:
	// コンストラクタ・デストラクタ
	PlayScene();
	~PlayScene();

	// 実行処理
	int Loop();
	// 描画処理
	void Draw();





private:
	// 初期化
	void Init(void);
	// 終了処理
	void Exit();
	// データロード
	void Load();
	// 毎フレーム呼ぶ処理
	void Step();
};