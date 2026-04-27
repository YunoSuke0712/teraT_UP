#pragma once
#include "DxLib.h"

//ゼロ
static const VECTOR ZERO = { 0.0f,0.0f,0.0f };
static const float  ZERO_F =  0.0f;
static const int    ZERO_I =  0 ;

//1
static const float F1 = 1.0f;
static const int   I1 = 1;

//ハンドル初期値
static const int HNDL_INIT = -1;
//--------------


static const float WINDOW_SIZE_X = 1600.0f;
static const float WINDOW_SIZE_Y = 900.0f;

static const VECTOR SPZ_POS = { -130.0f,105.0f,233.0f };

//重力------------------------
#define GRAVITY	(0.6)
#define ENEMY_UP (1.5)
//----------------------------



//敵--------------------------------------
//敵の通常速度　1倍
//敵のスローダウン：0.3倍
static float SlowSpeed = 0.3f;
//敵視界ゲージのクールダウン
static int SOUND_COOL_TIME = 180;
//----------------------------------------


//UI--------------------------------------
//P_スタミナ
static const int DASH_STAMINA = 300;
//E_視界ゲージ
static const int ENEMY_CAGE_MAX = 120;
//----------------------------------------


//スコア----------------------------------
static const VECTOR RESURT_SCORE_POS = {1350.0f,700.0f,0.0f};
static const VECTOR HIGH_SCORE_POS = { 1350.0f,750.0f,0.0f };

enum SCORE_RANK
{
	C,
	B,
	A,
	S,
	SS,
	SSS,

	SCORE_RANK_NUM,
};
//----------------------------------------


//アイテムタイプ--------------------------
enum ITEM_TYPE
{
	EMPTY,
	CAR,
	BOMB,
	KEY,
	SPIDER,
	DECOY,
	SPZ,
	SP1,
	SP2,
};
//----------------------------------------

enum EVENT_ID
{
	EVENT_NOT,
	EVENT_KEY,
	EVENT_BUTTON,

};

enum GIMMICK
{
	GIMMICK_KEY,
};




