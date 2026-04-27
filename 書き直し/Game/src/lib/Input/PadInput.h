#pragma once

#include "DxLib.h"

#include "math.h"

//コントローラーボタン

enum PAD_BUTTON

{

	BUTTON_A = 0,	//A

	BUTTON_B,		//B

	BUTTON_X,		//X

	BUTTON_Y,		//Y

	BUTTON_LB,		//LB

	BUTTON_RB,		//RB

	BUTTON_BACK,	//バックボタン

	BUTTON＿START,  //スタートボタン

	BUTTON_LSTICK,	//左スティック押し込み

	BUTTON_RSTICK,	//右スティック押し込み

	BUTTON_NUM,		//ボタンの総番号

};

//スティックの詳細

enum STICK

{

	STICK_LEFT,

	STICK_RIGHT,

	STICK_LX_POS,	//左スティックX軸(正)

	STICK_LX_NEG,	//左スティックX軸(負)

	STICK_LY_POS,	//左スティックY軸(正)

	STICK_LY_NEG,	//左スティックY軸(負)

	STICK_RX_POS,	//右スティックX軸(正)

	STICK_RX_NEG,	//右スティックX軸(負)

	STICK_RY_POS,	//右スティックY軸(正)

	STICK_RY_NEG,	//右スティックY軸(負)

};

//十字ボタンとLT、RTの判定用

enum CHECK

{

	UP,		//上

	UP_R,	//右上

	RIGHT,	//右

	DOWN_R,	//右下

	DOWN,	//下

	DOWN_L,	//左下

	LEFT,	//左

	UP_L,	//左上

};


class CGamePad

{

private:

public:

	//入力制御初期化

	static void InitGamePad();

	//入力制御ステップ

	static void StepGamePad();

	//接続台数取得

	static int GetPadNumState();

	//今押された

	static bool IsPadPush(int InputType, int Key_code);

	//ずっと押されている

	static bool IsPadKeep(int InputType, int Key_code);

	//キーを離した

	static bool IsPadRelease(int InputType, int Key_code);

	//単純に押されているか

	static bool IsPadDown(int InputType, int Key_code);

	//LTとRTの制御

	static bool IsPush_LR(CHECK check);

	//LTとRTの制御

	static bool IsKeep_LR(CHECK check);

	//十字キーの制御

	static bool IsPush_Cross(CHECK check);

	//十字キーの制御

	static bool IsKeep_Cross(CHECK check);

	//スティック操作

	static bool Stick(STICK stick);

	//スティック角度計算

	static float StickRot(STICK stick);

};

//Aボタンを押したら↓
//if(CGamePad::IsPadPush(DX_INPUT_PAD1, BUTTON_A))
//if(CGamePad::Stick(STICK_LY_POS) != 0)