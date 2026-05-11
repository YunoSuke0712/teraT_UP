#include"PlayScene.h"
#include"../System/SoundManager.h"
#include"../lib/input/input.h"
#include"../lib/input/PadInput.h"




//----------------------
// コンストラクタ
//----------------------
PlayScene::PlayScene()
{
	m_state = INIT;

}

//----------------------
// デストラクタ
//----------------------
PlayScene::~PlayScene()
{
	// 安全のためにデータ破棄処理を呼び出し
	Exit();
}

//------------------------
// 毎フレーム呼ぶ処理
//------------------------
int PlayScene::Loop()
{
	// ゲームが終了したかを外部に伝えるため
	int result = -1;



	switch (m_state)
	{
	case PlayScene::INIT:
		Init();
		
		m_state = PlayScene::LOAD;  // 次へ進む
		break;

	case PlayScene::LOAD:
		Load();
		//ゲーム本編の音を鳴らす
		SoundManager::Play(SoundManager::BGM_GAME,DX_PLAYTYPE_LOOP);
		m_state = PlayScene::MAIN;  // 次へ進む
		break;

	case PlayScene::MAIN:
		Step();

		break;

	case PlayScene::END:
		Exit();
		//全ての音楽を止めて次へ
		SoundManager::AllStop();
		m_state = PlayScene::INIT;  // 次へ進む
		result = 0;
		break;

	case PlayScene::CLEAR:
		Exit();
		//全ての音楽を止めて次へ
		SoundManager::AllStop();
		m_state = PlayScene::INIT;  // 次へ進む
		result = 1;
		break;


	default:
		break;
	}

	// 本編が終了したかどうかを外部に伝える
	return result;
}

//----------------------
// 
//----------------------
void PlayScene::Draw()
{
	switch (m_state)
	{
	case PlayScene::INIT:
		break;
	case PlayScene::LOAD:
		break;
	case PlayScene::MAIN:
		// ===== 3D描画 =====
		
		m_field.Draw();
		m_player.Draw();
		m_enemy.Draw();
		m_gimmick.Draw();
		//m_shot.Draw();
		//m_goal.Draw();
		//m_line.Draw(m_player, SPZ_POS, m_goal.GetPos(),m_item.GetLevel());
		// 
		m_camera.Draw();
		// ===== 壁越しUI =====
		//DrawEnemyBehindWallUI();
		//m_line.DrawEnemyBehindWallUI(m_player, m_camera, m_enemy, m_item.GetLevel());

		// ===== 通常UI =====


		//DataUI

		//if (!data->GetClear())
		//	DrawFormatString(1000, 60, GetColor(255, 255, 25), "AAAAA:%d", data->GetClear());
		//DrawFormatString(1000, 80, GetColor(255, 255, 25), "BBBBB:%d", data->GetItemNum());
		//DrawFormatString(1000, 100, GetColor(255, 255, 25), "CCCCC:%d", data->GetGimicNum());
		//DrawFormatString(1000, 120, GetColor(255, 255, 25), "DDDDD%d", data->GetTime());

		break;
	case PlayScene::END:
		break;
	case PlayScene::CLEAR:
		break;
	default:
		break;
	}


}
//----------------------
// 初期化
//----------------------
void PlayScene::Init()
{
	// それぞれのカメラを初期化

	m_field.Init();
	m_player.Init();
	m_enemy.Init();
	m_gimmick.Init();

	m_camera.Init();


}

//----------------------
// データロード
//----------------------
void PlayScene::Load()
{
	m_field.Load();
	m_player.Load();
	m_enemy.Load();
	m_gimmick.Load();
	
}

//----------------------
// カメラの座標計算
//----------------------
void PlayScene::Step()
{

	m_field.Step();
	m_player.Step(m_camera.GetRot());
	m_enemy.Step(m_player.GetPosition(),1,{1,1,1});
	m_gimmick.Step(m_player.GetPosition());



	// プレイヤーの生存フラグが消えたら、ゲーム終了へ
	if (m_player.IsActive() == false) {m_state = END;}



	//コリジョン
	m_col.CheckHitFieldToPlayer(m_field, m_player);
	m_col.CheckHitFieldToEnemy(m_field, m_enemy);
	m_col.CheckHitPlayerToEnemy(m_player, m_enemy);
	//

	// すべての結果を反映させる===================
	m_field.Updata();
	m_player.Update();
	m_enemy.Update();

	m_camera.Step(m_player.GetPosition(), m_player.GetRotationY());
	m_camera.Update();
}

//----------------------
//	終了処理
//----------------------
void PlayScene::Exit()
{
	m_field.Exit();
	m_player.Exit();
	m_enemy.Exit();
	
}




