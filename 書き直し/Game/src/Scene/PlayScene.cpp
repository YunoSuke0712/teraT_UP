#include"PlayScene.h"
#include"../lib/Sound/SoundManager.h"
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
		m_fade.RequestFadeIn();



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
		m_fade.RequestFadeIn();
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
	CData* data = CData::GetInstance();

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
		//m_line.Draw(m_player, SPZ_POS, m_goal.GetPos(),m_item.GetLevel());
		// 
		m_camera.Draw();
		m_effect.Draw();
		m_message.Draw();
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
	m_field.Init();
	m_player.Init();
	m_enemy.Init();
	m_gimmick.Init();
	m_message.Init();


	m_camera.Init();


	m_effect.Init(10,2000);
	m_effect.SetProjectionMtx(DX_PI_F / 4.0f, WINDOW_SIZE_X / WINDOW_SIZE_Y, Near, Far);

}

//----------------------
// データロード
//----------------------
void PlayScene::Load()
{
	CData* data = CData::GetInstance(); ////Dataはこれをコピーして頭に張り付ける

	m_field.Load(data->GetPlayMapID());
	m_player.Load();
	m_enemy.Load(data->GetPlayMapID());
	m_gimmick.Load(data->GetPlayMapID());
	m_effect.Load();
	m_message.Load();
	
}

//----------------------
// カメラの座標計算
//----------------------
void PlayScene::Step()
{
	CData* data = CData::GetInstance();


	m_field.Step();
	m_player.Step(m_camera.GetRot());
	m_enemy.Step(m_player.GetPosition(),1,{1,1,1});
	m_gimmick.Step(m_player,m_effect);
	m_message.Step();


	//コリジョン
	m_col.CheckHitFieldToPlayer(m_field, m_player);
	m_col.CheckHitFieldToEnemy(m_field, m_enemy);
	m_col.CheckHitPlayerToEnemy(m_player, m_enemy,m_field, m_effect);
	m_col.CheckHitGimmickToPlayer(m_gimmick, m_player);

	//


	// プレイヤーの生存フラグが消えたら、ゲーム終了へ
	if (m_player.IsActive() == false)
	{
		m_state = END;
	}
	if (m_player.IsGoal() == true)
	{
		m_state = CLEAR;
	}



	// すべての結果を反映させる===================
	m_field.Updata();
	m_player.Update();
	m_enemy.Update();
	m_gimmick.Update();

	m_camera.Step(m_player.GetPosition(), m_player.GetRotationY());
	m_camera.Update();

	m_effect.SetCameraRotMtx(m_camera.GetPlayCameraPos(), m_camera.GetRot(), VGet(0.0f, 1.0f, 0.0f));
	m_effect.Update();
}

//----------------------
//	終了処理
//----------------------
void PlayScene::Exit()
{
	m_field.Exit();
	m_player.Exit();
	m_enemy.Exit();
	m_gimmick.Exit();
	m_effect.Exit();
	m_message.Exit();

}




