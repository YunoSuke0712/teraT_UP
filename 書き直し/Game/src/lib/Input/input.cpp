#include "input.h"
#include <DxLib.h>

//キー入力情報に必要なデータをまとめた構造体
typedef struct {
	unsigned int m_NowKey; //現在のフレーム
	unsigned int m_PrevKey; //1フレーム前のボタン情報
}	INPUT_DATA;

//キー入力用にグローバル変数を作成
static INPUT_DATA g_inputData;

//-----------------------------
//キー入力情報の初期化
//-----------------------------
void CInput::InitInput()
{
	g_inputData.m_NowKey = g_inputData.m_PrevKey = 0;
}

//キー入力情報を更新
void CInput::UpdateInput()
{
	//最新情報は1フレーム前の情報になる
	g_inputData.m_PrevKey = g_inputData.m_NowKey;
	//今回の入力情報をいったん0にする
	g_inputData.m_NowKey = 0;

	//--
	//最新情報を取得していく
	//--

	//上を押した
	if (CheckHitKey(KEY_INPUT_W)||CheckHitKey(KEY_INPUT_UP)) {
		g_inputData.m_NowKey |= KEY_UP;
	}

	//下を押した
	if (CheckHitKey(KEY_INPUT_S) || CheckHitKey(KEY_INPUT_DOWN)) {
		g_inputData.m_NowKey |= KEY_DOWN;
	}

	//右を押した
	if (CheckHitKey(KEY_INPUT_D) || CheckHitKey(KEY_INPUT_RIGHT)) {
		g_inputData.m_NowKey |= KEY_RIGHT;
	}

	//左を押した
	if (CheckHitKey(KEY_INPUT_A) || CheckHitKey(KEY_INPUT_LEFT)) {
		g_inputData.m_NowKey |= KEY_LEFT;
	}

	//SPACEを押した
	if (CheckHitKey(KEY_INPUT_SPACE)) {
		g_inputData.m_NowKey |= KEY_JUMP;
	}

	//ダッシュを押した
	if (CheckHitKey(KEY_INPUT_LSHIFT)) {
		g_inputData.m_NowKey |= KEY_DASH;
	}

	//←マウスキーを押した
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
	{
		g_inputData.m_NowKey |= KEY_CLICK;
	}
	//→マウスキーを押した
	if ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0) {
		g_inputData.m_NowKey |= KEY_RCLICK;
	}
	//P
	if (CheckHitKey(KEY_INPUT_P)) {
		g_inputData.m_NowKey |= KEY_PAUSE;
	}

	//マウスホイールの回転量取得
	int wheel = GetMouseWheelRotVol();

	//ホイール上
	if (wheel > 0) {
		g_inputData.m_NowKey |= KEY_WHEEL_UP;
	}

	//ホイール下
	if (wheel < 0) {
		g_inputData.m_NowKey |= KEY_WHEEL_DOWN;
	}

}
//キーを押したか（通常判定）
bool CInput::IsInputRep(unsigned int key)
{
	if ((g_inputData.m_NowKey & key) != 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//キーを押したか（トリガー判定）
bool CInput::IsInputTrg(unsigned int key)
{
	if ((g_inputData.m_NowKey & key) &&
		!(g_inputData.m_PrevKey & key)) return true;
	
	else return false;
}


bool CInput::IsInputRel(unsigned int key)
{
	// 前のフレームで押していて、今は押していない
	if ((g_inputData.m_PrevKey & key) &&
		!(g_inputData.m_NowKey & key))
	{
		return true;
	}
	else {
		return false;
	}
}




