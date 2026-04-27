#include "PadInput.h"

//パッドの入力変数
DINPUT_JOYSTATE PadcurrentBuf;	//パッドの現在フレーム情報格納変数
DINPUT_JOYSTATE PadpreBuf;		//パッドの過去フレーム情報格納変数

#define NUM		(4500)

//初期化
void CGamePad::InitGamePad()
{
	memset(&PadcurrentBuf, 0, sizeof(DINPUT_JOYSTATE));
	memset(&PadpreBuf, 0, sizeof(DINPUT_JOYSTATE));
}


//入力制御ステップ
void CGamePad::StepGamePad()
{
	//過去の入力情報を格納
	PadpreBuf = PadcurrentBuf;

	//現在のパッド入力情報を取得
	GetJoypadDirectInputState(DX_INPUT_PAD1, &PadcurrentBuf);
}

//接続台数取得
int CGamePad::GetPadNumState()
{
	return GetJoypadNum();
}


//今押された
bool CGamePad::IsPadPush(int InputType, int Key_code)
{
	//前フレーム押されていないかつ現在フレームで押されている
	if (PadpreBuf.Buttons[Key_code] == 0 && PadcurrentBuf.Buttons[Key_code] != 0)
		return true;

	//押されていないので false
	return false;
}

//ずっと押されている
bool CGamePad::IsPadKeep(int InputType, int Key_code)
{
	//前フレーム押されているかつ現在フレームで押されている
	if (PadpreBuf.Buttons[Key_code] != 0 && PadcurrentBuf.Buttons[Key_code] != 0)
		return true;

	//押されていないので false
	return false;
}

//キーを離した
bool CGamePad::IsPadRelease(int InputType, int Key_code)
{
	//前フレーム押されていないかつ現在フレームで押されていない
	if (PadpreBuf.Buttons[Key_code] != 0 && PadcurrentBuf.Buttons[Key_code] == 0)
		return true;

	//押されていないので false
	return false;
}

//単純に押されているか
bool CGamePad::IsPadDown(int InputType, int Key_code)
{
	//現在フレームで押されている(前フレームは関係ない)
	if (PadcurrentBuf.Buttons[Key_code] != 0)
		return true;

	//押されていないので false
	return false;
}


//LTとRTの制御
bool CGamePad::IsPush_LR(CHECK check)
{
	//過去フレームで押されていないか
	if (PadpreBuf.Z == 0)
	{
		switch (check)
		{
		case LEFT:
			//値が0より大きいとき
			if (PadcurrentBuf.Z != 0 && PadcurrentBuf.Z > 0)
			{
				return true;
			}
			break;

		case RIGHT:
			//値が0より小さいとき
			if (PadcurrentBuf.Z != 0 && PadcurrentBuf.Z < 0)
			{
				return true;
			}
			break;
		default:
			break;
		}
	}

	//押されていないので false
	return false;
}


//LTとRTの制御(長押し)
bool CGamePad::IsKeep_LR(CHECK check)
{
	//過去フレームで押されているか
	if (PadpreBuf.Z != 0)
	{
		switch (check)
		{
		case LEFT:
			//値が0より大きいとき
			if (PadcurrentBuf.Z != 0 && PadcurrentBuf.Z > 0)
			{
				return true;
			}
			break;

		case RIGHT:
			//値が0より小さいとき
			if (PadcurrentBuf.Z != 0 && PadcurrentBuf.Z < 0)
			{
				return true;
			}
			break;
		default:
			break;
		}
	}

	//押されていないので false
	return false;
}


//十字キーの制御
bool CGamePad::IsPush_Cross(CHECK check)
{
	int TOTAL = NUM * check;

	//過去フレームで押されていないか
	if (PadpreBuf.POV[0] == -1)
	{
		if (PadcurrentBuf.POV[0] == TOTAL)
		{
			return true;
		}
	}

	return false;
}

//十字キーの制御(長押し)
bool CGamePad::IsKeep_Cross(CHECK check)
{
	int TOTAL = NUM * check;

	//過去フレームで押されていないか
	if (PadpreBuf.POV[0] != -1)
	{
		if (PadcurrentBuf.POV[0] == TOTAL)
		{
			return true;
		}
	}

	return false;
}

//スティック
bool CGamePad::Stick(STICK stick)
{
	switch (stick)
	{
	case STICK_LX_POS:
		if (PadcurrentBuf.X > 0 && PadcurrentBuf.X <= 1000)
		{
			return true;
		}
		break;

	case STICK_LX_NEG:
		if (PadcurrentBuf.X < 0 && PadcurrentBuf.X >= -1000)
		{
			return true;
		}
		break;

	case STICK_LY_POS:
		if (PadcurrentBuf.Y > 0 && PadcurrentBuf.Y <= 1000)
		{
			return true;
		}
		break;

	case STICK_LY_NEG:
		if (PadcurrentBuf.Y < 0 && PadcurrentBuf.Y >= -1000)
		{
			return true;
		}
		break;

	case STICK_RX_POS:
		if (PadcurrentBuf.Rx > 0 && PadcurrentBuf.Rx <= 1000)
		{
			return true;
		}
		break;

	case STICK_RX_NEG:
		if (PadcurrentBuf.Rx < 0 && PadcurrentBuf.Rx >= -1000)
		{
			return true;
		}
		break;

	case STICK_RY_POS:
		if (PadcurrentBuf.Ry > 0 && PadcurrentBuf.Ry <= 1000)
		{
			return true;
		}
		break;


	case STICK_RY_NEG:
		if (PadcurrentBuf.Ry < 0 && PadcurrentBuf.Ry >= -1000)
		{
			return true;
		}
		break;

	default:
		break;
	}

	return false;
}

//スティック角度計算
float CGamePad::StickRot(STICK stick)
{
	if (stick == STICK_LEFT)
	{
		return (float)atan2(PadcurrentBuf.X, PadcurrentBuf.Y * -1);
	}
	else if (stick == STICK_RIGHT)
	{
		return (float)atan2(PadcurrentBuf.Rx, PadcurrentBuf.Ry * -1);
	}
}