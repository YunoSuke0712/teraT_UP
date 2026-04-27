#include "sceneclearresult.h"
#include <DxLib.h>
#include "../../lib/input/input.h"
#include "../../lib/input/PadInput.h"
#include "../common/common.h"

//#include "../lib/sound.h"
//#include "event.h"



//コンスト・デスト
ClearResult::ClearResult()
{
	m_state = INIT;
}

ClearResult::~ClearResult()
{
	Exit();
}

//＝＝＝＝＝＝＝＝＝＝
//毎フレーム呼ぶ処理
//＝＝＝＝＝＝＝＝＝＝
int ClearResult::Loop()
{
	//ゲームが終了したか外部に伝えるため
	int resurt = -1;

	switch (m_state)
	{
	case ClearResult::INIT:
		Init();
		break;
	case ClearResult::LOAD:
		Load();
		break;
	case ClearResult::STARTWAIT://フェードなどを使う時
		m_state = MAIN;
		break;
	case ClearResult::MAIN:
		Step();

		break;
	case ClearResult::ENDWAIT://フェードなどを使うとき
		m_state = END;
		break;
	case ClearResult::END:
		Exit();
		resurt = 1;
		break;

	}
	return resurt;
}





//がめの状態移管初期化
void ClearResult::Init()
{
	m_hndl = -1;
	m_hndll = -1;
	//最初は初期化へ進む
	m_state = LOAD;

	Data::GetInstance();
	//m_data.SetClear(true);
	//m_data.Init(m_item.GetLevel());
}
//ロード管理
void ClearResult::Load()
{
	Data* data = Data::GetInstance();
	if (m_hndl == -1)
		m_hndl = LoadGraph("data/game/result/Cresult.png");

	m_state = STARTWAIT;

	data->Load();
}

//-----------------------
//リザルト画面の処理管理
//-----------------------
void ClearResult::Step()
{
	if (IsInputTrg(KEY_CLICK)
		|| CGamePad::IsPadPush(DX_INPUT_PAD1, BUTTON_B)
		|| CGamePad::IsPadPush(DX_INPUT_PAD1, BUTTON_A))
	{
		m_state = ENDWAIT;
	}
}

//---------------------------
//	リザルト画面の描画管理
//	-------------------------
void ClearResult::Draw()
{
	Data* data = Data::GetInstance();
	//タイトル画像描画

	DrawRotaGraph((int)(WINDOW_SIZE_X * 0.5f), (int)(WINDOW_SIZE_Y * 0.5f),
		1.0, 0.0, m_hndl, TRUE);

	data->DrawClearScore();
	data->SetHighScore(data->GetScore());
	//if (!data->GetClear())
	//	DrawFormatString(1000, 60, GetColor(255, 255, 25), "AAAAA:%d", data->GetClear());
	//DrawFormatString(1000, 80, GetColor(255, 255, 25), "BBBBB:%d", data->GetItemNum());
	//DrawFormatString(1000, 100, GetColor(255, 255, 25), "CCCCC:%d", data->GetGimicNum());
	//DrawFormatString(1000, 120, GetColor(255, 255, 25), "DDDDD%d", data->GetTime());

}



void ClearResult::Exit()
{
	if (m_hndl != -1)
	{
		DeleteGraph(m_hndl);
		m_hndl = -1;
	}
	Data::DeleteInstance();
	m_state = INIT;
}