#include "sceneresult.h"
#include <DxLib.h>
#include "../lib/input/input.h"
#include "../lib/input/PadInput.h"
#include "../lib/common/common.h"


//コンスト・デスト
Result::Result()
{
	m_state = INIT;
}

Result::~Result()
{
	Exit();
}

//＝＝＝＝＝＝＝＝＝＝
//毎フレーム呼ぶ処理
//＝＝＝＝＝＝＝＝＝＝
int Result::Loop()
{
	//ゲームが終了したか外部に伝えるため
	int resurt = -1;

	switch (m_state)
	{
	case Result::INIT:
		Init();
		break;
	case Result::LOAD:
		Load();
		break;
	case Result::STARTWAIT://フェードなどを使う時
		m_state = MAIN;
		break;
	case Result::MAIN:
		Step();

		break;
	case Result::ENDWAIT://フェードなどを使うとき
		m_state = END;
		break;
	case Result::END:
		Exit();
		resurt = 1;
		break;

	}
	return resurt;
}





//がめの状態移管初期化
void Result::Init()
{
	m_hndl = -1;
	m_hndll = -1;
	//最初は初期化へ進む
	m_state = LOAD;

}
//ロード管理
void Result::Load()
{
	if (m_hndl == -1)
		m_hndl = LoadGraph("data/game/result/result.png");

	m_state = STARTWAIT;

}

//-----------------------
//リザルト画面の処理管理
//-----------------------
void Result::Step()
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
void Result::Draw()
{
	//タイトル画像描画

	DrawRotaGraph((int)(WINDOW_SIZE_X * 0.5f), (int)(WINDOW_SIZE_Y * 0.5f),
		1.0, 0.0, m_hndl, TRUE);


}



void Result::Exit()
{
	if (m_hndl != -1)
	{
		DeleteGraph(m_hndl);
		m_hndl = -1;
	}
	m_state = INIT;
}