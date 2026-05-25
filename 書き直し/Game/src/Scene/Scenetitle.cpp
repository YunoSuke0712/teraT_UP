#include "scenetitle.h"
#include <DxLib.h>
#include "../lib/input/PadInput.h"
#include "../lib/common/common.h"

#include "../lib/fade/fade.h"


static const float CARD_SPEED = 20.0f;
static const float CARD_SELECT_POS  = 100.0f;
static const float STICK_SELECT_POS = 100.0f;


//コンスト・デスト
CTitle::CTitle()
{
	m_state = INIT;
}

CTitle::~CTitle()
{
	Exit();
}

//＝＝＝＝＝＝＝＝＝＝
//毎フレーム呼ぶ処理
//＝＝＝＝＝＝＝＝＝＝
int CTitle::Loop()
{
	//ゲームが終了したか外部に伝えるため
	int resurt = -1;

	switch (m_state)
	{
	case CTitle::INIT:
		Init();
		break;
	case CTitle::LOAD:
		Load();
		break;
	case CTitle::STARTWAIT://フェードなどを使う時
		m_state = MAIN;
		break;
	case CTitle::MAIN:
		Step();
		
		break;
	case CTitle::ENDWAIT://フェードなどを使うとき
		if(m_fade.IsEndFadeOut())
		m_state = END;
		break;
	case CTitle::END:
		Exit();
		resurt = 1;
		break;

	}
	return resurt;
}




//がめの状態移管初期化
void CTitle::Init()
{
	for (int i = 0; i < TITLE_MAX_HNDL; i++)
	{
		m_hndl[i] = HNDL_INIT;
	}


	
	for (int i = 0; i < CARD_MAX; i++)
	{
		m_cardPosX[i] = 2400;
	}
	//管理
	m_UI_active = false;
	m_TitleSelect = ZERO_I;
	m_TitleCoolTime = ZERO_I;
	m_NowSelect = ZERO_I;



	//最初は初期化へ進む
	m_state = LOAD;
}


//ロード管理
void CTitle::Load()
{
	m_fade.RequestFadeIn();

	if (m_hndl[0] == -1)
		m_hndl[0] = LoadGraph("data/game/title/title.png");
	if (m_hndl[1] == -1)
		m_hndl[1] = LoadGraph("data/game/title/title_select.png");
	if (m_hndl[2] == -1)
		m_hndl[2] = LoadGraph("data/game/title/card0.png");
	if (m_hndl[3] == -1)
		m_hndl[3] = LoadGraph("data/game/title/card1.png");
	if (m_hndl[4] == -1)
		m_hndl[4] = LoadGraph("data/game/title/card2.png");
	if (m_hndl[5] == -1)
		m_hndl[5] = LoadGraph("data/game/title/");
	
	if (m_hndl[6] == -1)
		m_hndl[6] = LoadGraph("data/game/title/title_select0.png");
	if (m_hndl[7] == -1)
		m_hndl[7] = LoadGraph("data/game/title/title_select1.png");
	if (m_hndl[8] == -1)
		m_hndl[8] = LoadGraph("data/game/title/title_select2.png");

	if (m_hndl[9] == -1)
		m_hndl[9] = LoadGraph("data/game/title/UI1.png");
	if (m_hndl[10] == -1)
		m_hndl[10] = LoadGraph("data/game/title/UI2.png");
	if (m_hndl[11] == -1)
		m_hndl[11] = LoadGraph("data/game/title/UI3.png");

	if (m_hndl[12] == -1)
		m_hndl[12] = LoadGraph("data/game/title/card00.png");
	if (m_hndl[13] == -1)
		m_hndl[13] = LoadGraph("data/game/title/card11.png");
	if (m_hndl[14] == -1)
		m_hndl[14] = LoadGraph("data/game/title/card22.png");

	if (m_hndl[15] == -1)
		m_hndl[15] = LoadGraph("data/game/title/card000.png");
	if (m_hndl[16] == -1)
		m_hndl[16] = LoadGraph("data/game/title/card111.png");
	if (m_hndl[17] == -1)
		m_hndl[17] = LoadGraph("data/game/title/card222.png");

	m_state = STARTWAIT;

}


//-----------------------
//タイトル画面の処理管理
//-----------------------
void CTitle::Step()
{
	CData* data = CData::GetInstance();

	//セレクト上下移動
	if (m_TitleSelect != Fast)
	{
		//選択切り替え
		if ((m_input.IsInputTrg(KEY_UP)
			|| CGamePad::IsPush_Cross(UP))
			&& !m_UI_active)
		{
			m_NowSelect--;
		}
		if ((m_input.IsInputTrg(KEY_DOWN)
			|| CGamePad::IsPush_Cross(DOWN))
			&& !m_UI_active)
		{
			m_NowSelect++;
		}
	}

	switch (m_TitleSelect)
	{
	case Fast://一枚絵
		if (m_input.IsInputTrg(KEY_CLICK)
			|| CGamePad::IsPadPush(DX_INPUT_PAD1, BUTTON_B)
			|| CGamePad::IsPadPush(DX_INPUT_PAD1, BUTTON_A))
		{
			m_TitleSelect = Select;
		}
		break;
	case Select://タイトル選択画面
		//選択中のカード別処理
		switch (m_NowSelect)
		{
		case 0:
			if (m_input.IsInputTrg(KEY_CLICK) || CGamePad::IsPadPush(DX_INPUT_PAD1, BUTTON_B))
			{
				m_TitleSelect = Map;
			}
			break;
		case 1:
			if (m_input.IsInputTrg(KEY_CLICK) || CGamePad::IsPadPush(DX_INPUT_PAD1, BUTTON_B))
			{
				UISwitch();
			}
			break;
		case 2:
			if (m_input.IsInputTrg(KEY_CLICK) || CGamePad::IsPadPush(DX_INPUT_PAD1, BUTTON_B))
			{
				UISwitch();
			}
			break;
		}
		break;
	case Map:
		switch (m_NowSelect)
		{
		case 0:
			if (m_input.IsInputTrg(KEY_CLICK) || CGamePad::IsPadPush(DX_INPUT_PAD1, BUTTON_B))
			{
				m_fade.RequestFadeOut();
				m_state = ENDWAIT;
				data->SetPlayMapID(1);
				
			}
			break;
		case 1:
			if (m_input.IsInputTrg(KEY_CLICK) || CGamePad::IsPadPush(DX_INPUT_PAD1, BUTTON_B))
			{
				m_fade.RequestFadeOut();
				m_state = ENDWAIT;
				data->SetPlayMapID(2);

			}
			break;
		case 2:
			if (m_input.IsInputTrg(KEY_CLICK) || CGamePad::IsPadPush(DX_INPUT_PAD1, BUTTON_B))
			{
				m_fade.RequestFadeOut();
				m_state = ENDWAIT;
				data->SetPlayMapID(3);
			}
			break;
		}

		break;
	}



	if (m_TitleSelect != Fast)
	{
		//見た目用ーーーー
		//カード移動
		for (int i = 0; i < CARD_MAX; i++)
		{
			if (m_cardPosX[i] > (TITLE_SIZE_X * 0.5f))
				m_cardPosX[i] -= CARD_SPEED;
		}

		//---Updat		//選択幅制限

		//セレクトオーバー修正
		if (m_NowSelect <= -1)m_NowSelect = 2;
		if (m_NowSelect >= 3)m_NowSelect = 0;

	}
}
//---------------------------
//	タイトル画面の描画管理
//	-------------------------
void CTitle::Draw()
{
	//タイトル画像描画
	switch (m_TitleSelect)
	{
	case Fast:
		//一枚絵
		DrawRotaGraph((int)(TITLE_SIZE_X * 0.5f), (int)(TITLE_SIZE_Y * 0.5f),
			1.0, 0.0, m_hndl[0], TRUE);

	break;
	case Select:
		//選択画面
		//タイトル背景
		switch (m_NowSelect)
		{
			case 0:
				DrawRotaGraph((int)(TITLE_SIZE_X * 0.5f), (int)(TITLE_SIZE_Y * 0.5f),
					1.0, 0.0, m_hndl[6], TRUE);
			break;
			case 1:
				DrawRotaGraph((int)(TITLE_SIZE_X * 0.5f), (int)(TITLE_SIZE_Y * 0.5f),
					1.0, 0.0, m_hndl[7], TRUE);
			break;
			case 2:
				DrawRotaGraph((int)(TITLE_SIZE_X * 0.5f), (int)(TITLE_SIZE_Y * 0.5f),
					1.0, 0.0, m_hndl[8], TRUE);
			break;
		}

		//ハイスコア


		//カード
		if (m_NowSelect != 0)
			DrawRotaGraph(m_cardPosX[0], (int)(TITLE_SIZE_Y * 0.5f),
				1.0, 0.0, m_hndl[2], TRUE);
		if (m_NowSelect != 1)
			DrawRotaGraph(m_cardPosX[1], (int)(TITLE_SIZE_Y * 0.5f),
				1.0, 0.0, m_hndl[3], TRUE);
		if (m_NowSelect != 2)
			DrawRotaGraph(m_cardPosX[2], (int)(TITLE_SIZE_Y * 0.5f),
				1.0, 0.0, m_hndl[4], TRUE);
		
		//選択カード
		switch (m_NowSelect)
		{
		case 0:
			DrawRotaGraph(m_cardPosX[0] - CARD_SELECT_POS, (int)(TITLE_SIZE_Y * 0.5f),
				1.0, 0.0, m_hndl[12], TRUE);
			DrawRotaGraph(STICK_SELECT_POS, (int)(TITLE_SIZE_Y * 0.5f -270.0f),
				1.0, 0.0, m_hndl[5], TRUE);
			break;
		case 1:
			DrawRotaGraph(m_cardPosX[1] - CARD_SELECT_POS, (int)(TITLE_SIZE_Y * 0.5f),
				1.0, 0.0, m_hndl[13], TRUE);
			DrawRotaGraph(STICK_SELECT_POS, (int)(TITLE_SIZE_Y * 0.5f),
				1.0, 0.0, m_hndl[5], TRUE);
			break;
		case 2:
			DrawRotaGraph(m_cardPosX[2] - CARD_SELECT_POS, (int)(TITLE_SIZE_Y * 0.5f),
				1.0, 0.0, m_hndl[14], TRUE);
			DrawRotaGraph(STICK_SELECT_POS, (int)(TITLE_SIZE_Y * 0.5f + 270.0f),
				1.0, 0.0, m_hndl[5], TRUE);
			break;
		}

		//UIたち
		switch (m_NowSelect)
		{
		case 2:
			if (!m_UI_active)break;
			DrawRotaGraph((int)(TITLE_SIZE_X * 0.5f), (int)(TITLE_SIZE_Y * 0.5f),
				1.0, 0.0, m_hndl[9], TRUE);
			DrawRotaGraph((int)(TITLE_SIZE_X * 0.5f), (int)(TITLE_SIZE_Y * 0.5f),
				1.0, 0.0, m_hndl[11], TRUE);
			break;
		case 1:
			if (!m_UI_active)break;
			DrawRotaGraph((int)(TITLE_SIZE_X * 0.5f), (int)(TITLE_SIZE_Y * 0.5f),
				1.0, 0.0, m_hndl[9], TRUE);
			DrawRotaGraph((int)(TITLE_SIZE_X * 0.5f), (int)(TITLE_SIZE_Y * 0.5f),
				1.0, 0.0, m_hndl[10], TRUE);
			break;
		}
	break;
	case Map:
		//タイトル背景
		switch (m_NowSelect)
		{
		case 0:
			DrawRotaGraph((int)(TITLE_SIZE_X * 0.5f), (int)(TITLE_SIZE_Y * 0.5f),
				1.0, 0.0, m_hndl[6], TRUE);
			break;
		case 1:
			DrawRotaGraph((int)(TITLE_SIZE_X * 0.5f), (int)(TITLE_SIZE_Y * 0.5f),
				1.0, 0.0, m_hndl[7], TRUE);
			break;
		case 2:
			DrawRotaGraph((int)(TITLE_SIZE_X * 0.5f), (int)(TITLE_SIZE_Y * 0.5f),
				1.0, 0.0, m_hndl[8], TRUE);
			break;
		}

		//ハイスコア


		//カード
		if (m_NowSelect != 0)
			DrawRotaGraph(m_cardPosX[0], (int)(TITLE_SIZE_Y * 0.5f),
				1.0, 0.0, m_hndl[2], TRUE);
		if (m_NowSelect != 1)
			DrawRotaGraph(m_cardPosX[1], (int)(TITLE_SIZE_Y * 0.5f),
				1.0, 0.0, m_hndl[3], TRUE);
		if (m_NowSelect != 2)
			DrawRotaGraph(m_cardPosX[2], (int)(TITLE_SIZE_Y * 0.5f),
				1.0, 0.0, m_hndl[4], TRUE);

		//選択カード
		switch (m_NowSelect)
		{
		case 0:
			DrawRotaGraph(m_cardPosX[0] - CARD_SELECT_POS, (int)(TITLE_SIZE_Y * 0.5f),
				1.0, 0.0, m_hndl[15], TRUE);
			DrawRotaGraph(STICK_SELECT_POS, (int)(TITLE_SIZE_Y * 0.5f - 270.0f),
				1.0, 0.0, m_hndl[5], TRUE);
			break;
		case 1:
			DrawRotaGraph(m_cardPosX[1] - CARD_SELECT_POS, (int)(TITLE_SIZE_Y * 0.5f),
				1.0, 0.0, m_hndl[16], TRUE);
			DrawRotaGraph(STICK_SELECT_POS, (int)(TITLE_SIZE_Y * 0.5f),
				1.0, 0.0, m_hndl[5], TRUE);
			break;
		case 2:
			DrawRotaGraph(m_cardPosX[2] - CARD_SELECT_POS, (int)(TITLE_SIZE_Y * 0.5f),
				1.0, 0.0, m_hndl[17], TRUE);
			DrawRotaGraph(STICK_SELECT_POS, (int)(TITLE_SIZE_Y * 0.5f + 270.0f),
				1.0, 0.0, m_hndl[5], TRUE);
			break;
		}


	break;

	}

	DrawFormatString(250, 250, ColorBLUE, "%d",m_data.GetPlayMapID());

}

void CTitle::Exit()
{
	for (int i = 0; i < TITLE_MAX_HNDL; i++)
	{
		if (m_hndl[i] != -1)
		{
			DeleteGraph(m_hndl[i]);
			m_hndl[i] = -1;
		}
	}
	m_state = INIT;
}


void CTitle::UISwitch()
{
	switch (m_UI_active)
	{
	case true:
		m_UI_active = false;
		break;
	case false:
		m_UI_active = true;
		break;
	}

}

