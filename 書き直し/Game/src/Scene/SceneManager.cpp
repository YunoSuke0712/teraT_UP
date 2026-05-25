#include"SceneManager.h"
#include"../lib/Sound/SoundManager.h"
#include"../lib/input/PadInput.h"


//----------------------
// コンストラクタ
//----------------------
SceneManager::SceneManager()
{
	m_sceneID = TITLE;

	SoundManager::Init();
	SoundManager::Load();



	//キー入力情報の初期化
	m_input.InitInput();
	CGamePad::InitGamePad();
	CGamePad::GetPadNumState();

	//fade
	m_fade.InitFade();

	
}


SceneManager::~SceneManager()
{
	SoundManager::Exit();
}
//------------------------
// 毎フレーム呼ぶ処理
//------------------------
int SceneManager::Loop()
{
	CGamePad::StepGamePad();
	// ゲームが終了したかを外部に伝えるため
	int result = -1;

	//キー入力情報を更新
	m_input.UpdateInput();

	switch (m_sceneID)
	{
	case SceneManager::INIT:
		break;
	case SceneManager::TITLE:
		if (m_title.Loop() != -1)
			m_sceneID = GAME;
		break;
	case SceneManager::GAME:
	{
		int result = m_play.Loop();
		if (result == 0)
		{
			m_sceneID = SceneManager::RESULT;

		}

		if (result == 1)
		{
			m_sceneID = SceneManager::CLEAR;

		}

		break;
	}
	case SceneManager::RESULT:
		if (m_result.Loop() != -1)
			m_sceneID = TITLE;
		break;

	case SceneManager::CLEAR:
		if (m_clear.Loop() != -1)
			m_sceneID = TITLE;
		break;
	}

	m_fade.StepFade();
	// 本編が終了したかどうかを外部に伝える
	return result;
}

//----------------------
// 
//----------------------
void SceneManager::Draw()
{
	switch (m_sceneID)
	{
	case SceneManager::INIT:
		break;
	case SceneManager::TITLE:
		m_title.Draw();
		DrawFormatString(25, 25, GetColor(255, 255, 0), "たいとる");
		break;
	case SceneManager::GAME:
		m_play.Draw();
		DrawFormatString(25, 25, GetColor(255, 255, 0), "ゲーム画面");
		break;
	case SceneManager::RESULT:
		m_result.Draw();
		DrawFormatString(25, 25, GetColor(255, 255, 0), "りざると");
		break;

	case SceneManager::CLEAR:
		m_clear.Draw();
		DrawFormatString(25, 25, GetColor(255, 255, 0), "くりあ");
		break;
	}

	m_fade.DrawFade();
}




