#include "fade.h"
#include <DxLib.h>

//定義関連---------------------------
#define FADE_SPEED (5)   //フェード速度
#define FADE_SIZE_X (1600) //フェードサイズ(横)
#define FADE_SIZE_Y (900) //フェードサイズ(縦)
//-----------------------------------

	//フェードの各種状態
enum tagFadeState {
	FADE_NON,		//フェードなし
	FADE_IN,		//フェードイン中（徐々に画面が出現
	FADE_OUT,		//フェードアウト中(徐々に画面が消える
	FADE_OUT_WAIT	//フェードアウト後の真っ暗状態
};


//フェード処理構造体
typedef struct {
	tagFadeState m_state;	//現在のフェード状況
	int m_count;			//フェード時間のカウント
}FADE_DATA;

FADE_DATA g_fade;



//
//フェード初期化
//
void CFade::InitFade()
{
	g_fade.m_state = FADE_OUT;
	g_fade.m_count = 0;
}

//
//フェード処理更新
//
void CFade::StepFade()
{
	switch (g_fade.m_state)
	{
	case FADE_IN:
		//徐々に数字を減らして明るくする
		g_fade.m_count -= FADE_SPEED;
		if (g_fade.m_count <= 0)
		{
			g_fade.m_count = 0;
			g_fade.m_state = FADE_NON;
		}
		break;

	case FADE_OUT:
		//徐々に数字を増やして暗くする
		g_fade.m_count += FADE_SPEED;
		if (g_fade.m_count >= 255)
		{
			g_fade.m_count = 255;
			g_fade.m_state = FADE_OUT_WAIT;
		}
		break;
	}
}



//
//フェード用の画像描画
//
void CFade::DrawFade()
{
	//黒画像を描画
	switch (g_fade.m_state)
	{
	case FADE_IN:
	case FADE_OUT:
	case FADE_OUT_WAIT:
		//まずはここでアルファ値をセットする
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, g_fade.m_count);

		//フェード用の黒い四角を表示
		DrawBox(0, 0, FADE_SIZE_X, FADE_SIZE_Y,
			GetColor(0, 0, 0), TRUE);

		//ほかの画像に影響を出さないように、初期設定に戻す
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

		break;
	}
}


//=------------------------------
//フェードインリクエスト
//-------------------------------
void CFade::RequestFadeIn()
{
	//徐々に明るくするので、最初はMAXに
	g_fade.m_count = 255;
	g_fade.m_state = FADE_IN;
}

//-------------------------------
//フェードアウトリクエスト
//-------------------------------
void CFade::RequestFadeOut()
{
	//徐々に暗くするので、最初は透明の０に
	g_fade.m_count = 0;
	g_fade.m_state = FADE_OUT;
}

//
//フェードインが終了したか
//
bool CFade::IsEndFadeIn()
{
	//フェードイン時はまだやっている
	if (g_fade.m_state==FADE_IN)
	{
		return false;
	}
	//他はすべて少なくともフェードインではない
	else return true;
}



//
//フェードアウトが終了したか
//
bool CFade::IsEndFadeOut()
{
	//フェードアウト時はまだやっている
	if (g_fade.m_state == FADE_OUT)
	{
		return false;
	}
	//他はすべて少なくともフェードアウトではない
	else return true;
}


